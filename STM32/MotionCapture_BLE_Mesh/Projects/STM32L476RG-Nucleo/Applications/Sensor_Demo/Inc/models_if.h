/**
******************************************************************************
* @file    models_if.h
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Mesh Modes interface file header 
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
#ifndef __MODELS_H
#define __MODELS_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"


/* Exported macro ------------------------------------------------------------*/
/* Exported variables  ------------------------------------------------------- */

/* Exported Functions Prototypes ---------------------------------------------*/

void BluenrgMesh_ModelsInit(void);
void BluenrgMesh_ModelsProcess(void);
void BluenrgMesh_ModelsCommand(void);

MOBLEUINT8 BluenrgMesh_ModelsGetElementNumber(MOBLE_ADDRESS dst_peer);
MOBLEUINT8 BluenrgMesh_ModelsGetElementIndex(MOBLE_ADDRESS dst_peer);
void BluenrgMesh_ModelsDelayPacket(MODEL_MessageHeader_t *pmsgParams, MOBLEUINT8 command, 
                        MOBLEUINT8 const * data, MOBLEUINT32 length);
void BluenrgMesh_ModelsSendDelayedPacket(void);
MOBLEUINT8 BluenrgMesh_ModelsASCII_To_Char(MOBLEUINT8 tempValue);
MOBLE_RESULT MeshClient_SetRemotePublication(MOBLEUINT32 modelId, MOBLE_ADDRESS element_number,
                                              MOBLEUINT16 msg_opcode, MOBLEUINT8 const *msg_buff, 
                                              MOBLEUINT32 length, MOBLEBOOL ack_flag,
                                              MOBLEUINT8 isVendor);

#endif /* __MODELS_H */


/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/

