/**
******************************************************************************
* @file    appli_generic_client.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Application interface for Generic client Mesh Models 
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
#include "appli_generic_client.h"

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
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
* @brief  Appli_Generic_OnOff_Status: This function is callback for Application
*          when Generic OnOff message is received
* @param  pOnOff_status: Pointer to the parameters received for message
* @param  plength: length of the data 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_OnOff_Status(MOBLEUINT8 const *pOnOff_status, MOBLEUINT32 plength, 
                                        MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex)
{
  
  TRACE_M(TF_GENERIC,"Appli_Generic_OnOff_Status callback received for elementIndex %d \r\n", elementIndex);
  TRACE_M(TF_SERIAL_CTRL,"#8204! for element %d \r\n", elementIndex);

  return MOBLE_RESULT_SUCCESS;
}

/******************************************************************************/
#ifdef ENABLE_GENERIC_MODEL_CLIENT_LEVEL
/******************************************************************************/

/**
* @brief  Appli_Generic_Level_Status: This function is callback for Application
*          when Generic Level Move message is received
* @param  plevel_status: Pointer to the parameters message
* @param  plength: length of data 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Generic_Level_Status(MOBLEUINT8 const *plevel_status, MOBLEUINT32 plength,
                                        MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex)
{

  TRACE_M(TF_GENERIC,"Generic_Level_Status callback received for elementIndex %d \r\n", elementIndex);

  TRACE_M(TF_SERIAL_CTRL,"#8208! for elementIndex %d \r\n", elementIndex);

  return MOBLE_RESULT_SUCCESS;
}

/******************************************************************************/
#endif  /* #ifdef ENABLE_GENERIC_MODEL_CLIENT_LEVEL */
/******************************************************************************/

/**
* @brief  Appli_Generic_DefaultTransitionTime_Status: This function is callback for Application
*          when Generic Power on off set message is received
* @param  pTransition_status: Pointer to the parameters message
* @param  plength: length of data 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/
MOBLE_RESULT Appli_Generic_DefaultTransitionTime_Status(MOBLEUINT8 const *pTransition_status , MOBLEUINT32 plength,MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex) 
{ 
  
  TRACE_M(TF_GENERIC,"Generic_DefaultTransitionTime_Status callback received for elementIndex %d \r\n", elementIndex);
  TRACE_M(TF_SERIAL_CTRL,"#8210! for elementIndex %d \r\n", elementIndex);
  
  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  Appli_Generic_PowerOnOff_Set: This function is callback for Application
*           when Generic Power on off set message is received
* @param   powerOnOff_status: Pointer to the parameters message
* @param  plength: length of data 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_PowerOnOff_Status(MOBLEUINT8 const *powerOnOff_status,\
                 MOBLEUINT32 plength, MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex) 
{  

  TRACE_M(TF_GENERIC,"Generic_PowerOnOff_Status callback received for elementIndex %d \r\n", elementIndex);
  TRACE_M(TF_SERIAL_CTRL,"#8212! for elementIndex %d \r\n", elementIndex);

  return MOBLE_RESULT_SUCCESS;
}

/**
* @brief  Appli_GenericClient_API: This function is a Wrapper to call Generic Client API depending on opcode received in input
* @param  elementIndex: Index of the element
* @param  msg_opcode: opcode of the desired API
* @param  msg_params: buffer containing the desired API parameters
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_GenericClient_API(MOBLEUINT8 elementIndex, MOBLEUINT16 msg_opcode, MOBLEUINT8 *msg_params) 
{ 
  MOBLE_RESULT result = MOBLE_RESULT_FAIL;
  switch(msg_opcode){
/******************************************************************************/
#ifdef ENABLE_GENERIC_MODEL_CLIENT_ONOFF  
/******************************************************************************/
  case GENERIC_ON_OFF_GET:
    {
      result = GenericClient_OnOff_Get(elementIndex);
      break;
    }
  case GENERIC_ON_OFF_SET_ACK:
    {
      result = GenericClient_OnOff_Set_Ack(elementIndex,
                              msg_params, 
                              (sizeof(Generic_OnOffParam_t)-2)); 
      break;
    }
  case GENERIC_ON_OFF_SET_UNACK:
    {  
      result = GenericClient_OnOff_Set_Unack(elementIndex,
                              msg_params, 
                              (sizeof(Generic_OnOffParam_t)-2));
      break;
    }
/******************************************************************************/    
#endif /* #ifdef ENABLE_GENERIC_MODEL_CLIENT_ONOFF */
/******************************************************************************/   
    
/******************************************************************************/
#ifdef ENABLE_GENERIC_MODEL_CLIENT_LEVEL 
/******************************************************************************/
  case GENERIC_LEVEL_GET:
    {
      result = GenericClient_Level_Get(elementIndex);
      break;
    }
  case GENERIC_LEVEL_SET_ACK:
    {
      result = GenericClient_Level_Set_Ack(elementIndex,
                                    msg_params, 
                                    (sizeof(Generic_LevelParam_t)-2));
      break;
    }
  case GENERIC_LEVEL_SET_UNACK:
    {
      result = GenericClient_Level_Set_Unack(elementIndex,
                                    msg_params, 
                                    (sizeof(Generic_LevelParam_t)-2));
      break;
    }
  case GENERIC_DELTA_SET:
    {

      result = GenericClient_Delta_Set_Ack(elementIndex,
                                    msg_params, 
                                    (sizeof(Generic_DeltaLevelParam_t)-2));
        break;
    }
  case GENERIC_DELTA_SET_UNACK:
    {
      result = GenericClient_Delta_Set_Unack(elementIndex,
                                    msg_params, 
                                    (sizeof(Generic_DeltaLevelParam_t)-2));
      break;
    }  
  case GENERIC_MOVE_SET:
    {
      result = GenericClient_Move_Set_Ack(elementIndex,
                                    msg_params, 
                                    (sizeof(Generic_LevelMoveParam_t)-2));
        break;
    }
  case GENERIC_MOVE_SET_UNACK:
    {
      result = GenericClient_Move_Set_Unack(elementIndex,
                                    msg_params, 
                                    (sizeof(Generic_LevelMoveParam_t)-2));
      break;
    }   
/******************************************************************************/    
#endif /* #ifdef ENABLE_GENERIC_MODEL_CLIENT_LEVEL */
/******************************************************************************/   

/******************************************************************************/
#ifdef ENABLE_GENERIC_MODEL_CLIENT_POWER_ONOFF 
/******************************************************************************/
  case GENERIC_POWER_ON_OFF_GET:
    {
      GenericClient_PowerOnOff_Get(elementIndex);
      break;
    }
  case GENERIC_POWER_ON_OFF_SET:
    {
      result = GenericClient_PowerOnOff_Set_Ack(elementIndex,
                                  msg_params, 
                                  sizeof(Generic_PowerOnOffParam_t));
      break;
    }
      case GENERIC_POWER_ON_OFF_SET_UNACK:
    {
      result = GenericClient_PowerOnOff_Set_Unack(elementIndex,
                                  msg_params, 
                                  sizeof(Generic_PowerOnOffParam_t));
      break;
    }
    
/******************************************************************************/    
#endif /* #ifdef ENABLE_GENERIC_MODEL_CLIENT_POWER_ONOFF */
/******************************************************************************/   

/******************************************************************************/    
#ifdef ENABLE_GENERIC_MODEL_CLIENT_DEFAULT_TRANSITION_TIME 
/******************************************************************************/
  case GENERIC_DEFAULT_TRANSITION_TIME_GET:
    {
      result = GenericClient_DefaultTransitionTime_Get(elementIndex);
      break;
    }
    
  case GENERIC_DEFAULT_TRANSITION_TIME_SET:
    {
      result = GenericClient_DefaultTransitionTime_Set_Ack(elementIndex,
                                  msg_params, 
                                  sizeof(Generic_DefaultTransitionParam_t));
      break;
    }
    
  case GENERIC_DEFAULT_TRANSITION_TIME_SET_UNACK:
    { 
      result = GenericClient_DefaultTransitionTime_Set_Unack(elementIndex,
                                  msg_params, 
                                  sizeof(Generic_DefaultTransitionParam_t));
      break;
    }
    
/******************************************************************************/    
#endif /* #ifdef ENABLE_GENERIC_MODEL_CLIENT_DEFAULT_TRANSITION_TIME */
/******************************************************************************/ 
 
  default:
    {
      TRACE_M(TF_GENERIC, "OpCode value invalid %d \r\n", msg_opcode);
      result = MOBLE_RESULT_FAIL;
    }
  }
  return result;
}

/**
* @}
*/

/**
* @}
*/

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

