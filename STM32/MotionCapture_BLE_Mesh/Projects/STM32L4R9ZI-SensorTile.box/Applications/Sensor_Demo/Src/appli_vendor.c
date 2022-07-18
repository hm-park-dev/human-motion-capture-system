/******************************************************************************
* @file    appli_vendor.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Application interface for Vendor Mesh Models 
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
#include "bluenrg_mesh.h"
#include "appli_mesh.h"
#include "vendor.h"
#include "appli_vendor.h"
#include "common.h"
#include "appli_light.h"
#include "models_if.h"
#include "mesh_cfg.h"
#include <string.h>


/** @addtogroup MODEL_VENDOR
*  @{
*/

/** @addtogroup Application_Mesh_Models
*  @{
*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
typedef struct
{
  MOBLE_ADDRESS dst;
  MOBLEUINT8 data[VENDOR_DATA_BUFFER_SIZE]; 
  MOBLEUINT32 length;
  MOBLEUINT8 elementIndex;
} APPLI_SEND_BIG_DATA_PACKET;

/* Private variables ---------------------------------------------------------*/

MOBLEUINT8 ResponseBuffer[VENDOR_DATA_BUFFER_SIZE];
MOBLEUINT16 BuffLength; 
APPLI_SEND_BIG_DATA_PACKET Appli_VendorBigData;

extern MOBLEUINT8 Appli_LedState;
extern uint16_t DUTY;
extern MOBLEUINT8 NumberOfElements;
MOBLEUINT32 TestHitCounter = 0;
extern Appli_LightPwmValue_t Appli_LightPwmValue;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Process the Vendor Device Info Command
* @param  data: Pointer to the data received from peer_addr
* @param  length: Length of the data
* @retval MOBLE_RESULT status of result
*/          
MOBLE_RESULT Appli_Vendor_DeviceInfo(MOBLEUINT8 const *data, MOBLEUINT32 length)
{
        MOBLEUINT8 tempBuffer[10];
        MOBLE_RESULT status = MOBLE_RESULT_SUCCESS;  
        
        MOBLEUINT8 subCmd = data[0];
        char *libVersion;
        char *subLibVersion;
        MOBLEUINT8 inc = 0;
        /*First Byte is sending the Sub Command*/      
        ResponseBuffer[0] = subCmd;
        

        switch(subCmd)
        {
        case IC_TYPE:
          {
            #ifdef BLUENRG1_DEVICE           
            ResponseBuffer[1] = BLUENRG1_BRD;              
            #endif
            
            #ifdef BLUENRG2_DEVICE              
            ResponseBuffer[1] = BLUENRG2_BRD;              
            #endif
            
            #ifdef BLUENRG_MS              
            ResponseBuffer[1] = BLUENRG_MS_BRD;               
            #endif
            
            BuffLength = 2;
            
            break;
          }
        case LIB_VER:
          {
            libVersion = BluenrgMesh_GetLibraryVersion();
            while(*libVersion != '\0')
            {
              tempBuffer[inc] = *libVersion;
              if(tempBuffer[inc] != 0x2E)
              {
                tempBuffer[inc] = BluenrgMesh_ModelsASCII_To_Char(tempBuffer[inc]);
              //  TRACE_M(TF_VENDOR,"Lib version is %x\n\r" ,(unsigned char)tempBuffer[inc]);
              }
              else
              {
              //  TRACE_M(TF_VENDOR,"Lib version is %c\n\r" ,(unsigned char)tempBuffer[inc]);
              }             
              libVersion++; 
             
              inc++;
            }             
            ResponseBuffer[1]= tempBuffer[0];
            ResponseBuffer[2]= tempBuffer[1];
            ResponseBuffer[3]= tempBuffer[3];
            ResponseBuffer[4]= tempBuffer[4];
            ResponseBuffer[5]= tempBuffer[6];
            ResponseBuffer[6]= tempBuffer[7];
            ResponseBuffer[7]= tempBuffer[8];
            BuffLength = 8;      
            break;
          }
        case LIB_SUB_VER:
          {
            subLibVersion = BluenrgMesh_GetLibrarySubVersion();
            while(*subLibVersion != '\0')
            {
              tempBuffer[inc] = * subLibVersion;
              if((tempBuffer[inc] != 0x2E) && (tempBuffer[inc] != 0x52))
              {               
                tempBuffer[inc] = BluenrgMesh_ModelsASCII_To_Char(tempBuffer[inc]);
               // TRACE_M(TF_VENDOR,"Sub Lib version is %x\n\r" ,(unsigned char)tempBuffer[inc]);
              }
              else
              {
               // TRACE_M(TF_VENDOR,"Sub Lib version is %c\n\r" ,(unsigned char)tempBuffer[inc]);
              } 
              subLibVersion++;
              inc++;
            }           
            ResponseBuffer[1]= tempBuffer[0];
            ResponseBuffer[2]= tempBuffer[1];
            ResponseBuffer[3]= tempBuffer[3];
            ResponseBuffer[4]= tempBuffer[5];
            ResponseBuffer[5]= tempBuffer[7];
            ResponseBuffer[6]= tempBuffer[9];
            
            BuffLength = 7;
            
            break;
          }
        case APPLICATION_VER:
          {
            /*Insert Command to check Application Version*/
            break;
          }
          
        default:
          {
            status = MOBLE_RESULT_FALSE;
            break;
          }
          
        }
        
        return status;
}


/**
* @brief  Process the Vendor Test Command 
* @param  data: Pointer to the data received from peer_addr
* @param  length: Length of the data
* @retval MOBLE_RESULT status of result
*/          
MOBLE_RESULT Appli_Vendor_Test(MOBLEUINT8 const *data, MOBLEUINT32 length)
{
       MOBLE_RESULT status = MOBLE_RESULT_SUCCESS;  
       MOBLEUINT8 subCmd = data[0];
       /*First Byte is sending the Sub Command*/      
       ResponseBuffer[0]=subCmd;
      // TRACE_M(TF_VENDOR, "#01-%02hx! \n\r",data[0]);
       switch(subCmd)
       {             
           case APPLI_TEST_ECHO: 
             {               
               if(length > sizeof(ResponseBuffer))
               {
                 length = sizeof(ResponseBuffer);
             //    TRACE_M(TF_VENDOR,"Length received greater than size of response buffer \r\n");
               }
               memcpy (&(ResponseBuffer[1]),&(data[1]),(length-1));
               BuffLength = length;
 			   break;
             }
           case APPLI_TEST_RANDOMIZATION_RANGE:  
             {
               /*Insert Test related Commands here*/
               break;
             }
           case APPLI_TEST_COUNTER:
             {
               /*Insert Test related Commands here*/
               break;
             }
           case APPLI_TEST_INC_COUNTER: 
             {
               /*Insert Test related Commands here*/
               break;
             }
           case APPLI_MODEL_PUBLISH_SELECT:
             {
                
               break;
             }
           default:
             {
                status = MOBLE_RESULT_FALSE;
                break;
             }
        }
       return status;
}

/**
* @brief  Process the Vendor LED Control Command
* @param  data: Pointer to the data received from peer_addr
* @param  length: Length of the data
* @param  elementIndex : selected element where '0' is first element        
* @retval MOBLE_RESULT status of result
*/ 
MOBLE_RESULT Appli_Vendor_LEDControl( MOBLEUINT8 const *data, MOBLEUINT32 length,
                                       MOBLEUINT8 elementIndex , MOBLE_ADDRESS dst_peer)
{
      MOBLE_RESULT status = MOBLE_RESULT_SUCCESS;
      MOBLEUINT8 subCommand; 
      subCommand = data[0];
      MOBLEUINT16 duty=0;
      MOBLEUINT16 intensityValue=0;
      TRACE_M(TF_VENDOR, "#03-%02hx!\n\r",data[0]);
      
 
      
     // TRACE_M(TF_VENDOR, "#03-%02hx!\n\r",data[0]);
      switch(subCommand)
      {
       /* 
       Meesage Received     B0     B1    B2      B3    B4    B5    B6     B7 
                   B0 - Sub-Cmd LED
                   B1-B7 - Data Bytes       
       */
      case APPLI_CMD_LED_BULB:
        {
          /*User Need to write the commands as per the element selected*/
          
     //     TRACE_M(TF_VENDOR,"Appli_LED_Control callback received for elementIndex %d \r\n", elementIndex);
          Appli_LedState = *(data+1); /* Toggle the state of the Blue LED */
          
          break;
        }
        
        /* Toggle Command */  
      case APPLI_CMD_TOGGLE:
        {
           /*User Need to write the commands as per the element selected*/
          
       //   TRACE_M(TF_VENDOR,"Appli_LED_Toggle callback received for elementIndex %d \r\n", elementIndex);
           
            Appli_LedState = !Appli_LedState; /* Toggle the state of the Blue LED */
          break;

        }
        /* On Command */  
      case APPLI_CMD_ON:
        {
          /*User Need to write the commands as per the element selected*/
          
       //   TRACE_M(TF_VENDOR,"Appli_LED_ON callback received for elementIndex %d \r\n", elementIndex);     
             
              Appli_LedState = 1; /* Switch On the Blue LED */
          
          break;
        }
        /* Off Command */  
      case APPLI_CMD_OFF:
        {
          /*User Need to write the commands as per the element selected*/
          
       //   TRACE_M(TF_VENDOR,"Appli_LED_OFF callback received for elementIndex %d \r\n", elementIndex);
                    
              Appli_LedState = 0; /* Switch Off the Blue LED */
        
          break;
        }
       case APPLI_CMD_LED_INTENSITY:
        {
          TRACE_M(TF_VENDOR,"Appli_LED_Intensity callback received for elementIndex %d \r\n", elementIndex);    
          intensityValue = data[2] << 8;
          intensityValue |= data[1];
          TRACE_M(TF_VENDOR,"%2x \r\n", intensityValue);
          duty = PwmValueMapping(intensityValue , 0x7FFF ,0);                         
          //Appli_LightPwmValue.IntensityValue = duty;
          if(duty >= 0x12BD)
          {
            Appli_LedState = 1;
          }
          else
          {
            Appli_LedState = 0;
          } 
      //    Light_UpdateLedValue(LOAD_STATE , Appli_LightPwmValue);    
        }
        /* Default case - Not valid command */
      default:
        {
          status = MOBLE_RESULT_FALSE;
          break;
        }
      }
         /*Buffer will be sent for Reliable Response*/
         /*First Byte is Sub Command and 2nd Byte is LED Status*/
           ResponseBuffer[0] = subCommand;
           ResponseBuffer[1] = Appli_LedState ;
           BuffLength = 2; 
           
       Appli_LedCtrl(); /* Controls the LED State */
      
      return status;
}

/**
* @brief  Process the Vendor Data write Command 
* @param  data: Pointer to the data received from peer_addr
* @param  length: Length of the data
* @retval MOBLE_RESULT status of result
*/          
MOBLE_RESULT Appli_Vendor_Data_write(MOBLEUINT8 const *data, MOBLEUINT32 length)
{
       MOBLE_RESULT status = MOBLE_RESULT_SUCCESS;  
       MOBLEUINT8 subCmd = data[0];
       /*First Byte is sending the Sub Command*/      
       ResponseBuffer[0]=subCmd;
      
      // TRACE_M(TF_VENDOR, "#0E-%02hx %02hx! \n\r",data[0], length);
       for(MOBLEUINT16 i=0; i<length; i++)
       {
       //   TRACE_I(TF_VENDOR,"%02hx ",data[i]);
       }
      // TRACE_I(TF_VENDOR,"\n\r");
       switch(subCmd)
       {     
         case APPLI_STRING_WRITE:
           {            
             memcpy(&ResponseBuffer,data,length);
             BuffLength = length;
             break;
           }
         default:
          {
            status = MOBLE_RESULT_FALSE;
            break;
          }
       }
      return status;        
}
                 
/**
* @brief  Appli_GetTestValue: This function is callback for Application
*          when Vensor application test command received then status message is to be provided
* @param  responseValue: Pointer to the status message
* @retval void
*/ 
void Appli_GetTestValue (MOBLEUINT8 *responseValue)
{
  *responseValue = TestHitCounter;
  *(responseValue+1)  = TestHitCounter >> 8;
  *(responseValue+2)  = TestHitCounter >> 16;
  *(responseValue+3)  = TestHitCounter >> 24;
  TestHitCounter = 0;
}
/**
* @brief  Process the Vendor LED Control Command
* @param  data: Pointer to the data received from peer_addr
* @param  length: Length of the data
* @param  elementIndex : selected element where '0' is first element       
* @param  dst_peer : Destination address
* @retval MOBLE_RESULT status of result
*/ 
MOBLE_RESULT Appli_Vendor_SetBigDataPacket(MOBLEUINT8 *data, MOBLEUINT32 length,
                                       MOBLEUINT8 elementIndex , MOBLE_ADDRESS dst_peer)
{
  MOBLE_RESULT status = MOBLE_RESULT_SUCCESS;
  
    if (length > VENDOR_DATA_BUFFER_SIZE)
    {
       status = MOBLE_RESULT_INVALIDARG;
    }
    memmove(Appli_VendorBigData.data, data, length);
    Appli_VendorBigData.dst = dst_peer;
    Appli_VendorBigData.length = length;
    Appli_VendorBigData.elementIndex = elementIndex;
    return status;
} 
/**
* @brief  Send Vendor big data packet
* @param  void      
* @retval MOBLE_RESULT status of result
*/ 
MOBLE_RESULT Appli_Vendor_SendBigDataPacket(void)
{
  MOBLE_RESULT status = MOBLE_RESULT_SUCCESS;
  
    if(BluenrgMesh_TrsptIsBusyState())
    {
       // SdkEvalLedOn(LED1); 
        status = MOBLE_RESULT_FALSE;
    }
    else
    {
        //SdkEvalLedOff(LED1);
        status = BluenrgMesh_SetRemoteData(Appli_VendorBigData.dst,
                                           Appli_VendorBigData.elementIndex,
                                           0x000E,                                   
                                           Appli_VendorBigData.data, 
                                           Appli_VendorBigData.length,
                                           MOBLE_FALSE, 
                                           MOBLE_TRUE);
 
    }
    return status;
}

/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

