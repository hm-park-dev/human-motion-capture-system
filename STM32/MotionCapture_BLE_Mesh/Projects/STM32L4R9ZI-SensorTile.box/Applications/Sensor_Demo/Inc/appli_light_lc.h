/**
******************************************************************************
* @file    appli_light_ctrl.h
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Application interface for Light Control Mesh Models  
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
#ifndef __APPLI_LIGHT_LC_H
#define __APPLI_LIGHT_LC_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"

/* Exported macro ------------------------------------------------------------*/
/* Exported Functions Prototypes ---------------------------------------------*/
/*******************************************************************************
Following Variables are used for the Light LC Mode MODEL 
*******************************************************************************/
void Appli_LightLCs_ModeGet(MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_ModeSet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_ModeSetUnack(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_OmGet(MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_OmSet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_OmSetUnack(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_OnOffGet(MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_OnOffSet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_OnOffSetUnack(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_PropertyGet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_PropertySet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam);
void Appli_LightLCs_PropertySetUnack(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam);
MOBLE_RESULT Appli_Light_LCs_Init(void);
MOBLE_RESULT Appli_Light_LC_SensorPropertyUpdate(MOBLEUINT8 elementIndex,
                                                 MOBLEUINT16 propertyId,
                                                 MOBLEUINT32 value);
#endif /* __APPLI_LIGHT_LC_H */


/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/

