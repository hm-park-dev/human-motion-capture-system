/**
******************************************************************************
* @file    appli_sensor.h
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Header file for Application interface for sensor Mesh Model
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
#ifndef __APPLI_SENSOR_H
#define __APPLI_SENSOR_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "sensors.h"

#pragma pack(1)
typedef struct displayFloatToInt_s 
{
  int8_t sign; /* 0 means positive, 1 means negative*/
  uint32_t  out_int;
  uint32_t  out_dec;
} displayFloatToInt_t;

/* Exported functions ------------------------------------------------------- */
void floatToInt(float in, displayFloatToInt_t *out_value, int32_t dec_prec);
void MX_MEMS_Init(void);
void Appli_Sensor_CadenceGet(sensor_CadenceCbParam_t* pDescriptorParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_CadenceSet(sensor_CadenceCbParam_t* pDescriptorParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_CadenceSetUnack(sensor_CadenceCbParam_t* pDescriptorParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_SettingsGet(sensor_SettingsCbParams_t* pDescriptorParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_SettingGet(sensor_SettingCbParams_t* pSettingParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_SettingSet(sensor_SettingCbParams_t* pSettingParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_SettingSetUnack(sensor_SettingCbParams_t* pSettingParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_DescriptorGet(MOBLEUINT8 pDescriptorParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_Get (MOBLEUINT8 pDescriptorParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_ColumnGet(sensor_ColumnCbParams_t* pDescriptorParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
void Appli_Sensor_SeriesGet(sensor_SeriesCbParams_t* pDescriptorParam,
                                         MOBLEUINT32 length,
                                         MOBLE_ADDRESS peerAddr,
                                         MOBLE_ADDRESS dstPeer,
                                         MOBLEUINT8 elementIndex);
MOBLE_RESULT Appli_Sensor_ReadDescriptor(MOBLEUINT8 sensorOffset,
                                         sensor_DescriptorCbParams_t* pDescriptorParams);
MOBLE_RESULT Appli_Sensor_ReadValue(MOBLEUINT8 sensorOffset,
                                    sensor_ValueCbParams_t* pValueParams);
MOBLE_RESULT Appli_Sensor_ReadColumn(MOBLEUINT8 sensorOffset,
                                   MOBLEUINT8 columnOffset,
                                     sensor_ColumnCbParams_t* pColumnParams);
MOBLE_RESULT Appli_Sensor_ReadSeries(MOBLEUINT8 sensorOffset,
                                     sensor_SeriesCbParams_t* pSeriesParams);
MOBLEUINT8 Appli_Sensor_IsFastCadence(MOBLEUINT8 sensorOffset,
                                      void* pFastCadenceLow, 
                                      void* pFastCadenceHigh);
MOBLEUINT8 Appli_Sensor_IsStatusTrigger(MOBLEUINT8 sensorOffset,
                                        status_trigger_type_e triggerType,
                                        void* pDeltaDown,
                                        void* pDeltaUp);
MOBLE_RESULT Appli_Sensor_Init(void);
void MX_MEMS_Init(void);
MOBLE_RESULT Appli_Sensor_Update(MOBLEUINT8 sensorOffset, MOBLEUINT32 value);
#endif /* __APPLI_SENSOR_H */

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/

