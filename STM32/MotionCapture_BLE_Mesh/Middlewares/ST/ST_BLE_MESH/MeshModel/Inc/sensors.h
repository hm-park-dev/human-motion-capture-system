/**
******************************************************************************
* @file    sensors.h
* @author  BLE Mesh Team
* @version V1.14.000
* @date    19-11-2021
* @brief   Header file for the sensors model file
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SENSORS_H
#define __SENSORS_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "bluenrg_mesh.h"

/* Exported types ------------------------------------------------------------*/

/**
* This structure contains sensor cadence callback parameters
*/ 
typedef struct 
{
  MOBLEUINT16 property_ID;
  MOBLEUINT8 fastCadenceDevisor;
  MOBLEUINT8 statusTriggerType; 
  MOBLEUINT32 triggerDeltaDown;
  MOBLEUINT32 triggerDeltaUp;
  MOBLEUINT8 statusMinInterval;
  MOBLEUINT32 fastCadenceLow;
  MOBLEUINT32 fastCadenceHigh;  
}sensor_CadenceCbParam_t;

/**
* This structure contains sensor settings callback parameters
*/ 
typedef struct
{
  MOBLEUINT16 propertyId;
  MOBLEUINT16 settingPropertyId;
}sensor_SettingsCbParams_t;

/**
* This structure contains sensor setting callback parameters
*/ 
typedef struct
{
  MOBLEUINT16 property_ID;
  MOBLEUINT16 settingPropertyId;
  MOBLEUINT32 settingRaw;
  MOBLEUINT8 settingAccess;
}sensor_SettingCbParams_t;

/**
* This structure contains sensor descriptor callback parameters
*/ 
typedef struct
{
  MOBLEUINT16 propertyId;
  MOBLEUINT16 positiveTolerance;                
  MOBLEUINT16 negativeTolerance;                
  MOBLEUINT8 samplingFunction;                  
  MOBLEUINT8 measurementPeriod;                 
  MOBLEUINT8 updateInterval; 
}sensor_DescriptorCbParams_t;

/**
* This structure contains sensor column callback parameters
*/ 
typedef struct
{
  MOBLEUINT16 propertyId;
  MOBLEUINT32 rawValueX;
  MOBLEUINT8 data[8];
  MOBLEUINT8 dataLength;
}sensor_ColumnCbParams_t;

/**
* This structure contains sensor series callback parameters
*/ 
typedef struct
{
  MOBLEUINT16 propertyId;
  MOBLEUINT32 rawValueX1;
  MOBLEUINT32 rawValueX2;
  MOBLEUINT8 data[379];
  MOBLEUINT16 dataLength;
}sensor_SeriesCbParams_t;

/**
* This structure contains sensor value callback parameters
*/ 
typedef struct
{
  MOBLEUINT16 propertyId;
  MOBLEUINT8 data[128];
}sensor_ValueCbParams_t;

/**
* Enum for status trigger type
*/ 
typedef enum
{
  STATUS_TRIGGER_TYPE_VALUE = 0,
  STATUS_TRIGGER_TYPE_PC
} status_trigger_type_e;

/**
* Enum for status trigger delta
*/ 
typedef enum
{
  STATUS_TRIGGER_DELTA_DOWN = 0,
  STATUS_TRIGGER_DELTA_UP
} status_trigger_delta_e;

/**
*  structure of sensor server function pointers callback
*/
typedef struct
{
  void (*Sensor_CadenceGet_cb)(sensor_CadenceCbParam_t* pCadenceParam,
                               MOBLEUINT32 length,
                               MOBLE_ADDRESS peerAddr,
                               MOBLE_ADDRESS dstPeer,
                               MOBLEUINT8 elementIndex);
  void (*Sensor_CadenceSet_cb)(sensor_CadenceCbParam_t* pCadenceParam,
                               MOBLEUINT32 length,
                               MOBLE_ADDRESS peerAddr,
                               MOBLE_ADDRESS dstPeer,
                               MOBLEUINT8 elementIndex);
  void (*Sensor_CadenceSetUnack_cb)(sensor_CadenceCbParam_t* pCadenceParam,
                                    MOBLEUINT32 length,
                                    MOBLE_ADDRESS peerAddr,
                                    MOBLE_ADDRESS dstPeer,
                                    MOBLEUINT8 elementIndex);
  void (*Sensor_SettingsGet_cb)(sensor_SettingsCbParams_t* pSettingsParam,
                                MOBLEUINT32 length,
                                MOBLE_ADDRESS peerAddr,
                                MOBLE_ADDRESS dstPeer,
                                MOBLEUINT8 elementIndex);
  void (*Sensor_SettingGet_cb)(sensor_SettingCbParams_t* pSettingParam,
                               MOBLEUINT32 length,
                               MOBLE_ADDRESS peerAddr,
                               MOBLE_ADDRESS dstPeer,
                               MOBLEUINT8 elementIndex);
  void (*Sensor_SettingSet_cb)(sensor_SettingCbParams_t* pSettingParam,
                               MOBLEUINT32 length,
                               MOBLE_ADDRESS peerAddr,
                               MOBLE_ADDRESS dstPeer,
                               MOBLEUINT8 elementIndex);
  void (*Sensor_SettingSetUnack_cb)(sensor_SettingCbParams_t* pSettingParam,
                                    MOBLEUINT32 length,
                                    MOBLE_ADDRESS peerAddr,
                                    MOBLE_ADDRESS dstPeer,
                                    MOBLEUINT8 elementIndex);
  void (*Sensor_DescriptorGet_cb)(MOBLEUINT8 propID,
                                  MOBLEUINT32 length,
                                  MOBLE_ADDRESS peerAddr,
                                  MOBLE_ADDRESS dstPeer,
                                  MOBLEUINT8 elementIndex);
  void (*Sensor_Get_cb)(MOBLEUINT8 propID,
                        MOBLEUINT32 length,
                        MOBLE_ADDRESS peerAddr,
                        MOBLE_ADDRESS dstPeer,
                        MOBLEUINT8 elementIndex);
  void (*Sensor_ColumnGet_cb)(sensor_ColumnCbParams_t* pColumnParam,
                              MOBLEUINT32 length,
                              MOBLE_ADDRESS peerAddr,
                              MOBLE_ADDRESS dstPeer,
                              MOBLEUINT8 elementIndex);
  void (*Sensor_SeriesGet_cb)(sensor_SeriesCbParams_t* pSeriesParam,
                              MOBLEUINT32 length,
                              MOBLE_ADDRESS peerAddr,
                              MOBLE_ADDRESS dstPeer,
                              MOBLEUINT8 elementIndex);
  MOBLE_RESULT (*Sensor_ReadDescriptor_cb)(MOBLEUINT8 sensorOffset,
                                           sensor_DescriptorCbParams_t* pDescriptorParams);
  MOBLE_RESULT (*Sensor_ReadValue_cb)(MOBLEUINT8 sensorOffset,
                                      sensor_ValueCbParams_t* pValueParams);
  MOBLE_RESULT (*Sensor_ReadColumn_cb)(MOBLEUINT8 sensorOffset,
                                       MOBLEUINT8 columnOffset,
                                       sensor_ColumnCbParams_t* pColumnParams);
  MOBLE_RESULT (*Sensor_ReadSeries_cb)(MOBLEUINT8 sensorOffset,
                                       sensor_SeriesCbParams_t* pSeriesParams);
  MOBLEUINT8 (*Sensor_IsFastCadence_cb)(MOBLEUINT8 sensorOffset,
                                        void* pFastCadenceLow, 
                                        void* pFastCadenceHigh);
  MOBLEUINT8 (*Sensor_IsStatusTrigger_cb)(MOBLEUINT8 sensorOffset,
                                          status_trigger_type_e triggerType,
                                          void* pDeltaDown,
                                          void* pDeltaUp);  
} sensor_server_cb_t;


/* Exported macro ------------------------------------------------------------*/
#define SENSOR_POSITIVE_TOLERANCE_UNSPECIFIED                         0x000
#define SENSOR_NEGATIVE_TOLERANCE_UNSPECIFIED                         0x000
#define SENSOR_SAMPLING_FUNC_UNSPECIFIED                               0x00
#define SENSOR_SAMPLING_FUNC_INSTANTANEOUS                             0x01
#define SENSOR_SAMPLING_FUNC_ARITHMETIC_MEAN                           0x02
#define SENSOR_SAMPLING_FUNC_RMS                                       0x03
#define SENSOR_SAMPLING_FUNC_MAX                                       0x04
#define SENSOR_SAMPLING_FUNC_MIN                                       0x05
#define SENSOR_SAMPLING_FUNC_ACCUMULATED                               0x06
#define SENSOR_SAMPLING_FUNC_COUNT                                     0x07
#define SENSOR_SAMPLING_FUNC_RFU(x)                              x>=0x08 ?\
                                                     MOBLE_TRUE:MOBLE_FALSE
#define SENSOR_MEASUREMENT_PERIOD_NA                                   0x00
#define SENSOR_UPDATE_INTERVAL_NA                                      0x00
#define SENSOR_SETTING_PROPERTY_ID_PROHIBITED                        0x0000
#define SENSOR_SETTING_ACCESS_READ                                     0x01
#define SENSOR_SETTING_ACCESS_READ_WRITE                               0x03
#define SENSOR_SETTING_ACCESS_PROHIBITED(x)     ((x == 0x02)||(x>=0x04)) ?\
                                                     MOBLE_TRUE:MOBLE_FALSE
#define SENSOR_STATUS_TRIG_FORMAT_PROP_ID                               0b0
#define SENSOR_STATUS_TRIG_FORMAT_UNITLESS                              0b1
#define SENSOR_FAST_CADENCE_PERIOD_DIV(n)                          pow(2,n)
#define SENSOR_FAST_CADENCE_PERIOD_DIV_PROHIBITED(x) \
                                             x>=16 ? MOBLE_TRUE:MOBLE_FALSE
#define SENSOR_STATUS_MIN_INTERVAL_PROHIBITED(x) \
                                             x>=27 ? MOBLE_TRUE:MOBLE_FALSE
#define SENSOR_CADENCE_NOT_SUPPORTED                                      0
#define SENSOR_CADENCE_SUPPORTED                                          1

/* Exported functions ------------------------------------------------------- */
MOBLE_RESULT SensorModelServer_GetOpcodeTableCb(const MODEL_OpcodeTableParam_t **data, 
                                                MOBLEUINT16 *length);
MOBLE_RESULT SensorModelServer_ProcessMessageCb(MODEL_MessageHeader_t *pmsgParams, 
                                                MOBLEUINT16 opcode, 
                                                MOBLEUINT8 const *data, 
                                                MOBLEUINT32 length, 
                                                MOBLEBOOL response);
MOBLE_RESULT SensorModelServer_GetStatusRequestCb(MODEL_MessageHeader_t *pmsgParams, 
                                                  MOBLEUINT16 opcode, 
                                                  MOBLEUINT8 *pResponsedata, 
                                                  MOBLEUINT32 *plength, 
                                                  MOBLEUINT8 const *pData,
                                                  MOBLEUINT32 length,
                                                  MOBLEBOOL response);
MOBLE_RESULT Sensor_Send(MOBLEUINT8 sensorOffset,
                         MOBLEUINT8 elementIdx,
                         MOBLEUINT16 propertyId);
MOBLE_RESULT Sensor_UpdateCadence(MOBLEUINT8 sensorOffset,
                                  MOBLEUINT8 elementIdx, 
                                  MOBLEUINT16 propertyId);
MOBLE_RESULT Sensor_UpdatePublishState(MOBLEUINT8 sensorOffset, MOBLEUINT8 state);
MOBLEUINT32 Sensor_SleepDurationMs_Get(void);
void Sensor_Process(void);
MOBLE_RESULT SensorServer_Init(void* sensorBuff,
                               const sensor_server_cb_t* sensor_cb,
                               MOBLEUINT16 sizeBuff, 
                             const void* sensorServerInitParams);
MOBLE_RESULT Sensor_ModelPublishSet(model_publicationparams_t* pPublishParams);
#endif /* __SENSORS_H */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

