/**
******************************************************************************
* @file    serial_prvn.c
* @author  BLE Mesh Team
* @version V1.14.000
* @date    19-11-2021
* @brief   Embedded provisioner Serial Control file 
******************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
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
* Initial BlueNRG-Mesh is built over Motorola?s Mesh over Bluetooth Low Energy 
* (MoBLE) technology. The present solution is developed and maintained for both 
* Mesh library and Applications solely by STMicroelectronics.
*
******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "hal_common.h"
#include "serial_if.h"
#include "serial_ctrl.h"
#include "mesh_cfg.h"
#include "bluenrg_mesh.h"
#include "appli_config_client.h"
#include "serial_prvn.h"
#include "appli_mesh.h"

/** @addtogroup BlueNRG_Mesh
*  @{
*/

/** @addtogroup Middlewares_Serial_Interface
*  @{
*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static neighbor_params_t NeighborTable[5]; 
static MOBLEUINT8 NoOfNeighborPresent;
static MOBLEUINT8 PrvningInProcess = 0;
static MOBLEUINT16 PrvndNodeAddress = 0;
extern MOBLEUINT16 nodeAddressOffset;
/* Private function prototypes -----------------------------------------------*/
static MOBLE_RESULT SerialPrvn_ProvisionDevice(char *text);
static MOBLE_RESULT SerialPrvn_UnProvisionDevice(char *text);
static MOBLE_RESULT SerialPrvn_ScanDevices(char *text);
/* Private functions ---------------------------------------------------------*/ 
/**
* @brief  This function scans and prints unprovisioned devices  
* @param  unprovDeviceArray: Pointer of an array for filling unprovisioned device UUIDs
* @param  noOfUnprovDevices: Pointer to take total count of nearby unprovisioned devices
* @retval MOBLE_RESULT
*/  
__weak MOBLE_RESULT BluenrgMesh_ScanDevices(neighbor_params_t *unprovDeviceArray, MOBLEUINT8 *noOfUnprovDevices)
{
  return MOBLE_RESULT_NOTIMPL;
}
/**
* @brief  This function returns starts the provisioning of one of the devices
* @param  unprovDeviceArray: Pointer of an array having unprovisioned device UUIDs
* @param  index: Index of the device to be provisioned
* @retval MOBLE_RESULT
*/  
__weak MOBLE_RESULT BluenrgMesh_ProvisionDevice(neighbor_params_t *unprovDeviceArray, MOBLEUINT16 index)
{
    return MOBLE_RESULT_NOTIMPL;
}
/**
* @brief  This function is used to parse the string given by the user
* @param  rcvdStringBuff: buffer to store input string 
* @param  rcvdStringSize: length of the input string 
* @retval void
*/ 
void SerialPrvn_Process(char *rcvdStringBuff, uint16_t rcvdStringSize)
{
  MOBLE_RESULT result = MOBLE_RESULT_INVALIDARG;

  /* Command to make a devices as Root node which creates Mesh network credentials */
  if (!strncmp(rcvdStringBuff+COMMAND_OFFSET, "ROOT",4))
  {   
#if defined (ENABLE_PROVISIONER_FEATURE) || defined(DYNAMIC_PROVISIONER)
    /* Initializes Mesh network parameters */
    Appli_StartProvisionerMode(1);
    result = MOBLE_RESULT_SUCCESS;
#endif    
  }
  /* Command to scan the unprovisioned devices */
  else if (!strncmp(rcvdStringBuff+COMMAND_OFFSET, "SCAN",4))
  {   
      result = SerialPrvn_ScanDevices(rcvdStringBuff+COMMAND_OFFSET);
  }
   /* Command to start the unprovisioned devices */
  else if (!strncmp(rcvdStringBuff+COMMAND_OFFSET, "PRVN-",4))
  {
      if(!PrvningInProcess)
      {
          result = SerialPrvn_ProvisionDevice(rcvdStringBuff+COMMAND_OFFSET);
      }
      else
      {
          BluenrgMesh_PrintStringCb("Link opened already. Wait.\r\n");
          result = MOBLE_RESULT_FAIL;
      }
  }
  else if (!strncmp(rcvdStringBuff+COMMAND_OFFSET, "UNPV",4))
  {
      
    result = SerialPrvn_UnProvisionDevice(rcvdStringBuff+COMMAND_OFFSET);
      
  }
     /* Command to start the unprovisioned devices */
  else if (!strncmp(rcvdStringBuff+COMMAND_OFFSET, "RESET",5))
  {
        BluenrgMesh_PrintStringCb("Reseting Board...\r\n");
        NVIC_SystemReset();
  }
  /* Command to scan the unprovisioned devices - Used By node only */
  else if (!strncmp(rcvdStringBuff+COMMAND_OFFSET, "NDSCAN",4))
  {   
      result = BluenrgMesh_ScanDevices(NeighborTable, &NoOfNeighborPresent);
  }
   /* Command to start the unprovisioned devices - Used By node only */
  else if (!strncmp(rcvdStringBuff+COMMAND_OFFSET, "NDPRVN-",4))
  {   
      MOBLEINT16 index = 0;  
      sscanf(rcvdStringBuff, "PRVN-%hd", &index);
      result = BluenrgMesh_ProvisionDevice(NeighborTable, index);
  }
  else
  {
      BluenrgMesh_PrintStringCb("Invalid Command\r\n");
      return;
  }
  
  /* Check the result of command processing */
  if(result == MOBLE_RESULT_SUCCESS)
  {
      BluenrgMesh_PrintStringCb("Test command executed successfully\r\n");
  }
  else if(result == MOBLE_RESULT_OUTOFMEMORY)
  {
      BluenrgMesh_PrintStringCb("Test command Failed. Out of memory\r\n");  
  }
  else if(result == MOBLE_RESULT_INVALIDARG)
  {
      BluenrgMesh_PrintStringCb("Test command Failed. Invalid Argument\r\n");  
  }
  else
  {
       BluenrgMesh_PrintStringCb("Test command Failed.\r\n");   
  }
}

/**
* @brief  This function returns starts the provisioning of one of the devices
* @param  text: received array
* @retval MOBLE_RESULT
*/  
static MOBLE_RESULT SerialPrvn_ProvisionDevice(char *text)
{
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;
    
#if defined (ENABLE_PROVISIONER_FEATURE) || defined(DYNAMIC_PROVISIONER)  
  MOBLEINT16 index = 0;
  MOBLEINT16 na = 0;

  
  sscanf(text, "PRVN-%hd %hd", &index, &na);  
  if(na>1)
  { /* Address 1 is reserved for the Provisioner */
          
      result = BluenrgMesh_ProvisionRemote(NeighborTable[index].uuid);
      
      /* Make copy of the UUID */
      memcpy (NodeUnderProvisionParam.NewProvNodeUUID, 
              NeighborTable[index].uuid,
              UUID_SIZE);
  }
  else 
  {
      result = MOBLE_RESULT_INVALIDARG;
  }

#endif  
  return result;
}

/**
* @brief  This function Un-Provision one of the devices
* @param  text: received array
* @retval MOBLE_RESULT
*/  
static MOBLE_RESULT SerialPrvn_UnProvisionDevice(char *text)
{
  MOBLEINT16 na = 0;
  MOBLE_RESULT result = MOBLE_RESULT_SUCCESS;
  
  sscanf(text, "UNPV %hd", &na);  
  if(na>1)
  {
      result = ConfigClient_NodeReset(na);
  }
  else 
  {
      result = MOBLE_RESULT_INVALIDARG;
  }

  return result;
}

/**
* @brief  This function scans and prints unprovisioned devices  
* @param  text: received array
* @retval MOBLE_RESULT
*/  
static MOBLE_RESULT SerialPrvn_ScanDevices(char *text)
{
  MOBLE_RESULT result;
  
    result = BluenrgMesh_GetNeighborState(NeighborTable,&NoOfNeighborPresent);
    /* Check if any unprovisioned device is available */
    if(!NoOfNeighborPresent)
    {
        TRACE_I(TF_PROVISION,"No Unprovisioned Device Nearby\r\n");  
    }
    else
    {
        for(MOBLEINT8 count=0; count < NoOfNeighborPresent; count++)
        {
          BluenrgMesh_PrintStringCb("");  
          TRACE_I(TF_PROVISION,"Device-%d -> ", count);  
          BluenrgMesh_PrintDataCb(NeighborTable[count].uuid, 16);
        }
    }
  return result;
}
/**
* @brief  This funcrion is used to update the status of the provisioning
* @retval void
*/ 
void SerialPrvn_ProvisioningStatusUpdateCb(uint8_t flagPrvningInProcess, MOBLEUINT16 nodeAddress)
{
    PrvningInProcess = flagPrvningInProcess;
    PrvndNodeAddress = nodeAddress;
}
/**
* @}
*/

/**
* @}
*/
/******************* (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
