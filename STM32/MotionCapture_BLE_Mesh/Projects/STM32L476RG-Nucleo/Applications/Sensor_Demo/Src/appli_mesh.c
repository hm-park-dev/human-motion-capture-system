/**
******************************************************************************
* @file    appli_mesh.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Application interface for Mesh 
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
#include "bluenrg_mesh.h"
#ifdef STM32_BLUENRG1
#include "bluenrg1_aci.h"
#include "bluenrg1_hci_le.h"
#include "bluenrg1_hal_aci.h"
#else
#include "bluenrg_aci.h"
#include "hci_le.h"
#endif
#include <string.h>
#include "models_if.h"
#include "mesh_cfg.h"
#include "generic.h"
#include "appli_nvm.h"
#include "common.h"
#include "gp_timer.h"
#if defined (ENABLE_PROVISIONER_FEATURE) || defined(DYNAMIC_PROVISIONER)
#include "serial_prvn.h"
#endif
/** @addtogroup ST_BLE_Mesh
*  @{
*/

/** @addtogroup Application_Mesh_Models
*  @{
*/

/* Private define ------------------------------------------------------------*/

/*********** Macros to be modified according to the requirement *************/
#define BOUNCE_THRESHOLD                        20U
#define LONG_PRESS_THRESHOLD                    1000U
#define MANUAL_UNPROVISION_TIMER                3000U
#define FLASH_ERASE_TIME                        100U
#define DISCOVER_TIMER                          10*60*1000 /* 10 minutes */
#define DEFAULT_DELAY_PACKET_FROM               500U
#define DEFAULT_DELAY_PACKET_RANDOM_TIME        500U
#define USER_OUTPUT_OOB_APPLI_PROCESS           0U
#define INPUT_OOB_TIMEOUT                       300U /* input Oob30 Sec timeout*/
#define PBADV_UNPROV_DEV_BEACON_INTERVAL        100U /* 100 ms */

/* Private macro -------------------------------------------------------------*/
#define MAX_APPLI_BUFF_SIZE             8 
#define MAX_PENDING_PACKETS_QUE_SIZE    2
#define DATA_BUFFER_LENGTH              8
#define CUSTOM_BEACON_AD_TYPE           0x00
#define MAX_NUMB_ELEMENTS               1

/**********************Friendship callbacks macros ****************************/
#define FN_CLEARED_REPEAT_REQUEST   1
#define FN_CLEARED_POLL_TIMEOUT     2
#define FN_CLEARED_FRIEND_CLEAR     3
#define LPN_CLEARED_NO_RESPONSE     1

/* Private variables ---------------------------------------------------------*/

enum ButtonState
{
  BS_OFF,
  BS_DEBOUNCE,
  BS_SHORT_PRESS,
  BS_LONG_PRESS
};

enum ButtonState buttonState = BS_OFF;
tClockTime tBounce = 0;
MOBLEUINT8 Appli_LedState = 0;
MOBLEUINT16 IntensityValue = INTENSITY_LEVEL_ZERO;
MOBLEUINT8 IntensityFlag = FALSE;
MOBLEUINT8 ProvisionFlag = 0;


#ifdef ENABLE_AUTH_TYPE_OUTPUT_OOB
static MOBLEUINT8 PrvngInProcess = 0;
static MOBLEUINT32 OutputOobData = 0;
static MOBLEUINT32 OutputOobBlinkCount = 0;
#endif
#ifdef ENABLE_AUTH_TYPE_INPUT_OOB
MOBLEUINT8 InputOobData[8] = {0};
MOBLEUINT8 inputOOBDataReady = 0;
#endif

#if defined (ENABLE_PROVISIONER_FEATURE) || defined(DYNAMIC_PROVISIONER)
NodeUnderProvisionParam_t NodeUnderProvisionParam;
#endif

/*Number Of Elements selected per Node. Maximum Elements supported = 3*/
MOBLEUINT8 NumberOfElements = APPLICATION_NUMBER_OF_ELEMENTS;

#ifdef ENABLE_AUTH_TYPE_STATIC_OOB
/* 16 octets Static OOB information to be input here. Used during provisioning by Library */
const MOBLEUINT8 StaticOobBuff[SIZE_STATIC_OOB] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
#else
const MOBLEUINT8 StaticOobBuff[] = {0};
#endif

#ifdef PUB_KEY_TYPE_OOB
/* 64 octets Public Key information to be input here. It is only required for Public Key OOB case.
Used during provisioning by Library */
const MOBLEUINT8 PubKeyBuff[64] =  {0xF4, 0x65, 0xE4, 0x3F, 0xF2, 0x3D, 0x3F, 0x1B, 0x9D, 0xC7, 
0xDF, 0xC0, 0x4D, 0xA8, 0x75, 0x81, 0x84, 0xDB, 0xC9, 0x66, 0x20, 0x47, 0x96, 0xEC, 0xCF, 
0x0D, 0x6C, 0xF5, 0xE1, 0x65, 0x00, 0xCC, 0x02, 0x01, 0xD0, 0x48, 0xBC, 0xBB, 0xD8, 0x99, 
0xEE, 0xEF, 0xC4, 0x24, 0x16, 0x4E, 0x33, 0xC2, 0x01, 0xC2, 0xB0, 0x10, 0xCA, 0x6B, 0x4D, 
0x43, 0xA8, 0xA1, 0x55, 0xCA, 0xD8, 0xEC, 0xB2, 0x79};

/* 32 octets Private Key information to be input here. It is only required for Public Key OOB case.
Used during provisioning by Library */
const MOBLEUINT8 PrivKeyBuff[32] =  {0x52, 0x9A, 0xA0, 0x67, 0x0D, 0x72, 0xCD, 0x64, 0x97, 0x50, 
0x2E, 0xD4, 0x73, 0x50, 0x2B, 0x03, 0x7E, 0x88, 0x03, 0xB5, 0xC6, 0x08, 0x29, 0xA5, 0xA3, 
0xCA, 0xA2, 0x19, 0x50, 0x55, 0x30, 0xBA};
#else
const MOBLEUINT8 PubKeyBuff[] = NULL;
const MOBLEUINT8 PrivKeyBuff[] = NULL;
#endif



/* Select Node as Sniffer, Means able to sniff all the packets 
*  0 - Filters are enabled and packets not targeted to node are filtered
*  1 - Filters are disabled and packets not targeted to node are not filtered
*/
MOBLEUINT8 DisableFilter = 0;

#if LOW_POWER_FEATURE
MOBLEINT32 BluenrgMesh_sleepTime;
MOBLEUINT32 SysRefCount;
#endif

/* Timer to control unprovisioned device beacons */
#if PB_ADV_SUPPORTED
struct timer discoverTimer;
tClockTime discoverTimerinterval = DISCOVER_TIMER;
#endif

extern const MOBLEUINT8 _bdaddr[];

/********************* Application configuration **************************/
#if defined(__GNUC__) || defined(__IAR_SYSTEMS_ICC__) || defined(__CC_ARM)
MOBLEUINT8 bdaddr[8];


#ifdef INTERNAL_UNIQUE_NUMBER_MAC
static void Appli_GetMACfromUniqueNumber(void);
#endif 

extern const char _mobleNvmBase_data[];
const void *mobleNvmBase = _mobleNvmBase_data;
#else
#error "Unknown compiler"
#endif /* __GNUC__ || defined(__IAR_SYSTEMS_ICC__) || defined(__CC_ARM) */
/* Private function prototypes -----------------------------------------------*/
static void Appli_LongButtonPress(void);
static void Appli_ShortButtonPress(void);

/* Private functions ---------------------------------------------------------*/

/************************* Button Control functions ********************/
/**
* @brief  Function calls when a button is pressed for short duration  
* @param  void
* @retval void
*/ 
static void Appli_ShortButtonPress(void)
{
  BluenrgMesh_ModelsCommand();
}

/**
* @brief  Function calls when a button is pressed for Long duration  
* @param  void
* @retval void
*/ 
static void Appli_LongButtonPress(void)
{
  /* User Implementation */

}

/**
* @brief  Updates the button status  
* @param  int isPressed
* @retval void
*/ 
static void Appli_UpdateButtonState(int isPressed)
{
  /* Check for button state */
  switch (buttonState)
  {
    /* Case for Button State off */
  case BS_OFF:
    /* if button is pressed */
    if (isPressed)
    {
      buttonState = BS_DEBOUNCE;
      tBounce = Clock_Time();
    }
    break;
    
    /* Case for Button Debouncing */
  case BS_DEBOUNCE:
    if (isPressed)
    {
      /* Debouncing Delay check */
      if (Clock_Time() - tBounce > BOUNCE_THRESHOLD)
      {   
	  if (GetButtonState() == BUTTON_PRESSED)    
        buttonState = BS_SHORT_PRESS;
      }
      else
      {
        break;
      }
    }
    else
    {
      buttonState = BS_OFF;

    }
    break;
    /* Case if Button is pressed for small duration */
  case BS_SHORT_PRESS:
    if (isPressed && ((Clock_Time() - tBounce) > LONG_PRESS_THRESHOLD))
    {
      buttonState = BS_LONG_PRESS;
    }
    else
    {
      if (!isPressed)
      {
        Appli_ShortButtonPress();
      }

    }
    break;
    /* Case if Button is pressed for long duration */
  case BS_LONG_PRESS:
    if (!isPressed)
    {
      Appli_LongButtonPress();
    }
    break;
    /* Default case */
  default:
    buttonState = BS_OFF;
    break;
  }
  if (!isPressed)
  {
    buttonState = BS_OFF;
  }
}

/************************* LED Control functions ********************/
/**
* @brief  Controls the state of on board LED
* @param  void
* @retval void
*/ 
void Appli_LedCtrl(void)
{
  SetLed(Appli_LedState);
}

/************* BlueNRG-Mesh library callback functions ***************/

/**
* @brief  Blinks the on board LED  
* @param  none
* @retval MOBLE_RESULT status of result
*/ 
MOBLE_RESULT Appli_LedBlink(void)
{
  /* Switch On the LED */
  Appli_LedState = 1;
  Appli_LedCtrl();
  Clock_Wait(500);
  
  /* Switch Off the LED */
  Appli_LedState = 0;
  Appli_LedCtrl();
  Clock_Wait(500);
  
  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  Callback function Sets the state of the bulb 
* @param  MOBLEUINT16 ctrl which sets the lighting state of LED
* @retval MOBLE_RESULT status of result
*/ 
MOBLE_RESULT Appli_LedStateCtrlCb(MOBLEUINT16 ctrl)
{
  /* Switch On the LED */
  if(ctrl > 0)
  {
    Appli_LedState = 1;
  }
  /* Switch Off the LED */
  else
  {
    Appli_LedState = 0;
  }
  
  Appli_LedCtrl();
  
  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  initializes BlueNRG Stack    
* @param  none
* @retval MOBLE_RESULT status of result
*/ 
MOBLE_RESULT Appli_BleStackInitCb()
{
  /* BTLE Stack initialization */
  /* Not Required in BlueNRG-MS */
  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  Sets transmission power of RF 
* @param  none
* @retval MOBLE_RESULT status of result
*/ 
MOBLE_RESULT Appli_BleSetTxPowerCb(void)
{
   tBleStatus status;
  /* API to change the Transmission power of BlueNRG Device */
  /* uint8_t en_high_power, uint8_t pa_level
  en_high_power Can be only 0 or 1. Set high power bit on or off.
  pa_level Can be from 0 to 7. Set the PA level value
  */ 
  status = aci_hal_set_tx_power_level(POWER_LEVEL_HIGH, TX_POWER_LEVEL_PLUS_4DBM);
  if (status)
    return MOBLE_RESULT_FAIL;
  else
    return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  SET UUID value 
* @param  uuid_prefix_data : Pointer of UUID buffer data
* @retval MOBLE_RESULT status of result
*/ 
MOBLE_RESULT Appli_BleSetUUIDCb(MOBLEUINT8 *uuid_prefix_data)
{
  /* UUID is 128 bits (16 bytes) and can guarantee uniqueness across space and time.
     It can be ?Time-based ? UUID or ?truly-random or pseudo-random numbers?
 
     In this buffer user need to fill 10 bytes of UUID data. 
     Remaining 6 bytes, library fill this data with BDaddress.

    For example :
        F81D4FAE-7DEC-XBC4-Y12F-17D1AD07A961 (16 bytes)
        <any number> |_|  |_|   <BDAddress>

      X = 1 i.e. ?Time Base UUID? 
      X = 4 i.e. ?Random Number?
      Y = 4 i.e. Conforming to the current spec 
    For UUID information refer RFC4122
  */
  
  /* copy UUID prefix data*/
  uint8_t uuid_buff[10] = {0xF8,0x1D,0x4F,0xAE,0x7D,0xEC};/*random value by user */

   uuid_buff[6] = 0x4B;  /* 0x4B => 4 : Random */
   uuid_buff[7] = 'S' ;  /* User define value */
   uuid_buff[8] = 0xA1;  /* 0xA1 => A : Conforming to the current Spec */
   uuid_buff[9] = 'T' ;  /* User define value */  

   memcpy(uuid_prefix_data,uuid_buff,sizeof(uuid_buff));
   memcpy(&uuid_prefix_data[10],bdaddr,6);  /* Copy bdaddr to last 6 bytes of UUID */
   return MOBLE_RESULT_SUCCESS;
}


/**
* @brief  SET CID , PID and VID values 
* @param  company_product_info : vendor fill product information in this buffer
* @retval MOBLE_RESULT status of result
*/
MOBLE_RESULT Appli_BleSetProductInfoCB(MOBLEUINT8 *company_product_info)
{
  /* CID : provide 16-bit company identifier assigned by the Bluetooth SIG */
  uint16_t company_id                   = COMPANY_ID;
  
  /* PID : Provide 16-bit vendor-assigned product identifier */
  uint16_t product_id                   = PRODUCT_ID;
  
  /* VID : Provide 16-bit vendor-assigned product version identifier*/
  uint16_t product_version_id           = PRODUCT_VERSION_ID;
  
  memcpy(company_product_info + 0,(void *)&company_id,sizeof(company_id));
  memcpy(company_product_info + 2 ,(void *)&product_id,sizeof(product_id));
  memcpy(company_product_info + 4 ,(void *)&product_version_id,sizeof(product_version_id));
  
  return MOBLE_RESULT_SUCCESS;
}


/**
* @brief  Call back function called when GATT Connection Created  
* @param  none
* @retval none
*/ 
void Appli_BleGattConnectionCompleteCb(void)
{ 
  ProvisionFlag = 1;
  /* Proxy Node, will be called whenever Gatt connection is established */

}

/**
* @brief  Call back function called when GATT Disconnection Complete  
* @param  none
* @retval none
*/ 
void Appli_BleGattDisconnectionCompleteCb(void)
{ 
  /* Proxy Node, will be called whenever Gatt disconnected */

  ProvisionFlag = 0;
   
}

/**
* @brief Unprovisioned Node Identification
* @param MOBLEUINT8 data 
* @retval none
*/
void Appli_BleUnprovisionedIdentifyCb(MOBLEUINT8 data)
{
#ifdef ENABLE_AUTH_TYPE_OUTPUT_OOB
  PrvngInProcess = 1;  
#endif
  TRACE_M(TF_PROVISION,"Unprovisioned Node Identifier received: %02x\n\r", data);    
}

/**
* @brief  Set Number of Elements in a Node
* @param  none
* @retval Sending the value to BLE Mesh Library
*/ 
MOBLEUINT8 Appli_BleSetNumberOfElementsCb(void)
{
  if(NumberOfElements > BluenrgMesh_GetNumberOfElements())
  {
   // TRACE_M(TF_MISC,"In version 1.11.000 one Element per node is supported!\r\n"); 
    return BluenrgMesh_GetNumberOfElements();
  }

  else if(NumberOfElements == 0)
  {
   // TRACE_M(TF_MISC, "Number Of Elements must be 1 or greater than 1!\r\n"); 
    return 1;
  }
  
  else
  {
  return NumberOfElements;
  }
}

/**
* @brief  Sets the Attention Timer Callback function
* @param  none
* @retval MOBLE_RESULT status of result
*/ 
MOBLE_RESULT Appli_BleAttentionTimerCb(void)
{
/* avoid printf, if low power feature is supported */ 
  #if !defined(DISABLE_TRACES)
  printf("Attention timer callback received \r\n");
  #endif
  
  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  Call back function to give Output OOB information 
* @param  MOBLEUINT8* output_oob
* @param  MOBLEUINT8 size
* @retval void
*/ 
void Appli_BleOutputOOBAuthCb(MOBLEUINT8* output_oob, MOBLEUINT8 size)
{
#ifdef ENABLE_AUTH_TYPE_OUTPUT_OOB
  uint32_t ooBData = 0;    
    for (MOBLEUINT8 i = 0; i < size; i++)
    {
        ooBData |= (output_oob[i] << 8*i);
    }
    OutputOobData = ooBData;
   // TRACE_M(TF_PROVISION,"Output OOB information for provisioner: %d\n\r", ooBData);   
#endif
}

#ifdef ENABLE_AUTH_TYPE_OUTPUT_OOB
/**
* @brief  Process for both output and Input OOB handling
* @param  void
* @retval void
*/ 
void Appli_OobAuthenticationProcess(void)
{
    if(OutputOobBlinkCount < OutputOobData)
    {
      OutputOobBlinkCount++;
      Appli_LedBlink();
    }
    else
    {
        OutputOobBlinkCount++;
        Clock_Wait(1000);
        if(OutputOobBlinkCount > OutputOobData+3)
        {
            OutputOobBlinkCount = 0;
        }
    }
}
#endif

/**
* @brief  Call back function to provide Input OOB information
* @param  MOBLEUINT8 size
* @retval MOBLEUINT8*  
*/ 
MOBLEUINT8* Appli_BleInputOOBAuthCb(MOBLEUINT8 size)
{
#if defined (ENABLE_AUTH_TYPE_INPUT_OOB) && (ENABLE_SERIAL_INTERFACE)
  MOBLEUINT16 inputTimer = 0; 
  //TRACE_M(TF_PROVISION,"Input OOB information for provisioner-Size: %d\n\r", size);   
  while(1)
  {
      Serial_InterfaceProcess();
      #ifdef BLUENRG1_NWK_COPROC
      BTLE_StackTick();
      else
      HCI_Process();
      #endif
      /* Check if input is completed or timeout */
      if((inputOOBDataReady != 0x00) | (inputTimer > INPUT_OOB_TIMEOUT))
      {
          inputOOBDataReady = 0;
          break;
      }
      Clock_Wait(100);
      inputTimer++;
  }
  return InputOobData; 
#else
  return NULL;
#endif
}

/**
* @brief  Call back function to provide Input OOB information
* @param  rcvdStringBuff: buffer to store input string 
* @param  rcvdStringSize: length of the input string 
* @retval void  
*/ 
void Appli_BleSerialInputOOBValue(char *rcvdStringBuff, uint16_t rcvdStringSize)
{
#ifdef  ENABLE_AUTH_TYPE_INPUT_OOB
  unsigned long long InputOobDatatemp;
    sscanf(rcvdStringBuff + 5, "%lld", &InputOobDatatemp);
    memmove(&InputOobData, &InputOobDatatemp, sizeof(InputOobDatatemp));
    inputOOBDataReady = 1;
#endif
}

/**
* @brief  Enable Node as Sniffer to Capture all the packets
* @param  none
* @retval Sending the value to BLE Mesh Library
*/
MOBLEUINT8 Appli_BleDisableFilterCb(void)
{
    return DisableFilter;
}

/**
* @brief  Checks and do Manual Unprovision of board  
* @param  void
* @retval void
*/ 
void Appli_CheckForUnprovision(void)
{
  /* Checks if the User button is pressed or not at the startup */
  if (BUTTON_PRESSED == GetButtonState())
  {
    SetLed(1);
    tClockTime t = Clock_Time();
    int interrupted = 0;
    
    /*Wait to check if user is pressing the button persistently*/
    while ((Clock_Time() - t) < MANUAL_UNPROVISION_TIMER)
    {
      if (BUTTON_PRESSED != GetButtonState())
      {
        interrupted = 1;
        break;
      }
    }
    /*Unprovision, show that unprovisioning is completed, and 
    wait until user releases button*/
    if (!interrupted)
    {
      BluenrgMesh_Unprovision();
#if (SAVE_MODEL_STATE_NVM == 1)
      AppliNvm_ClearModelState();
#endif
      printf("Device is unprovisioned by application \r\n");
      
      t = Clock_Time();
      while ((Clock_Time() - t) < FLASH_ERASE_TIME);
      
      while (BUTTON_PRESSED == GetButtonState())
      {
        Appli_LedBlink();
      }
    }
    SetLed(0);
  }
}

/**
* @brief  Application processing 
*         This function should be called in main loop
* @param  void
* @retval void
*/ 
void Appli_Process(void)
{
  Appli_UpdateButtonState(GetButtonState() == BUTTON_PRESSED);
#ifdef ENABLE_SAVE_MODEL_STATE_NVM  
  AppliNvm_Process();
#endif
}


/**
* @brief  Checks and updates Mac address to generate MAC Address
* @param  void
* @retval MOBLEUINT8 sum return the sum calculated mac
*/ 
int Appli_CheckBdMacAddr(void)
{
  MOBLEUINT8 sum = 239;
  MOBLEUINT8 result = 0;
  
#ifdef EXTERNAL_MAC_ADDR_MGMT
  memcpy(bdaddr, (const MOBLEUINT8 *)_bdaddr , 7);
  bdaddr[7] = (EXTERNAL_MAC_ADDR_MGMT | EXTERNAL_MAC_TYPE);
#endif
  
#ifdef INTERNAL_UNIQUE_NUMBER_MAC
  Appli_GetMACfromUniqueNumber();
  bdaddr[7] = INTERNAL_UNIQUE_NUMBER_MAC;
#endif

  for (int i = 0; i < 6; ++i)
  {
    sum = (sum << 1) + bdaddr[i];
  }

  if (sum == bdaddr[6])
  {
    result = 1;
  }

#if defined(EXTERNAL_MAC_ADDR_MGMT) && defined(EXTERNAL_MAC_IS_PUBLIC_ADDR)
   /* Do nothing for modification of 2 MSb */
#else
  bdaddr[5] |= 0xC0;    /* 2 Msb bits shall be 11b for Static Random Address */
#endif
  
#ifdef GENERATE_STATIC_RANDOM_MAC
  bdaddr[7] = GENERATE_STATIC_RANDOM_MAC;   
                      /* Do nothing for bdaddr, just pass the identification */
  result = 1;         /* This will overwrite the above for loop result, 
                          which is redundant for this case */
#endif  

  return result;
}


/**
* @brief  Reads the unique serial number of the device
* @param  void
* @retval void
*/
#ifdef INTERNAL_UNIQUE_NUMBER_MAC
static void Appli_GetMACfromUniqueNumber(void)
{
#ifdef STM32L152xE
  /************************STM32L152RE 96 bit Unique ID addresses***************/
#define DEVICE_ID_REG0 (0x1FF800D0)
#define DEVICE_ID_REG1 (0x1FF800D4)
#define DEVICE_ID_REG2 (0x1FF800E4)
#endif

#ifdef STM32F401xE
  /************************STM32F401RE 96 bit Unique ID addresses***************/
#define DEVICE_ID_REG0 (0x1FFF7A10)
#define DEVICE_ID_REG1 (0x1FFF7A14)
#define DEVICE_ID_REG2 (0x1FFF7A18)
#endif  

#ifdef STM32L476xG    
  /************************STM32L476RG 96 bit Unique ID addresses***************/
#define DEVICE_ID_REG0 (0x1FFF7590)
#define DEVICE_ID_REG1 (0x1FFF7594)
#define DEVICE_ID_REG2 (0x1FFF7598)
#endif
  
#ifdef STM32F303xE  
#define DEVICE_ID_REG0 (0x1FFFF7AC)
#define DEVICE_ID_REG1 (0x1FFFF7B0)
#define DEVICE_ID_REG2 (0x1FFFF7B4)
#endif  
  /*
  The unique serial number is a six bytes value generated from STM32 UID 
  stored at DEVICE_ID_REG0, DEVICE_ID_REG1 and DEVICE_ID_REG2. It is generated 
  cancating 4bytes from DEVICE_ID_REG2 and first bytes of DEVICE_ID_REG0 and 
  DEVICE_ID_REG1. Since the UID at DEVICE_ID_REG0 and 
  DEVICE_ID_REG1 could be identical for same batch samples, 
  4 bytes have been taken from DEVICE_ID_REG2
  */
  
  uint8_t i;
  uint8_t sum = 239;
  uint8_t *ls_addr;
  
  ls_addr = (uint8_t*)DEVICE_ID_REG2;
  
  for(i = 0; i < 4; i += 1) 
  {
    bdaddr[i] = *ls_addr;
    ls_addr++;
  }
  
  bdaddr[4] = *(uint8_t*)(DEVICE_ID_REG0);
  bdaddr[5] = (*(uint8_t*)(DEVICE_ID_REG1)) | 0xC0; 
  /* Static Device Address: 
  The two most significant bits 
  of the address shall be equal to 1, 
  hence ORed with 0xC0)*/
  
  for (i = 0; i < 6; ++i)
  {
    sum = (sum << 1) + bdaddr[i];
  }
  bdaddr[6] = sum;
}
#endif


/**
* @brief  callback for unprovision the node by provisioner.
* @param  status reserved for future 
* @retval void
*/
void BluenrgMesh_UnprovisionCallback(MOBLEUINT8 status)
{
  ProvisionFlag = 0; 
  printf("Device is unprovisioned by provisioner \n\r");
	//HAL_Delay(1);
  //HAL_NVIC_SystemReset();
 // printf("Device is unprovisioned by provisioner \n\r");
#if PB_ADV_SUPPORTED
  BluenrgMesh_SetUnprovisionedDevBeaconInterval(PBADV_UNPROV_DEV_BEACON_INTERVAL);
#endif 
#if (SAVE_MODEL_STATE_NVM == 1)
  AppliNvm_ClearModelState();
#endif
}

/*----------------------------------------------------------------------------*/
/* Following Functions are ONLY required for the Embedded Provisioner --------*/
#if (defined(ENABLE_PROVISIONER_FEATURE) || defined(DYNAMIC_PROVISIONER))
/*----------------------------------------------------------------------------*/

void Appli_ProvisionerInit(void)
{
   NodeUnderProvisionParam.nodeAddress = 0; 
   NodeUnderProvisionParam.numOfElements = 0;
   NodeUnderProvisionParam.Reserved1 = 0;
   NodeUnderProvisionParam.saveToNVM = NVM_INIT;
}

/**
* @brief  Function for saving the Provisioned node address
* @param  void 
* @retval void
*/
void SaveProvisionedNodeAddress(void)
{
  NodeUnderProvisionParam.nodeAddress = NodeUnderProvisionParam.newNodeAddress;
  NodeUnderProvisionParam.numOfElements = NodeUnderProvisionParam.newNodeElements;
    
  if (NodeUnderProvisionParam.saveToNVM == NVM_SAVE_PENDING)
  {
    NodeUnderProvisionParam.saveToNVM = NVM_INIT;
    AppliPrvnNvm_SaveKeys(1);  /* This will trigger the saving in flash */
  }
}


/**
* @brief  Getting the New Node Provisioning Device Key 
* @param  void 
* @retval void
*/
MOBLEUINT8* GetNewProvNodeDevKey(void)
{
  return &NodeUnderProvisionParam.NewProvNodeDevKey[0];
}


/**
* @brief  Getting the New Node under Provisioning Application Key 
* @param  void 
* @retval void
*/
MOBLEUINT8* GetNewProvNodeAppKey(void)
{
  return &NodeUnderProvisionParam.NewProvNodeAppKey[0];
}


/**
* @brief  Function to Get the Node Address for provisioning 
* @param  void
* @retval void
*/
MOBLE_ADDRESS GetAddressToConfigure(void)
{
  return NodeUnderProvisionParam.nodeAddress;
}


/**
* @brief  Function to Get the Node Address for provisioning 
* @param  void
* @retval void
*/
MOBLE_ADDRESS GetNewAddressToProvision(void)
{
  return NodeUnderProvisionParam.nodeAddress + NodeUnderProvisionParam.numOfElements;
}


/**
* @brief  callback for getting the Node Address by provisioner & giving device key, app key & number of elements.
* @param  device key, app key & number of elements
* @retval To be assigned Node Address
*/
MOBLEUINT16 BluenrgMesh_PvnrDataInputCallback(MOBLEUINT8* devKey, 
                                              MOBLEUINT8* appKey, 
                                              MOBLEUINT8 numOfElements)
{
  MOBLE_ADDRESS newNodeAddressToProvision;
  MOBLEUINT8 *pUUID = {0};  /* Not used currently, not passed by Provisioner */
  
  /* Make a copy for DeviceKey and ApplicationKey, these are required later for 
       device configuration */
  memcpy(&NodeUnderProvisionParam.NewProvNodeDevKey[0], devKey, DEVICE_KEY_SIZE);
  memcpy(&NodeUnderProvisionParam.NewProvNodeAppKey[0], appKey, APP_KEY_SIZE);
  
  /* Print the keys for user */
  //TRACE_M(TF_PROVISION,"Device Key: ");
  for (MOBLEUINT8 count=0 ; count<DEVICE_KEY_SIZE; count++)
  {
   // TRACE_I(TF_PROVISION,"%.2x ", NodeUnderProvisionParam.NewProvNodeDevKey[count]);
  }

  //TRACE_M(TF_PROVISION,"App Key: ");
  for (MOBLEUINT8 count=0 ; count<DEVICE_KEY_SIZE; count++)
  {
  //  TRACE_I(TF_PROVISION,"%.2x ", NodeUnderProvisionParam.NewProvNodeAppKey[count]);
  }
  
  //TRACE_M(TF_PROVISION,"\r\n");
  
  newNodeAddressToProvision = GetNewAddressToProvision();
  //TRACE_M(TF_PROVISION,"Node Address Assigned = %d \r\n",newNodeAddressToProvision);
  
  /* Save Dev key and number of Elements  */   
  AppliPrvnNvm_SaveData(NodeUnderProvisionParam.NewProvNodeDevKey,
                        newNodeAddressToProvision,
                        pUUID,
                        numOfElements);
  
  NodeUnderProvisionParam.saveToNVM = NVM_SAVE_PENDING;
  
  return newNodeAddressToProvision;
}


/**
* @brief  start Provisioner mode 
* @param  void
* @retval void
*/
void Appli_StartProvisionerMode(MOBLEUINT8 mode)
{
  MOBLEUINT8 prvsnrDevKey[16];
  MOBLEUINT8 PrvnDevKeyFlag = mode;
     
  /* Initializes Mesh network parameters */
  BluenrgMesh_CreateNetwork(prvsnrDevKey);
  
  /* Following functions help to Configure the Provisioner to default settings*/
  Start_SelfConfiguration();

  //TRACE_I(TF_PROVISION,"Provisioner node \r\n");
 // TRACE_I(TF_PROVISION,"Provisioner Dev Key:");
   for(MOBLEUINT8 i=0;i<16;i++)
  {
 //   TRACE_I(TF_INIT,"[%02x] ",prvsnrDevKey[i]);
  }
//  TRACE_I(TF_INIT,"\r\n"); 

  if (mode ==1)
  {
  AppliPrvnNvm_SaveProvisionerDevKey(&prvsnrDevKey[0],
                                     PROVISIONER_ROOT_ADDR_DEFAULT,
                                     &PrvnDevKeyFlag, 
                                     APPLICATION_NUMBER_OF_ELEMENTS);  
  }/* if (mode ==1) */
}


#define SELF_CONFIG_IDLE_STATE 0
#define SELF_CONFIG_INIT_STATE 1 
#define SELF_CONFIG_START_STATE 2
#define SELF_APPKEY_BIND_STATE 3
#define SELF_SUBSCRIBE_DEFAULT_STATE 4
#define SELF_PUBLISH_DEFAULT_STATE 5
uint8_t self_config_state= SELF_CONFIG_IDLE_STATE;

void Start_SelfConfiguration (void)
{
  self_config_state = SELF_CONFIG_INIT_STATE;
}

/**
* @brief  callback for getting the Node Address by provisioner & giving device key.
* @param  void
* @retval void
*/
void Appli_SelfConfigurationProcess(void)
{
  /* Following functions help to Configure the Provisioner to default settings*/
    
  switch (self_config_state)
  {
  case SELF_CONFIG_IDLE_STATE:
   /* Nothing to do, just wait*/ 
    return;
    
  case SELF_CONFIG_INIT_STATE:
     /* This state is just to make a "NVM Process" to run once, because the 
         function will exit after changing the state*/
    self_config_state = SELF_CONFIG_START_STATE;
    break;
  
  case SELF_CONFIG_START_STATE:
    ApplicationSetNodeSigModelList();
    self_config_state = SELF_APPKEY_BIND_STATE;
   break;
    
  case SELF_APPKEY_BIND_STATE:
    Appli_ConfigClient_SelfDefaultAppKeyBind();
    self_config_state = SELF_SUBSCRIBE_DEFAULT_STATE;
    break;
  
  case SELF_SUBSCRIBE_DEFAULT_STATE:
    AppliConfigClient_SelfSubscriptionSetDefault();
    self_config_state = SELF_PUBLISH_DEFAULT_STATE;
    break;

  case SELF_PUBLISH_DEFAULT_STATE:
    AppliConfigClient_SelfPublicationSetDefault();
    self_config_state = SELF_CONFIG_IDLE_STATE;
    break;
    
    
  default:
    break;
  }
}


/**
* @brief  This function returns starts the provisioning of one of the devices
* @param  unprovDeviceArray: Pointer of an array having unprovisioned device UUIDs
* @param  index: Index of the device to be provisioned
* @retval MOBLE_RESULT
*/  
MOBLE_RESULT BluenrgMesh_ProvisionDevice(neighbor_params_t *unprovDeviceArray, MOBLEUINT16 index)
{
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;
    
  result = BluenrgMesh_ProvisionRemote((unprovDeviceArray+index)->uuid);

  return result;
}

/* Customized implementation for provisioning a device from mesh node - End */

/**
* @brief  Call back function called when PB-ADV link Opened  
* @param  none
* @retval none
*/ 
void BluenrgMesh_PbAdvLinkOpenCb(void)
{ 
  ProvisionFlag = 0;
  //TRACE_M(TF_PROVISION,"PB-ADV Link opened successfully \n\r");    
  SerialPrvn_ProvisioningStatusUpdateCb(MOBLE_TRUE, 0);
  /* Turn ON Red LED*/
#if LOW_POWER_FEATURE
  /* do nothing */
#else
  SdkEvalLedOn(LED2);
#endif
}


/**
* @brief  Call back function called when PB-ADV link Closed   
* @param  none
* @retval none
*/ 
void BluenrgMesh_PbAdvLinkCloseCb(void)
{
 // TRACE_M(TF_PROVISION,"PB-ADV Link Closed successfully \n\r");   
  /* Turn Off Red LED*/
#if LOW_POWER_FEATURE
  /* do nothing */
#else
  SdkEvalLedOff(LED2);
  SerialPrvn_ProvisioningStatusUpdateCb(MOBLE_FALSE, NodeUnderProvisionParam.nodeAddress);
#endif

  if (ProvisionFlag == 1)
  {
    SaveProvisionedNodeAddress();
    ProvisionFlag = 0;
    Appli_ConfigClientStartNodeConfiguration(1);
  }

}

/*----------------------------------------------------------------------------*/
/* The Embedded Provisioner specific code ends ------------------------------ */
#endif  /* (PROVISIONER_FEATURE == 1) */
/*----------------------------------------------------------------------------*/



/**
* @brief  callback for provision the node by provisioner.
* @param  void
* @retval void
*/
void BluenrgMesh_ProvisionCallback(void)
{
  ProvisionFlag = 1;
#ifdef ENABLE_AUTH_TYPE_OUTPUT_OOB
  PrvngInProcess = 0;
#endif
 printf("Device is provisioned by provisioner \r\n");
}


/**
* @brief  callback for friendship established by friend node
* @param  address of corresponding low power node
* @param  receive delay of low power node (unit ms)
* @param  poll timeout of low power node (unit 100ms)
* @param  number of elements of low power node
* @param  previous friend address of low power node (can be invalid address)
* @retval void
*/
void BluenrgMesh_FnFriendshipEstablishedCallback(MOBLE_ADDRESS lpnAddress,
                                                 MOBLEUINT8 lpnReceiveDelay,
                                                 MOBLEUINT32 lpnPollTimeout,
                                                 MOBLEUINT8 lpnNumElements,
                                                 MOBLE_ADDRESS lpnPrevFriendAddress)
{ 
 // TRACE_M(TF_LPN_FRND,"Friendship established. Low power node address 0x%.4X \r\n", lpnAddress);
 // TRACE_M(TF_LPN_FRND,"Low power node receive delay %dms \r\n", lpnReceiveDelay);
 // TRACE_M(TF_LPN_FRND,"Low power node poll timeout %dms \r\n", lpnPollTimeout*100);
 // TRACE_M(TF_LPN_FRND,"Low power node number of elements %d \r\n", lpnNumElements);
  if (lpnPrevFriendAddress != MOBLE_ADDRESS_UNASSIGNED)
  {
  //  TRACE_M(TF_LPN_FRND,"Low power node previous friend address 0x%.4X \r\n", lpnPrevFriendAddress);
  }
}

/**
* @brief  callback for friendship clear by friend node
* @param  reason of friendship clear
*         0: reserved,
*         1: friend request received from existing low power node (friend)
*         2: low power node poll timeout occurred
*         3: friend clear received
* @param  previous friend address of low power node (can be invalid address)
* @retval void
*/
void BluenrgMesh_FnFriendshipClearedCallback(MOBLEUINT8 reason, MOBLE_ADDRESS lpnAddress)
{
 // TRACE_M(TF_LPN_FRND,"Friendship cleared. Low power node address 0x%.4X \r\n", lpnAddress);
  
  switch(reason)
  {
  case FN_CLEARED_REPEAT_REQUEST: 
  //  TRACE_M(TF_LPN_FRND,"Reason: New friend request received from existing low power node \r\n");
    break;
  case FN_CLEARED_POLL_TIMEOUT:
   // TRACE_M(TF_LPN_FRND,"Reason: Low power node poll timeout occurred \r\n");
    break;
  case FN_CLEARED_FRIEND_CLEAR:
  //  TRACE_M(TF_LPN_FRND,"Reason: Friend clear received \r\n");
    break;
  default:
  //  TRACE_M(TF_LPN_FRND,"Reason: Invalid \r\n");
    break;
  }
}

/**
* @brief  callback for friendship established by low power node
* @param  address of corresponding friend node
* @retval void
*/
void BluenrgMesh_LpnFriendshipEstablishedCallback(MOBLE_ADDRESS fnAddress)
{
  /* Friendship established */
}

/**
* @brief  callback for friendship cleare by low power node
* @param  reason of friendship clear.
*         0: reserved
*         1: No response received from friend node
* @retval void
*/
void BluenrgMesh_LpnFriendshipClearedCallback(MOBLEUINT8 reason, MOBLE_ADDRESS fnAddress)
{ 
  //TRACE_M(TF_LPN_FRND,"Friendship cleared. Friend node address 0x%.4x \r\n", fnAddress);
  
  if (reason == LPN_CLEARED_NO_RESPONSE)
  {
  //  TRACE_M(TF_LPN_FRND,"Reason: Friend node not responding \r\n");
  }
  else
  {
  //  TRACE_M(TF_LPN_FRND,"Reason: Invalid \r\n");
  } 
}

/** 
* @brief  New neighbor appeared callback in neighbor table.
          If MAC address of neighbor changes it appears as new neighbor.
* @param  MAC address of neighbor.
*         is neighbor provisioned or unprovisioned device.
*         uuid of neighbor. NULL if not available
*         network address of neighbor. MOBLE_ADDRESS_UNASSIGNED if not available
*         last updated rssi value.
* @retval void
*/
void BluenrgMesh_NeighborAppearedCallback(const MOBLEUINT8* bdAddr,
                                          MOBLEBOOL provisioned,
                                          const MOBLEUINT8* uuid,
                                          MOBLE_ADDRESS networkAddress,
                                          MOBLEINT8 rssi)
{
 // TRACE_M(TF_NEIGHBOUR,"New neighbor appeared. Neighbor MAC address:");
  
  for (MOBLEUINT8 count=0 ; count<6; count++)
  {
 //   TRACE_M(TF_NEIGHBOUR,"%.2x ", bdAddr[count]);
  }
  
  if (provisioned == MOBLE_TRUE)
  {
 //   TRACE_M(TF_NEIGHBOUR,"-> Provisioned node. \n\r");
  }
  else
  {
  //  TRACE_M(TF_NEIGHBOUR,"-> Unprovisioned device. \n\r");
  }
  
 // TRACE_M(TF_NEIGHBOUR,"rssi: %d. ", rssi);
  
  if (networkAddress != MOBLE_ADDRESS_UNASSIGNED)
  {
 //   TRACE_M(TF_NEIGHBOUR,"Network address: 0x%.4x\n\r", networkAddress);
  }
  else
  {
 //   TRACE_M(TF_NEIGHBOUR,"Network address not available\n\r");
  }

  for (MOBLEUINT8 i=0; i<16; i++)
  {
    if (uuid[i] == 0x00)
    {
      continue;
    }
    else
    {
    //  TRACE_M(TF_NEIGHBOUR,"UUID: ");
      
      for (MOBLEUINT8 count=0 ; count<16; count++)
      {
    //    TRACE_M(TF_NEIGHBOUR,"%.2x ", uuid[count]);
      }
      
      break;
    }
  }
  
 // TRACE_M(TF_NEIGHBOUR,"\n\r");
}

/** 
* @brief  Existing neighbor refreshed callback in neighbor table.
          If MAC address of neighbor changes it appears as new neighbor.
* @param  MAC address of neighbor.
*         is neighbor provisioned or unprovisioned device.
*         uuid of neighbor. NULL if not available
*         network address of neighbor. MOBLE_ADDRESS_UNASSIGNED if not available
*         last updated rssi value.
* @retval void
*/
void BluenrgMesh_NeighborRefreshedCallback(const MOBLEUINT8* bdAddr,
                                          MOBLEBOOL provisioned,
                                          const MOBLEUINT8* uuid,
                                          MOBLE_ADDRESS networkAddress,
                                          MOBLEINT8 rssi)
{
 // TRACE_M(TF_NEIGHBOUR,"Existing neighbor refreshed. Neighbor MAC address:");
  
  for (MOBLEUINT8 count=0 ; count<6; count++)
  {
  //  TRACE_M(TF_NEIGHBOUR,"%.2x ", bdAddr[count]);
  }
  
  if (provisioned == MOBLE_TRUE)
  {
  //  TRACE_M(TF_NEIGHBOUR,"-> Provisioned node. \n\r");
  }
  else
  {
   // TRACE_M(TF_NEIGHBOUR,"-> Unprovisioned device. \n\r");
  }
  
//  TRACE_M(TF_NEIGHBOUR,"rssi: %d. ", rssi);
  
  if (networkAddress != MOBLE_ADDRESS_UNASSIGNED)
  {
  //  TRACE_M(TF_NEIGHBOUR,"Network address: 0x%.4x\n\r", networkAddress);
  }
  else
  {
  //  TRACE_M(TF_NEIGHBOUR,"Network address not available\n\r");
  }
  
  for (MOBLEUINT8 i=0; i<16; i++)
  {
    if (uuid[i] == 0x00)
    {
      continue;
    }
    else
    {
  //    TRACE_M(TF_NEIGHBOUR,"UUID: ");
      
      for (MOBLEUINT8 count=0 ; count<16; count++)
      {
   //     TRACE_M(TF_NEIGHBOUR,"%.2x ", uuid[count]);
      }
      
      break;
    }
  }
  
 // TRACE_M(TF_NEIGHBOUR,"\n\r");
}

/** 
* @brief  Beacon received callback
*         Beacons are received only if received beacon ad type is not 
*         Mesh Message, Mesh Beacon or PB-ADV
* @param  MAC address
*         data
*         length of beacon
*         rssi value of beacon
* @retval void
*/
#if 0 /* BluenrgMesh_CustomBeaconReceivedCallback high frequency callback */
void BluenrgMesh_CustomBeaconReceivedCallback(const MOBLEUINT8* bdAddr,
                                              const MOBLEUINT8* data,
                                              MOBLEUINT8 length,
                                              MOBLEINT8 rssi)
{
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;
  
  if (length < 2)
  {
    result = MOBLE_RESULT_FAIL;
   // TRACE_M(TF_BEACON, "Message is too small \r\n");
  }
  
  if (result == MOBLE_RESULT_SUCCESS)
  {
      if (data[1] == CUSTOM_BEACON_AD_TYPE)
      {
         // TRACE_M(TF_BEACON, "Message length(%d), rssi(%d) \r\n", length, rssi);
          
          if (TF_BEACON == 1)
          {
              printf("Data: ");
              for (MOBLEUINT8 count=0; count<length; count++)
              {
                printf("%.2x ", data[count]);
              }
              printf(" \r\n");
          }
      }
  }
}
#endif /* BluenrgMesh_CustomBeaconReceivedCallback high frequency callback */

/** 
* @brief  Custom beacon generator
*         If size set to > 31 bytes, beacon is rejected
*         BluenrgMesh_SetCustomBeaconInterval should be set to get this callback
*         Packet to be formatted as per Bluetooth specifications
* @param  beacon data buffer. It includes length and AD type fields
*         buffer size
* @retval void
*/
void BluenrgMesh_CustomBeaconGeneratorCallback(void* buffer, int* size)
{
  MOBLEUINT8 adType = CUSTOM_BEACON_AD_TYPE;
  MOBLEUINT8 dataLength = 5;
  MOBLEUINT8 data[5] = {0x00,0x01,0x02,0x03,0x04};
  MOBLEUINT8* buf = (MOBLEUINT8*)buffer;

  buf[0] = dataLength+1;
  buf[1] = adType;
  memcpy(buf+2, data, dataLength);
  
  *size = dataLength+2;  
}

/**
* @brief  Initializes the Application  
* @param  void
* @retval void
*/
void Appli_Init(MOBLEUINT8 *flag)
{
#ifdef ENABLE_UNPROVISIONING_BY_POWER_ONOFF_CYCLE  
  /* Hardware Factory Restore implementation */
  AppliNvm_FactorySettingReset();
#endif
  
#if PB_ADV_SUPPORTED
  Timer_Set(&discoverTimer, discoverTimerinterval);
#endif
}

extern tListNode hciReadPktPool;
void printdebugfunc(MOBLEUINT32 printId)
{
//  MOBLEUINT32 x = gethcireadpktpoolnextval();
//  printf("Id:%d debug ptr %d \r\n", printId, x);
}



/**
* @brief  PWM_CoolValue: This function is used to calculate the value for the 
          cool temperature for the light.
* @param  colourValue: Temperature value ratio
* @param  brightValue: Lightness value ratio.
* @retval duty: duty fot the PWM
*/ 
MOBLEUINT16 PWM_CoolValue(float colourValue ,float brightValue)
{
  float colourDuty; 
  MOBLEUINT16 duty;
  
  colourDuty = colourValue * brightValue;    
  duty = (MOBLEUINT16)(colourDuty * PWM_TIME_PERIOD);
  
  return duty;
}


/**
* @brief  PWM_WarmValue: This function is used to calculate the value for the 
          warm temperature for the light.
* @param  colourValue: Temperature value ratio
* @param  brightValue: Lightness value ratio.
* @retval duty: duty fot the PWM
*/ 
MOBLEUINT16 PWM_WarmValue(float colourValue ,float brightValue)
{
  float warmDuty;    
  MOBLEUINT16 duty;
  
  warmDuty = (1-colourValue)* brightValue;
  duty = (MOBLEUINT16)(warmDuty * PWM_TIME_PERIOD);
  
  return duty;
}

/**
* @brief  PwmValueMapping: This function takes the value as parameter from the 
*         model and return the value according to .
* @param  setValue: value to be set from model
* @param  maxRange: Max range of the parameter
* @param  minRange: Min range of the parameter
* @retval MOBLEUINT8
*/
MOBLEUINT16 PwmValueMapping(MOBLEUINT16 setValue , MOBLEUINT16 maxRange , MOBLEINT16 minRange)
{
  MOBLEUINT16 percentValue;
  MOBLEUINT16 duty;
  
#ifdef SMART_PLUG
   percentValue =  (setValue * 100)/ (maxRange - minRange);
        
   if(percentValue < 2)
   {
     duty = 0;
   }   
   else if((percentValue > 2) && (percentValue <= 10))
   {
     duty = 1;
   }
   else if((percentValue > 10) && (percentValue <= 20))
   {
     duty = 2;
   }
   else if((percentValue > 20) && (percentValue <= 30))
   {
     duty = 3;
   }
   else if((percentValue > 30) && (percentValue <= 40))
   {
     duty = 4;
   }
   else if((percentValue > 40) && (percentValue <= 50))
   {
     duty = 5;
   }
   else if((percentValue > 50) && (percentValue <= 60))
   {
     duty = 6;
   }
   else if((percentValue > 60) && (percentValue <= 70))
   {
     duty = 7;
   }
   else if((percentValue > 70) && (percentValue <= 80))
   {
     duty = 8;
   }
   else if((percentValue > 80) && (percentValue <= 90))
   {
     duty = 9;
   }
   else if(percentValue > 90)
   {
     duty = 10;
   }
#else
   if(minRange > 0x00)
   {
     percentValue =  (setValue - 800)/ (maxRange - minRange);
     percentValue = (percentValue*100);
   }
   else
   {
     percentValue =  (setValue * 100)/ (maxRange - minRange);
   }
   
   duty = percentValue*320 ;
   
   if(duty >= 32000)
   {
     duty = 31999;
   }
   if(duty == 0)
   {
     duty = 1;
   }
#endif
     
   return duty;
}

/**
* @brief  Function used to calculate the delay with random time..
* @param  MOBLEUINT16
* @retval MOBLEUINT8
*/
MOBLEBOOL Wait_RandomTime(void)
{
   static MOBLEUINT8 Clockflag = 0;
   static MOBLEUINT32 wait_Time;
   static MOBLEUINT32 check_Time;
   MOBLEUINT8 random_time[8];
 
   if(Clockflag == 0)
   {   
    hci_le_rand(random_time);
    check_Time = Clock_Time();
    wait_Time = DEFAULT_RANDOM_DELAY_VALUE + 
                                     (random_time[0] + random_time[1]*256)\
                                         %DEFAULT_RANDOM_DELAY_VALUE; 

     Clockflag = 1;
   } 
/* The function will called untill the testcount will not become zero */     

     if((Clock_Time() - check_Time) >=  wait_Time)
     {
        Clockflag = 0;
        return MOBLE_TRUE;
                
       }
   return MOBLE_FALSE;
}
/************************************ Weak linking ***********************************
If implemented in application, linker would replace weak linking in library */
WEAK_FUNCTION (void SerialPrvn_ProvisioningStatusUpdateCb(uint8_t flagPrvningInProcess, MOBLEUINT16 nodeAddress))
{
    
}

/**
* @}
*/

/**
* @}
*/
/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
