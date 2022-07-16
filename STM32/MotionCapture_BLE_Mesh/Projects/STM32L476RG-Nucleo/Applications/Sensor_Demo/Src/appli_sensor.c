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
#include <stdio.h>
#include "stm32l4_nucleo_l476rg.h"      
#include "iks01a3_motion_sensors.h"
#include "iks01a3_env_sensors.h"
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
#define MAX_BUF_SIZE 256 


/** @addtogroup BlueNRG_Mesh
*  @{
*/

/** @addtogroup models_BlueNRG-MS
*  @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

void floatToInt(float in, displayFloatToInt_t *out_value, int32_t dec_prec);
static void Accelero_Sensor_Handler(uint32_t Instance,IKS01A3_MOTION_SENSOR_Axes_t *acceleration);
static void Gyro_Sensor_Handler(uint32_t Instance,IKS01A3_MOTION_SENSOR_Axes_t *angular_velocity);
static void Magneto_Sensor_Handler(uint32_t Instance,IKS01A3_MOTION_SENSOR_Axes_t *magnetic_field);
static void Temp_Sensor_Handler(uint32_t Instance,float *value);
static void Hum_Sensor_Handler(uint32_t Instance,float *value);
static void Press_Sensor_Handler(uint32_t Instance,float *value);
static void MX_IKS01A3_DataLogTerminal_Init(void);
static char dataOut[MAX_BUF_SIZE];
static uint8_t verbose = 1;  /* Verbose output to UART terminal ON/OFF. */
static IKS01A3_MOTION_SENSOR_Capabilities_t MotionCapabilities[IKS01A3_MOTION_INSTANCES_NBR];
static IKS01A3_ENV_SENSOR_Capabilities_t EnvCapabilities[IKS01A3_ENV_INSTANCES_NBR];
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

/*
#if USER_DEFINED_PLATFORM == USER_EVAL_PLATFORM
lsm6dso_pin_int1_route_t int1_route;
lsm6dso_all_sources_t all_source;
#endif */






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
 IKS01A3_MOTION_SENSOR_Axes_t acceleration;
 IKS01A3_MOTION_SENSOR_Axes_t angular_velocity;
 IKS01A3_MOTION_SENSOR_Axes_t magnetic_field;
 int i;
 
 for(i = 0; i < IKS01A3_ENV_INSTANCES_NBR; i++)
 {
   if(EnvCapabilities[i].Humidity)
   {
     Hum_Sensor_Handler(i,&humidity);
   }
   if(EnvCapabilities[i].Temperature)
   {
     Temp_Sensor_Handler(i,&temperature);
   }
   if(EnvCapabilities[i].Pressure)
   {
     Press_Sensor_Handler(i,&pressure);
   }
 }  
 
 for(i = 0; i < IKS01A3_MOTION_INSTANCES_NBR; i++)
 {
   if(MotionCapabilities[i].Acc)
   {
     Accelero_Sensor_Handler(i,&acceleration);
   }
   if(MotionCapabilities[i].Gyro)
   {
     Gyro_Sensor_Handler(i,&angular_velocity);
   }
   if(MotionCapabilities[i].Magneto)
   {
     Magneto_Sensor_Handler(i,&magnetic_field);
   }
 }


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
    else if(sensorOffset == 3)
    {
       uint8_t index=0;
      memcpy(pValueParams->data,(void*)&magnetic_field.x,4);   
      index = index + 4;
      memcpy((pValueParams->data)+index,(void*)&magnetic_field.y,4);  
      index = index + 4;
      memcpy((pValueParams->data)+index,(void*)&magnetic_field.z,4);     

    }
    else if(sensorOffset == 4)
    {
      uint8_t index=0;
      memcpy(pValueParams->data,(void*)&acceleration.x,4);  
      index = index + 4;      
      memcpy((pValueParams->data)+index,(void*)&acceleration.y,4);  
      index = index + 4;
      memcpy((pValueParams->data)+index,(void*)&acceleration.z,4);  
      
    }
    else if(sensorOffset == 5)
    {
       uint8_t index=0;
      memcpy(pValueParams->data,(void*)&angular_velocity.x,4);  
      index = index + 4;      
      memcpy((pValueParams->data)+index,(void*)&angular_velocity.y,4);  
      index = index + 4;
      memcpy((pValueParams->data)+index,(void*)&angular_velocity.z,4);  
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

#if USER_DEFINED_PLATFORM == USER_EVAL_PLATFORM
  /* Configure I2C @ 400 kHz */
  SdkEvalI2CInit(400000);
  
  /** Init Structure */
  GPIO_StructInit(&GPIO_InitStructure);
  /** Configure GPIO_Pin_7 for Proximity Sensor XSHUT */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Output;
  GPIO_InitStructure.GPIO_Pull = DISABLE;
  GPIO_InitStructure.GPIO_HighPwr = ENABLE;
  GPIO_Init(&GPIO_InitStructure);
  
  /* Turn OFF Proximity Sensor */
  GPIO_WriteBit(GPIO_Pin_7, Bit_RESET);

  /* Configure Sensor Common INT pin */
  GPIO_InitStructure.GPIO_Mode = GPIO_Input;
  GPIO_InitStructure.GPIO_HighPwr = DISABLE;
  GPIO_InitStructure.GPIO_Pin = SDK_EVAL_IRQ_SENSOR_PIN;
  GPIO_InitStructure.GPIO_Pull = DISABLE;
  GPIO_Init(&GPIO_InitStructure);
  
  
#ifdef LPS22HH_ENABLED
Init_Pressure_Temperature_Sensor();
#endif

#ifdef HTS221_ENABLED
  Init_Humidity_Sensor();
#endif
  
#ifdef LSM6DSO_ENABLED
Init_Accelerometer_Gyroscope();
/* Enable interrupt on SENSOR INT pin */
GPIO_EXTICmd(SDK_EVAL_IRQ_SENSOR_PIN, ENABLE);
#endif

#ifdef LIS2MDL_ENABLED
Init_Magnetometer();
#endif

#ifdef VL53L1_ENABLED
  Init_Proximity_Sensor();
  /* Enable interrupt on SENSOR INT pin */
  GPIO_EXTICmd(SDK_EVAL_IRQ_SENSOR_PIN, ENABLE);
  lis2mdl_operating_mode_set(0, LIS2MDL_POWER_DOWN);
#endif
  /*Low Power Mode for all sensors*/
  //SensorsLowPower();
#endif    

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
  * @brief  Handles the accelerometer axes data getting/sending
  * @param  Instance the device instance
  * @retval None
  */
static void Accelero_Sensor_Handler(uint32_t Instance,IKS01A3_MOTION_SENSOR_Axes_t *acceleration)
{
  float odr;
  int32_t fullScale;
  displayFloatToInt_t out_value;
  uint8_t whoami;

  if (IKS01A3_MOTION_SENSOR_GetAxes(Instance, MOTION_ACCELERO, acceleration))
  {
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nACC[%d]: Error\r\n", (int)Instance);
  }
  else
  {
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nACC_X[%d]: %d, ACC_Y[%d]: %d, ACC_Z[%d]: %d\r\n", (int)Instance,
             (int)acceleration->x, (int)Instance, (int)acceleration->y, (int)Instance, (int)acceleration->z);
  }

  printf("%s", dataOut);

  if (verbose == 1)
  {
    if (IKS01A3_MOTION_SENSOR_ReadID(Instance, &whoami))
    {
      snprintf(dataOut, MAX_BUF_SIZE, "WHOAMI[%d]: Error\r\n", (int)Instance);
    }
    else
    {
      snprintf(dataOut, MAX_BUF_SIZE, "WHOAMI[%d]: 0x%x\r\n", (int)Instance, (int)whoami);
    }

 //   printf("%s", dataOut);

    if (IKS01A3_MOTION_SENSOR_GetOutputDataRate(Instance, MOTION_ACCELERO, &odr))
    {
      snprintf(dataOut, MAX_BUF_SIZE, "ODR[%d]: ERROR\r\n", (int)Instance);
    }
    else
    {
      floatToInt(odr, &out_value, 3);
      snprintf(dataOut, MAX_BUF_SIZE, "ODR[%d]: %d.%03d Hz\r\n", (int)Instance, (int)out_value.out_int,
               (int)out_value.out_dec);
    }

//    printf("%s", dataOut);

    if (IKS01A3_MOTION_SENSOR_GetFullScale(Instance, MOTION_ACCELERO, &fullScale))
    {
      snprintf(dataOut, MAX_BUF_SIZE, "FS[%d]: ERROR\r\n", (int)Instance);
    }
    else
    {
      snprintf(dataOut, MAX_BUF_SIZE, "FS[%d]: %d g\r\n", (int)Instance, (int)fullScale);
    }

 //  printf("%s", dataOut);
  }
}

/**
  * @brief  Handles the gyroscope axes data getting/sending
  * @param  Instance the device instance
  * @retval None
  */
static void Gyro_Sensor_Handler(uint32_t Instance,IKS01A3_MOTION_SENSOR_Axes_t *angular_velocity)
{
  float odr;
  int32_t fullScale;
  displayFloatToInt_t out_value;
  uint8_t whoami;

  if (IKS01A3_MOTION_SENSOR_GetAxes(Instance, MOTION_GYRO, angular_velocity))
  {
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nGYR[%d]: Error\r\n", (int)Instance);
  }
  else
  {
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nGYR_X[%d]: %d, GYR_Y[%d]: %d, GYR_Z[%d]: %d\r\n", (int)Instance,
             (int)angular_velocity->x, (int)Instance, (int)angular_velocity->y, (int)Instance, (int)angular_velocity->z);
  }

  printf("%s", dataOut);

  if (verbose == 1)
  {
    if (IKS01A3_MOTION_SENSOR_ReadID(Instance, &whoami))
    {
      snprintf(dataOut, MAX_BUF_SIZE, "WHOAMI[%d]: Error\r\n", (int)Instance);
    }
    else
    {
      snprintf(dataOut, MAX_BUF_SIZE, "WHOAMI[%d]: 0x%x\r\n", (int)Instance, (int)whoami);
    }

  //  printf("%s", dataOut);

    if (IKS01A3_MOTION_SENSOR_GetOutputDataRate(Instance, MOTION_GYRO, &odr))
    {
      snprintf(dataOut, MAX_BUF_SIZE, "ODR[%d]: ERROR\r\n", (int)Instance);
    }
    else
    {
      floatToInt(odr, &out_value, 3);
      snprintf(dataOut, MAX_BUF_SIZE, "ODR[%d]: %d.%03d Hz\r\n", (int)Instance, (int)out_value.out_int,
               (int)out_value.out_dec);
    }

 //   printf("%s", dataOut);

    if (IKS01A3_MOTION_SENSOR_GetFullScale(Instance, MOTION_GYRO, &fullScale))
    {
      snprintf(dataOut, MAX_BUF_SIZE, "FS[%d]: ERROR\r\n", (int)Instance);
    }
    else
    {
      snprintf(dataOut, MAX_BUF_SIZE, "FS[%d]: %d dps\r\n", (int)Instance, (int)fullScale);
    }

 //   printf("%s", dataOut);
  }
}

/**
  * @brief  Handles the magneto axes data getting/sending
  * @param  Instance the device instance
  * @retval None
  */
static void Magneto_Sensor_Handler(uint32_t Instance,IKS01A3_MOTION_SENSOR_Axes_t *magnetic_field)
{
  float odr;
  int32_t fullScale;
  displayFloatToInt_t out_value;
  uint8_t whoami;
  
  if (IKS01A3_MOTION_SENSOR_GetAxes(Instance, MOTION_MAGNETO, magnetic_field))
  {
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nMAG[%d]: Error\r\n", (int)Instance);
  }
  else
  {
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nMAG_X[%d]: %d, MAG_Y[%d]: %d, MAG_Z[%d]: %d\r\n", (int)Instance,
             (int)magnetic_field->x, (int)Instance, (int)magnetic_field->y, (int)Instance, (int)magnetic_field->z);
  }

//  printf("%s", dataOut);

  if (verbose == 1)
  {
    if (IKS01A3_MOTION_SENSOR_ReadID(Instance, &whoami))
    {
      snprintf(dataOut, MAX_BUF_SIZE, "WHOAMI[%d]: Error\r\n", (int)Instance);
    }
    else
    {
      snprintf(dataOut, MAX_BUF_SIZE, "WHOAMI[%d]: 0x%x\r\n", (int)Instance, (int)whoami);
    }

//    printf("%s", dataOut);

    if (IKS01A3_MOTION_SENSOR_GetOutputDataRate(Instance, MOTION_MAGNETO, &odr))
    {
      snprintf(dataOut, MAX_BUF_SIZE, "ODR[%d]: ERROR\r\n", (int)Instance);
    }
    else
    {
      floatToInt(odr, &out_value, 3);
      snprintf(dataOut, MAX_BUF_SIZE, "ODR[%d]: %d.%03d Hz\r\n", (int)Instance, (int)out_value.out_int,
               (int)out_value.out_dec);
    }

 //   printf("%s", dataOut);

    if (IKS01A3_MOTION_SENSOR_GetFullScale(Instance, MOTION_MAGNETO, &fullScale))
    {
      snprintf(dataOut, MAX_BUF_SIZE, "FS[%d]: ERROR\r\n", (int)Instance);
    }
    else
    {
      snprintf(dataOut, MAX_BUF_SIZE, "FS[%d]: %d gauss\r\n", (int)Instance, (int)fullScale);
    }

 //   printf("%s", dataOut);
  }
}

/**
  * @brief  Handles the temperature data getting/sending
  * @param  Instance the device instance
  * @retval None
  */
static void Temp_Sensor_Handler(uint32_t Instance,float *temperature)
{
  displayFloatToInt_t out_value;

  if (IKS01A3_ENV_SENSOR_GetValue(Instance, ENV_TEMPERATURE, temperature))
  {
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nTemp[%d]: Error\r\n", (int)Instance);
  }
  else
  {
    floatToInt(*temperature, &out_value, 2);
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nTemp[%d]: %d.%02d degC\r\n", (int)Instance, (int)out_value.out_int,
             (int)out_value.out_dec);
  }



}

/**
  * @brief  Handles the pressure sensor data getting/sending
  * @param  Instance the device instance
  * @retval None
  */
static void Press_Sensor_Handler(uint32_t Instance, float *pressure)
{
  displayFloatToInt_t out_value;

  if (IKS01A3_ENV_SENSOR_GetValue(Instance, ENV_PRESSURE, pressure))
  {
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nPress[%d]: Error\r\n", (int)Instance);
  }
  else
  {
    floatToInt(*pressure, &out_value, 2);
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nPress[%d]: %d.%02d hPa\r\n", (int)Instance, (int)out_value.out_int,
             (int)out_value.out_dec);
  }

 // printf("%s", dataOut);

}

/**
  * @brief  Handles the humidity data getting/sending
  * @param  Instance the device instance
  * @retval None
  */
static void Hum_Sensor_Handler(uint32_t Instance,float *humidity)
{
  displayFloatToInt_t out_value;

  if (IKS01A3_ENV_SENSOR_GetValue(Instance, ENV_HUMIDITY, humidity))
  {
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nHum[%d]: Error\r\n", (int)Instance);
  }
  else
  {
    floatToInt(*humidity, &out_value, 2);
    snprintf(dataOut, MAX_BUF_SIZE, "\r\nHum[%d]: %d.%02d %%\r\n", (int)Instance, (int)out_value.out_int,
             (int)out_value.out_dec);
  }

}

void MX_MEMS_Init(void)
{
  /* USER CODE BEGIN SV */ 

  /* USER CODE END SV */

  /* USER CODE BEGIN MEMS_Init_PreTreatment */
  
  /* USER CODE END MEMS_Init_PreTreatment */

  /* Initialize the peripherals and the MEMS components */
  MX_IKS01A3_DataLogTerminal_Init();

  /* USER CODE BEGIN MEMS_Init_PostTreatment */

  /* USER CODE END MEMS_Init_PostTreatment */
}
/**
  * @brief  Initialize the DataLogTerminal application
  * @retval None
  */
void MX_IKS01A3_DataLogTerminal_Init(void)
{
  int i;

  /* Initialize LED */
//  BSP_LED_Init(LED2);

  /* Initialize button */
  //BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

  /* Initialize Virtual COM Port */
  BSP_COM_Init(COM1);

  IKS01A3_MOTION_SENSOR_Init(IKS01A3_LSM6DSO_0, MOTION_ACCELERO | MOTION_GYRO);

  IKS01A3_MOTION_SENSOR_Init(IKS01A3_LIS2DW12_0, MOTION_ACCELERO);

  IKS01A3_MOTION_SENSOR_Init(IKS01A3_LIS2MDL_0, MOTION_MAGNETO);

  for(i = 0; i < IKS01A3_MOTION_INSTANCES_NBR; i++)
  {
    IKS01A3_MOTION_SENSOR_GetCapabilities(i, &MotionCapabilities[i]);
  }
  IKS01A3_ENV_SENSOR_Init(IKS01A3_HTS221_0, ENV_TEMPERATURE | ENV_HUMIDITY);

  IKS01A3_ENV_SENSOR_Init(IKS01A3_LPS22HH_0, ENV_TEMPERATURE | ENV_PRESSURE);

  IKS01A3_ENV_SENSOR_Init(IKS01A3_STTS751_0, ENV_TEMPERATURE);

  for(i = 0; i < IKS01A3_ENV_INSTANCES_NBR; i++)
  {
    IKS01A3_ENV_SENSOR_GetCapabilities(i, &EnvCapabilities[i]);
  }
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

