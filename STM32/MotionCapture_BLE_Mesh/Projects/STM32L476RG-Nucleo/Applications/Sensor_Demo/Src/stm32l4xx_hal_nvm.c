/**
******************************************************************************
* @file    stm32l4xx_hal_nvm.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Flash management for the Controller
******************************************************************************
* @attention
*
* Copyright (c) 2021 STMicroelectronics.
* All rights reserved.
*
* This software is licensed under terms that can be found in the LICENSE file
* in the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "pal_nvm.h"
#include "pal_if.h"  
#include "cube_hal.h"
#include <string.h>

extern const void* mobleNvmBase;
#define NVM_BASE ((unsigned int)mobleNvmBase)
#define NVM_SIZE 0x1000
#define FLASH_SECTOR_SIZE 0x800
#define ADDR_FLASH_PAGE_256   ((uint32_t)0x08080000) /* Base @ of Page 256, 2 Kbytes */
#define ADDR_FLASH_PAGE_258   ((uint32_t)0x08081000) /* Base @ of Page 258, 2 Kbytes */

/* Private functions ---------------------------------------------------------*/
/**
* @brief  returns NVM write protect status
* @param  None
* @retval TRUE if flash is write protected
*/
MOBLEBOOL BnrgmPalNvmIsWriteProtected(void)
{
    FLASH_OBProgramInitTypeDef ob;
    HAL_FLASHEx_OBGetConfig(&ob);

    switch (3)
    {
        case 0:
            return MOBLE_FALSE;
            /* return ob.WRPSector0To31 & sectorMask ? MOBLE_TRUE : MOBLE_FALSE; */
        case 1:
            return MOBLE_FALSE;
           /* return ob.WRPSector32To63 & sectorMask ? MOBLE_TRUE : MOBLE_FALSE; */
        case 2:
            return MOBLE_FALSE;
           /* return ob.WRPSector64To95 & sectorMask ? MOBLE_TRUE : MOBLE_FALSE; */
        case 3:
            return MOBLE_FALSE;
           /* return ob.WRPSector96To127 & sectorMask ? MOBLE_TRUE : MOBLE_FALSE; */
        default:
            /* TRACE_E(TF_PAL_MEMORY, "Invalid sector group"); */
            return MOBLE_TRUE;
    }
}

/**
* @brief  Read NVM
* @param  offset: offset wrt start address of nvm
* @param  buf: copy of read content
* @param  size: size of memory to be read
* @param  backup: If read from backup memory
* @retval Result of read operation
*/
MOBLE_RESULT BnrgmPalNvmRead(MOBLEUINT32 offset, void *buf, MOBLEUINT32 size, MOBLEBOOL backup)
{
    MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;

    if (offset > NVM_SIZE)
    {
        result = MOBLE_RESULT_INVALIDARG;
    }
    else if (size == 0)
    {
        result = MOBLE_RESULT_FALSE;
    }
    else if (offset + size > NVM_SIZE)
    {
        result = MOBLE_RESULT_INVALIDARG;
    }
    else
    {
        memmove(buf, (void *)(NVM_BASE + offset), size);
    }

    return result;
}

/**
* @brief  Compare with NVM
* @param  offset: offset wrt start address of nvm
* @param  buf: copy of content
* @param  size: size of memory to be compared
* @param  comparison: outcome of comparison
* @retval Result
*/
MOBLE_RESULT BnrgmPalNvmCompare(MOBLEUINT32 offset, void const *buf, MOBLEUINT32 size, MOBLE_NVM_COMPARE* comparison)
{
    MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;

    if ((comparison == NULL) || (buf == NULL))
    {
        result = MOBLE_RESULT_INVALIDARG;
    }
    else if (offset > NVM_SIZE)
    {
        result = MOBLE_RESULT_INVALIDARG;
    }
    else if (size == 0)
    {
        result = MOBLE_RESULT_FALSE;
    }
    else if (offset + size > NVM_SIZE)
    {
        result = MOBLE_RESULT_INVALIDARG;
    }
    else if (offset & 3)
    {
        result = MOBLE_RESULT_INVALIDARG;
    }
    else if (size & 3)
    {
        result = MOBLE_RESULT_INVALIDARG;
    }
    else 
    {
        *comparison = MOBLE_NVM_COMPARE_EQUAL;
        size >>= 2;
      
        MOBLEUINT32* src = (MOBLEUINT32*)buf;
        MOBLEUINT32* dst = (MOBLEUINT32*)(NVM_BASE + offset);

        for (MOBLEUINT32 i=0; i<size; ++i)
        {
            if ((src[i] != dst[i]) && (*comparison == MOBLE_NVM_COMPARE_EQUAL))
            {
                 *comparison = MOBLE_NVM_COMPARE_NOT_EQUAL_ERASE;
            }

        }
    }

    return result;
}

/**
* @brief  Erase NVM
* @param  None
* @retval Result
*/
MOBLE_RESULT BnrgmPalNvmErase()
{
    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_OPTVERR);

    FLASH_EraseInitTypeDef erase;
    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.Banks       = FLASH_BANK_2;
    erase.Page        = 2; 
    erase.NbPages     = 2;

    uint32_t pageError = 0;
    HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&erase, &pageError);

    HAL_FLASH_Lock();

    return status == HAL_OK ? MOBLE_RESULT_SUCCESS : MOBLE_RESULT_FAIL;
}

/**
* @brief  Queue write requests to NVM
* @param  offset: offset wrt start address of nvm
* @param  buf: copy of write content
* @param  size: size of memory to be written
* @retval Result
*/
MOBLE_RESULT BnrgmPalNvmWrite(MOBLEUINT32 offset, void const *buf, MOBLEUINT32 size)
{
    MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;

    /* TRACE_B(TF_PAL_MEMORY, ">>>"); */

    if (offset > NVM_SIZE)
    {
        /* TRACE_E(TF_PAL_MEMORY, "Invalid memory address"); */
        result = MOBLE_RESULT_INVALIDARG;
    }
    else if (size == 0)
    {
        result = MOBLE_RESULT_FALSE;
    }
    else if (offset + size > NVM_SIZE)
    {
        /* TRACE_E(TF_PAL_MEMORY, "Invalid memory size"); */
        result = MOBLE_RESULT_INVALIDARG;
    }
    else if (offset & 3)
    {
        /* TRACE_E(TF_PAL_MEMORY, "Invalid memory alignment"); */
        result = MOBLE_RESULT_INVALIDARG;
    }
    else if (size & 3)
    {
        /* TRACE_E(TF_PAL_MEMORY, "Invalid size alignment"); */
        result = MOBLE_RESULT_INVALIDARG;
    }
    else
    {

#ifdef TRACE_ENABLE_B
#if TRACE_CONFIG & TF_PAL_MEMORY
        printf("W>[%08X]", NVM_BASE + offset);
        for (MOBLEUINT32 i=0; i<size; ++i)
        {
            printf(" %02X", ((MOBLEUINT8*)buf)[i]);
        }
        printf("\n\r");
#endif
#endif

        size >>= 3;
        size +=1;
      
        uint64_t* src = (uint64_t*)buf;
        uint64_t* dst = (uint64_t*)(NVM_BASE + offset);

        HAL_StatusTypeDef status = HAL_OK;

        /* TRACE_B(TF_PAL_MEMORY, "Writing..."); */

        HAL_FLASH_Unlock();
       
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_OPTVERR);
       
        for (size_t i = 0; i < size && status == HAL_OK; ++i)
        {
            if (src[i] != dst[i])
            {
                status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, NVM_BASE + offset + (i << 3), (uint64_t)src[i]);
                if (status != HAL_OK)
                {
                    break;
                }
            }
        }
        HAL_FLASH_Lock();

        if (HAL_OK != status)
        {
            /* TRACE_E(TF_PAL_MEMORY, "Unable to write"); */
            result = MOBLE_RESULT_FAIL;
        }

    }

    return result;
}

/**
* @brief  NVM process
* @param  None
* @retval Result
*/
MOBLE_RESULT BnrgmPalNvmProcess(void)
{
    /* do nothing */
    return MOBLE_RESULT_SUCCESS;
}

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
