/**
******************************************************************************
* @file    appli_light_client.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Application interface for light client Mesh Models 
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
#include "appli_generic.h"
#include "appli_light.h"
#include "common.h"
#include "mesh_cfg_usr.h"
#include "appli_nvm.h"
#include "appli_mesh.h"
#include "generic_client.h"
#include "appli_light_client.h"
#include "light_lc.h"
#include "light_client.h"


/** @addtogroup ST_BLE_Mesh
*  @{
*/

/** @addtogroup Application_Mesh_Models
*  @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

extern MOBLEUINT8 Tid_Client;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Appli_LightClient_API: This function is a Wrapper to call Light Client API depending on opcode received in input
* @param  elementIndex: Index of the element
* @param  msg_opcode: opcode of the desired API
* @param  msg_params: buffer containing the desired API parameters
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_LightClient_API(MOBLEUINT8 elementIndex, MOBLEUINT16 msg_opcode, MOBLEUINT8 *msg_params) 
{ 
  MOBLE_RESULT result = MOBLE_RESULT_FAIL;
    
  switch(msg_opcode){
/******************************************************************************/
#ifdef ENABLE_LIGHT_MODEL_CLIENT_LIGHTNESS  
/******************************************************************************/
  case LIGHT_LIGHTNESS_GET:
    {
      result = LightClient_Lightness_Get(elementIndex);
      break;
    }
  case LIGHT_LIGHTNESS_SET:
    {
      result = LightClient_Lightness_Set_Ack(elementIndex,
                                             msg_params, 
                                             (sizeof(Light_LightnessParam_t)-4));   /*Remove the size of Linear Lightness params,delay,transition time */
      break;
    }
  case LIGHT_LIGHTNESS_SET_UNACK:
    {  
      result = LightClient_Lightness_Set_Unack(elementIndex,
                                               msg_params, 
                                               (sizeof(Light_LightnessParam_t)-4));  /*Remove the size of Linear Lightness params,delay,transition time */
      break;
    }
    
  case LIGHT_LIGHTNESS_LINEAR_GET:
    {
      result = LightClient_Lightness_Linear_Get(elementIndex);
      break;
    }
  case LIGHT_LIGHTNESS_LINEAR_SET:
    {
      result = LightClient_Lightness_Linear_Set_Ack(elementIndex,
                                                    msg_params, 
                                                    (sizeof(Light_LightnessParam_t)-4));   /*Remove the size of  Lightness params,delay,transition time */
      break;
    }
  case LIGHT_LIGHTNESS_LINEAR_SET_UNACK:
    {     
      result = LightClient_Lightness_Linear_Set_Unack(elementIndex,
                                                      msg_params, 
                                                      (sizeof(Light_LightnessParam_t)-4));  /*Remove the size of  Lightness params,delay,transition time */
      break;
    }
    
  case LIGHT_LIGHTNESS_DEFAULT_GET:
    {
      result = LightClient_Lightness_Default_Get(elementIndex);
      break;
    }
  case LIGHT_LIGHTNESS_DEFAULT_SET:
    {
      result = LightClient_Lightness_Default_Set_Ack(elementIndex,
                                                     msg_params, 
                                                     sizeof(Light_LightnessDefaultParam_t));
      break;
    }
  case LIGHT_LIGHTNESS_DEFAULT_SET_UNACK:
    {     
      result = LightClient_Lightness_Default_Set_Unack(elementIndex,
                                                       msg_params, 
                                                       sizeof(Light_LightnessDefaultParam_t));
      break;
    }
    
    
  case LIGHT_LIGHTNESS_RANGE_GET:
    {
      result = LightClient_Lightness_Range_Get(elementIndex);
      break;
    }
  case LIGHT_LIGHTNESS_RANGE_SET:
    {
      result = LightClient_Lightness_Range_Set_Ack(elementIndex,
                                                     msg_params, 
                                                     sizeof(Light_LightnessRangeParam_t)-1);    /*Remove the size of StatusCode*/
      break;
    }
  case LIGHT_LIGHTNESS_RANGE_SET_UNACK:
    {     
      result = LightClient_Lightness_Range_Set_Unack(elementIndex,
                                                       msg_params, 
                                                       sizeof(Light_LightnessRangeParam_t)-1);  /*Remove the size of StatusCode*/
      break;
    }


/******************************************************************************/
#endif /* #ifdef ENABLE_LIGHT_MODEL_CLIENT_LIGHTNESS */
/******************************************************************************/
    
/******************************************************************************/
#ifdef ENABLE_LIGHT_MODEL_CLIENT_CTL  
/******************************************************************************/
  case LIGHT_CTL_GET:
    {
      result = LightClient_Ctl_Get(elementIndex);
      break;
    }
  case LIGHT_CTL_SET:
    {
      result = LightClient_Ctl_Set_Ack(elementIndex,
                                       msg_params, 
                                       (sizeof(Light_CtlParam_t)-6)); /*Remove the size of Last_Lightness, Last_Temperature, Delay, transition time  */
      break;
    }
  case LIGHT_CTL_SET_UNACK:
    {  
      result = LightClient_Ctl_Set_Unack(elementIndex,
                                         msg_params, 
                                         (sizeof(Light_CtlParam_t)-6)); /*Remove the size of Last_Lightness and Last_TemperatureDelay, transition time */
      break;
    }
    
  case LIGHT_CTL_TEMPERATURE_GET:
    {
      result = LightClient_Ctl_Temperature_Get(elementIndex);
      break;
    }
  case LIGHT_CTL_TEMPERATURE_SET:
    {
      result = LightClient_Ctl_Temperature_Set_Ack(elementIndex,
                                                   msg_params, 
                                                   (sizeof(Light_CtlTemperatureParam_t)-2));
      break;
    }
  case LIGHT_CTL_TEMPERATURE_SET_UNACK:
    {  
      result = LightClient_Ctl_Temperature_Set_Unack(elementIndex,
                                                     msg_params, 
                                                     (sizeof(Light_CtlTemperatureParam_t)-2));
      break;
    }
                                                     
    case LIGHT_CTL_TEMPERATURE_RANGE_GET:
      {
        result = LightClient_Ctl_Temperature_Range_Get(elementIndex);
        break;
      }
    case LIGHT_CTL_TEMPERATURE_RANGE_SET:
      {
        result = LightClient_Ctl_Temperature_Range_Set_Ack(elementIndex,
                                                           msg_params, 
                                                           sizeof(Light_CtlTemperatureRangeParam_t)-1);  /*Remove the size of StatusCode */
        break;
      }
  case LIGHT_CTL_TEMPERATURE_RANGE_SET_UNACK:
    {  
      result = LightClient_Ctl_Temperature_Range_Set_Unack(elementIndex,
                                                           msg_params, 
                                                           sizeof(Light_CtlTemperatureRangeParam_t)-1);  /*Remove the size of StatusCode */
      break;
    }
      
    case LIGHT_CTL_DEFAULT_GET:
      {
        result = LightClient_Ctl_Default_Get(elementIndex);
        break;
      }
    case LIGHT_CTL_DEFAULT_SET:
      {
        result = LightClient_Ctl_Default_Set_Ack(elementIndex,
                                                 msg_params, 
                                                 sizeof(Light_CtlDefaultParam_t));
        break;
      }
  case LIGHT_CTL_DEFAULT_SET_UNACK:
    {  
      result = LightClient_Ctl_Default_Set_Unack(elementIndex,
                                                 msg_params, 
                                                 sizeof(Light_CtlDefaultParam_t));
      break;
    }
/******************************************************************************/
#endif /* #ifdef ENABLE_LIGHT_MODEL_CLIENT_CTL */
/******************************************************************************/

/******************************************************************************/
#ifdef ENABLE_LIGHT_MODEL_CLIENT_HSL  
/******************************************************************************/
  case LIGHT_HSL_GET:
    {
      result = LightClient_Hsl_Get(elementIndex);
      break;
    }
  case LIGHT_HSL_SET:
    {
      result = LightClient_Hsl_Set_Ack(elementIndex,
                                       msg_params, 
                                       (sizeof(Light_HslParam_t)-2)); 
      break;
    }
  case LIGHT_HSL_SET_UNACK:
    {  
      result = LightClient_Hsl_Set_Unack(elementIndex,
                                         msg_params, 
                                         (sizeof(Light_HslParam_t)-2));
      break;
    }
    
  case LIGHT_HSL_DEFAULT_GET:
    {
      result = LightClient_Hsl_Default_Get(elementIndex);
      break;
    }
  case LIGHT_HSL_DEFAULT_SET:
    {
      result = LightClient_Hsl_Default_Set_Ack(elementIndex,
                                       msg_params, 
                                       sizeof(Light_HslDefaultParam_t)); 
      break;
    }
  case LIGHT_HSL_DEFAULT_SET_UNACK:
    {  
      result = LightClient_Hsl_Default_Set_Unack(elementIndex,
                                         msg_params, 
                                         sizeof(Light_HslDefaultParam_t));
      break;
    }
    
  case LIGHT_HSL_RANGE_GET:
    {
      result = LightClient_Hsl_Range_Get(elementIndex);
      break;
    }
  case LIGHT_HSL_RANGE_SET:
    {
      result = LightClient_Hsl_Range_Set_Ack(elementIndex,
                                               msg_params, 
                                               sizeof(Light_HslRangeParam_t)-1);  /*Remove the size of StatusCode */
      break;
    }
  case LIGHT_HSL_RANGE_SET_UNACK:
    {  
      result = LightClient_Hsl_Range_Set_Unack(elementIndex,
                                                 msg_params, 
                                                 sizeof(Light_HslRangeParam_t)-1);  /*Remove the size of StatusCode */
      break;
    }
    
  case LIGHT_HSL_HUE_GET:
    {
      result = LightClient_Hsl_Hue_Get(elementIndex);
      break;
    }
  case LIGHT_HSL_HUE_SET:
    {
      result = LightClient_Hsl_Hue_Set_Ack(elementIndex,
                                             msg_params, 
                                             (sizeof(Light_HslHueParam_t)-2));
      break;
    }
  case LIGHT_HSL_HUE_SET_UNACK:
    {  
      result = LightClient_Hsl_Hue_Set_Unack(elementIndex,
                                               msg_params, 
                                               (sizeof(Light_HslHueParam_t)-2));
      break;
    }
    
    case LIGHT_HSL_SATURATION_GET:
      {
        result = LightClient_Hsl_Saturation_Get(elementIndex);
        break;
      }
    case LIGHT_HSL_SATURATION_SET:
      {
        result = LightClient_Hsl_Saturation_Set_Ack(elementIndex,
                                                    msg_params, 
                                                    (sizeof(Light_HslSaturationParam_t)-2));
        break;
      }
    case LIGHT_HSL_SATURATION_SET_UNACK:
      {  
        result = LightClient_Hsl_Saturation_Set_Unack(elementIndex,
                                                      msg_params, 
                                                      (sizeof(Light_HslSaturationParam_t)-2));
        break;
    }
/******************************************************************************/
#endif /* #ifdef ENABLE_LIGHT_MODEL_CLIENT_HSL */
/******************************************************************************/   
    /******************************************************************************/
#ifdef ENABLE_LIGHT_MODEL_CLIENT_LC  
/******************************************************************************/   
    case LIGHT_LC_MODE_GET:
      {
        result = LightClient_LC_Mode_Get(elementIndex);
        break;
      }
    case LIGHT_LC_MODE_SET:
      {
        result = LightClient_LC_Mode_Set_Ack(elementIndex,
                                             msg_params, 
                                             sizeof(Light_LC_ModeParam_t));
        break;
      }
    case LIGHT_LC_MODE_SET_UNACK:
      {  
        result = LightClient_LC_Mode_Set_Unack(elementIndex,
                                               msg_params, 
                                               sizeof(Light_LC_ModeParam_t));
        break;
      }
    case LIGHT_LC_OM_GET:
      {
        result = LightClient_LC_OM_Get(elementIndex);
        break;
      }
    case LIGHT_LC_OM_SET:
      {
        result = LightClient_LC_OM_Set_Ack(elementIndex,
                                             msg_params, 
                                             sizeof(Light_LC_OccupancyModeParam_t));
        break;
      }
    case LIGHT_LC_OM_SET_UNACK:
      {  
        result = LightClient_LC_OM_Set_Unack(elementIndex,
                                               msg_params, 
                                               sizeof(Light_LC_OccupancyModeParam_t));
        break;
      }
    case LIGHT_LC_ON_OFF_GET:
      {
        result = LightClient_LC_OnOff_Get(elementIndex);
        break;
      }
    case LIGHT_LC_ON_OFF_SET:
      {
        result = LightClient_LC_OnOff_Set_Ack(elementIndex,
                                             msg_params, 
                                             sizeof(Light_LC_OnOffParam_t));
        break;
      }
    case LIGHT_LC_ON_OFF_SET_UNACK:
      {  
        result = LightClient_LC_OnOff_Set_Unack(elementIndex,
                                               msg_params, 
                                               sizeof(Light_LC_OnOffParam_t));
        break;
      }
/******************************************************************************/
#endif /* #ifdef ENABLE_LIGHT_MODEL_CLIENT_LC */
/******************************************************************************/
    default:
        {
          TRACE_M(TF_LIGHT, "OpCode value invalid %d \r\n", msg_opcode);
          result = MOBLE_RESULT_FAIL;
        }
  }
  return result;
}

/**
* @brief  Appli_Light_Lightness_Status: This function is callback for Application
*           when Light Lightness status message is received
* @param  pLightness_status: Pointer to the parameters received for message
* @param  pLength: length of data 
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Light_Lightness_Status(MOBLEUINT8 const *pLightness_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#824E! \n\r");
  TRACE_M(TF_LIGHT, "Element index %d\r\n", elementIndex); 
  
  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  Appli_Light_Lightness_Linear_Status: This function is callback for Application
*         when Light Lightness Linear status message is received
* @param  pLightnessLinear_status: Pointer to the parameters received for message
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @param  pLength: length of data
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Light_Lightness_Linear_Status(MOBLEUINT8 const *pLightnessLinear_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#8252! \n\r");
  TRACE_M(TF_LIGHT,"Appli_Light_Lightness_Linear_Status callback received for elementIndex %d \r\n", elementIndex);
  
  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  Appli_Light_Lightness_Default_Status: This function is callback for Application
*         when Light Lightness Default status message is received
* @param  pLightnessDefault_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Light_Lightness_Default_Status(MOBLEUINT8 const *pLightnessDefault_status, MOBLEUINT32 pLength
                                                  , MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#8256! \n\r");
  TRACE_M(TF_LIGHT,"Appli_Light_Lightness_Default_Status callback received for elementIndex %d \r\n", elementIndex);
  
  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  Appli_Light_Lightness_Range_Status: This function is callback for Application
*         when Light Lightness range ststus message is received
* @param  pLightnessRange_status: Pointer to the parameters received for message
* @param  pLength: length of data 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Light_Lightness_Range_Status(MOBLEUINT8 const *pLightnessRange_status, MOBLEUINT32 pLength
                                                , MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#8258! \n\r");
  TRACE_M(TF_LIGHT,"Appli_Light_Lightness_Range_Status callback received for elementIndex %d \r\n", elementIndex);
  
  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  Appli_Light_Ctl_Status: This function is callback for Application
*         when Light CTL status message is received
* @param  pLightCtl_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Light_Ctl_Status(MOBLEUINT8 const *pLightCtl_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#8260! \n\r");
  TRACE_M(TF_LIGHT,"Light_Ctl_Status callback received for elementIndex %d \r\n", elementIndex);
  
  return MOBLE_RESULT_SUCCESS;
}

/**                                                  
* @brief  Appli_Light_CtlTemperature_Status: This function is callback for Application
*         when Light CTL temperature status message is received
* @param  pLightCtlTemp_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Light_CtlTemperature_Status(MOBLEUINT8 const *pLightCtlTemp_status, MOBLEUINT32 pLength
                                               , MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#8266! \n\r");
  TRACE_M(TF_LIGHT,"Light_CtlTemperature_Status callback received for elementIndex %d \r\n", elementIndex);
  
  return MOBLE_RESULT_SUCCESS;
}

/**                                                  
* @brief  Appli_Light_CtlTemperature_Range_Set: This function is callback for Application
*         when Light CTL temperature range status message is received
* @param  pCtlTempRange_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Light_CtlTemperature_Range_Status(MOBLEUINT8 const *pCtlTempRange_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#8263! \n\r");
  TRACE_M(TF_LIGHT,"Appli_Light_CtlTemperature_Range_Status callback received for elementIndex %d \r\n", elementIndex);
  
  return MOBLE_RESULT_SUCCESS;
}

/**                                                  
* @brief  Appli_Light_CtlDefault_Status: This function is callback for Application
*         when Light CTL Default status message is received
* @param  pCtlDefault_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Light_CtlDefault_Status(MOBLEUINT8 const *pCtlDefault_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#8268! \n\r");
  TRACE_M(TF_LIGHT,"Light_Ctl_DefaultStatus callback received for elementIndex %d \r\n", elementIndex);
  return MOBLE_RESULT_SUCCESS;
}

/**                                                  
* @brief  Appli_Light_Hsl_Status: This function is callback for Application
*         when Light HSL status message is received
* @param  pHsl_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Light_Hsl_Status(MOBLEUINT8 const *pHsl_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#8278! \n\r");
  TRACE_M(TF_LIGHT,"Light_Hsl_Status callback received for elementIndex %d \r\n", elementIndex);

  return MOBLE_RESULT_SUCCESS;
}

/**                                                  
* @brief  Appli_Light_HslHue_Status: This function is callback for Application
*         when Light HSL HUE status message is received
* @param  pHslHue_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Light_HslHue_Status(MOBLEUINT8 const *pHslHue_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#8271! \n\r");
  TRACE_M(TF_LIGHT,"Light_HslHue_Status callback received for elementIndex %d \r\n", elementIndex);
  return MOBLE_RESULT_SUCCESS;
}

/**                                                  
* @brief  Appli_Light_HslSaturation_Status: This function is callback for Application
*         when Light HSL Saturation status message is received
* @param  pHslSaturation_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Light_HslSaturation_Status(MOBLEUINT8 const *pHslSaturation_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{

  TRACE_M(TF_SERIAL_CTRL,"#8275! \n\r");
  TRACE_M(TF_LIGHT,"Light_HslSaturation_Status callback received for elementIndex %d \r\n", elementIndex);
  return MOBLE_RESULT_SUCCESS;
}

/**                                                  
* @brief  Appli_Light_HslDefault_Status: This function is callback for Application
*          when Light HSL Default status  message is received
* @param  pHslDefault_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Light_HslDefault_Status(MOBLEUINT8 const *pHslDefault_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{

  TRACE_M(TF_SERIAL_CTRL,"#827C! \n\r");
  TRACE_M(TF_LIGHT,"Light_HslDefault_Status callback received for elementIndex %d \r\n", elementIndex);   
  return MOBLE_RESULT_SUCCESS;
}

/**                                                  
* @brief  Appli_Light_HslRange_Status: This function is callback for Application
*         when Light HSL range status message is received
* @param  pHslRange_status: Pointer to the parameters received for message
* @param  pLength: length of data
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Light_HslRange_Status(MOBLEUINT8 const *pHslRange_status, MOBLEUINT32 pLength, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{
  TRACE_M(TF_SERIAL_CTRL,"#827E! \n\r");
  TRACE_M(TF_LIGHT,"Light_HslRange_Status callback received for elementIndex %d \r\n", elementIndex); 
  return MOBLE_RESULT_SUCCESS;
}

/**
  * @brief  Callback corresponding to LightLCc_ModeSatus_cb
  * @param  Message parameters
  * @retval None
*/ 
void Appli_LightLCc_ModeStatus(MOBLEUINT8 const* pLightLCMode_status,
                               MOBLEUINT32 plength, 
                               MOBLEUINT16 dstPeer, 
                               MOBLEUINT8 elementIndex)
{                              
  MOBLEUINT8 i;
  TRACE_M(TF_LIGHT_LC,"LightLCs_ModeStatus callback received for element %d \r\n", elementIndex);
  TRACE_M(TF_SERIAL_CTRL,"#8294!\r\n");
  
  for(i = 0; i < plength; i++)
  {
    if(i == 0)
      TRACE_M(TF_SERIAL_CTRL,"Light LC Mode value: %d\n\r", 
              pLightLCMode_status[i]);
  }
}

/**
  * @brief  Callback corresponding to LightLCc_OmStatus_cb
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCc_OmStatus(MOBLEUINT8 const* pLightLCOccupancyMode_status,
                             MOBLEUINT32 plength, 
                             MOBLEUINT16 dstPeer, 
                             MOBLEUINT8 elementIndex)
{                              
  MOBLEUINT8 i;
  TRACE_M(TF_LIGHT_LC,"LightLCs_OmStatus callback received for element %d \r\n", elementIndex);
  TRACE_M(TF_SERIAL_CTRL,"#8298!\r\n");
  
  for(i = 0; i < plength; i++)
  {
    if(i == 0)
      TRACE_M(TF_SERIAL_CTRL,"Light LC OM value: %d\n\r", 
              pLightLCOccupancyMode_status[i]);
  }
}

/**
  * @brief  Callback corresponding to LightLCc_OnOffStatus_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
*/ 
void Appli_LightLCc_OnOffStatus(MOBLEUINT8 const* pLightLCOnOff_status,
                                MOBLEUINT32 plength, 
                                MOBLEUINT16 dstPeer, 
                                MOBLEUINT8 elementIndex)
{                              
  MOBLEUINT8 i;
  TRACE_M(TF_LIGHT_LC,"LightLCs_OnOffStatus callback received for element %d \r\n", elementIndex);
  TRACE_M(TF_SERIAL_CTRL,"#829C!\r\n");
  
  for(i = 0; i < plength; i++)
  {
    if(i == 0)
      TRACE_M(TF_SERIAL_CTRL,"Light LC OnOff status: %d\n\r", 
              pLightLCOnOff_status[i]);
  }
}

/**
  * @brief  Callback corresponding to LightLCc_PropertyStatus_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
*/ 
void Appli_LightLCc_PropertyStatus(MOBLEUINT8 const* pLightLCProperty_status,
                                   MOBLEUINT32 plength, 
                                   MOBLEUINT16 dstPeer, 
                                   MOBLEUINT8 elementIndex)
{                              
  MOBLEUINT8 i;
  TRACE_M(TF_LIGHT_LC,"LightLCs_PropertyStatus callback received for element %d \r\n", elementIndex);
  TRACE_M(TF_SERIAL_CTRL,"#64!\r\n");
  
  for(i = 0; i < plength; i++)
  {
    if(i == 0)
      TRACE_M(TF_SERIAL_CTRL,"Light LC Property status: %d\n\r", 
              pLightLCProperty_status[i]);
  }
}

/**
* @}
*/

/**
* @}
*/

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

