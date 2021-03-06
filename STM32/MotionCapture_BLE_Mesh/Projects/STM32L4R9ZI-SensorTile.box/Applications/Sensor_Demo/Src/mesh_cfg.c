/**
******************************************************************************
* @file    mesh_cfg.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   User configurable settings for BlueNRG-Mesh
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
#include "mesh_cfg.h"
#include "types.h"
#include "compiler.h"
#include "string.h"
#include "generic.h"
#include "light.h"
#include "sensors.h"
#include "vendor.h"
#include "config_client.h"
#include "light_lc.h"
#include "common.h"
#include "appli_mesh.h"
#include "sensor_cfg_usr.h"
#include <string.h>

/* Note: Please use Full Library configuration in project options to use the full 
         configuration of the C/C++ runtime library for printf and scanf functionality */
#if ((ENABLE_SERIAL_CONTROL) | (ENABLE_UT) | (( ENABLE_SERIAL_INTERFACE)))
  #if ((!ENABLE_USART) || (!ENABLE_SERIAL_INTERFACE))
    #error "Serial Interface also needed for Serial Control Application."
  #else
    #include "serial_if.c"
    #if ENABLE_SERIAL_CONTROL
      #include "serial_ctrl.c"    
    #endif
    #if ENABLE_UT
      #include "serial_ut.c"      
    #endif
    #if ENABLE_APPLI_TEST
      #include "appli_test.c"   
    #endif       
  #endif
#endif










/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

__attribute__((aligned(4))) 
MOBLEUINT8 dyn_buffer_m[DYNAMIC_MEMORY_SIZE + \
                        FRIEND_BUFF_DYNAMIC_MEMORY_SIZE + \
                        MAX_APPLICATION_PACKET_SIZE + \
                        SAR_BUFFER_SIZE + \
                        NEIGHBOR_TABLE_DYNAMIC_MEMORY_SIZE] = {0};

#define MODELDATA_SIZE (MAX_APPLICATION_PACKET_SIZE+16)
#define MODELS_BUFFER_SIZE (MODELDATA_SIZE)


#ifdef STATIC_MEMORY_ALLOCATION_IN_APPLI
ALIGN(4)
MOBLEUINT8 aModelsBuff[MODELS_BUFFER_SIZE]; 

ALIGN(4)
MOBLEUINT8 aModelsBuff_Response[MODELS_BUFFER_SIZE]; 

ALIGN(4)
MOBLEUINT8 aLowerTptBuff[MODELS_BUFFER_SIZE]; 

ALIGN(4)
MOBLEUINT8 aLowerTptFnBuff[16];  

ALIGN(4)
MOBLEUINT8 aLowerTptAppBuff[MAX_APPLICATION_PACKET_SIZE+16]; 

ALIGN(4)
MOBLEUINT8 aProvisionParamBuff[448];

ALIGN(4)
MOBLEUINT8 aAppli_SAR_Buffer[24+MAX_APPLICATION_PACKET_SIZE]; 

ALIGN(4)
MOBLEUINT8 aTrans_SegIn_Buffer[40*TPT_SEGMENT_COUNT]; 

ALIGN(4)
MOBLEUINT8 aTrans_Seq0_Buffer[40*TPT_SEGMENT_COUNT]; 

ALIGN(4)
MOBLEUINT8 aTrans_Out_Buffer[12*TPT_SEGMENT_COUNT];    

ALIGN(4)
MOBLEUINT8 aElementsCC[0x3b8];  
#endif

extern const MOBLEUINT8 StaticOobBuff[];
extern const MOBLEUINT8 PubKeyBuff[];
extern const MOBLEUINT8 PrivKeyBuff[];
extern MOBLEUINT8 NumberOfElements;

#if defined(BLUENRG1_DEVICE) || defined(BLUENRG2_DEVICE) /* BLUENRG1 or BLUENRG2 */
ALIGN(4)
#endif
const DynBufferParam_t DynBufferParam =
{
  dyn_buffer_m,
  (MOBLEUINT16) (DYNAMIC_MEMORY_SIZE + SAR_BUFFER_SIZE ),
  (MOBLEUINT16) FRIEND_BUFF_DYNAMIC_MEMORY_SIZE,
  (MOBLEUINT16) MAX_APPLICATION_PACKET_SIZE,
  (MOBLEUINT16) NEIGHBOR_TABLE_DYNAMIC_MEMORY_SIZE,
  (MOBLEUINT16) MODELS_BUFFER_SIZE
};
 
const MOBLEUINT8 Device_Name[] = {DEVICE_NAME_SIZE+1, AD_TYPE_NAME, DEVICE_NAME};
const device_name_params_t DeviceNameParams = DEVICE_NAME_PARAMS;
const tr_params_t TrParams = TRANSMIT_RECEIVE_PARAMS;
#if defined(BLUENRG1_DEVICE) || defined(BLUENRG2_DEVICE) /* BLUENRG1 or BLUENRG2 */
const lpn_params_t LpnParams = LOW_POWER_NODE_PARAMS;
#else
const lpn_params_t LpnParams;
#endif
const fn_params_t FnParams = FRIEND_NODE_PARAMS;
const prvn_params_t PrvnParams = UNPROV_NODE_INFO_PARAMS;
const neighbor_table_init_params_t NeighborTableParams = NEIGHBOR_TABLE_PARAMS;

__attribute__((aligned(4)))
MOBLEUINT16 Appli_SIG_Models[APPLICATION_NUMBER_OF_ELEMENTS][APPLICATION_SIG_MODELS_MAX_COUNT];
MOBLEUINT32 Appli_Vendor_Models[APPLICATION_NUMBER_OF_ELEMENTS][APPLICATION_VENDOR_MODELS_MAX_COUNT];

/**
* Memory allocation for sensor server model
*/
MOBLEUINT8 BufferSensorServer[TOTAL_SENSOR_SERVER_BUFF_SIZE];

/**
* Memory allocation for light lc server model
*/
MOBLEUINT8 BufferLcServer[SIZE_OF_LC_SERVER_T];

/** 
* @brief AppliCheck_EnabledModelsList: This function checks whether the Enabled  
*                             Models in the defined range or exceeding the limit
* retval MOBLE_RESULT
*/
MOBLE_RESULT AppliCheck_EnabledModelsList(void)
{ 
   MOBLE_RESULT result = MOBLE_RESULT_FAIL;
/* Initialization of the  SIG Models list */
   result = ApplicationInitSigModelList();
  {
    if(result == MOBLE_RESULT_FALSE)
    {
      printf("The number of Models enabled in Application exceed the Library limit");
      result = MOBLE_RESULT_FAIL;
          return result;
    }
    
    else if(result == MOBLE_RESULT_FAIL)
    {
      printf("The number of Models enabled exceed the limit of %d !\r\n",
              USER_SIG_MODELS_MAX_COUNT);
          return result;
    }

  }
  
    /* Initialization of the  VENDOR Models list, if any */
  result = ApplicationInitVendorModelList();
  {
    
    if(result == MOBLE_RESULT_FALSE)
    {
      printf("The number of Models enabled in Application exceed the Library limit");
      result = MOBLE_RESULT_FAIL;
          return result;
    }

    else if(result == MOBLE_RESULT_FAIL)
    {    
    printf("The number of Vendor Models enabled exceed the limit of %d !\r\n",
            USER_VENDOR_MODELS_MAX_COUNT); 
        return result;
    }
    
  }
  
  return result;
}

/** 
* @brief ApplicationInitSigModelList: This function initialize the list of the 
*                                     SIG Models.
* retval MOBLE_RESULT
*/
MOBLE_RESULT ApplicationInitSigModelList(void)
{
  /*If Models enabled by user are exceeding the library capability*/
  if(APPLICATION_SIG_MODELS_MAX_COUNT > BluenrgMesh_GetTotalModelsCount() - 
                                            APPLICATION_VENDOR_MODELS_MAX_COUNT)
  {
    return(MOBLE_RESULT_FALSE);
  }
  
  for(uint8_t index = 0; index < APPLICATION_NUMBER_OF_ELEMENTS; index++)
  {
    uint8_t modelIndex = 0;
    uint8_t modelCount = 0;    
    Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
    
#ifdef ENABLE_CONFIG_MODEL_CLIENT
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_CONFIG_MODEL_CLIENT & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = SIG_MODEL_ID_CONFIG_CLIENT;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_ONOFF
    
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_ONOFF & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_ONOFF_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_LEVEL
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_LEVEL & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_LEVEL_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_DEFAULT_TRANSITION_TIME
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_DEFAULT_TRANSITION_TIME & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_DEFAULT_TRANSITION_TIME_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
    
#endif
#ifdef ENABLE_GENERIC_MODEL_SERVER_POWER_ONOFF
    
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_POWER_ONOFF & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_POWER_ONOFF_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_POWER_ONOFF_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_POWER_ONOFF_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_POWER_ONOFF_SETUP_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_POWER_LEVEL
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_POWER_LEVEL & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_POWER_LEVEL_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_POWER_LEVEL_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_POWER_LEVEL_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_POWER_LEVEL_SETUP_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_BATTERY
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_BATTERY & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_BATTERY_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_LOCATION
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_LOCATION & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_LOCATION_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_LOCATION_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_LOCATION_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_LOCATION_SETUP_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_ADMIN_PROPERTY
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_ADMIN_PROPERTY & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_ADMIN_PROPERTY_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_MANUFACTURER_PROPERTY
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_MANUFACTURER_PROPERTY & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_MANUFACTURER_PROPERTY_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_USER_PROPERTY
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_USER_PROPERTY & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_USER_PROPERTY_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_SERVER_CLIENT_PROPERTY
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_SERVER_CLIENT_PROPERTY & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_SERVER_CLIENT_PROPERTY_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif

    /**************************************************************************/
    /** Following Section places LIGHTING MODEL Enabled SERVER IDs    *********/
    /**************************************************************************/

#ifdef ENABLE_LIGHT_MODEL_SERVER_LIGHTNESS
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_LIGHTNESS & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_LIGHTNESS_MODEL_ID;       
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_LIGHTNESS_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_LIGHTNESS_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_LIGHTNESS_SETUP_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_CTL
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_CTL & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_CTL_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_CTL_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_CTL_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_CTL_SETUP_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_CTL_TEMPERATURE
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_CTL_TEMPERATURE & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_CTL_TEMPERATURE_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_HSL
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_HSL & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_HSL_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_HSL_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_HSL_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_HSL_SETUP_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_HSL_HUE
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_HSL_HUE & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_HSL_HUE_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_HSL_SATURATION
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_HSL_SATURATION & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_HSL_SATURATION_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif

    /**************************************************************************/
    /** Following Section places Light XYL MODEL Enabled SERVER IDs   *********/
    /**************************************************************************/
#ifdef ENABLE_LIGHT_MODEL_SERVER_XYL
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_XYL & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_XYL_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_XYL_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_XYL_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_SERVER_XYL_SETUP_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif

    /**************************************************************************/
    /** Following Section places Light LC MODEL Enabled SERVER IDs    *********/
    /**************************************************************************/
#ifdef ENABLE_LIGHT_MODEL_SERVER_LC
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_LC & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_LC_SERVER_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_SERVER_LC_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_SERVER_LC_SETUP & (1 << index)) == (1 << index)) 

    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_LC_SETUP_SERVER_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif

    /**************************************************************************/
    /** Following Section places SENSOR MODEL Enabled SERVER IDs      *********/
    /**************************************************************************/
#ifdef ENABLE_SENSOR_MODEL_SERVER
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_SENSOR_MODEL_SERVER & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = SENSOR_SERVER_MODEL_ID;    
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_SENSOR_MODEL_SERVER_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_SENSOR_MODEL_SERVER_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = SENSOR_SETUP_SERVER_MODEL_ID; 
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif

    /**************************************************************************/
    /** Following Section places Time and Scene MODEL Enabled SERVER IDs    ***/
    /**************************************************************************/

#ifdef ENABLE_TIME_MODEL_SERVER
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_TIME_MODEL_SERVER & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = TIME_MODEL_SERVER_MODEL_ID;             
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_TIME_MODEL_SERVER_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_TIME_MODEL_SERVER_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = TIME_MODEL_SERVER_SETUP_MODEL_ID;       
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_SCENE_MODEL_SERVER
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_SCENE_MODEL_SERVER & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = SCENE_MODEL_SERVER_MODEL_ID;            
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_SCENE_MODEL_SERVER_SETUP
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_SCENE_MODEL_SERVER_SETUP & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = SCENE_MODEL_SERVER_SETUP_MODEL_ID;      
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif

    /**************************************************************************/
    /** Following Section places Generic MODEL Enabled Client IDs    **********/
    /**************************************************************************/ 
#ifdef ENABLE_GENERIC_MODEL_CLIENT_ONOFF
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_CLIENT_ONOFF & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_ONOFF_CLIENT_MODEL_ID ; //GENERIC_MODEL_CLIENT_ONOFF_MODEL_ID;   
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_GENERIC_MODEL_CLIENT_LEVEL
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_GENERIC_MODEL_CLIENT_LEVEL & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = GENERIC_MODEL_CLIENT_LEVEL_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
#ifdef ENABLE_LIGHT_MODEL_CLIENT_LIGHTNESS
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
    
    if((ENABLE_LIGHT_MODEL_CLIENT_LIGHTNESS & (1 << index)) == (1 << index)) 
    {
      Appli_SIG_Models[index][modelIndex++] = LIGHT_MODEL_CLIENT_LIGHTNESS_MODEL_ID;
      Appli_SIG_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
#endif
    
    if(modelCount >= APPLICATION_SIG_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
  }
  return (MOBLE_RESULT_SUCCESS); 
}

/** 
* @brief ApplicationInitVendorModelList: This function initialize the list of the 
*                                     VENDOR Models.
* retval MOBLE_RESULT
*/
MOBLE_RESULT ApplicationInitVendorModelList(void)
{
#ifdef ENABLE_VENDOR_MODEL_SERVER  
  
  /*If Models enabled by user are exceeding the library capability*/
  if( APPLICATION_VENDOR_MODELS_MAX_COUNT > BluenrgMesh_GetTotalModelsCount() - 
                                            APPLICATION_SIG_MODELS_MAX_COUNT)
  {
    printf("The number of Models enabled in Application exceeding the limit of Library");
    return(MOBLE_RESULT_FALSE);
  }
  for(uint8_t index = 0; index < APPLICATION_NUMBER_OF_ELEMENTS; index++)
  {
    uint8_t modelIndex = 0;
    uint8_t modelCount = 0;    
    Appli_Vendor_Models[index][modelIndex] = NO_MODEL_AVLBL;
    
    if((ENABLE_VENDOR_MODEL_SERVER & (1 << index)) == (1 << index)) 
    {
      Appli_Vendor_Models[index][modelIndex++] = VENDORMODEL_STMICRO_ID1;
      Appli_Vendor_Models[index][modelIndex] = NO_MODEL_AVLBL;
      modelCount++;
    }
    
    if(modelCount >= APPLICATION_VENDOR_MODELS_MAX_COUNT)
    {
      return(MOBLE_RESULT_FAIL);
    }
  }
#endif
  return (MOBLE_RESULT_SUCCESS); 
}

/* Private functions ---------------------------------------------------------*/

/** 
* @brief ApplicationGetSigModelList: This function provides the list of the 
*           SIG Models to the calling function
* @param pModels_sig_ID: Pointer of the array to be filled with SIG Models list
* @param elementIndex: Index of the element for Model List
* retval Count of the SIG Model Servers enabled in the Application
*/
MOBLEUINT8 ApplicationGetSigModelList(MOBLEUINT16* pModels_sig_ID, MOBLEUINT8 elementIndex)
{
  uint8_t count=0;
  /* Since the SIG Models are 2 bytes, copy 2*size for memcpy */
  for(uint8_t index=0; index <= elementIndex; index++)
  {
    if(index == elementIndex)
    {
      for(uint8_t modelCount=0; modelCount < APPLICATION_SIG_MODELS_MAX_COUNT; modelCount++)
      {
        if(Appli_SIG_Models[index][modelCount] == NO_MODEL_AVLBL)
        {
          memcpy(pModels_sig_ID, Appli_SIG_Models+index, count*2);
          break;
        }
        
        else
        {
          count++;
        }
      }
      
      break;
    }
    
    else
    {
      /*do nothing*/
    }
  }
  
  return count; 
}


/** 
* @brief ApplicationGetCLIENTSigModelList: This function provides the list of the 
*           SIG Models to the calling function
* @param pModels_sig_ID: Pointer of the array to be filled with SIG Models list
* @param elementIndex: Index of the element for Model List
* retval Count of the SIG Model Servers enabled in the Application
*/
MOBLEUINT8 ApplicationGetCLIENTSigModelList(MOBLEUINT16* pModels_sig_ID, MOBLEUINT8 elementIndex)
{
  
  uint8_t count=0;
  /* Since the SIG Models are 2 bytes, copy 2*size for memcpy */
  for(uint8_t index=0; index <= elementIndex; index++)
  {
    if(index == elementIndex)
    {
      for(uint8_t modelCount=0; modelCount < APPLICATION_SIG_MODELS_MAX_COUNT; modelCount++)
      {
        if(Appli_SIG_Models[index][modelCount] == NO_MODEL_AVLBL)
        {
          memcpy(pModels_sig_ID, Appli_SIG_Models+index, count*2);
          break;
        }
        
        else
        {
          count++;
        }
      }
      
      break;
    }
    
    else
    {
      /*do nothing*/
    }
  }
  
  return count; 
}


/** 
* @brief ApplicationGetCLIENTSigModelList: This function provides the list of the 
*           SIG Models to the calling function
* @param pModels_sig_ID: Pointer of the array to be filled with SIG Models list
* @param elementIndex: Index of the element for Model List
* retval Count of the SIG Model Servers enabled in the Application
*/
MOBLEUINT8 ApplicationSetNodeSigModelList(void)
{
  /* Since the SIG Models are 2 bytes, copy 2*size for memcpy */
    BLEMeshSetSelfModelList(NumberOfElements);
  return 1;
}


/** 
* @brief ApplicationGetVendorModelList: This function provides the list of the 
*           Vendor Models to the calling function
* @param pModels_sig_ID: Pointer of the array to be filled with Vendor Models list
* @param elementIndex: Index of the element for Model List
* retval Count of the Vendor Model Servers enabled in the Application
*/

MOBLEUINT8 ApplicationGetVendorModelList(MOBLEUINT32* pModels_vendor_ID, MOBLEUINT8 elementIndex)
{
   uint8_t count=0;
#ifdef ENABLE_VENDOR_MODEL_SERVER 
  for(uint8_t index=0; index <= elementIndex; index++)
  {
    if(index == elementIndex)
    {
      for(uint8_t modelCount=0; modelCount < APPLICATION_VENDOR_MODELS_MAX_COUNT; modelCount++)
      {
        if(Appli_Vendor_Models[index][modelCount] == NO_MODEL_AVLBL)
        {
          memcpy(pModels_vendor_ID, Appli_Vendor_Models+index, count*4);
          break;
        }
        
        else
        {
          count++;
        }
      }
      
      break;
    }
    
    else
    {
      /*do nothing*/
    }
  }
#endif  
  return count; 
}


/** 
* @brief ApplicationChkSigModelActive: This function checks if a specific 
*          Model Server is active in the Model Server list
* @param modelID: Model Server ID received for the checking function
* @param elementIndex : index of element for which active model checking is needed
* retval Bool: True or False, if the Server ID matches with the list 
*/
MOBLEBOOL ApplicationChkSigModelActive(MOBLEUINT16 modelID, MOBLEUINT8 elementIndex)
{
  
  MOBLEBOOL result = MOBLE_FALSE;
  
  for(uint8_t index = 0; index <= elementIndex; index++)
  {
    if(index == elementIndex)
    {
      for(uint8_t count = 0; count < APPLICATION_SIG_MODELS_MAX_COUNT; count++)
      {
        if (modelID == Appli_SIG_Models[index][count])      
        {
          result = MOBLE_TRUE;
          break;
        }
        
        else
        {
           /*do nothing*/ 
        }
      }
      break;
    }
    
    else
    {
      /*do nothing*/  
    }
  }
  
  return result;
}


/** 
* @brief ApplicationChkVendorModelActive: This function checks if a specific 
*          Model Server is active in the Vendor Model Server list
* @param modelID: Model Server ID received for the checking function
* @param elementIndex : index of element for which active model checking is needed
* retval Bool: True or False, if the Server ID matches with the list 
*/
MOBLEBOOL ApplicationChkVendorModelActive(MOBLEUINT32 modelID, MOBLEUINT8 elementIndex)
{
  MOBLEBOOL result = MOBLE_FALSE;
  
  for(uint8_t index = 0; index <= elementIndex; index++)
  {
    if(index == elementIndex)
    {
      for(uint8_t count = 0; count < APPLICATION_VENDOR_MODELS_MAX_COUNT; count++)
      {
        if (modelID == Appli_Vendor_Models[index][count])      
        {
          result = MOBLE_TRUE;
          break;
        }
        
        else
        {
           /*do nothing*/ 
        }
      }
      break;
    }
    
    else
    {
      /*do nothing*/  
    }
  }
  
  return result;
    
}


/** 
* @brief GetModel Data buffer to use by the library 
* @param none
* retval void* Pointer to the used buffer 
*/
#ifdef STATIC_MEMORY_ALLOCATION_IN_APPLI
void* GetMemoryDataBuffer(MOBLEUINT8 buffer_type, MOBLEUINT32 u32length)
{
  void* ptr = NULL;
  MOBLEUINT32 allocated_len;

  switch (buffer_type)
  {
  case MESH_MODEL_BUFFER:
  case HEALTH_MODEL_NEW_BUFFER:
  case HEALTH_MODEL_PUBLISH_BUFFER:
    ptr = &aModelsBuff[0];  
    allocated_len = sizeof(aModelsBuff); 
    break;
    
  case MESH_MODEL_RESPONSE_BUFFER:
  case VENDOR_MODEL_WRITE_BUFFER:
  case VENDOR_MODEL_WRITE_PUBLISHBUFFER:
  case VENDOR_MODEL_RESPONSE_BUFFER:
  case GENERIC_MODEL_REPLY_BUFFER:
  case GENERIC_MODEL_SENDREMOTE_BUFFER:
  case GENERIC_MODEL_SENDDATA_BUFFER:
  case CONFIG_MODEL_PUBLISH_BUFFER:
    ptr = &aModelsBuff_Response[0];  
    allocated_len = sizeof(aModelsBuff_Response);
    break;
    
  case MESH_LOWER_TPT_BUFFER:
    ptr = &aLowerTptBuff[0]; 
    allocated_len = sizeof(aLowerTptBuff);
    break;
    
  case MESH_LOWER_TPT_FN_BUFFER:
    ptr = &aLowerTptFnBuff[0];  
    allocated_len = sizeof(aLowerTptFnBuff);
    break;
    
  case MESH_LOWER_TPT_APP_BUFFER:
    ptr = &aLowerTptAppBuff[0];    
    allocated_len = sizeof(aLowerTptAppBuff);
    break;
    
  case PROVISIONER_BUFFER:
  case PROVISION_NODE_BUFFER:
    ptr = &aProvisionParamBuff[0];    
    allocated_len = sizeof(aProvisionParamBuff);
    break;
    
  case ACCESS_APPLI_BUFFER:
    ptr = &aAppli_SAR_Buffer[0];    
    allocated_len = sizeof(aAppli_SAR_Buffer);
    
  case MESH_LOWER_TPT_INSEG:
    ptr = &aTrans_SegIn_Buffer[0];    
    allocated_len = sizeof(aTrans_SegIn_Buffer);
    break;
    
  case MESH_LOWER_TPT_INSEQ0:
    ptr = &aTrans_Seq0_Buffer[0];    
    allocated_len = sizeof(aTrans_Seq0_Buffer);
    break;
    
  case MESH_LOWER_TPT_OUTMSG:
    ptr = &aTrans_Out_Buffer[0];    
    allocated_len = sizeof(aTrans_Out_Buffer);
    
  default:
    break;
  }

  /*TRACE_M(TF_MEMORY, "BuffType= %d, RequiredLength=%d, Allocated= %d \r\n", buffer_type, u32length, allocated_len);  */
  if (u32length > allocated_len)
  {
 /*  TRACE_M(TF_MEMORY, "***<<<ERROR>>> Short buffer Allocated \r\n"); */
  }
  
  return ptr;
}
#endif

#if (FRIEND_FEATURE == 0)
void BnrgmFrndFnProcess(void* param)
{
  
}

MOBLE_RESULT BnrgmFrndFnProcessFrndClear(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndFnProcessFrndClearConf(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndFnProcessFrndPoll(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndFnProcessFrndRequest(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndFnProcessFrndSubscrListAdd(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndFnProcessFrndSubscrListRem(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndFnSendFrndClear(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndFnSwitchKeys(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndFnUpdateKeys(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndMgmtFnInit(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndMgmtGetFriendshipStatus(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLEUINT32 BnrgmFrndMgmtGetLpnPollTimeout(void* param)
{
  return 0;
}

MOBLE_RESULT BnrgmFrndMgmtGetSubscrStatus(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndMgmtQueLpnPkt(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

void BnrgmFrndMgmtSendSecurityUpdate(void* param)
{
  
}
#endif /* #if (FRIEND_FEATURE == 0) */

#if (LOW_POWER_FEATURE == 0)
MOBLE_RESULT BnrgmFrndLpnProcess(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndLpnProcessFrndOffer(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndLpnProcessFrndUpdate(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndLpnProcessFrndRfu(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndLpnProcessFrndSubscrListConf(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndLpnSwitchKeys(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndLpnTranspSegRecvd(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndLpnUpdateKeys(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}

MOBLE_RESULT BnrgmFrndMgmtLpnInit(void* param)
{
  return MOBLE_RESULT_NOTIMPL;
}
#endif /* #if (LOW_POWER_FEATURE == 0) */

#if (NEIGHBOR_TABLE_SUPPORTED == 0)
MOBLE_RESULT BluenrgMesh_NeighborTableInit(void* param)
{
  return MOBLE_RESULT_SUCCESS;
}

void BluenrgMesh_UpdateNeighbors(void* param)
{
  /* empty function */
}
#endif /* #if (NEIGHBOR_TABLE_SUPPORTED == 0) */

void Appli_Light_LC_SerialCmd(char *rcvdStringBuff, uint16_t rcvdStringSize)
{
  
}

#ifndef ENABLE_SENSOR_MODEL_SERVER /* Flash optimization corresponding to sensor server */
MOBLE_RESULT Appli_Sensor_Init(void){return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_ExtractSettingPropertyId(const MOBLEUINT8* data, MOBLEUINT16* pSettingPropertyId)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_ExtractSensorOffset(MOBLEUINT8 elementIdx,MOBLEUINT8* pSensorOffsetBuff, 
                                        MOBLEUINT8* pSensorCount, MOBLEUINT32 length, 
                                        const MOBLEUINT8* pData, MOBLEUINT16* pidNotFound)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_FillDescriptor(MOBLEUINT8 sensorOffset, void* pParams, MOBLEUINT8* pData, MOBLEUINT8* pLengthInc)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_MarshalPid(MOBLEUINT8 sensorOffset, void* pParams, MOBLEUINT8* pData, MOBLEUINT8* pLengthInc,
                               MOBLEUINT8 pidMatch, MOBLEUINT16 pidNotFound)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_CadenceStatus(MOBLEUINT8 pidMatch,void* pParams,MOBLEUINT16 pidNotFound,
                                  MOBLE_ADDRESS dstAddr,MOBLEUINT8 elementIdx,MOBLEUINT8 statusSend)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_SettingsStatus(MOBLEUINT8* offsetBuff,MOBLEUINT8 sensorCount,
                                   MOBLE_ADDRESS dstAddr,MOBLEUINT16 pidNotFound)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_SettingStatus(MOBLEUINT8 pidMatch, MOBLEUINT8 readViolation,
                                  void* pParams,void* pSettingsParam,MOBLEUINT16 pidNotFound,
                                  MOBLEUINT16 rcvdSettingId,MOBLE_ADDRESS dstAddr,
                                  MOBLEUINT8 elementIdx,MOBLEUINT8 statusSend)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_DescriptorStatus(MOBLEUINT8* offsetBuff, MOBLEUINT8 sensorCount,
                                     MOBLE_ADDRESS dstAddr, MOBLEUINT16 pidNotFound)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_Status(MOBLEUINT8* offsetBuff, MOBLEUINT8 sensorCount,MOBLE_ADDRESS dstAddr,
                           MOBLEUINT16 pidNotFound,MOBLEUINT8 statusSend)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_ColumnStatus(MOBLEUINT8* offsetBuff, MOBLEUINT8 sensorCount,
                                 MOBLE_ADDRESS dstAddr,MOBLEUINT32 rawValueX,
                                 MOBLEUINT8 rcvdRawXLength,MOBLEUINT16 pidNotFound,
                                 MOBLEUINT8 elementIndex,MOBLEUINT8 statusSend)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_SeriesStatus(MOBLEUINT8* offsetBuff, MOBLEUINT8 sensorCount,
                                 MOBLE_ADDRESS dstAddr,MOBLEUINT32 rcvdX1,
                                 MOBLEUINT32 rcvdX2,MOBLEUINT8 isX1X2Present,
                                 MOBLEUINT8 rcvdRawXLength,MOBLEUINT16 pidNotFound,
                                 MOBLEUINT8 elementIndex,MOBLEUINT8 statusSend)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_DescriptorGet(const MOBLEUINT8* pDescriptorParam, MOBLEUINT32 length,
                                  MOBLE_ADDRESS peerAddr,MOBLE_ADDRESS dstPeer,MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_CadenceGet(const MOBLEUINT8* pCadenceParam,MOBLEUINT32 length,
                               MOBLE_ADDRESS peerAddr,MOBLE_ADDRESS dstPeer,MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_CadenceSet(const MOBLEUINT8* pCadenceParam,MOBLEUINT32 length,
                               MOBLE_ADDRESS peerAddr,MOBLE_ADDRESS dstPeer,MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_CadenceSetUnack(const MOBLEUINT8* pCadenceParam, MOBLEUINT32 length,
                                    MOBLE_ADDRESS peerAddr, MOBLE_ADDRESS dstPeer,MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_SettingsGet(const MOBLEUINT8* pSettingsParam, MOBLEUINT32 length,
                                MOBLE_ADDRESS peerAddr, MOBLE_ADDRESS dstPeer,MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_SettingGet(const MOBLEUINT8* pRcvdParam, MOBLEUINT32 length,
                               MOBLE_ADDRESS peerAddr,MOBLE_ADDRESS dstPeer,MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_SettingSet(const MOBLEUINT8* pRcvdParam,MOBLEUINT32 length,MOBLE_ADDRESS peerAddr,
                               MOBLE_ADDRESS dstPeer,MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_SettingSetUnack(const MOBLEUINT8* pRcvdParam,MOBLEUINT32 length,
                                    MOBLE_ADDRESS peerAddr,MOBLE_ADDRESS dstPeer,
                                    MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_Get(const MOBLEUINT8* pGetParam, MOBLEUINT32 length,MOBLE_ADDRESS peerAddr,
                        MOBLE_ADDRESS dstPeer,MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_ColumnGet(const MOBLEUINT8* pColumnParam,MOBLEUINT32 length,MOBLE_ADDRESS peerAddr,
                              MOBLE_ADDRESS dstPeer,MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_SeriesGet(const MOBLEUINT8* pSeriesParam, MOBLEUINT32 length,
                              MOBLE_ADDRESS peerAddr, MOBLE_ADDRESS dstPeer,
                              MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT SensorModelServer_GetOpcodeTableCb(const MODEL_OpcodeTableParam_t **data, 
                                                MOBLEUINT16 *length)
{return MOBLE_RESULT_NOTIMPL;}

MOBLE_RESULT SensorModelServer_GetStatusRequestCb(MODEL_MessageHeader_t *pmsgParams, 
                                                  MOBLEUINT16 opcode, MOBLEUINT8 *pResponsedata, 
                                                  MOBLEUINT32 *plength, MOBLEUINT8 const *pRxData,
                                                  MOBLEUINT32 dataLength,MOBLEBOOL response)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT SensorModelServer_ProcessMessageCb(MODEL_MessageHeader_t *pmsgParams, 
                                                MOBLEUINT16 opcode,MOBLEUINT8 const *data, 
                                                MOBLEUINT32 length,MOBLEBOOL response)
{return MOBLE_RESULT_NOTIMPL;}
MOBLEUINT32 Sensor_SleepDurationMs_Get(void)
{return 0;}
MOBLE_RESULT Sensor_UpdatePublishParameters(MOBLEUINT8 sensorOffset)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_CheckStatusTrigger(MOBLEUINT8 sensorOffset)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_Send(MOBLEUINT8 sensorOffset,MOBLEUINT8 elementIdx,MOBLEUINT16 propertyId)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_UpdateCadence(MOBLEUINT8 sensorOffset, MOBLEUINT8 elementIdx, 
                                  MOBLEUINT16 propertyId)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Sensor_UpdatePublishState(MOBLEUINT8 sensorOffset, MOBLEUINT8 state)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT SensorServer_Init(void* sensorBuff, const sensor_server_cb_t* sensor_cb,
                               MOBLEUINT16 sizeBuff,const void* initParams)
{return MOBLE_RESULT_NOTIMPL;}
void Sensor_Process(void){}
MOBLE_RESULT Sensor_ModelPublishSet(model_publicationparams_t* pPublishParams)
{ 
  return MOBLE_RESULT_NOTIMPL;
}
#endif

void Appli_Sensor_SerialCmd(char *rcvdStringBuff, uint16_t rcvdStringSize)
{
}

#ifndef ENABLE_LIGHT_MODEL_SERVER_LC
MOBLE_RESULT LightLcServer_GetOpcodeTableCb(const MODEL_OpcodeTableParam_t **data, 
                                            MOBLEUINT16 *length)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT LightLcServer_GetStatusRequestCb(MODEL_MessageHeader_t *pmsgParam, 
                                              MOBLEUINT16 opcode, 
                                              MOBLEUINT8 *pResponsedata, 
                                              MOBLEUINT32 *plength, 
                                              MOBLEUINT8 const *pRxData,
                                              MOBLEUINT32 dataLength,
                                              MOBLEBOOL response)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT LightLcServer_ProcessMessageCb(MODEL_MessageHeader_t *pmsgParam, 
                                            MOBLEUINT16 opcode, 
                                            MOBLEUINT8 const *pRxData, 
                                            MOBLEUINT32 dataLength, 
                                            MOBLEBOOL response)
{return MOBLE_RESULT_NOTIMPL;}
void LightLC_SaveModelStates(MOBLEUINT8 elementIndex,
                             MOBLEUINT8* lightLcNvmParamsBuff, 
                             MOBLEUINT8 lcNvmParamsSize)
{}
MOBLEUINT8 Light_LC_OnPowerUp(MOBLEUINT8 elementIndex,
                              MOBLEUINT8 const *pModelValue_Load, 
                              MOBLEUINT8 genericOnPowerUp,
                              MOBLEUINT16 lightDefault,
                              MOBLEUINT16 lightLast,
                              MOBLEUINT16 lightActualLKV,
                              MOBLEUINT16* pLightActualToBeSet)
{return 0;}
MOBLE_RESULT Light_LC_SetTransitionTimeZero(MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Light_LC_SensorPropertyUpdate(MOBLEUINT8 lcsElementIndex,
                                           MOBLEUINT16 sensorPropertyId,
                                           MOBLEUINT32 value)
{return MOBLE_RESULT_NOTIMPL;}
void Light_LC_LigtnessLinearUnsolicitedChange(MOBLEUINT8 elementIndex)
{}
MOBLEUINT32 Light_LC_SleepDurationMs_Get(void)
{return 0;}
MOBLE_RESULT Light_LC_Send(MOBLEUINT8 elementIndex)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Light_LC_LcOnOffUpdate(MOBLEUINT8 elementIndex, 
                                    MOBLEUINT8 onOff,
                                    MOBLEUINT8 optionalParams,
                                    MOBLEUINT32 delayMsOnOffMsg,
                                    MOBLEUINT32 stepResMsOnOffMsg,
                                    MOBLEUINT32 trTimeMsOnOffMsg)
{return MOBLE_RESULT_NOTIMPL;}
void Light_LC_Process(void)
{}
MOBLE_RESULT Light_LCs_Init(void* lcsBuff,
                            MOBLEUINT8 lcsElementIndex,
                            const light_lc_cb_t* lcs_cb,
                            MOBLEUINT16 sizeBuff)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT ExtractLcServerElementIndex(MOBLEUINT8* pLcsElementIndex,
                                         MOBLEUINT8 noOfElements,
                                         MOBLEUINT8 lcServer,
                                         MOBLEUINT8 lcSetupServer,
                                         MOBLEUINT8 genericOnOffServer,
                                         MOBLEUINT8 genericPowerOnOffServer,
                                         MOBLEUINT8 sensorServer,
                                         MOBLEUINT8 lightLightnessServer)
{return MOBLE_RESULT_NOTIMPL;}
MOBLE_RESULT Appli_Light_LCs_Init(void)
{return MOBLE_RESULT_NOTIMPL;}
#endif /* #ifndef ENABLE_LIGHT_MODEL_SERVER_LC */

/* Empty functions to reduce code size in case of PB-ADV functionality not in use */

#if (PB_ADV_SUPPORTED == 0)
MOBLE_RESULT MoblePBADVInit(void* param){return MOBLE_RESULT_SUCCESS;}
MOBLE_RESULT MoblePBADVProcessData(void* param){return MOBLE_RESULT_SUCCESS;}
MOBLE_RESULT MoblePBADVStartProvisioning(void* param){return MOBLE_RESULT_SUCCESS;}
MOBLE_RESULT MoblePBADVStopProvisioning(void* param){return MOBLE_RESULT_SUCCESS;}
#endif 

/* PLEASE REFER TO THE .h file for different settings */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
