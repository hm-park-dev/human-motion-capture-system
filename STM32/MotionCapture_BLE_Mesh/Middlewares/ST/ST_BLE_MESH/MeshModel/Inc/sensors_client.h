/**
******************************************************************************
* @file    sensors_client.h
* @author  BLE Mesh Team
* @version V1.14.000
* @date    19-11-2021
* @brief   Header file for the sensor client model 
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
#ifndef __SENSORS_CLIENT_H
#define __SENSORS_CLIENT_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"


/* Exported macro ------------------------------------------------------------*/
/* Variable-------------------------------------------------------------------*/
#pragma pack(1)
typedef union  
{
  sensor_CadenceCbParam_t sSensor_CadenceParam;
  MOBLEUINT8 a_Cadence_param[sizeof(sensor_CadenceCbParam_t)]; 
} _Sensor_CadenceParam;

typedef union  
{
  sensor_SettingCbParams_t sSensor_SettingParam;
  MOBLEUINT8 a_Setting_param[sizeof(sensor_SettingCbParams_t)]; 
} _Sensor_SettingParam;

/**
*  structure of sensor server function pointers callback
*/
typedef struct
{
  void (*Sensor_Descriptor_Status_cb)(const MOBLEUINT8 *pDescriptor,
                                      MOBLEUINT32 length,
                                      MOBLE_ADDRESS dstPeer,
                                      MOBLEUINT8 elementIndex);
  void (*Sensor_Cadence_Status_cb)(const MOBLEUINT8 *pCadence,
                                   MOBLEUINT32 length,
                                   MOBLE_ADDRESS dstPeer,
                                   MOBLEUINT8 elementIndex);
  void (*Sensor_Settings_Status_cb)(const MOBLEUINT8 *pSettings,
                                    MOBLEUINT32 length,
                                    MOBLE_ADDRESS dstPeer,
                                    MOBLEUINT8 elementIndex);
  void (*Sensor_Setting_Status_cb)(const MOBLEUINT8 *pSetting,
                                   MOBLEUINT32 length,
                                   MOBLE_ADDRESS dstPeer,
                                   MOBLEUINT8 elementIndex);
  void (*Sensor_Status_cb)(const MOBLEUINT8 *pStatus,
                           MOBLEUINT32 length,
                           MOBLE_ADDRESS dstPeer,
                           MOBLEUINT8 elementIndex);
  void (*Sensor_Column_Status_cb)(const MOBLEUINT8 *pColumn,
                                  MOBLEUINT32 length,
                                  MOBLE_ADDRESS dstPeer,
                                  MOBLEUINT8 elementIndex);
  void (*Sensor_Series_Status_cb)(const MOBLEUINT8 *pSeries,
                                  MOBLEUINT32 length,
                                  MOBLE_ADDRESS dstPeer,
                                  MOBLEUINT8 elementIndex);  
} sensor_client_cb_t;

//extern const sensor_client_cb_t SensorAppli_cb;

/******************************************************************************/
/********** Following Section defines the Opcodes for the Messages ************/
/******************************************************************************/


/* Exported Functions Prototypes ---------------------------------------------*/
MOBLE_RESULT SensorsModelClient_GetOpcodeTableCb(const MODEL_OpcodeTableParam_t **data, 
                                                 MOBLEUINT16 *length);

MOBLE_RESULT SensorsModelClient_GetStatusRequestCb(MODEL_MessageHeader_t *pmsgParam,
                                                   MOBLEUINT16 opcode, 
                                                   MOBLEUINT8 *pResponsedata, 
                                                   MOBLEUINT32 *plength, 
                                                   MOBLEUINT8 const *pRxData,
                                                   MOBLEUINT32 dataLength,
                                                   MOBLEBOOL response);

MOBLE_RESULT SensorsModelClient_ProcessMessageCb(MODEL_MessageHeader_t *pmsgParam,
                                                 MOBLEUINT16 opcode, 
                                                 MOBLEUINT8 const *pRxData, 
                                                 MOBLEUINT32 dataLength, 
                                                 MOBLEBOOL response);

MOBLE_RESULT SensorsClient_Descriptor_Get(MOBLEUINT8 elementIndex, 
                                          MOBLEUINT8 * ppropertyId);

MOBLE_RESULT SensorsClient_Cadence_Get(MOBLEUINT8 elementIndex, 
                                       MOBLEUINT8 * ppropertyId);

MOBLE_RESULT SensorsClient_Cadence_Set(MOBLEUINT8 elementIndex, 
                                       MOBLEUINT8 *pCadence_param, 
                                       MOBLEUINT32 length);

MOBLE_RESULT SensorsClient_Cadence_Set_Unack(MOBLEUINT8 elementIndex, 
                                             MOBLEUINT8 *pCadence_param, 
                                             MOBLEUINT32 length); 

MOBLE_RESULT SensorsClient_Settings_Get(MOBLEUINT8 elementIndex, 
                                        MOBLEUINT8 * ppropertyId);

MOBLE_RESULT SensorsClient_Setting_Get(MOBLEUINT8 elementIndex, 
                                       MOBLEUINT8 * pparam,
                                       MOBLEUINT8 length);

MOBLE_RESULT SensorsClient_Setting_Set(MOBLEUINT8 elementIndex, 
                                       MOBLEUINT8 *pSetting_param, 
                                       MOBLEUINT32 length); 

MOBLE_RESULT SensorsClient_Setting_Set_Unack(MOBLEUINT8 elementIndex, 
                                             MOBLEUINT8 *pSetting_param, 
                                             MOBLEUINT32 length); 

MOBLE_RESULT SensorsClient_Get(MOBLEUINT8 elementIndex, 
                               MOBLEUINT8 * ppropertyId);

MOBLE_RESULT SensorsColumn_Get(MOBLEUINT8 elementIndex, 
                               MOBLEUINT8 * pparam,
                               MOBLEUINT8 length);

MOBLE_RESULT SensorsSeries_Get(MOBLEUINT8 elementIndex, 
                               MOBLEUINT8 * pparam,
                               MOBLEUINT8 length);

#endif /* __SENSORS_CLIENT */

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/

