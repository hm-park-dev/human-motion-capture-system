/**
******************************************************************************
* @file    main.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   main file of the application
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
#include "appli_light.h"
#include "appli_config.h"
#include "appli_config_client.h"
#include "pal_nvm.h"
#include "models_if.h"
#include "mesh_cfg.h"
#include "appli_sensor.h"
#include "compiler.h"
#include "hci.h"
#ifdef STM32_BLUENRG1
#include "bluenrg1_hci_le.h"
#include "bluenrg1_hal_aci.h"
#else
#include "hci_le.h"
#endif
#include "stm32_bluenrg_ble.h"
#include "bluenrg_mesh.h"

/** @addtogroup ST_BLE_Mesh
 *  @{
 */

/** @addtogroup main_BlueNRG-MS
*  @{
*/

/* Private typedef -----------------------------------------------------------*/
/*-----------------------------------------------------------*/

/* WEAK FUNCTION  -----------------------------------------------------------*/
WEAK_FUNCTION(void Appli_GetAppKeyAddParamsCb(model_securityKeyParams_t* param)){}
WEAK_FUNCTION(void Appli_GetAppKeyDeleteParamsCb(model_securityKeyParams_t* param)) {}
WEAK_FUNCTION(void Appli_GetAppKeyListParamsCb(model_appKeyListParams_t* appKeyListParams)) {}
WEAK_FUNCTION(void Appli_GetAppKeyUpdateParamsCb(model_securityKeyParams_t* appKeyUpdatedParams)) {}
WEAK_FUNCTION(void Appli_GetNetKeyAddParamsCb(model_securityKeyParams_t* netKeyAddParams)) {} 
WEAK_FUNCTION(void Appli_GetNetKeyDeleteParamsCb(model_securityKeyParams_t* netKeyDeleteParams)) {} 
WEAK_FUNCTION(void Appli_GetNetKeyListParamsCb(model_netKeyListParams_t* netKeyListParams)) {} 
WEAK_FUNCTION(void Appli_GetNetKeyUpdateParamsCb(model_securityKeyParams_t* netKeyUpdatedParams)) {} 
WEAK_FUNCTION(void Appli_GetAppKeyBindingParamsCb(model_appKeyBindingParams_t* appKeyBindParams)) {} 
WEAK_FUNCTION(void Appli_GetAppKeyUnBindingParamsCb(model_appKeyBindingParams_t* appKeyUnbindParams)) {} 
WEAK_FUNCTION(void Appli_GetSubDeleteParamsCb(model_subParams_t* subDeleteParams)) {} 
WEAK_FUNCTION(void Appli_GetSubOverwriteParamsCb(model_subParams_t* subOverwriteParams)) {} 
WEAK_FUNCTION(void Appli_GetPublicationSetParamsCb(model_publicationparams_t* pPubParameters)) {}
WEAK_FUNCTION(void Appli_GetPublicationGetParamsCb(model_publicationparams_t* pPubParameters)) {}
WEAK_FUNCTION(void Appli_GetSubAddParamsCb(model_subParams_t* param)) {}
/* Private define ------------------------------------------------------------*/

const MESH_USER_CB_MAP user_cb =
{  
  Appli_BleUnprovisionedIdentifyCb,
  Appli_BleSetUUIDCb,
  Appli_BleSetProductInfoCB,
  Appli_BleSetNumberOfElementsCb,
  Appli_BleDisableFilterCb
};

const MESH_BLE_CB_MAP ble_cb =
{
  Appli_BleStackInitCb,
  Appli_BleSetTxPowerCb,
  Appli_BleGattConnectionCompleteCb,
  Appli_BleGattDisconnectionCompleteCb,
};

const MOBLE_CONFIG_MODEL_CB_MAP config_model_cb = 
{
  Appli_GetAppKeyAddParamsCb,
  Appli_GetAppKeyDeleteParamsCb,
  Appli_GetAppKeyListParamsCb,
  Appli_GetAppKeyUpdateParamsCb,
  Appli_GetNetKeyAddParamsCb,
  Appli_GetNetKeyDeleteParamsCb,
  Appli_GetNetKeyListParamsCb,
  Appli_GetNetKeyUpdateParamsCb,
  Appli_GetAppKeyBindingParamsCb,
  Appli_GetAppKeyUnBindingParamsCb,
  Appli_GetSubAddParamsCb,
  Appli_GetSubDeleteParamsCb,
  Appli_GetSubOverwriteParamsCb,
  Appli_GetPublicationSetParamsCb,
  Appli_GetPublicationGetParamsCb
};

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* This structure contains Mesh library Initialisation info data */
const Mesh_Initialization_t BLEMeshlib_Init_params = {
  &DeviceNameParams,
  bdaddr,
  &TrParams,
  &FnParams,
  &LpnParams,
  &NeighborTableParams,
  BLUENRG_MESH_FEATURES,
  BLUENRG_MESH_PRVN_BEARER_INFO,
  &PrvnParams,
  &DynBufferParam
};
static MOBLEUINT8 uuid[16];

/* Private function prototypes -----------------------------------------------*/
void Appli_ConfigurationInfoDump(void);

static void MX_GPIO_Init(void);
/* Private functions ---------------------------------------------------------*/

/**
* @brief This function is the Main routine.
* @param  None
* @retval None
*/
int main(void)
{ 
  MOBLEUINT8 PrvnDevKeyFlag = 0;

  /* Device Initialization */
  InitDevice();
  MX_GPIO_Init(); 
  
  /* Check for valid Board Address */
  if (!Appli_CheckBdMacAddr())
  {  
    printf("Bad BD_MAC ADDR!\r\n");
    /* LED Blinks if BDAddr is not appropriate */
  
    while (1)
    {
      Appli_LedBlink();
    }
  }

  /* Set BLE configuration function call backs */
  BluenrgMesh_BleHardwareInitCallBack(&user_cb, &ble_cb);  
  /*Set BLE Config Model APIs callback*/
  BluenrgMesh_BleConfigModelInitCallBack(&config_model_cb);
    
  /* Initializes BlueNRG-Mesh Library */
  if (MOBLE_FAILED (BluenrgMesh_Init(&BLEMeshlib_Init_params) ))
  {   
    printf("Could not initialize BlueNRG-Mesh library!\r\n");   
    /* LED continuously blinks if library fails to initialize */
    while (1)
    {
      Appli_LedBlink();
    }
  }

  /*Checking if allocated Flash is able to save the required Buffer*/
  if((BluenrgMesh_GetBufferSize_Flash()) > 0x1000)
  {
    TRACE_I(TF_INIT, "Allocated Flash < Buffer Size!\r\n");   
    /* LED continuously blinks if allocated flash < buffer */
    while (1)
    {
      Appli_LedBlink();
    }    
    
  }
  
  /*Check SIG & VENDOR models limit*/
  if(MOBLE_FAILED(AppliCheck_EnabledModelsList()))
  {
    /* LED continuously blinks if library fails to initialize */
    while (1)
    {
      Appli_LedBlink();
    }
  }
  /* Initializes the Application */
  /* This function also checks for Power OnOff Cycles     
     Define the following Macro "ENABLE_UNPROVISIONING_BY_POWER_ONOFF_CYCLE" 
     to check the Power-OnOff Cycles
    5 Continous cycles of OnOff with Ontime <2 sec will cause unprovisioning
  */
  Appli_Init(&PrvnDevKeyFlag);
  
/* Check if Node is a Provisioner */
#if PROVISIONER_FEATURE
  
    Appli_StartProvisionerMode(PrvnDevKeyFlag);
    TRACE_I(TF_INIT, "Embedded Provisioner Address: [%04x] \n\r", BluenrgMesh_GetAddress());  
  
#else
  /* Checks if the node is already provisioned or not */
  if (BluenrgMesh_IsUnprovisioned() == MOBLE_TRUE)
  {
    BluenrgMesh_InitUnprovisionedNode(); /* Initalizes Unprovisioned node */
   
	 printf("Unprovisioned device \r\n");

#if PB_ADV_SUPPORTED
    BluenrgMesh_SetUnprovisionedDevBeaconInterval(100);
#endif    
  }
  else
  {
    BluenrgMesh_InitProvisionedNode();  /* Initalizes Provisioned node */      
    
    printf("Provisioned node \r\n");
  }
#endif  
    
/* Check to manually unprovision the board */
	Appli_CheckForUnprovision();
 
 /* Set attention timer callback */
  BluenrgMesh_SetAttentionTimerCallback(Appli_BleAttentionTimerCb);

#if TF_MISC
  Appli_ConfigurationInfoDump();
#endif  

  /* Prints the MAC Address of the board */ 
  printf("BlueNRG-Mesh Sensor Demo v1.4.0\n\r"); 
  printf("BlueNRG-Mesh Library v%s\n\r", BluenrgMesh_GetLibraryVersion()); 
  printf("BD_MAC Address = [%02x]:[%02x]:[%02x]:[%02x]:[%02x]:[%02x] \n\r",
          bdaddr[5],bdaddr[4],bdaddr[3],bdaddr[2],bdaddr[1],bdaddr[0]);
/* Set uuid for the board*/
  Appli_BleSetUUIDCb(uuid);
  printf("UUID = ");
  for(MOBLEUINT8 i=0;i<16;i++)
  {
    printf("[%02x] ",uuid[i]);
  }
  printf("\r\n");

/* Models intialization */  
  BluenrgMesh_ModelsInit();
  
  MX_MEMS_Init();  
  /* Main infinite loop */
  while(1)
  {
    BluenrgMesh_Process();
    BluenrgMesh_ModelsProcess(); /* Models Processing */
    Appli_Process();   
  }  
}


/**
* @brief This function is the Information dump function
* @param  None
* @retval None
*/
void Appli_ConfigurationInfoDump(void)
{
  
#ifdef APPLICATION_NUMBER_OF_ELEMENTS     
  /*TRACE_I(TF_MISC,"Number of Elements enabled in Application: %d \r\n", APPLICATION_NUMBER_OF_ELEMENTS);  */
#endif
  
#ifdef ENABLE_NEIGHBOR_TABLE
 /* TRACE_I(TF_MISC,"Neighbour Table is enabled \r\n");*/
#endif
  
/*  TRACE_I(TF_MISC,"********************\r\n\r\n");  */

}


/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PB10 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

#ifdef USE_FULL_ASSERT /* USE_FULL_ASSERT */
/**
* @brief This function is the assert_failed function.
* @param file
* @param line
* @note  Reports the name of the source file and the source line number
*        where the assert_param error has occurred.
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
  while (1)
  {
    SetLed(1);
    Clock_Wait(100);
    SetLed(0);
    Clock_Wait(100);
  }
}
#endif /* USE_FULL_ASSERT */
/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
