/**
******************************************************************************
* @file    appli_sensor.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Application interface for Sensor Mesh Models 
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
#include "hal_common.h"
#include "types.h"
#include "sensor_cfg_usr.h"
#include "sensors.h"
#include "appli_sensor.h"
#include "light_lc.h"
#include "mesh_cfg.h"
#include "string.h"
#include "common.h"
#include "math.h"
#include "STBOX1_config.h"   
#define MAX_BUF_SIZE 256 

#ifdef STM32_SENSORTILEBOX
  #include "SensorTile.box_env_sensors.h"
#endif


/** @addtogroup BlueNRG_Mesh
*  @{
*/

/** @addtogroup models_BlueNRG-MS
*  @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Application variables of sensor model definition */


/**
  * @brief Sensor server model init parameters
  */
__attribute__((aligned(4)))
const sensor_server_init_params_t SensorServerInitParams = SENSOR_SERVER_INIT_PARAMS;

/**
  * @brief Sensor server model callbacks
  */
__attribute__((aligned(4)))
const sensor_server_cb_t AppliSensor_cb = 
{
  Appli_Sensor_CadenceGet,
  Appli_Sensor_CadenceSet,
  Appli_Sensor_CadenceSetUnack,
  Appli_Sensor_SettingsGet,
  Appli_Sensor_SettingGet,
  Appli_Sensor_SettingSet,
  Appli_Sensor_SettingSetUnack,
  Appli_Sensor_DescriptorGet,
  Appli_Sensor_Get,
  Appli_Sensor_ColumnGet,
  Appli_Sensor_SeriesGet,
  Appli_Sensor_ReadDescriptor,
  Appli_Sensor_ReadValue,
  Appli_Sensor_ReadColumn,
  Appli_Sensor_ReadSeries,
  Appli_Sensor_IsFastCadence,
  Appli_Sensor_IsStatusTrigger
};



/**
  * @brief Variables for people 
  */

MOBLEUINT8 AppliSensorReadFromSensor = 0; /* Used for PTS testing */
MOBLEUINT8 PresentTemperatureValue = 0;
MOBLEUINT8 PreviousTemperatureValue = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Callback corresponding to Sensor_CadenceGet_cb
  * @param  Cadence parameters
  * @retval None
  */
void Appli_Sensor_CadenceGet(sensor_CadenceCbParam_t* pCadenceParam,
                             MOBLEUINT32 length,
                             MOBLE_ADDRESS peerAddr,
                             MOBLE_ADDRESS dstPeer,
                             MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SENSOR, "Property ID %X  element index %X  peer addr %X dst peer %X\r\n",
                      pCadenceParam->property_ID, elementIndex, peerAddr, dstPeer);
}


/**
  * @brief  Callback corresponding to Sensor_CadenceSet_cb
  * @param  Cadence parameters
  * @retval None
  */
void Appli_Sensor_CadenceSet(sensor_CadenceCbParam_t* pCadenceParam,
                             MOBLEUINT32 length,
                             MOBLE_ADDRESS peerAddr,
                             MOBLE_ADDRESS dstPeer,
                             MOBLEUINT8 elementIndex)                                    
{  
  TRACE_M(TF_SENSOR, "Property ID %X element index %X peer addr %X dst peer %X\r\n",
                      pCadenceParam->property_ID, elementIndex, peerAddr, dstPeer); 
}


/**
  * @brief  Callback corresponding to Sensor_CadenceSetUnack_cb
  * @param  Cadence parameters
  * @retval None
  */
void Appli_Sensor_CadenceSetUnack(sensor_CadenceCbParam_t* pCadenceParam,
                                  MOBLEUINT32 length,
                                  MOBLE_ADDRESS peerAddr,
                                  MOBLE_ADDRESS dstPeer,
                                  MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SENSOR, "Property ID %X element index %X peer addr %X dst peer %X\r\n",
                      pCadenceParam->property_ID, elementIndex, peerAddr, dstPeer);
}


/**
  * @brief  Callback corresponding to Sensor_SettingsGet_cb
  * @param  Setting parameters
  * @retval None
  */
void Appli_Sensor_SettingsGet(sensor_SettingsCbParams_t* pSettingParam,
                              MOBLEUINT32 length,
                              MOBLE_ADDRESS peerAddr,
                              MOBLE_ADDRESS dstPeer,
                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SENSOR, "Property ID %X element index %X peer addr %X dst peer %X\r\n",
                      pSettingParam->propertyId, elementIndex, peerAddr, dstPeer); 
}

/**
  * @brief  Callback corresponding to Sensor_SettingGet_cb
  * @param  Setting parameters
  * @retval None
  */
void Appli_Sensor_SettingGet(sensor_SettingCbParams_t* pSettingParam,
                             MOBLEUINT32 length,
                             MOBLE_ADDRESS peerAddr,
                             MOBLE_ADDRESS dstPeer,
                             MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SENSOR, "Property ID %X element index %X peer addr %X dst peer %X\r\n",
                      pSettingParam->property_ID, elementIndex, peerAddr, dstPeer);
}


/**
  * @brief  Callback corresponding to Sensor_SettingSet_cb
  * @param  Setting parameters
  * @retval None
  */
void Appli_Sensor_SettingSet(sensor_SettingCbParams_t* pSettingParam,
                             MOBLEUINT32 length,
                             MOBLE_ADDRESS peerAddr,
                             MOBLE_ADDRESS dstPeer,
                             MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SENSOR, "Property ID %X element index %X peer addr %X dst peer %X\r\n",
                      pSettingParam->property_ID, elementIndex, peerAddr, dstPeer);
}


/**
  * @brief  Callback corresponding to Sensor_SettingSetUnack_cb
  * @param  Setting parameters
  * @retval None
  */
void Appli_Sensor_SettingSetUnack(sensor_SettingCbParams_t* pSettingParam,
                                  MOBLEUINT32 length,
                                  MOBLE_ADDRESS peerAddr,
                                  MOBLE_ADDRESS dstPeer,
                                  MOBLEUINT8 elementIndex)
{  
  TRACE_M(TF_SENSOR, "Property ID %X element index %X peer addr %X dst peer %X\r\n",
                      pSettingParam->property_ID, elementIndex, peerAddr, dstPeer);
}


/**
  * @brief  Callback corresponding to Sensor_DescriptorGet_cb
  * @param  Descriptor parameters
  * @retval None
  */
void Appli_Sensor_DescriptorGet(MOBLEUINT8 prop_ID,
                                MOBLEUINT32 length,
                                MOBLE_ADDRESS peerAddr,
                                MOBLE_ADDRESS dstPeer,
                                MOBLEUINT8 elementIndex)
{  
  if(length == 0)
  {
    TRACE_M(TF_SENSOR, "Sensor Descriptor data for all sensors on element index %X peer addr %X, dst peer %X\r\n",
                        elementIndex, peerAddr, dstPeer);
  }
  else
  {
    TRACE_M(TF_SENSOR, "Property ID %X element index %X peer addr %X, dst peer %X\r\n",
                        prop_ID, elementIndex, peerAddr, dstPeer);
  }
}


/**
  * @brief  Callback corresponding to Sensor_Get_cb
  * @param  Get parameters
  * @retval None
  */
void Appli_Sensor_Get(MOBLEUINT8 prop_ID,
                      MOBLEUINT32 length,
                      MOBLE_ADDRESS peerAddr,
                      MOBLE_ADDRESS dstPeer,
                      MOBLEUINT8 elementIndex)
{
  if(length == 0)
  {
    TRACE_M(TF_SENSOR, "Sensor Data for all sensors on element index %X peer addr %X dst peer %X\r\n",
                       elementIndex, peerAddr, dstPeer);
  }
  else
  {
    TRACE_M(TF_SENSOR, "Property ID %X element index %X peer addr %X dst peer %X \r\n",
                      prop_ID, elementIndex, peerAddr, dstPeer); 
  }
}


/**
  * @brief  Callback corresponding to Sensor_ColumnGet_cb
  * @param  Column parameters
  * @retval None
  */
void Appli_Sensor_ColumnGet(sensor_ColumnCbParams_t* pColumnParam,
                            MOBLEUINT32 length,
                            MOBLE_ADDRESS peerAddr,
                            MOBLE_ADDRESS dstPeer,
                            MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SENSOR, "Property ID %X  element index %X peer addr %X dst peer %X\r\n",
                      pColumnParam->propertyId, elementIndex, peerAddr, dstPeer);
}


/**
  * @brief  Callback corresponding to Sensor_SeriesGet_cb
  * @param  Series parameters
  * @retval None
  */
void Appli_Sensor_SeriesGet(sensor_SeriesCbParams_t* pSeriesParam,
                            MOBLEUINT32 length,
                            MOBLE_ADDRESS peerAddr,
                            MOBLE_ADDRESS dstPeer,
                            MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SENSOR, "Property ID %X  Raw Value X1 %d  Raw Value X2 %d\r\n",
                      pSeriesParam->propertyId,
                      pSeriesParam->rawValueX1,
                      pSeriesParam->rawValueX2);  
}


/**
  * @brief  Callback corresponding to Sensor_ReadDescriptor_cb
  *         Update SENSORX descriptor identified by sensorOffset
  *         Read from application to optimize RAM
  * @param  Sensor offset in sensor init structure
  * @param  descriptor parameters
  * @retval Fail if sensor doesn't exist or property ID mismatch occurrs
  *         else Success
  */
MOBLE_RESULT Appli_Sensor_ReadDescriptor(MOBLEUINT8 sensorOffset,
                                         sensor_DescriptorCbParams_t* pDescriptorParams)
{
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;
  const sensor_init_params_t* pSensorInitParams = NULL;
  
  if (sensorOffset < SensorServerInitParams.sensorsCount)
  {
    pSensorInitParams = &(SensorServerInitParams.sensorInitParams[sensorOffset]);
    
    if (pSensorInitParams->propertyId != pDescriptorParams->propertyId)
    {
      result = MOBLE_RESULT_FAIL;
    }
    else
    {
      /* */
    }
  }
  else
  {
    result = MOBLE_RESULT_FAIL;
  }
  
  if (pSensorInitParams != NULL &&
      pDescriptorParams != NULL)
  {
    pDescriptorParams->positiveTolerance = pSensorInitParams->positiveTolerance;
    pDescriptorParams->negativeTolerance = pSensorInitParams->negativeTolerance;
    pDescriptorParams->samplingFunction = pSensorInitParams->samplingFunction;
    pDescriptorParams->measurementPeriod = pSensorInitParams->measurementPeriod;
    pDescriptorParams->updateInterval = pSensorInitParams->updateInterval;
  }
  else
  {
    result = MOBLE_RESULT_FAIL;
  }

  return result;
}


/**
  * @brief  Callback corresponding to Sensor_ReadValue_cb
  *         Read sensor value and update buffer
  *         data length <= 128
  *         PreviousTemperatureValue, PresentTemperatureValue  to be updated 
  *         everytime sensor value is changed and call to Sensor_UpdateCadence
  * @param  Sensor offset in sensor init structure
  * @param  Value parameters
  * @retval Fail if sensor doesn't exist
  *         else Success
  */
MOBLE_RESULT Appli_Sensor_ReadValue(MOBLEUINT8 sensorOffset,
                                    sensor_ValueCbParams_t* pValueParams)
{
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;
  MOBLEUINT8 length = SensorServerInitParams.sensorInitParams[sensorOffset].dataLength;
  float temperature, pressure,humidity;
 
 
#ifdef STM32_SENSORTILEBOX
  BSP_ENV_SENSOR_GetValue(LPS22HH_0, ENV_PRESSURE, (float*) &pressure);
  BSP_ENV_SENSOR_GetValue(STTS751_0, ENV_TEMPERATURE, (float*) &temperature);
  BSP_ENV_SENSOR_GetValue(HTS221_0, ENV_HUMIDITY, (float*) &humidity);
#endif

  if (sensorOffset < SensorServerInitParams.sensorsCount)
  {
    if (sensorOffset == 0)
    {
      /* Get Temperature data */
      pValueParams->data[0] = ((MOBLEUINT8)temperature)*2;
    }
    else if (sensorOffset == 1)
    {
      /* Get pressure data */
      memcpy(pValueParams->data, &pressure, length);  
    }
    else if(sensorOffset == 2)
    {
      /* Get Humidit data */

      pValueParams->data[0] = (MOBLEUINT8)humidity;
      pValueParams->data[1] = (MOBLEUINT8)humidity>>8;
//      memcpy(pValueParams->data, &humidity, length);  
    }
    else
    {
      result = MOBLE_RESULT_FAIL;
    }
  }
  
  return result;
}

/**
  * @brief  Callback corresponding to Sensor_ReadColumn_cb
  *         Fill column width and raw valye Y in data buffer
  *         data length <= 8
  * @param  Sensor offset in sensor init structure
  * @param  Series column parameters
  * @retval Fail if sensor doesn't exist
  *         else Success
*/  
MOBLE_RESULT Appli_Sensor_ReadColumn(MOBLEUINT8 sensorOffset,
                                     MOBLEUINT8 columnOffset,
                                     sensor_ColumnCbParams_t* pColumnParams)
{
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;
  const sensor_init_params_t* pSensorInitParams = NULL;
  MOBLEUINT8 dataLength = 0;
  MOBLEUINT8* data = pColumnParams->data;
  
  if (sensorOffset < SensorServerInitParams.sensorsCount)
  {
    pSensorInitParams = &(SensorServerInitParams.sensorInitParams[sensorOffset]);
    
    /* fill sensor column data */
    memcpy(data+dataLength, 
           &(pSensorInitParams->seriesColumn[columnOffset].columnWidth), 
           pSensorInitParams->dataLength);
    dataLength = pSensorInitParams->dataLength;
    
    memset(data+dataLength, 0xAA, pSensorInitParams->dataLength);
    dataLength += pSensorInitParams->dataLength;
    
    pColumnParams->dataLength = dataLength;
  }
  else
  {
    result = MOBLE_RESULT_FAIL;
  }
  
  return result;
}


/**
  * @brief  Callback corresponding to Sensor_ReadSeries_cb
  *         Fill sensor series state for all columns between and including X1 and X2
  *         Series data to be concatenated in triplet of raw value X, column width and raw value Y
  *         X[n] CW[n] Y[n] X[n+1] CW[n+1] Y[n+1] ...
  *         data length should be less than minimum of 379 or max application packet length supported
  * @param  Sensor offset in sensor init structure
  * @param  Series parameters
  * @retval Fail if sensor doesn't exist
  *         else Success
  */
MOBLE_RESULT Appli_Sensor_ReadSeries(MOBLEUINT8 sensorOffset,
                                     sensor_SeriesCbParams_t* pSeriesParams)
{
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;
  const sensor_init_params_t* pSensorInitParams = NULL;
  MOBLEUINT16 dataLength = 0;
  MOBLEUINT8* data = pSeriesParams->data;
  
  if (sensorOffset < SensorServerInitParams.sensorsCount)
  {
    pSensorInitParams = &(SensorServerInitParams.sensorInitParams[sensorOffset]);
    
    for (MOBLEUINT8 count=0; count<pSensorInitParams->seriesCount; count++)
    {
      /* fill sensor series data */
      if (pSensorInitParams->seriesColumn[count].rawX >= pSeriesParams->rawValueX1 &&
          pSensorInitParams->seriesColumn[count].rawX <= pSeriesParams->rawValueX2)
      {
        memcpy(data+dataLength, 
               &(pSensorInitParams->seriesColumn[count].rawX), 
               pSensorInitParams->dataLength);
        dataLength += pSensorInitParams->dataLength;
        memcpy(data+dataLength, 
               &(pSensorInitParams->seriesColumn[count].columnWidth), 
               pSensorInitParams->dataLength);
        dataLength += pSensorInitParams->dataLength;
        memset(data+dataLength, 0xAA, pSensorInitParams->dataLength);
        dataLength += pSensorInitParams->dataLength;
        
        pSeriesParams->dataLength = dataLength;
      }
      else
      {
        /* */
      }
    }
  }
  else
  {
    result = MOBLE_RESULT_FAIL;
  }
  
  return result;
}
  

/**
  * @brief  Callback corresponding to Sensor_IsFastCadence_cb
  *         To check if fast cadence to be used for current sensor state
  * @param  Sensor offset in sensor init structure
  * @param  Fast Cadence Low
  * @param  Fast Cadence High
  * @retval Trigger status
  */
MOBLEUINT8 Appli_Sensor_IsFastCadence(MOBLEUINT8 sensorOffset,
                                      void* pFastCadenceLow, 
                                      void* pFastCadenceHigh)
{
  MOBLEUINT8 fastCadenceStatus = 0;
  MOBLEUINT32 fastCadenceLow = *((MOBLEUINT32*)pFastCadenceLow);
  MOBLEUINT32 fastCadenceHigh = *((MOBLEUINT32*)pFastCadenceHigh);
  MOBLEUINT32 sensorValue = PresentTemperatureValue;
  
  if (sensorOffset == 0)
  {
    if (fastCadenceLow <= fastCadenceHigh)
    {
      fastCadenceStatus = sensorValue >= fastCadenceLow &&
                          sensorValue <= fastCadenceHigh;
    }
    else
    {
      fastCadenceStatus = sensorValue > fastCadenceLow ||
                          sensorValue < fastCadenceHigh;
    }
  }
  else
  {
    /* Implmented only for sensor at offset 0 */
  }
  
  return fastCadenceStatus;
}


/**
  * @brief  Callback corresponding to Sensor_IsStatusTrigger_cb
  *         To check if sensor change in sensor state (delta) is more than
  *         given trigger state value 
  *         delta up values
  * @param  Sensor offset in sensor init structure
  * @param  Trigger type -> value or percent change
  * @param  Status trigger delta down
  * @param  Status trigger delta up
  * @retval Trigger status
  */
MOBLEUINT8 Appli_Sensor_IsStatusTrigger(MOBLEUINT8 sensorOffset,
                                        status_trigger_type_e triggerType,
                                        void* pDeltaDown,
                                        void* pDeltaUp)
{
  const sensor_init_params_t* pSensorInitParams = NULL;
  MOBLEUINT8 triggerStatus = 0;
  MOBLEUINT32 deltaDown = *((MOBLEUINT32*)pDeltaDown);
  MOBLEUINT32 deltaUp = *((MOBLEUINT32*)pDeltaUp);
  status_trigger_delta_e statusTriggerDelta;
  MOBLEUINT32 delta;
  
  if (sensorOffset == 0)
  {
    if (PresentTemperatureValue < PreviousTemperatureValue)
    {
      /* status trigger delta down */
      statusTriggerDelta = STATUS_TRIGGER_DELTA_DOWN;
      delta = PreviousTemperatureValue - PresentTemperatureValue;

      TRACE_M(TF_SENSOR, "Delta down value %d\r\n", delta);
    }
    else
    {
      /* status trigger delta up */
      statusTriggerDelta = STATUS_TRIGGER_DELTA_UP;
      delta = PresentTemperatureValue - PreviousTemperatureValue;

      TRACE_M(TF_SENSOR, "Delta up value %d\r\n", delta);
    }
    
    if (triggerType == STATUS_TRIGGER_TYPE_PC)
    {
      pSensorInitParams = &(SensorServerInitParams.sensorInitParams[sensorOffset]);
      
      if (pSensorInitParams->valuesRange != 0)
      {
        /* change delta to percentage change (of 0.01 % steps) */
        delta = (MOBLEUINT32)((delta*10000)/pSensorInitParams->valuesRange);
      }
      else
      {
        triggerStatus = 0;
      }
    }
    
    if ((statusTriggerDelta == STATUS_TRIGGER_DELTA_DOWN && delta >= deltaDown) ||
        (statusTriggerDelta == STATUS_TRIGGER_DELTA_UP && delta >= deltaUp))
    {
      triggerStatus = 1;
    }
    else
    {
      triggerStatus = 0;
    }
  }
    
  return triggerStatus;
}


/**
* @brief  Appli_Sensor_Init: This function is callback for Initialisation of 
Application interface
* @void  No input parameter 
* @retval MOBLE_RESULT
*/ 


__weak MOBLE_RESULT Appli_Sensor_Init(void)                                        
{
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;


  /* initialize sensor server model */
  result = SensorServer_Init(&BufferSensorServer, 
                             &AppliSensor_cb,
                             TOTAL_SENSOR_SERVER_BUFF_SIZE, 
                             &SensorServerInitParams);
  
  if(MOBLE_FAILED(result))
  {
    TRACE_M(TF_SENSOR, "Sensor Server init failed\r\n");
  }

  
  return MOBLE_RESULT_SUCCESS; 
}


/**
  * @brief  Handling of serial inputs to sensor model
  * @param  Sensor offset in sensor init structure
  * @param  Sensor value
  * @retval void
  */
MOBLE_RESULT Appli_Sensor_Update(MOBLEUINT8 sensorOffset, MOBLEUINT32 value)
{
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;
  
  AppliSensorReadFromSensor = 1;
  
  /* Update previous with current and current with new */
  PreviousTemperatureValue = PresentTemperatureValue;
  PresentTemperatureValue = (MOBLEUINT8)value;
  
  /* To update cadence parameters
     results in either status trigger or (and) fast cadence based on change and present
     Application may decide not to update cadence parameters if senosr value is changing
     very frequently in some cases to save bandwidth */
  if (PresentTemperatureValue != PreviousTemperatureValue)
  {
    result = Sensor_UpdateCadence(sensorOffset, 
                                  SensorServerInitParams.sensorInitParams[0].elementIdx, 
                                  SensorServerInitParams.sensorInitParams[0].propertyId);
  }
  
  return result;
}


/**
* @brief  floatToInt: This function is used to convert the float to integer 
* @param  in: sensor data value
* @param  out_value: pointer to the structure
* @param dec_prec: decimal point resolution
* @retval void
*/ 
void floatToInt(float in, displayFloatToInt_t *out_value, int32_t dec_prec)
{
  if(in >= 0.0f)
  {
    out_value->sign = 0;
  }else
  {
    out_value->sign = 1;
    in = -in;
  }
  out_value->out_int = (int32_t)in;
  in = in - (float)(out_value->out_int);
  out_value->out_dec = (int32_t)trunc(in * pow(10, dec_prec));
}



/**
* @}
*/

/**
* @}
*/

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/

