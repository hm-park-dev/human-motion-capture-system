/**
******************************************************************************
* @file    appli_mesh.c
* @author  BLE Mesh Team
* @version V1.08.000
* @date    10-July-2018
* @brief   Flash management for the Controller
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* Initial BlueNRG-Mesh is built over Motorola�s Mesh over Bluetooth Low Energy 
* (MoBLE) technology. The present solution is developed and maintained for both 
* Mesh library and Applications solely by STMicroelectronics.
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
#define NVM_SIZE 0x00001000
#define FLASH_SECTOR_SIZE 0x1000

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

    const int sector = (NVM_BASE - FLASH_BASE) / FLASH_SECTOR_SIZE;
    const int sectorGroup = sector >> 5;
    const int sectorMask = 1 << (sector & 0x1f);

    switch (sectorGroup)
    {
        case 0:
            return ob.WRPSector0To31 & sectorMask ? MOBLE_TRUE : MOBLE_FALSE;
        case 1:
            return ob.WRPSector32To63 & sectorMask ? MOBLE_TRUE : MOBLE_FALSE;
        case 2:
            return ob.WRPSector64To95 & sectorMask ? MOBLE_TRUE : MOBLE_FALSE;
        case 3:
            return ob.WRPSector96To127 & sectorMask ? MOBLE_TRUE : MOBLE_FALSE;
        default:
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
                *comparison = MOBLE_NVM_COMPARE_NOT_EQUAL;
            }
#ifdef STM32F0
            if ((src[i] | dst[i]) != dst[i])
#else
            if ((src[i] & dst[i]) != dst[i])
#endif
            {
                *comparison = MOBLE_NVM_COMPARE_NOT_EQUAL_ERASE;
                break;
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
    erase.PageAddress = NVM_BASE;
    erase.NbPages = NVM_SIZE >> 12;

    uint32_t pageError = 0;
    HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&erase, &pageError);

    HAL_FLASH_Lock();

    return status == HAL_OK ? MOBLE_RESULT_SUCCESS : MOBLE_RESULT_FAIL;
}

/**
* @brief  Write to NVM
* @param  offset: offset wrt start address of nvm
* @param  buf: copy of write content
* @param  size: size of memory to be written
* @retval Result
*/
MOBLE_RESULT BnrgmPalNvmWrite(MOBLEUINT32 offset, void const *buf, MOBLEUINT32 size)
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
        size >>= 2;
      
        MOBLEUINT32* src = (MOBLEUINT32*)buf;
        MOBLEUINT32* dst = (MOBLEUINT32*)(NVM_BASE + offset);

        HAL_StatusTypeDef status = HAL_OK;

        HAL_FLASH_Unlock();
        __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_OPTVERR);
        for (size_t i = 0; i < size && status == HAL_OK; ++i)
        {
            if (src[i] != dst[i])
            {
                status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, NVM_BASE + offset + (i << 2), src[i]);
                if (status != HAL_OK)
                {
                    break;
                }
            }
        }
        HAL_FLASH_Lock();

        if (HAL_OK != status)
        {
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
