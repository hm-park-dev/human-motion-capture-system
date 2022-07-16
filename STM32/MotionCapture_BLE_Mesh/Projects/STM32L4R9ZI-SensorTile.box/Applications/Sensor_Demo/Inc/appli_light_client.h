/**
******************************************************************************
* @file    appli_light_client.h
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Application interface for light client Mesh Models  
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
#ifndef __APPLI_LIGHT_CLIENT_H
#define __APPLI_LIGHT_CLIENT_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "generic.h"
#include "mesh_cfg.h"


/* Exported macro ------------------------------------------------------------*/
/* Exported variables  ------------------------------------------------------- */
/* Application Variable-------------------------------------------------------*/
/* Exported Functions Prototypes ---------------------------------------------*/
MOBLE_RESULT Appli_LightClient_API(MOBLEUINT8 elementIndex, MOBLEUINT16 msg_opcode, MOBLEUINT8* msg_params);

void Appli_LightLCc_ModeStatus(MOBLEUINT8 const* pLightLCMode_status,
                               MOBLEUINT32 plength, 
                               MOBLEUINT16 dstPeer, 
                               MOBLEUINT8 elementIndex);
void Appli_LightLCc_OmStatus(MOBLEUINT8 const* pLightLCOccupancyMode_status,
                             MOBLEUINT32 plength, 
                             MOBLEUINT16 dstPeer, 
                             MOBLEUINT8 elementIndex);
void Appli_LightLCc_OnOffStatus(MOBLEUINT8 const* pLightLCOnOff_status,
                                MOBLEUINT32 plength, 
                                MOBLEUINT16 dstPeer, 
                                MOBLEUINT8 elementIndex);
void Appli_LightLCc_PropertyStatus(MOBLEUINT8 const* pLightLCProperty_status,
                                   MOBLEUINT32 plength, 
                                   MOBLEUINT16 dstPeer, 
                                   MOBLEUINT8 elementIndex);
#endif /* __APPLI_LIGHT_CLIENT_H */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

