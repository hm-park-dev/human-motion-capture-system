/**
******************************************************************************
* @file    appli_nvm.h
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Header file for the user application file 
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APPLI_NVM_H
#define __APPLI_NVM_H

/* Includes ------------------------------------------------------------------*/

#include "mesh_cfg.h"

/* Exported macro ------------------------------------------------------------*/

extern const MOBLEUINT8* _prvsnr_data[];

/* offset defined for the embedded provisioner node */
#define PRVN_NVM_PAGE_SIZE          2048U
#define PRVN_NVM_BASE_OFFSET        (unsigned int)_prvsnr_data    
#define PRVN_NVM_CHUNK_SIZE         (sizeof(NvmPerNode_t)) /* Number of bytes saved per Element */
#define PRVN_NVM_SUBPAGE_SIZE       (sizeof(NvmPerNode_t)) /* Number of bytes saved per Element */
#define PRVN_NVM_MAX_SUBPAGE        (unsigned int)(PRVN_NVM_PAGE_SIZE/PRVN_NVM_CHUNK_SIZE)
#define PRVN_NVM_SUBPAGE_OFFSET(i)  (unsigned int)(PRVN_NVM_BASE_OFFSET+PRVN_NVM_SUBPAGE_SIZE*i)
#define N_BYTES_PAGE  2048
#define _MEMORY_FLASH_SIZE_  0xFFFFF
#define N_PAGES       (_MEMORY_FLASH_SIZE_/N_BYTES_PAGE)

typedef struct
{
  MOBLEUINT8 devKey[4+DEVICE_KEY_SIZE];

#if ENABLE_SAVE_UUID_PER_NODE  
  MOBLEUINT8 node_UUID[UUID_SIZE];
#endif
 
} NvmPerNode_t;
/* Exported variables  ------------------------------------------------------- */
/* Exported Functions Prototypes ---------------------------------------------*/
MOBLE_RESULT AppliNvm_FlashProgram(uint32_t Address, uint8_t Data[], uint16_t size); //uint8_t Data[]
MOBLE_RESULT AppliNvm_FactorySettingReset(void);
MOBLE_RESULT AppliNvm_FlashErase(uint16_t PageNumber);
MOBLE_RESULT AppliNvm_SaveModelState(uint8_t* state, uint16_t size);
MOBLE_RESULT AppliNvm_LoadModelState(uint8_t state[], uint8_t* size);
void AppliNvm_Process(void);
void AppliNvm_SaveMessageParam (void);
MOBLE_RESULT AppliNVM_Save_FlashTesting(MOBLEUINT8 *buffer,MOBLEUINT16 buffer_size);
MOBLE_RESULT AppliNVM_Retrieve_FlashTesting(MOBLEUINT8 *buffer,MOBLEUINT16 buffer_size);

#endif /* __APPLI_NVM_H */


/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

