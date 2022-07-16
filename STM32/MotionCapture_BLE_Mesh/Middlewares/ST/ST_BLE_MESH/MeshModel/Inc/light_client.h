/**
******************************************************************************
* @file    light_client.h
* @author  BLE Mesh Team
* @version V1.14.000
* @date    19-11-2021
* @brief   Header file for the light client model 
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
* Initial BlueNRG-Mesh is built over Motorola’s Mesh over Bluetooth Low Energy 
* (MoBLE) technology. The present solution is developed and maintained for both 
* Mesh library and Applications solely by STMicroelectronics.
*
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIGHT_CLIENT_H
#define __LIGHT_CLIENT_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "bluenrg_mesh.h"


/* Exported macro ------------------------------------------------------------*/

/* Variable ------------------------------------------------------------------*/

/******************************************************************************/
/********** Following Section defines the Opcodes for the Messages ************/
/******************************************************************************/
/* Light Client Structures */
/* Light Ctl Temperature parameters*/
#pragma pack(push, 1)
typedef struct
{
  MOBLEUINT16 CTL_Temperature;
  MOBLEINT16 CTL_DeltaUv;
  MOBLEUINT8  CTL_TID;
  MOBLEUINT8  CTL_TransitionTime;
  MOBLEUINT8  CTL_Delay;
}Light_CtlTemperatureParam_t;

typedef struct
{
  MOBLEUINT16 HslHueLightness16;
  MOBLEUINT8  Hsl_TID;
  MOBLEUINT8  Hsl_TransitionTime;
  MOBLEUINT8  Hsl_Delay;
}Light_HslHueParam_t;

typedef struct
{
  MOBLEUINT16 HslSaturation16;
  MOBLEUINT8  Hsl_TID;
  MOBLEUINT8  Hsl_TransitionTime;
  MOBLEUINT8  Hsl_Delay;
}Light_HslSaturationParam_t;
#pragma pack(pop)


/**
  * LC client callback structure
 */
typedef struct
{
  void (*LightLCc_ModeStatus_cb)(MOBLEUINT8 const*, 
                                 MOBLEUINT32,
                                 uint16_t, 
                                 uint8_t);
  void (*LightLCc_OmStatus_cb)(MOBLEUINT8 const*, 
                               MOBLEUINT32,
                               uint16_t, 
                               uint8_t);
  void (*LightLCc_OnOffStatus_cb)(MOBLEUINT8 const *, 
                                  MOBLEUINT32,
                                  uint16_t, 
                                  uint8_t);
  void (*LightLCc_PropertyStatus_cb)(MOBLEUINT8 const*, 
                                     MOBLEUINT32,
                                     uint16_t, 
                                     uint8_t);
} light_lc_client_cb_t;

extern const light_lc_client_cb_t AppliLightLcClient_cb;

/* Exported Functions Prototypes ---------------------------------------------*/
MOBLE_RESULT LightModelClient_GetOpcodeTableCb(const MODEL_OpcodeTableParam_t **data, 
                                                 MOBLEUINT16 *length);

MOBLE_RESULT LightModelClient_GetStatusRequestCb(MODEL_MessageHeader_t* pmsgParam, 
                                                   MOBLEUINT16 opcode, 
                                                   MOBLEUINT8 *pResponsedata, 
                                                   MOBLEUINT32 *plength, 
                                                   MOBLEUINT8 const *pRxData,
                                                   MOBLEUINT32 dataLength,
                                                   MOBLEBOOL response);

MOBLE_RESULT LightModelClient_ProcessMessageCb(MODEL_MessageHeader_t* pmsgParam, 
                                                 MOBLEUINT16 opcode, 
                                                 MOBLEUINT8 const *pRxData, 
                                                 MOBLEUINT32 dataLength, 
                                                 MOBLEBOOL response
                                                   );

MOBLE_RESULT LightClient_Lightness_Get(MOBLEUINT8 elementIndex); 
MOBLE_RESULT LightClient_Lightness_Set_Ack(MOBLEUINT8 elementIndex,  
                                           MOBLEUINT8 *pLightness_param, 
                                           MOBLEUINT32 length);
MOBLE_RESULT LightClient_Lightness_Set_Unack(MOBLEUINT8 elementIndex,  
                                             MOBLEUINT8 *pLightness_param, 
                                             MOBLEUINT32 length);

MOBLE_RESULT LightClient_Lightness_Linear_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Lightness_Linear_Set_Ack(MOBLEUINT8 elementIndex, 
                                                  MOBLEUINT8 *pLightnessLinear_param, 
                                                  MOBLEUINT32 length);
MOBLE_RESULT LightClient_Lightness_Linear_Set_Unack(MOBLEUINT8 elementIndex, 
                                                    MOBLEUINT8 *pLightnessLinear_param, 
                                                    MOBLEUINT32 length);

MOBLE_RESULT LightClient_Lightness_Default_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Lightness_Default_Set_Ack(MOBLEUINT8 elementIndex, 
                                                   MOBLEUINT8 *pLightnessDefault_param, 
                                                   MOBLEUINT32 length);
MOBLE_RESULT LightClient_Lightness_Default_Set_Unack(MOBLEUINT8 elementIndex, 
                                                     MOBLEUINT8 *pLightnessDefault_param, 
                                                     MOBLEUINT32 length);

MOBLE_RESULT LightClient_Lightness_Range_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Lightness_Range_Set_Ack(MOBLEUINT8 elementIndex, 
                                                 MOBLEUINT8 *pLightnessRange_param, 
                                                 MOBLEUINT32 length);
MOBLE_RESULT LightClient_Lightness_Range_Set_Unack(MOBLEUINT8 elementIndex, 
                                                   MOBLEUINT8 *pLightnessRange_param, 
                                                   MOBLEUINT32 length);

MOBLE_RESULT LightClient_Ctl_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Ctl_Set_Ack(MOBLEUINT8 elementIndex, 
                                     MOBLEUINT8 *pLightCtl_param, 
                                     MOBLEUINT32 length); 
MOBLE_RESULT LightClient_Ctl_Set_Unack(MOBLEUINT8 elementIndex, 
                                       MOBLEUINT8 *pLightCtl_param,
                                       MOBLEUINT32 length);

MOBLE_RESULT LightClient_Ctl_Temperature_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Ctl_Temperature_Set_Ack(MOBLEUINT8 elementIndex, 
                                                 MOBLEUINT8 *pLightCtlTemperature_param, 
                                                 MOBLEUINT32 length); 
MOBLE_RESULT LightClient_Ctl_Temperature_Set_Unack(MOBLEUINT8 elementIndex, 
                                                   MOBLEUINT8 *pLightCtlTemperature_param,
                                                   MOBLEUINT32 length); 

MOBLE_RESULT LightClient_Ctl_Temperature_Range_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Ctl_Temperature_Range_Set_Ack(MOBLEUINT8 elementIndex, 
                                                       MOBLEUINT8 *pLightCtlTemperatureRange_param, 
                                                       MOBLEUINT32 length); 
MOBLE_RESULT LightClient_Ctl_Temperature_Range_Set_Unack(MOBLEUINT8 elementIndex, 
                                                         MOBLEUINT8 *pLightCtlTemperatureRange_param,
                                                         MOBLEUINT32 length); 

MOBLE_RESULT LightClient_Ctl_Default_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Ctl_Default_Set_Ack(MOBLEUINT8 elementIndex, 
                                             MOBLEUINT8 *pLightCtlDefault_param, 
                                             MOBLEUINT32 length); 
MOBLE_RESULT LightClient_Ctl_Default_Set_Unack(MOBLEUINT8 elementIndex, 
                                               MOBLEUINT8 *pLightCtlDefault_param,
                                               MOBLEUINT32 length); 

MOBLE_RESULT LightClient_Hsl_Get(MOBLEUINT8 elementIndex) ;
MOBLE_RESULT LightClient_Hsl_Set_Ack(MOBLEUINT8 elementIndex, 
                                     MOBLEUINT8 *pLightHsl_param, 
                                     MOBLEUINT32 length); 

MOBLE_RESULT LightClient_Hsl_Set_Unack(MOBLEUINT8 elementIndex, 
                                     MOBLEUINT8 *pLightHsl_param,
                                     MOBLEUINT32 length); 

MOBLE_RESULT LightClient_Hsl_Default_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Hsl_Default_Set_Ack(MOBLEUINT8 elementIndex, 
                                             MOBLEUINT8 *pLightHslDefault_param, 
                                             MOBLEUINT32 length); 
MOBLE_RESULT LightClient_Hsl_Default_Set_Unack(MOBLEUINT8 elementIndex, 
                                               MOBLEUINT8 *pLightHslDefault_param,
                                               MOBLEUINT32 length); 
                                             
MOBLE_RESULT LightClient_Hsl_Range_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Hsl_Range_Set_Ack(MOBLEUINT8 elementIndex, 
                                           MOBLEUINT8 *pLightHslRange_param, 
                                           MOBLEUINT32 length); 
MOBLE_RESULT LightClient_Hsl_Range_Set_Unack(MOBLEUINT8 elementIndex, 
                                             MOBLEUINT8 *pLightHslRange_param,
                                             MOBLEUINT32 length); 
 
MOBLE_RESULT LightClient_Hsl_Hue_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Hsl_Hue_Set_Ack(MOBLEUINT8 elementIndex, 
                                         MOBLEUINT8 *pLightHslHue_param, 
                                         MOBLEUINT32 length); 
MOBLE_RESULT LightClient_Hsl_Hue_Set_Unack(MOBLEUINT8 elementIndex, 
                                           MOBLEUINT8 *pLightHslHue_param,
                                           MOBLEUINT32 length);

MOBLE_RESULT LightClient_Hsl_Saturation_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_Hsl_Saturation_Set_Ack(MOBLEUINT8 elementIndex, 
                                         MOBLEUINT8 *pLightHslSaturation_param, 
                                         MOBLEUINT32 length); 
MOBLE_RESULT LightClient_Hsl_Saturation_Set_Unack(MOBLEUINT8 elementIndex, 
                                           MOBLEUINT8 *pLightHslSaturation_param,
                                           MOBLEUINT32 length);

#ifdef ENABLE_LIGHT_MODEL_CLIENT_LC  
MOBLE_RESULT LightClient_LC_Mode_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_LC_Mode_Set_Ack(MOBLEUINT8 elementIndex, 
                                         MOBLEUINT8 *pLightLCMode_param, 
                                         MOBLEUINT32 length); 
MOBLE_RESULT LightClient_LC_Mode_Set_Unack(MOBLEUINT8 elementIndex, 
                                           MOBLEUINT8 *pLightLCMode_param,
                                           MOBLEUINT32 length);

MOBLE_RESULT LightClient_LC_OM_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_LC_OM_Set_Ack(MOBLEUINT8 elementIndex, 
                                       MOBLEUINT8 *pLightLCOccupancyMode_param, 
                                       MOBLEUINT32 length); 
MOBLE_RESULT LightClient_LC_OM_Set_Unack(MOBLEUINT8 elementIndex, 
                                         MOBLEUINT8 *pLightLCOccupancyMode_param,
                                         MOBLEUINT32 length);

MOBLE_RESULT LightClient_LC_OnOff_Get(MOBLEUINT8 elementIndex);
MOBLE_RESULT LightClient_LC_OnOff_Set_Ack(MOBLEUINT8 elementIndex, 
                                          MOBLEUINT8 *pLightLCOnOff_param, 
                                          MOBLEUINT32 length); 
MOBLE_RESULT LightClient_LC_OnOff_Set_Unack(MOBLEUINT8 elementIndex, 
                                            MOBLEUINT8 *pLightLCOnOff_param,
                                            MOBLEUINT32 length);

MOBLE_RESULT LightClient_LC_Property_Get(MOBLEUINT8 elementIndex,
                                         MOBLEUINT8 *pLightLCProperty_param, 
                                         MOBLEUINT32 length);
MOBLE_RESULT LightClient_LC_Property_Set_Ack(MOBLEUINT8 elementIndex, 
                                             MOBLEUINT8 *pLightLCProperty_param, 
                                             MOBLEUINT32 length); 
MOBLE_RESULT LightClient_LC_Property_Set_Unack(MOBLEUINT8 elementIndex, 
                                               MOBLEUINT8 *pLightLCProperty_param,
                                               MOBLEUINT32 length);
#endif /* #ifdef ENABLE_LIGHT_MODEL_CLIENT_LC */

MOBLE_RESULT Light_Client_Lightness_Status(MOBLEUINT8 const *pLightness_status, MOBLEUINT32 plength,
                                           MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex);

MOBLE_RESULT Light_Client_Lightness_Linear_Status(MOBLEUINT8 const *pLightnessLinear_status, MOBLEUINT32 pLength,
                                                  MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_Lightness_Last_Status(MOBLEUINT8 const *pLightnessLast_status, MOBLEUINT32 pLength,
                                                  MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_Lightness_Default_Status(MOBLEUINT8 const *pLightnessDefault_status, MOBLEUINT32 pLength,
                                                   MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_Lightness_Range_Status(MOBLEUINT8 const *pLightnessRange_status, MOBLEUINT32 pLength,
                                                 MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_Ctl_Status(MOBLEUINT8 const *pLightCtl_status, MOBLEUINT32 pLength,
                                                 MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_CtlTemperature_Range_Status(MOBLEUINT8 const *pCtlTempRange_status, MOBLEUINT32 pLength,
                                                      MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_CtlDefault_Status(MOBLEUINT8 const *pCtlDefault_status, MOBLEUINT32 pLength,
                                                  MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_CtlTemperature_Status(MOBLEUINT8 const *pLightCtlTemp_status, MOBLEUINT32 pLength,
                                                  MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_Hsl_Status(MOBLEUINT8 const *pHsl_status, MOBLEUINT32 pLength,MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_HslDefault_Status(MOBLEUINT8 const *pHslDefault_status, MOBLEUINT32 pLength,
                                                  MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_HslRange_Status(MOBLEUINT8 const *pHslRange_status, MOBLEUINT32 pLength,
                                                  MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_HslTarget_Status(MOBLEUINT8 const *pHslTarget_status, MOBLEUINT32 pLength,
                                                  MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_HslHue_Status(MOBLEUINT8 const *pHslHue_status, MOBLEUINT32 pLength,
                                                  MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_Client_HslSaturation_Status(MOBLEUINT8 const *pHslSaturation_status, MOBLEUINT32 pLength,
                                                  MOBLEUINT16 dstPeer,MOBLEUINT8 elementIndex);
#ifdef ENABLE_LIGHT_MODEL_CLIENT_LC  
MOBLE_RESULT LightLC_Client_Mode_Status(MOBLEUINT8 const *pLCMode_status, 
                                        MOBLEUINT32 plength, 
                                        MOBLEUINT16 dstPeer,
                                        MOBLEUINT8 elementIndex);
MOBLE_RESULT LightLC_Client_OM_Status(MOBLEUINT8 const *pLCOccupancyMode_status,
                                      MOBLEUINT32 plength, 
                                      MOBLEUINT16 dstPeer, 
                                      MOBLEUINT8 elementIndex);
MOBLE_RESULT LightLC_Client_OnOff_Status(MOBLEUINT8 const *pLCOnOff_status, 
                                         MOBLEUINT32 plength, 
                                         MOBLEUINT16 dstPeer, 
                                         MOBLEUINT8 elementIndex);
MOBLE_RESULT LightLC_Client_Property_Status(MOBLEUINT8 const *pLCProperty_status,
                                            MOBLEUINT32 plength, 
                                            MOBLEUINT16 dstPeer, 
                                            MOBLEUINT8 elementIndex);
#endif /* #ifdef ENABLE_LIGHT_MODEL_CLIENT_LC */

#endif /* __LIGHT_CLIENT_H */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

