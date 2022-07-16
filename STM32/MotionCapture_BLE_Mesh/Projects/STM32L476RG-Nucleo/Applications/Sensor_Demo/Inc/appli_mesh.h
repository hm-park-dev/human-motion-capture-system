/**
******************************************************************************
* @file    appli_mesh.h
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Header file for the user application file 
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
#ifndef __APPLI_MESH_H
#define __APPLI_MESH_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include "mesh_cfg_usr.h"
#include "mesh_cfg.h"

/* Exported macro ------------------------------------------------------------*/
typedef enum _prvn_nvm_state
{
  NVM_INIT = 0,
  NVM_SAVE_PENDING,
} prvn_nvm_state;

/* MACROS for Power Level definitions */
#define POWER_LEVEL_LOW            0 
#define TX_POWER_LEVEL_MINUS_18DBM 0 // = -18 dBm,
#define TX_POWER_LEVEL_MINUS_15DBM 1 // = -15 dBm,
#define TX_POWER_LEVEL_MINUS_12DBM 2 // = -12 dBm,
#define TX_POWER_LEVEL_MINUS_9DBM  3 // = -9 dBm,
#define TX_POWER_LEVEL_MINUS_6DBM  4 // = -6 dBm,
#define TX_POWER_LEVEL_MINUS_2DBM  5 // = -2 dBm,
#define TX_POWER_LEVEL_0DBM        6 // =  0 dBm,
#define TX_POWER_LEVEL_PLUS_5DBM   7 // =  5 dBm.
#define POWER_LEVEL_HIGH           1
#define TX_POWER_LEVEL_MINUS_14DBM 0 // = -14 dBm,
#define TX_POWER_LEVEL_MINUS_11DBM 1 // = -11 dBm,
#define TX_POWER_LEVEL_MINUS_8DBM  2 // = -8 dBm,
#define TX_POWER_LEVEL_MINUS_5DBM  3 // = -5 dBm,
//#define TX_POWER_LEVEL_MINUS_2DBM  4 // = -2 dBm,
#define TX_POWER_LEVEL_PLUS_2DBM   5 // =  2 dBm,
#define TX_POWER_LEVEL_PLUS_4DBM   6 // =  4 dBm,
#define TX_POWER_LEVEL_PLUS_8DBM   7 // =  8 dBm

/* Exported variables  ------------------------------------------------------- */

extern MOBLEUINT8 bdaddr[]; 

typedef struct
{
  MOBLEUINT16 nodeAddress;
  MOBLEUINT8  numOfElements;
  MOBLEUINT8  Reserved1;   /* For Alignment by 4*/
  MOBLEUINT16 newNodeAddress;
  MOBLEUINT8  newNodeElements;
  prvn_nvm_state  saveToNVM; 
  MOBLEUINT8 NewProvNodeDevKey[DEVICE_KEY_SIZE];  
  MOBLEUINT8 NewProvNodeAppKey[APP_KEY_SIZE];
  MOBLEUINT8 NewProvNodeUUID[UUID_SIZE];
} NodeUnderProvisionParam_t;

extern NodeUnderProvisionParam_t NodeUnderProvisionParam;
extern MOBLEUINT16 Appli_SIG_Models[APPLICATION_NUMBER_OF_ELEMENTS][APPLICATION_SIG_MODELS_MAX_COUNT];
extern MOBLEUINT32 Appli_Vendor_Models[APPLICATION_NUMBER_OF_ELEMENTS][APPLICATION_VENDOR_MODELS_MAX_COUNT];
/* Exported Functions Prototypes ---------------------------------------------*/
MOBLE_RESULT Appli_BleStackInitCb(void);
MOBLE_RESULT Appli_BleSetTxPowerCb(void);
MOBLE_RESULT Appli_BleSetUUIDCb(MOBLEUINT8 *uuid_prefix_data);
MOBLE_RESULT Appli_BleSetProductInfoCB(MOBLEUINT8 *company_product_info);
void Appli_BleUnprovisionedIdentifyCb(MOBLEUINT8 data);
void Appli_BleGattConnectionCompleteCb(void);
void Appli_BleGattDisconnectionCompleteCb(void);
MOBLEUINT8 Appli_BleSetNumberOfElementsCb(void);
MOBLE_RESULT Appli_BleAttentionTimerCb(void);
void Appli_BleOutputOOBAuthCb(MOBLEUINT8* output_oob, MOBLEUINT8 size);
MOBLEUINT8* Appli_BleInputOOBAuthCb(MOBLEUINT8 size);
void Appli_BleSerialInputOOBValue(char *rcvdStringBuff, uint16_t rcvdStringSize);
MOBLEUINT8 Appli_BleDisableFilterCb(void);
void BluenrgMesh_PbAdvLinkCloseCb(void);
void Appli_IntensityControlPublishing(MOBLEUINT8* value);

int Appli_CheckBdMacAddr(void);
MOBLE_RESULT Appli_LedBlink(void);
MOBLE_RESULT Appli_LedStateCtrlCb(MOBLEUINT16 ctrl);

void Appli_CheckForUnprovision(void);
void Appli_Process(void);
void Appli_LedCtrl(void);
void Appli_Init(MOBLEUINT8 *flag);

MOBLE_ADDRESS GetAddressToConfigure(void);
MOBLE_ADDRESS GetNewAddressToProvision(void);
void SaveProvisionedNodeAddress(void);
MOBLEUINT8* GetNewProvNodeDevKey(void);
MOBLEUINT8* GetNewProvNodeAppKey(void);
void IntensityPublish(void);
void Start_SelfConfiguration (void);
void Appli_ProvisionerInit(void);
void Appli_StartProvisionerMode(MOBLEUINT8 mode);

MOBLEUINT16 PWM_CoolValue(float colourValue ,float brightValue);
MOBLEUINT16 PWM_WarmValue(float colourValue ,float brightValue);
MOBLEUINT16 PwmValueMapping(MOBLEUINT16 setValue , MOBLEUINT16 maxRange , MOBLEINT16 minRange);

MOBLE_RESULT BluenrgMesh_ScanDevices(neighbor_params_t *unprovDeviceArray, MOBLEUINT8 *noOfUnprovDevices);
MOBLE_RESULT BluenrgMesh_ProvisionDevice(neighbor_params_t *unprovDeviceArray, MOBLEUINT16 index);
MOBLEBOOL Wait_RandomTime(void);
MOBLEUINT8* GetProvNodeDevKey(MOBLEUINT16 na,MOBLEUINT32 *dev);
#endif /* __APPLI_MESH_H */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

