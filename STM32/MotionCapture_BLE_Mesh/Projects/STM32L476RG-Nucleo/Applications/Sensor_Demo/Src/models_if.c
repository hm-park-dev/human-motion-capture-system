/**
******************************************************************************
* @file    models_if.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Mesh Models interface file of the application
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
#include "appli_mesh.h"
#include "vendor.h"
#include "light.h"
#include "sensors.h"
#include "generic.h"
#include "generic_client.h"
#include "light_client.h"
#include "time_scene.h"
#include "common.h"
#include "appli_generic.h"
#include "appli_vendor.h"
#include "appli_light.h"
#include "appli_sensor.h"
#include "appli_nvm.h"
#ifdef STM32_BLUENRG1
#include "bluenrg1_hci_le.h"
#else
#include <hci_le.h>
#include "bluenrg_itf.h"
#endif
#include "appli_generic_client.h"
#include "appli_light_client.h"
#include "config_client.h"
#include "sensors_client.h"
#include "appli_light_lc.h"
#include "light_lc.h"


/** @addtogroup Application_Mesh_Models
 *  @{
 */
/* Private variables ---------------------------------------------------------*/
MOBLEUINT8 Led_Value = 0;

MOBLEUINT8 ButtonIndex_Value = 0;

/* Private typedef -----------------------------------------------------------*/
#pragma pack(push, 1)

typedef struct
{
  MOBLE_ADDRESS peer;
  MOBLE_ADDRESS dst;
  MOBLEUINT8 command;
  MOBLEUINT8 elementIndex;
  MOBLEUINT8 appKeyOffset;
  MOBLEUINT8 netKeyOffset;
  MOBLEUINT8 data[DATA_BUFFER_LENGTH]; /* 8-Bytes response packet */
  MOBLEUINT32 length;
} APPLI_SEND_RESPONSE_MODULE;


typedef struct
{
  MOBLEUINT8 packet_count;
  MOBLEUINT32 send_time;
  APPLI_SEND_RESPONSE_MODULE* head;
  MOBLEUINT8 head_index;
  APPLI_SEND_RESPONSE_MODULE packet[MAX_PENDING_PACKETS_QUE_SIZE];
} APPLI_PENDING_PACKETS;

#pragma pack(pop)
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
   

/* Private variables ---------------------------------------------------------*/

MOBLEUINT8 pGeneric_OnOffParam[sizeof(Generic_OnOffParam_t)];
MOBLEUINT8 pGeneric_LevelParam[sizeof(Generic_LevelParam_t)];
MOBLEUINT8 pGeneric_DeltaLevelParam[sizeof(Generic_DeltaLevelParam_t)];
MOBLEUINT8 pGeneric_MoveLevelParam[sizeof(Generic_LevelMoveParam_t)];
MOBLEUINT8 pGeneric_PowerOnOffParam[sizeof(Generic_PowerOnOffParam_t)];
MOBLEUINT8 pGeneric_DefaultTransitionTimeParam[sizeof(Generic_DefaultTransitionParam_t)];

MOBLEUINT8 pLightnessParam[sizeof(Light_LightnessParam_t)];
MOBLEUINT8 pLightnessRangeParam[sizeof(Light_LightnessRangeParam_t)];

MOBLEUINT8 pLightCtlParam[sizeof(Light_CtlParam_t)];
MOBLEUINT8 pLightCtlTemperatureParam[sizeof(Light_CtlTemperatureParam_t)];
MOBLEUINT8 pLightCtlTemperatureRangeParam[sizeof(Light_CtlTemperatureRangeParam_t)];
MOBLEUINT8 pLightCtlDefaultParam[sizeof(Light_CtlDefaultParam_t)];

MOBLEUINT8 pLightHslParam[sizeof(Light_HslParam_t)];
MOBLEUINT8 pLightHslRangeParam[sizeof(Light_HslRangeParam_t)];
MOBLEUINT8 pLightHslHueParam[sizeof(Light_HslHueParam_t)];
MOBLEUINT8 pLightHslSaturationParam[sizeof(Light_HslSaturationParam_t)];

MOBLEUINT8 pLightLCModeParam[sizeof(Light_LC_ModeParam_t)];
MOBLEUINT8 pLightLCOccupancyModeParam[sizeof(Light_LC_ModeParam_t)];
MOBLEUINT8 pLightLCOnOffParam[sizeof(Light_LC_OnOffParam_t)];

MOBLEUINT8 pSensorsCadenceParam[sizeof(sensor_CadenceCbParam_t)];

APPLI_PENDING_PACKETS Appli_PendingPackets = {0};

__attribute__((aligned(4))) 
const MOBLE_VENDOR_CB_MAP vendor_cb = 
{
  Vendor_WriteLocalDataCb,
  Vendor_ReadLocalDataCb,
  Vendor_OnResponseDataCb
};

__attribute__((aligned(4))) 
const Appli_Vendor_cb_t VendorAppli_cb = 
{
  /*Vendor Commads*/
  Appli_Vendor_LEDControl,
  Appli_Vendor_DeviceInfo,
  Appli_Vendor_Test,
  Appli_LedCtrl,
  Appli_GetTestValue,
  Appli_Vendor_Data_write
};

__attribute__((aligned(4)))   
const Appli_Generic_cb_t GenericAppli_cb = 
{
  /* Generic OnOff callbacks */
  Appli_Generic_OnOff_Set,
  /* Generic OnOff Status callbacks */
  Appli_Generic_OnOff_Status,
  /* Generic Level callbacks */
  Appli_Generic_Level_Set,
  /* Generic Level Status callbacks */ 
  Appli_Generic_Level_Status,
  /* Generic Power on off callbacks */
  Appli_Generic_PowerOnOff_Set,
  /* Generic Power on off callbacks */
  Appli_Generic_PowerOnOff_Status,
    
  /* Generic Default transition time callbacks */  
  Appli_Generic_DefaultTransitionTime_Set,
  /* Generic Default transition time callbacks */
  Appli_Generic_DefaultTransitionTime_Status
};

__attribute__((aligned(4))) 
const Appli_Generic_State_cb_t Appli_GenericState_cb =
{
  
 /* Generic Get On Off status */
  Appli_Generic_GetOnOffStatus, 
  Appli_Generic_GetOnOffValue,
 /* Generic Get level status */
  Appli_Generic_GetLevelStatus,
 /* Generic Get Power on off status */
  Appli_Generic_GetPowerOnOffStatus, 
 /* Generic Get Default transition time status */
  Appli_Generic_GetDefaultTransitionStatus
};

__attribute__((aligned(4))) 
const Appli_Light_GetStatus_cb_t Appli_Light_GetStatus_cb = 
{
  Appli_Light_GetLightnessStatus,
  Appli_Light_GetLightnessLinearStatus,
  Appli_Light_GetLightnessDefaultStatus,
  Appli_Light_GetLightnessLastStatus,
  Appli_Light_GetLightnessRangeStatus, 
  Appli_Light_GetCtlLightStatus,
  Appli_Light_GetCtlTargetStatus,
  Appli_Light_GetCtlTemperatureStatus,
  Appli_Light_GetCtlTemperatureRange,
  Appli_Light_GetCtlDefaultStatus,  
  Appli_Light_GetHslStatus,
  Appli_Light_GetHslTargetStatus,
  Appli_Light_GetHslHueStatus,
  Appli_Light_GetHslSaturationStatus,
  Appli_Light_GetHslHueRange,
  Appli_Light_GetHslSatRange,
  Appli_Light_GetHslDefaultStatus  
};


__attribute__((aligned(4))) 
const Appli_Light_cb_t LightAppli_cb = 
{ 
 /* Light Lightness callbacks */
  Appli_Light_Lightness_Set,
  Appli_Light_Lightness_Status,
  
  Appli_Light_Lightness_Linear_Set,
  Appli_Light_Lightness_Linear_Status,
  
  Appli_Light_Lightness_Default_Set,
  Appli_Light_Lightness_Default_Status,
  
  Appli_Light_Lightness_Last_Set,
  
  Appli_Light_Lightness_Range_Set,
  Appli_Light_Lightness_Range_Status,
  
  Appli_Light_Ctl_Set,
  Appli_Light_Ctl_Status,
  
  Appli_Light_CtlTemperature_Set,
  Appli_Light_CtlTemperature_Status,
  
  Appli_Light_CtlTemperature_Range_Set,
  Appli_Light_CtlTemperature_Range_Status,
  
  Appli_Light_CtlDefault_Set,
  Appli_Light_CtlDefault_Status,
  
  Appli_Light_Hsl_Set,
  Appli_Light_Hsl_Status,
  
  Appli_Light_HslHue_Set,
  Appli_Light_HslHue_Status,
  
  Appli_Light_HslSaturation_Set,
  Appli_Light_HslSaturation_Status,
  
  Appli_Light_HslDefault_Set,
  Appli_Light_HslDefault_Status,
  
  Appli_Light_HslRange_Set,
  Appli_Light_HslRange_Status
};

__attribute__((aligned(4))) 
const light_lc_client_cb_t AppliLightLcClient_cb = 
{
  Appli_LightLCc_ModeStatus,
  Appli_LightLCc_OmStatus,
  Appli_LightLCc_OnOffStatus,
  Appli_LightLCc_PropertyStatus
};

__attribute__((aligned(4))) 
const MODEL_SIG_cb_t Model_SIG_cb[] = 
{
#ifdef ENABLE_GENERIC_MODEL_SERVER  
  {
    GenericModelServer_GetOpcodeTableCb,
    GenericModelServer_GetStatusRequestCb,
    GenericModelServer_ProcessMessageCb
  },
#endif

#ifdef ENABLE_LIGHT_MODEL_SERVER
  {
    LightModelServer_GetOpcodeTableCb,
    LightModelServer_GetStatusRequestCb,
    LightModelServer_ProcessMessageCb
  },
#endif
  
#ifdef ENABLE_SENSOR_MODEL_SERVER
  {
    SensorModelServer_GetOpcodeTableCb,
    SensorModelServer_GetStatusRequestCb,
    SensorModelServer_ProcessMessageCb
  },
#endif
  
#ifdef ENABLE_TIME_SCENE_MODEL_SERVER
  {
    Time_SceneModelServer_GetOpcodeTableCb,
    Time_SceneModelServer_GetStatusRequestCb,
    Time_SceneModelServer_ProcessMessageCb
  },
#endif
  
#ifdef ENABLE_LIGHT_MODEL_SERVER_LC
  {
    LightLcServer_GetOpcodeTableCb,
    LightLcServer_GetStatusRequestCb,
    LightLcServer_ProcessMessageCb
  },
#endif
  
#ifdef ENABLE_GENERIC_MODEL_CLIENT
  {
    GenericModelClient_GetOpcodeTableCb,
    GenericModelClient_GetStatusRequestCb,
    GenericModelClient_ProcessMessageCb
  },
#endif
  
#ifdef ENABLE_CONFIG_MODEL_CLIENT
  {
    ConfigClientModel_GetOpcodeTableCb,
    ConfigClientModel_GetStatusRequestCb,
    ConfigClientModel_ProcessMessageCb
  },
#endif

#ifdef ENABLE_LIGHT_MODEL_CLIENT
  {
    LightModelClient_GetOpcodeTableCb,
    LightModelClient_GetStatusRequestCb,
    LightModelClient_ProcessMessageCb
  },
#endif  
  
#ifdef ENABLE_SENSOR_MODEL_CLIENT
  {
    SensorsModelClient_GetOpcodeTableCb,
    SensorsModelClient_GetStatusRequestCb,
    SensorsModelClient_ProcessMessageCb
  },
#endif    
  {
    0, 0, 0 
  }
};

__attribute__((aligned(4))) 
const APPLI_SAVE_MODEL_STATE_CB SaveModelState_cb = AppliNvm_SaveModelState;
__attribute__((aligned(4))) 
const APPLI_SAVE_MODEL_TEST_STATE_CB SaveModelTestState_cb = AppliNVM_Save_FlashTesting;
__attribute__((aligned(4))) 
const APPLI_RETRIEVE_MODEL_TEST_STATE_CB RetrieveModelTestState_cb = AppliNVM_Retrieve_FlashTesting;

#define MODEL_SIG_COUNT ( ( sizeof(Model_SIG_cb)/sizeof(Model_SIG_cb[0]) - 1 ))

__attribute__((aligned(4))) 
const MODEL_Vendor_cb_t Model_Vendor_cb[] = 
{
#ifdef ENABLE_VENDOR_MODEL_SERVER  
  {
    VendorModel_PID1_GetOpcodeTableCb,
    VendorModel_PID1_GetStatusRequestCb,
    VendorModel_PID1_ProcessMessageCb
  },
#endif  
  { 0, 0,0 }
};

#define MODEL_VENDOR_COUNT ( ( sizeof(Model_Vendor_cb)/sizeof(Model_Vendor_cb[0]) - 1 )) 

extern MOBLEUINT8 NumberOfElements;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void GetApplicationVendorModels(const MODEL_Vendor_cb_t** pModelsTable, MOBLEUINT32* VendorModelscount)
{
  *pModelsTable = Model_Vendor_cb;
  *VendorModelscount = MODEL_VENDOR_COUNT;
  
   TRACE_M(TF_VENDOR_M,"GetApplicationVendorModels \r\n");
}

/**
* @brief  Initialization Commands for Models
* @param  void
* @retval void
*/    
void BluenrgMesh_ModelsInit(void)
{
  MOBLEUINT8 modelStateLoad_Size;
  MOBLEUINT8 modelStateLoadBuff[APP_NVM_MODEL_SIZE];    
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;

#ifdef ENABLE_NVM_TEST	
  /* Testing of flash code */
  Device_FlashTesting();
#endif

  /* Inintialise the light model range states with default values */
  BluenrgMesh_ModelsDefaultValueInit();

  /* Callbacks used by BlueNRG-Mesh Models */
 result = BluenrgMesh_SetSIGModelsCbMap(Model_SIG_cb, MODEL_SIG_COUNT);
  if(MOBLE_FAILED(result))
  {
    TRACE_I(TF_INIT,"BluenrgMesh models init failed \r\n");
    while (1)
    {
      Appli_LedBlink();
    }
  }

#ifdef ENABLE_SENSOR_MODEL_SERVER
  Appli_Sensor_Init();  

#endif





#ifdef ENABLE_LIGHT_MODEL_SERVER_LC  
  Appli_Light_LCs_Init();
  
  if(MOBLE_FAILED(result))
  {     
    TRACE_I(TF_INIT, "Light LC model init failed\r\n");
    while (1)
    {
      Appli_LedBlink();
    }    
  }  
#endif

  /* Load generic model states from nvm */
  AppliNvm_LoadModelState(modelStateLoadBuff, &modelStateLoad_Size);
   if (modelStateLoad_Size != 0)
   {
    /* update states of generic model */
     Model_RestoreStates(modelStateLoadBuff, modelStateLoad_Size);
  }  
}

/**
* @brief  Process Commands for Models
* @param  void
* @retval void
*/    
void BluenrgMesh_ModelsProcess(void)
{
#ifdef ENABLE_GENERIC_MODEL_SERVER  
  Generic_Process();
#endif

#ifdef ENABLE_LIGHT_MODEL_SERVER  
  Lighting_Process();
#endif

#ifdef ENABLE_VENDOR_MODEL_SERVER  
  Vendor_Process();
#endif
#if defined ENABLE_SENSOR_MODEL_SERVER 
  Sensor_Process();
#endif

#if ENABLE_APPLI_TEST  
  Test_Process();
#endif   
 #ifdef ENABLE_SAVE_MODEL_STATE_NVM  
  ModelSave_Process();
#endif
  
#ifdef ENABLE_LIGHT_MODEL_SERVER_LC   
  Light_LC_Process();
#endif 
}

/**
* @brief  Publish Command for Models
* @param  void
* @retval void
*/    
void BluenrgMesh_ModelsCommand(void)
{
#ifdef VENDOR_SERVER_MODEL_PUBLISH     
  Appli_Vendor_Publish(BluenrgMesh_GetAddress());
#endif
  
#if defined(GENERIC_CLIENT_MODEL_PUBLISH) || defined(LIGHT_CLIENT_MODEL_PUBLISH) 
      Led_Value ^= APPLI_LED_ON;
  pGeneric_OnOffParam[0] = Led_Value;    /* OnOff parameter byte 0 : The target value of the Generic Onoff state */  
  
  pLightLCModeParam[0] = Led_Value;
  pLightLCOccupancyModeParam[0] = Led_Value;
  pLightLCOnOffParam[0] = Led_Value;
  
  /*This Switch-case allows to quickly set the different Models Messages parameters in order to demonstrate Client APIs functionning */
      switch (ButtonIndex_Value){
      case 0:
        ButtonIndex_Value=0x1;
        
    pGeneric_LevelParam[0]= 0xE8;           /* Level parameter byte 0 : The target value of the Generic Level state */
    pGeneric_LevelParam[1]= 0x03;           /* Level parameter byte 1 : The target value of the Generic Level state */
        
    pGeneric_DeltaLevelParam[0]= 0xE8;      /* Delta Level parameter byte 0 : The Delta change of the Generic Level state */
    pGeneric_DeltaLevelParam[1]= 0x03;      /* Delta Level parameter byte 1 : The Delta change of the Generic Level state */
    pGeneric_DeltaLevelParam[2]= 0x00;      /* Delta Level parameter byte 2 : The Delta change of the Generic Level state */
    pGeneric_DeltaLevelParam[3]= 0x00;      /* Delta Level parameter byte 3 : The Delta change of the Generic Level state */
        
    pGeneric_MoveLevelParam[0]= 0xE8;       /*Move Delta Level parameter byte 0 : The Delta Level step to calculate Move speed for the Generic Level state */
    pGeneric_MoveLevelParam[1]= 0x03;       /*Move Delta  Level parameter byte 1 : The Delta Level step to calculate Move speed for the Generic Level state */
        
    pGeneric_DefaultTransitionTimeParam[0]=0x0F;    /*Transition time parameter byte 0 : The value of the Generic Default Transition Time state */
        
    pGeneric_PowerOnOffParam[0]=0x1;        /*OnPowerUp parameter byte 0 : The value of the Generic OnPowerUp state */
        
    pLightnessParam[0] = 0xE8;              /*Lightness parameter byte 0 : The target value of the Light Lightness Actual/Linear/Default state */
    pLightnessParam[1] = 0x03;              /*Lightness parameter byte 1 : The target value of the Light Lightness Actual/Linear/Default state */
        
    pLightnessRangeParam[0] = 0xE8;         /*Lightness Range Min parameter byte 0 : The value of the Lightness Range Min field of the Light Lightness Range state */
    pLightnessRangeParam[1] = 0x03;         /*Lightness Range Min parameter byte 1 : The value of the Lightness Range Min field of the Light Lightness Range state */
    pLightnessRangeParam[2] = 0x88;         /*Lightness Range Max parameter byte 0 : The value of the Lightness Range Max field of the Light Lightness Range state */
    pLightnessRangeParam[3] = 0x13;         /*Lightness Range Max parameter byte 1 : The value of the Lightness Range Max field of the Light Lightness Range state */
                
    pLightCtlParam[0] = 0xE8;               /*CTL Lightness parameter byte 0 : The target value of the Light CTL Lightness state */
    pLightCtlParam[1] = 0x03;               /*CTL Lightness parameter byte 1 : The target value of the Light CTL Lightness state */
    pLightCtlParam[2] = 0xE8;               /*CTL Temperature parameter byte 0 : The target value of the Light CTL Temperature state */
    pLightCtlParam[3] = 0x03;               /*CTL Temperature parameter byte 1 : The target value of the Light CTL Temperature state */
    pLightCtlParam[4] = 0xE8;               /*CTL Delta UV parameter byte 0 : The target value of the Light CTL Delta UV state */
    pLightCtlParam[5] = 0x03;               /*CTL Delta UV parameter byte 1 : The target value of the Light CTL Delta UV state */
                
    pLightCtlTemperatureParam[0] = 0xE8;    /*CTL Temperature parameter byte 0 : The target value of the Light CTL Temperature state */
    pLightCtlTemperatureParam[1] = 0x03;    /*CTL Temperature parameter byte 1 : The target value of the Light CTL Temperature state */
    pLightCtlTemperatureParam[2] = 0xE8;    /*CTL Delta UV parameter byte 0 : The target value of the Light CTL Delta UV state */
    pLightCtlTemperatureParam[3] = 0x03;    /*CTL Delta UV parameter byte 1 : The target value of the Light CTL Delta UV state */
        
    pLightCtlTemperatureRangeParam[0] = 0xE8;       /*Temperature Range Min parameter byte 0 : The value of the Temperature Range Min field of the Light CTL Temperature Range state */
    pLightCtlTemperatureRangeParam[1] = 0x03;       /*Temperature Range Min parameter byte 1 : The value of the Temperature Range Min field of the Light CTL Temperature Range state */
    pLightCtlTemperatureRangeParam[2] = 0x88;       /*Temperature Range Max parameter byte 0 : The value of the Temperature Range Max field of the Light CTL Temperature Range state */
    pLightCtlTemperatureRangeParam[3] = 0x13;       /*Temperature Range Max parameter byte 1 : The value of the Temperature Range Max field of the Light CTL Temperature Range state */
        
    pLightCtlDefaultParam[0] = 0xE8;        /*CTL Lightness parameter byte 0 : The target value of the Light CTL Lightness Default state */
    pLightCtlDefaultParam[1] = 0x03;        /*CTL Lightness parameter byte 1 : The target value of the Light CTL Lightness Default state */
    pLightCtlDefaultParam[2] = 0xE8;        /*CTL Temperature parameter byte 0 : The target value of the Light CTL Temperature Default state */
    pLightCtlDefaultParam[3] = 0x03;        /*CTL Temperature parameter byte 1 : The target value of the Light CTL Temperature Default state */
    pLightCtlDefaultParam[4] = 0xE8;        /*CTL Delta UV parameter byte 0 : The target value of the Light CTL Delta UV Default state */
    pLightCtlDefaultParam[5] = 0x03;        /*CTL Delta UV parameter byte 1 : The target value of the Light CTL Delta UV Default state */
        
    pLightHslParam[0] = 0xE8;               /*HSL Lightness parameter byte 0 : The target value of the Light HSL Lightness state */
    pLightHslParam[1] = 0x03;               /*HSL Lightness parameter byte 1 : The target value of the Light HSL Lightness state */
    pLightHslParam[2] = 0xE8;               /*HSL Hue parameter byte 0 : The target value of the Light HSL Hue state */
    pLightHslParam[3] = 0x03;               /*HSL Hue parameter byte 1 : The target value of the Light HSL Hue state */
    pLightHslParam[4] = 0xE8;               /*HSL Saturation parameter byte 0 : The target value of the Light HSL Saturation state */
    pLightHslParam[5] = 0x03;               /*HSL Saturation parameter byte 1 : The target value of the Light HSL Saturation state */
        
    pLightHslRangeParam[0] = 0xE8;          /*HSL Hue Range Min parameter byte 0 : The value of the Hue Range Min field of the Light HSL Hue Range state */
    pLightHslRangeParam[1] = 0x03;          /*HSL Hue Range Min parameter byte 1 : The value of the Hue Range Min field of the Light HSL Hue Range state */
    pLightHslRangeParam[2] = 0x88;          /*HSL Hue Range Max parameter byte 0 : The value of the Hue Range Max field of the Light HSL Hue Range state */
    pLightHslRangeParam[3] = 0x13;          /*HSL Hue Range Max parameter byte 1 : The value of the Hue Range Max field of the Light HSL Hue Range state */
    pLightHslRangeParam[4] = 0x88;          /*HSL Saturation Min parameter byte 0 : The value of the Saturation Range Min field of the Light HSL Saturation Range state */
    pLightHslRangeParam[5] = 0x13;          /*HSL Saturation Min parameter byte 1 : The value of the Saturation Range Min field of the Light HSL Saturation Range state */
    pLightHslRangeParam[6] = 0x70;          /*HSL Saturation Max parameter byte 0 : The value of the Saturation Range Max field of the Light HSL Saturation Range state */
    pLightHslRangeParam[7] = 0x17;          /*HSL Saturation Max parameter byte 1 : The value of the Saturation Range Max field of the Light HSL Saturation Range state */
        
    pLightHslHueParam[0] = 0xE8;            /*HSL Hue parameter byte 0 : The target value of the Light HSL Hue state */
    pLightHslHueParam[1] = 0x03;            /*HSL Hue parameter byte 1 : The target value of the Light HSL Hue state */
    
    pLightHslSaturationParam[0] = 0xE8;     /*HSL Saturation parameter byte 0 : The target value of the Light HSL Saturation state */
    pLightHslSaturationParam[1] = 0x03;     /*HSL Saturation parameter byte 1 : The target value of the Light HSL Saturation state */
        break;
        
      case 1:
        ButtonIndex_Value=0x2;
        
    pGeneric_LevelParam[0]= 0xff;           /* Level parameter byte 0 : The target value of the Generic Level state */
    pGeneric_LevelParam[1]= 0x7f;           /* Level parameter byte 1 : The target value of the Generic Level state */
        
    pGeneric_DeltaLevelParam[0]= 0x10;      /* Delta Level parameter byte 0 : The Delta change of the Generic Level state */
    pGeneric_DeltaLevelParam[1]= 0x27;      /* Delta Level parameter byte 1 : The Delta change of the Generic Level state */
    pGeneric_DeltaLevelParam[2]= 0x00;      /* Delta Level parameter byte 2 : The Delta change of the Generic Level state */
    pGeneric_DeltaLevelParam[3]= 0x00;      /* Delta Level parameter byte 3 : The Delta change of the Generic Level state */
    
    pGeneric_MoveLevelParam[0]= 0xff;       /*Move Delta Level parameter byte 0 : The Delta Level step to calculate Move speed for the Generic Level state */
    pGeneric_MoveLevelParam[1]= 0x7f;       /*Move Delta  Level parameter byte 1 : The Delta Level step to calculate Move speed for the Generic Level state */
                
    pGeneric_DefaultTransitionTimeParam[0]=0x10;    /*Transition time parameter byte 0 : The value of the Generic Default Transition Time state */
        
    pGeneric_PowerOnOffParam[0]=0x2;        /*OnPowerUp parameter byte 0 : The value of the Generic OnPowerUp state. */
        
    pLightnessParam[0] = 0xff;              /*Lightness parameter byte 0 : The target value of the Light Lightness Actual/Linear/Default state */
    pLightnessParam[1] = 0xff;              /*Lightness parameter byte 1 : The target value of the Light Lightness Actual/Linear/Default state */
        
    pLightnessRangeParam[0] = 0x00;         /*Lightness Range Min parameter byte 0 : The value of the Lightness Range Min field of the Light Lightness Range state */
    pLightnessRangeParam[1] = 0x00;         /*Lightness Range Min parameter byte 1 : The value of the Lightness Range Min field of the Light Lightness Range state */
    pLightnessRangeParam[2] = 0xff;         /*Lightness Range Max parameter byte 0 : The value of the Lightness Range Max field of the Light Lightness Range state */
    pLightnessRangeParam[3] = 0xff;         /*Lightness Range Max parameter byte 1 : The value of the Lightness Range Max field of the Light Lightness Range state */
        
    pLightCtlParam[0] = 0xff;               /*CTL Lightness parameter byte 0 : The target value of the Light CTL Lightness state */
    pLightCtlParam[1] = 0xff;               /*CTL Lightness parameter byte 1 : The target value of the Light CTL Lightness state */
    pLightCtlParam[2] = 0x20;               /*CTL Temperature parameter byte 0 : The target value of the Light CTL Temperature state */
    pLightCtlParam[3] = 0x4e;               /*CTL Temperature parameter byte 1 : The target value of the Light CTL Temperature state */
    pLightCtlParam[4] = 0xff;               /*CTL Delta UV parameter byte 0 : The target value of the Light CTL Delta UV state */
    pLightCtlParam[5] = 0x7f;               /*CTL Delta UV parameter byte 1 : The target value of the Light CTL Delta UV state */
        
    pLightCtlTemperatureParam[0] = 0x20;    /*CTL Temperature parameter byte 0 : The target value of the Light CTL Temperature state */
    pLightCtlTemperatureParam[1] = 0x4e;    /*CTL Temperature parameter byte 1 : The target value of the Light CTL Temperature state */
    pLightCtlTemperatureParam[2] = 0xff;    /*CTL Delta UV parameter byte 0 : The target value of the Light CTL Delta UV state */
    pLightCtlTemperatureParam[3] = 0x7f;    /*CTL Delta UV parameter byte 1 : The target value of the Light CTL Delta UV state */
        
    pLightCtlTemperatureRangeParam[0] = 0x19;       /*Temperature Range Min parameter byte 0 : The value of the Temperature Range Min field of the Light CTL Temperature Range state */
    pLightCtlTemperatureRangeParam[1] = 0x4e;       /*Temperature Range Min parameter byte 1 : The value of the Temperature Range Min field of the Light CTL Temperature Range state */
    pLightCtlTemperatureRangeParam[2] = 0x20;       /*Temperature Range Max parameter byte 0 : The value of the Temperature Range Max field of the Light CTL Temperature Range state */
    pLightCtlTemperatureRangeParam[3] = 0x4e;       /*Temperature Range Max parameter byte 1 : The value of the Temperature Range Max field of the Light CTL Temperature Range state */
        
    pLightCtlDefaultParam[0] = 0xff;        /*CTL Lightness parameter byte 0 : The target value of the Light CTL Lightness Default state */
    pLightCtlDefaultParam[1] = 0xff;        /*CTL Lightness parameter byte 1 : The target value of the Light CTL Lightness Default state */
    pLightCtlDefaultParam[2] = 0x20;        /*CTL Temperature parameter byte 0 : The target value of the Light CTL Temperature Default state */
    pLightCtlDefaultParam[3] = 0x4e;        /*CTL Temperature parameter byte 1 : The target value of the Light CTL Temperature Default state */
    pLightCtlDefaultParam[4] = 0xff;        /*CTL Delta UV parameter byte 0 : The target value of the Light CTL Delta UV Default state */
    pLightCtlDefaultParam[5] = 0x7f;        /*CTL Delta UV parameter byte 1 : The target value of the Light CTL Delta UV Default state */
        
    pLightHslParam[0] = 0xff;               /*HSL Lightness parameter byte 0 : The target value of the Light HSL Lightness state */
    pLightHslParam[1] = 0xff;               /*HSL Lightness parameter byte 1 : The target value of the Light HSL Lightness state */
    pLightHslParam[2] = 0xee;               /*HSL Hue parameter byte 0 : The target value of the Light HSL Hue state */
    pLightHslParam[3] = 0xee;               /*HSL Hue parameter byte 1 : The target value of the Light HSL Hue state */
    pLightHslParam[4] = 0xdd;               /*HSL Saturation parameter byte 0 : The target value of the Light HSL Saturation state */
    pLightHslParam[5] = 0xdd;               /*HSL Saturation parameter byte 1 : The target value of the Light HSL Saturation state */
       
    pLightHslRangeParam[0] = 0x00;          /*HSL Hue Range Min parameter byte 0 : The value of the Hue Range Min field of the Light HSL Hue Range state */
    pLightHslRangeParam[1] = 0xf0;          /*HSL Hue Range Min parameter byte 1 : The value of the Hue Range Min field of the Light HSL Hue Range state */
    pLightHslRangeParam[2] = 0xff;          /*HSL Hue Range Max parameter byte 0 : The value of the Hue Range Max field of the Light HSL Hue Range state */
    pLightHslRangeParam[3] = 0xff;          /*HSL Hue Range Max parameter byte 1 : The value of the Hue Range Max field of the Light HSL Hue Range state */
    pLightHslRangeParam[4] = 0x00;          /*HSL Saturation Min parameter byte 0 : The value of the Saturation Range Min field of the Light HSL Saturation Range state */
    pLightHslRangeParam[5] = 0xe0;          /*HSL Saturation Min parameter byte 1 : The value of the Saturation Range Min field of the Light HSL Saturation Range state */
    pLightHslRangeParam[6] = 0xff;          /*HSL Saturation Max parameter byte 0 : The value of the Saturation Range Max field of the Light HSL Saturation Range state */
    pLightHslRangeParam[7] = 0xef;          /*HSL Saturation Max parameter byte 1 : The value of the Saturation Range Max field of the Light HSL Saturation Range state */
        
    pLightHslHueParam[0] = 0xff;            /*HSL Hue parameter byte 0 : The target value of the Light HSL Hue state */
    pLightHslHueParam[1] = 0xff;            /*HSL Hue parameter byte 1 : The target value of the Light HSL Hue state */
        
    pLightHslSaturationParam[0] = 0xff;     /*HSL Saturation parameter byte 0 : The target value of the Light HSL Saturation state */
    pLightHslSaturationParam[1] = 0xff;     /*HSL Saturation parameter byte 1 : The target value of the Light HSL Saturation state */
        break;
        
      case 2:
        ButtonIndex_Value=0x0;
        
    pGeneric_LevelParam[0]= 0x00;           /* Level parameter byte 0 : The target value of the Generic Level state */ 
    pGeneric_LevelParam[1]= 0x00;           /* Level parameter byte 1 : The target value of the Generic Level state */
        
    pGeneric_DeltaLevelParam[0]= 0x00;      /* Delta Level parameter byte 0 : The Delta change of the Generic Level state */
    pGeneric_DeltaLevelParam[1]= 0x00;      /* Delta Level parameter byte 1 : The Delta change of the Generic Level state */
    pGeneric_DeltaLevelParam[2]= 0x00;      /* Delta Level parameter byte 2 : The Delta change of the Generic Level state */
    pGeneric_DeltaLevelParam[3]= 0x00;      /* Delta Level parameter byte 3 : The Delta change of the Generic Level state */
        
    pGeneric_MoveLevelParam[0]= 0x00;       /*Move Delta Level parameter byte 0 : The Delta Level step to calculate Move speed for the Generic Level state */
    pGeneric_MoveLevelParam[1]= 0x00;       /*Move Delta  Level parameter byte 1 : The Delta Level step to calculate Move speed for the Generic Level state */
        
    pGeneric_DefaultTransitionTimeParam[0]=0x00;    /*Transition time parameter byte 0 : The value of the Generic Default Transition Time state */
        
    pGeneric_PowerOnOffParam[0]=0x0;        /*OnPowerUp parameter byte 0 : The value of the Generic OnPowerUp state. */
        
    pLightnessParam[0] = 0x00;              /*Lightness parameter byte 0 : The target value of the Light Lightness Actual/Linear/Default state */
    pLightnessParam[1] = 0x00;              /*Lightness parameter byte 1 : The target value of the Light Lightness Actual/Linear/Default state */
        
    pLightnessRangeParam[0] = 0x00;         /*Lightness Range Min parameter byte 0 : The value of the Lightness Range Min field of the Light Lightness Range state */
    pLightnessRangeParam[1] = 0x00;         /*Lightness Range Min parameter byte 1 : The value of the Lightness Range Min field of the Light Lightness Range state */
    pLightnessRangeParam[2] = 0x00;         /*Lightness Range Max parameter byte 0 : The value of the Lightness Range Max field of the Light Lightness Range state */
    pLightnessRangeParam[3] = 0x10;         /*Lightness Range Max parameter byte 1 : The value of the Lightness Range Max field of the Light Lightness Range state */
        
    pLightCtlParam[0] = 0x00;               /*CTL Lightness parameter byte 0 : The target value of the Light CTL Lightness state */
    pLightCtlParam[1] = 0x00;               /*CTL Lightness parameter byte 1 : The target value of the Light CTL Lightness state */
    pLightCtlParam[2] = 0x20;               /*CTL Temperature parameter byte 0 : The target value of the Light CTL Temperature state */
    pLightCtlParam[3] = 0x03;               /*CTL Temperature parameter byte 1 : The target value of the Light CTL Temperature state */
    pLightCtlParam[4] = 0x00;               /*CTL Delta UV parameter byte 0 : The target value of the Light CTL Delta UV state */
    pLightCtlParam[5] = 0x00;               /*CTL Delta UV parameter byte 1 : The target value of the Light CTL Delta UV state */
        
    pLightCtlTemperatureParam[0] = 0x20;    /*CTL Temperature parameter byte 0 : The target value of the Light CTL Temperature state */
    pLightCtlTemperatureParam[1] = 0x03;    /*CTL Temperature parameter byte 1 : The target value of the Light CTL Temperature state */
    pLightCtlTemperatureParam[2] = 0x00;    /*CTL Delta UV parameter byte 0 : The target value of the Light CTL Delta UV state */
    pLightCtlTemperatureParam[3] = 0x00;    /*CTL Delta UV parameter byte 1 : The target value of the Light CTL Delta UV state */
        
    pLightCtlTemperatureRangeParam[0] = 0x20;       /*Temperature Range Min parameter byte 0 : The value of the Temperature Range Min field of the Light CTL Temperature Range state */
    pLightCtlTemperatureRangeParam[1] = 0x03;       /*Temperature Range Min parameter byte 1 : The value of the Temperature Range Min field of the Light CTL Temperature Range state */
    pLightCtlTemperatureRangeParam[2] = 0x21;       /*Temperature Range Max parameter byte 0 : The value of the Temperature Range Max field of the Light CTL Temperature Range state */
    pLightCtlTemperatureRangeParam[3] = 0x03;       /*Temperature Range Max parameter byte 1 : The value of the Temperature Range Max field of the Light CTL Temperature Range state */
        
    pLightCtlDefaultParam[0] = 0x00;        /*CTL Lightness parameter byte 0 : The target value of the Light CTL Lightness Default state */
    pLightCtlDefaultParam[1] = 0x00;        /*CTL Lightness parameter byte 1 : The target value of the Light CTL Lightness Default state */
    pLightCtlDefaultParam[2] = 0x20;        /*CTL Temperature parameter byte 0 : The target value of the Light CTL Temperature Default state */
    pLightCtlDefaultParam[3] = 0x03;        /*CTL Temperature parameter byte 1 : The target value of the Light CTL Temperature Default state */
    pLightCtlDefaultParam[4] = 0x00;        /*CTL Delta UV parameter byte 0 : The target value of the Light CTL Delta UV Default state */
    pLightCtlDefaultParam[5] = 0x00;        /*CTL Delta UV parameter byte 1 : The target value of the Light CTL Delta UV Default state */
        
    pLightHslParam[0] = 0x00;               /*HSL Lightness parameter byte 0 : The target value of the Light HSL Lightness state */
    pLightHslParam[1] = 0x00;               /*HSL Lightness parameter byte 1 : The target value of the Light HSL Lightness state */
    pLightHslParam[2] = 0x00;               /*HSL Hue parameter byte 0 : The target value of the Light HSL Hue state */
    pLightHslParam[3] = 0x00;               /*HSL Hue parameter byte 1 : The target value of the Light HSL Hue state */
    pLightHslParam[4] = 0x00;               /*HSL Saturation parameter byte 0 : The target value of the Light HSL Saturation state */
    pLightHslParam[5] = 0x00;               /*HSL Saturation parameter byte 1 : The target value of the Light HSL Saturation state */
        
    pLightHslRangeParam[0] = 0x00;          /*HSL Hue Range Min parameter byte 0 : The value of the Hue Range Min field of the Light HSL Hue Range state */
    pLightHslRangeParam[1] = 0x00;          /*HSL Hue Range Min parameter byte 1 : The value of the Hue Range Min field of the Light HSL Hue Range state */
    pLightHslRangeParam[2] = 0x00;          /*HSL Hue Range Max parameter byte 0 : The value of the Hue Range Max field of the Light HSL Hue Range state */
    pLightHslRangeParam[3] = 0x10;          /*HSL Hue Range Max parameter byte 1 : The value of the Hue Range Max field of the Light HSL Hue Range state */
    pLightHslRangeParam[4] = 0x00;          /*HSL Saturation Min parameter byte 0 : The value of the Saturation Range Min field of the Light HSL Saturation Range state */
    pLightHslRangeParam[5] = 0x00;          /*HSL Saturation Min parameter byte 1 : The value of the Saturation Range Min field of the Light HSL Saturation Range state */
    pLightHslRangeParam[6] = 0x00;          /*HSL Saturation Max parameter byte 0 : The value of the Saturation Range Max field of the Light HSL Saturation Range state */
    pLightHslRangeParam[7] = 0x20;          /*HSL Saturation Max parameter byte 1 : The value of the Saturation Range Max field of the Light HSL Saturation Range state */
        
    pLightHslHueParam[0] = 0x00;            /*HSL Hue parameter byte 0 : The target value of the Light HSL Hue state */
    pLightHslHueParam[1] = 0x00;            /*HSL Hue parameter byte 1 : The target value of the Light HSL Hue state */
        
    pLightHslSaturationParam[0] = 0x00;     /*HSL Saturation parameter byte 0 : The target value of the Light HSL Saturation state */
    pLightHslSaturationParam[1] = 0x00;     /*HSL Saturation parameter byte 1 : The target value of the Light HSL Saturation state */
        break;
      
      default:
        break;
      }
      
      
#ifdef GENERIC_CLIENT_MODEL_PUBLISH  
      /** GENERIC ONOFF **/ 
/*      
      TRACE_M(TF_GENERIC_CLIENT_M, "----------- Generic API ONOFF SET ACK ------------- \r\n");
      Appli_GenericClient_API(0, GENERIC_ON_OFF_SET_ACK, pGeneric_OnOffParam); 
*/ 
      TRACE_M(TF_GENERIC_CLIENT_M, "----------- Generic API ONOFF SET UNACK ------------- \r\n");
      Appli_GenericClient_API(0, GENERIC_ON_OFF_SET_UNACK, pGeneric_OnOffParam);  
      
#endif
      
#endif  
}


/**
* @brief  Get the Element Number for selected Model 
* @param  dst_peer : Destination Address received
* @retval MOBLEUINT8 : elementNumber
*/ 
MOBLEUINT8 BluenrgMesh_ModelsGetElementNumber(MOBLE_ADDRESS dst_peer)
{
  
  MOBLE_ADDRESS nodeAddress;
  MOBLEUINT8 elementNumber;
  
  nodeAddress = BluenrgMesh_GetAddress();
  elementNumber = ((dst_peer - nodeAddress)+1);
  
  return elementNumber;
}

/**
* @brief  Get the Element Index for selected Model 
* @param  dst_peer : Destination Address received
* @retval MOBLEUINT8 : elementIndex
*/ 
MOBLEUINT8 BluenrgMesh_ModelsGetElementIndex(MOBLE_ADDRESS dst_peer)
{
  
  MOBLE_ADDRESS nodeAddress;
  MOBLEUINT8 elementIndex;
  
  nodeAddress = BluenrgMesh_GetAddress();
  elementIndex =(dst_peer - nodeAddress);
  
  return elementIndex;
}


/**
* @brief  Schedule a packet to be sent with randomized send timestamp  
*         If a que is empty, random timestamp is calculated
*         Subsequent packets are sent in sequence
* @param  *pmsgParam Pointer to structure of message header for parameters:
*          elementIndex, src, dst addresses, TTL, RSSI, NetKey & AppKey Offset
* @param  status:  Command status
* @param  data:    Data buffer.
* @param  length:  Length of data in bytes.
* @retval None
*/ 
void BluenrgMesh_ModelsDelayPacket(MODEL_MessageHeader_t *pmsgParams,
                              MOBLEUINT8 command, 
                              MOBLEUINT8 const * data, 
                              MOBLEUINT32 length)
{
  MOBLEUINT8 random_time[8];
  
  if (Appli_PendingPackets.packet_count == 0)
  {
    Appli_PendingPackets.packet_count = 1;
    hci_le_rand(random_time);
    Appli_PendingPackets.send_time = Clock_Time() + 
                                     DEFAULT_DELAY_PACKET_FROM + 
                                     (random_time[0] + random_time[1]*256)\
                                         %DEFAULT_DELAY_PACKET_RANDOM_TIME;    
    Appli_PendingPackets.head = Appli_PendingPackets.packet;
    Appli_PendingPackets.head_index = 0;	
    TRACE_M(TF_MISC, "Randomized time: %d\n\r", Appli_PendingPackets.send_time - Clock_Time());	
  }
  else 
  {
    Appli_PendingPackets.packet_count += 1;
    Appli_PendingPackets.packet_count = (Appli_PendingPackets.packet_count)%\
                                              (MAX_PENDING_PACKETS_QUE_SIZE+1);

    if (Appli_PendingPackets.head != (Appli_PendingPackets.packet + \
                                      MAX_PENDING_PACKETS_QUE_SIZE - 1))
    {
      Appli_PendingPackets.head = Appli_PendingPackets.head +1;
      Appli_PendingPackets.head_index = Appli_PendingPackets.head_index+1;
    }
    else
    {
      Appli_PendingPackets.head = Appli_PendingPackets.packet;
      Appli_PendingPackets.head_index = 0;
    }
  }  
  
  Appli_PendingPackets.head->peer = pmsgParams->peer_addr;
  Appli_PendingPackets.head->dst = pmsgParams->dst_peer;
  Appli_PendingPackets.head->elementIndex = pmsgParams->elementIndex;
  Appli_PendingPackets.head->appKeyOffset = pmsgParams->rcvdAppKeyOffset;
  Appli_PendingPackets.head->netKeyOffset = pmsgParams->rcvdNetKeyOffset;
  Appli_PendingPackets.head->command = command;
  Appli_PendingPackets.head->length = length;
  for (MOBLEUINT8 count=0; count<length; count++)
  Appli_PendingPackets.head->data[count] = data[count];
}   
  

/**
* @brief  If send timestamp is reached and que is not empty, send all packets
* @param  None
* @retval None
*/
void BluenrgMesh_ModelsSendDelayedPacket(void)
{
  APPLI_SEND_RESPONSE_MODULE* ptr;
  MODEL_MessageHeader_t msgParam;
  MOBLEUINT8 temp_index;
  
  if ((Appli_PendingPackets.packet_count != 0) && 
      (Appli_PendingPackets.send_time <= Clock_Time()))
  {
    for (MOBLEUINT8 count=Appli_PendingPackets.packet_count; count!=0; count--)
    {	
    TRACE_M(TF_MISC, "Sending randomized packets. Packet count: %d \n\r",\
    Appli_PendingPackets.packet_count - count + 1);   
      temp_index = ((Appli_PendingPackets.head_index+MAX_PENDING_PACKETS_QUE_SIZE+1)\
                                   -count)%MAX_PENDING_PACKETS_QUE_SIZE;
      ptr = Appli_PendingPackets.packet + temp_index;
      
      /* Initialize the messageParam*/
      msgParam.dst_peer = ptr->dst;
      msgParam.peer_addr = ptr->peer;
      msgParam.elementIndex = 0;
      msgParam.rcvdAppKeyOffset = 0;
      msgParam.rcvdNetKeyOffset = 0;
      msgParam.rssi = 0;
      msgParam.ttl = 0;
      
      BluenrgMesh_SendVendorApplicationResponse(VENDOR_STMICRO_CID, 
                               &msgParam,
                               ptr->command,
                               ptr->data,
                               ptr->length);
    }
    
    Appli_PendingPackets.packet_count = 0;
  }
}

/** \brief Set remote publication for the given Model ID & node Address
* User is responsible for serializing data into \a data buffer. Vendor_WriteLocalDataCb 
*                                  callback will be called on the remote device.
* @param modelId ID of the model. 
* @param srcAddress element Address of the Node
* @param command vendor model commands 
* @param data Data buffer.
* @param length Length of data in bytes.
* @param response If 'MOBLE_TRUE', used to get the response. If 'MOBLE_FALSE', no response 
* @return MOBLE_RESULT_SUCCESS on success.
*/
MOBLE_RESULT MeshClient_SetRemotePublication(MOBLEUINT32 modelId, MOBLEUINT16 elementIdx,
                                              MOBLEUINT16 msg_opcode, MOBLEUINT8 const *msg_buff, 
                                              MOBLEUINT32 length, MOBLEBOOL ack_flag,
                                              MOBLEUINT8 isVendor)
{
    MOBLE_ADDRESS srcAddress;
      
    srcAddress = BluenrgMesh_GetAddress();
    srcAddress += elementIdx;  /* Get the Address to send in the message */
    
    return BluenrgMesh_SetRemotePublication(modelId, 
                                            srcAddress ,
                                            msg_opcode , 
                                            msg_buff, length,
                                            ack_flag, 
                                            MOBLE_FALSE);
}

/**
* @brief  Convert ASCII value into Character
* @param  tempValue : 8bit value for conversion
* @retval MOBLEUINT8 
*/         
MOBLEUINT8 BluenrgMesh_ModelsASCII_To_Char(MOBLEUINT8 tempValue)
{
   tempValue = tempValue - 0x30;
   return tempValue;
} 

__weak void Test_Process(void)
{
}
/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
