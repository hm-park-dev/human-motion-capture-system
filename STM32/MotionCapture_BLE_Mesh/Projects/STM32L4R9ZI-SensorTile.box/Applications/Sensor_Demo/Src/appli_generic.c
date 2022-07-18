/**
******************************************************************************
* @file    appli_generic.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Application interface for Generic Mesh Models 
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

extern MOBLEUINT8 RestoreFlag;
extern MOBLEUINT16 IntensityValue;
extern MOBLEUINT8 IntensityFlag;
extern MOBLEUINT8 PowerOnOff_flag;
extern Appli_LightPwmValue_t Appli_LightPwmValue;

Appli_Generic_OnOffSet AppliOnOffSet[APPLICATION_NUMBER_OF_ELEMENTS];
Appli_Generic_LevelSet AppliLevelSet[APPLICATION_NUMBER_OF_ELEMENTS];
Appli_Generic_PowerOnOffSet AppliPowerOnSet[APPLICATION_NUMBER_OF_ELEMENTS];
Appli_Generic_DefaultTransitionSet AppliDefaultTransitionSet[APPLICATION_NUMBER_OF_ELEMENTS];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
#ifdef ENABLE_GENERIC_MODEL_SERVER_ONOFF
/******************************************************************************/

/**
* @brief  Appli_Generic_OnOff_Set: This function is callback for Application
*          when Generic OnOff message is received
* @param  pGeneric_OnOffParam: Pointer to the parameters received for message
* @param  OptionalValid: Flag to inform about the validity of optional parameters 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_OnOff_Set(Generic_OnOffStatus_t* pGeneric_OnOffParam, 
                                     MOBLEUINT8 OptionalValid,
									 MOBLEUINT16 dstPeer, 
                                     MOBLEUINT8 elementIndex)
{
  /* LED control only for main element */
  if(elementIndex == GENERIC_SERVER_MAIN_ELEMENT_INDEX)
  { 
    /* This condition is applicable when user want to on off the light with some 
    default transition value, or optionalValid =IN_TRANSITION ,
    transition is in progress.
    */
  if((OptionalValid == DEFAULT_TRANSITION) || (OptionalValid == IN_TRANSITION))
   {

    if( pGeneric_OnOffParam->Present_OnOff_State >= APPLI_LED_ON)
    {
      AppliOnOffSet[elementIndex].Present_OnOff = pGeneric_OnOffParam->Present_OnOff_State;
        Appli_LightPwmValue.IntensityValue = PWM_TIME_PERIOD;
     /* Light_UpdateLedValue(LOAD_STATE ,Appli_LightPwmValue); */
    }
    else
    {
      Appli_LightPwmValue.IntensityValue = pGeneric_OnOffParam->Present_OnOff_State;
    /*  Light_UpdateLedValue(LOAD_STATE ,Appli_LightPwmValue); */
    }
  }  
  else
  {
    AppliOnOffSet[elementIndex].Present_OnOff = pGeneric_OnOffParam->Present_OnOff_State;
	SetLed(AppliOnOffSet[elementIndex].Present_OnOff);
	if((AppliOnOffSet[elementIndex].Present_OnOff == APPLI_LED_ON) && (OptionalValid == NO_TRANSITION))
    { 
      Appli_LightPwmValue.IntensityValue = PWM_TIME_PERIOD;
      /* Light_UpdateLedValue(LOAD_STATE , Appli_LightPwmValue); */
    }
    else
    { Appli_LightPwmValue.IntensityValue = PWM_VALUE_OFF;
     // Light_UpdateLedValue(RESET_STATE , Appli_LightPwmValue);
    } 
   }
 }

  TRACE_M(TF_GENERIC, "Appli_Generic_OnOff_Set callback received for elementIndex %d \r\n", elementIndex);           
  TRACE_M(TF_SERIAL_CTRL, "#8202!for elementIndex %d \r\n", elementIndex);
  
  NvmStatePowerFlag_Set(GENERIC_ON_OFF_NVM_FLAG, elementIndex);
    
  return MOBLE_RESULT_SUCCESS;
}

/******************************************************************************/
#endif  /* #ifdef ENABLE_GENERIC_MODEL_SERVER_ONOFF */
/******************************************************************************/

/******************************************************************************/
#ifdef ENABLE_GENERIC_MODEL_SERVER_LEVEL
/******************************************************************************/

/**
* @brief  Appli_Generic_Level_Set: This function is callback for Application
*          when Generic Level message is received
* @param  plevelParam: Pointer to the parameters message
* @param  OptionalValid: Flag to inform about the validity of optional parameters 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_Level_Set(Generic_LevelStatus_t* plevelParam, 
                                     MOBLEUINT8 OptionalValid,MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{ 
  MOBLEUINT16 duty;
  static MOBLEUINT16 previousIntensity = 0;
  
  AppliLevelSet[elementIndex].Present_Level16= plevelParam->Present_Level16;
  if(AppliLevelSet[elementIndex].Present_Level16 >= 50)
  {
    SetLed(1);
  }
  else
  {
    SetLed(0);
  } 
  

  if(AppliLevelSet[elementIndex].Present_Level16 <= 0)
  {
    AppliLevelSet[elementIndex].Present_Level16 = 0;
  }
  
  IntensityValue =  AppliLevelSet[elementIndex].Present_Level16;
  
  if(((IntensityValue > previousIntensity) && (IntensityValue <PWM_TIME_PERIOD)) ||
     IntensityValue == INTENSITY_LEVEL_ZERO)
  {
    IntensityFlag = FALSE;
  }
  else
  {
    IntensityFlag = TRUE;
  }
  previousIntensity = IntensityValue;     
  
  if(AppliLevelSet[elementIndex].Present_Level16 < 0x00)
  {
     AppliLevelSet[elementIndex].Present_Level16 = 0;
  }
  duty = PwmValueMapping(AppliLevelSet[elementIndex].Present_Level16 , 0x7FFF ,0x0000); 
  Appli_LightPwmValue.IntensityValue = duty;
  //Light_UpdateLedValue(LOAD_STATE , Appli_LightPwmValue);
  
  TRACE_M(TF_GENERIC,"Appli_Generic_Level_Set callback received for elementIndex %d \r\n", elementIndex);
  TRACE_M(TF_SERIAL_CTRL,"#8206!for elementIndex %d \r\n", elementIndex);

  NvmStatePowerFlag_Set(GENERIC_LEVEL_NVM_FLAG, elementIndex);
  
  return MOBLE_RESULT_SUCCESS;
}


/**
* @brief  Appli_Generic_Delta_Set: This function is callback for Application
*          when Generic Level Delta message is received
* @param  pdeltalevelParam: Pointer to the parameters message
* @param  OptionalValid: Flag to inform about the validity of optional parameters
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_LevelDelta_Set(Generic_LevelStatus_t* pdeltalevelParam, 
                                          MOBLEUINT8 OptionalValid,MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{  
  AppliLevelSet[elementIndex].Present_Level16 = pdeltalevelParam->Present_Level16;
  
  /* For demo, if Level is more than 50, switch ON the LED */
  if (AppliLevelSet[elementIndex].Present_Level16 >= 50)
  {
    SetLed(1);
    Appli_LightPwmValue.IntensityValue = PWM_TIME_PERIOD;
    //Light_UpdateLedValue(LOAD_STATE , Appli_LightPwmValue);
  }
  else
  {
    SetLed(0);
    //Light_UpdateLedValue(RESET_STATE , Appli_LightPwmValue);
  }
  TRACE_M(TF_SERIAL_CTRL,"#8206! for elementIndex %d \r\n", elementIndex);


  return MOBLE_RESULT_SUCCESS;
}


/**
* @brief  Appli_Generic_LevelMove_Set: This function is callback for Application
*          when Generic Level Move message is received
* @param  pdeltaMoveParam: Pointer to the parameters message
* @param  OptionalValid: Flag to inform about the validity of optional parameters 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_LevelMove_Set(Generic_LevelStatus_t* pdeltaMoveParam, 
                                         MOBLEUINT8 OptionalValid, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{ 
  if(OptionalValid == 1) 
  {
    AppliLevelSet[elementIndex].Present_Level16= pdeltaMoveParam->Present_Level16;   
  }

  TRACE_M(TF_SERIAL_CTRL,"#8206! for elementIndex %d \r\n", elementIndex);
  return MOBLE_RESULT_SUCCESS;
  
}

/******************************************************************************/
#endif   /* ENABLE_GENERIC_MODEL_SERVER_LEVEL */
/******************************************************************************/

/******************************************************************************/
#ifdef ENABLE_GENERIC_MODEL_SERVER_POWER_ONOFF
/******************************************************************************/

/**
* @brief  Appli_Generic_PowerOnOff_Set: This function is callback for Application
*           when Generic Power on off set message is received
* @param  pPowerOnOffParam: Pointer to the parameters message
* @param  OptionalValid: Flag to inform about the validity of optional parameters 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_PowerOnOff_Set(Generic_PowerOnOffParam_t* pPowerOnOffParam, 
                                         MOBLEUINT8 OptionalValid, MOBLEUINT16 dstPeer, 
                                              MOBLEUINT8 elementIndex)
{ 
  
  AppliPowerOnSet[elementIndex].PowerOnState = pPowerOnOffParam->PowerOnOffState;
  TRACE_M(TF_SERIAL_CTRL,"#8213! for elementIndex %d \r\n", elementIndex);
  TRACE_M(TF_GENERIC,"Appli_Generic_PowerOnOff_Set callback received for elementIndex %d \r\n", elementIndex);
  
  /* set the flag value for NVM store */
  AppliNvm_SaveMessageParam();
  
  return MOBLE_RESULT_SUCCESS;
}

/******************************************************************************/
#endif  /* ENABLE_GENERIC_MODEL_SERVER_POWER_ONOFF */
/******************************************************************************/

/******************************************************************************/
#ifdef ENABLE_GENERIC_MODEL_SERVER_DEFAULT_TRANSITION_TIME
/******************************************************************************/

/**
* @brief  Appli_Generic_DefaultTransitionTime_Set: This function is callback for Application
*          when Generic Power on off set message is received
* @param  pDefaultTimeParam: Pointer to the parameters message
* @param  OptionalValid: Flag to inform about the validity of optional parameters 
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_DefaultTransitionTime_Set(Generic_DefaultTransitionParam_t* pDefaultTimeParam, 
                                         MOBLEUINT8 OptionalValid, MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex)
{

  AppliDefaultTransitionSet[elementIndex].DefaultTransitionTime = pDefaultTimeParam->DefaultTransitionTime;

  return MOBLE_RESULT_SUCCESS;
}



/******************************************************************************/
#endif   /* ENABLE_GENERIC_MODEL_SERVER_DEFAULT_TRANSITION_TIME */
/******************************************************************************/


/**
* @brief  Appli_Generic_GetOnOffState: This function is callback for Application
*          when Generic on off status message is to be provided
* @param  pOnOff_status: Pointer to the status message
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_GetOnOffStatus(MOBLEUINT8* pOnOff_Status,MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex)                                        
{
  
  *pOnOff_Status = AppliOnOffSet[elementIndex].Present_OnOff;
  return MOBLE_RESULT_SUCCESS; 
}


/**
* @brief  Appli_Generic_GetOnOffValue: This function is callback for Application
          to get the PWM value for the generic on off
* @param  pOnOff_Value: Pointer to the status message
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_GetOnOffValue(MOBLEUINT8* pOnOff_Value, MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex)                                        
{
  
  return MOBLE_RESULT_SUCCESS; 
}


/**
* @brief  Appli_Generic_GetLevelStatus: This function is callback for Application
            when Generic Level status message is to be provided
* @param  pLevel_status: Pointer to the status message
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_GetLevelStatus(MOBLEUINT8* pLevel_Status, MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex) 
{ 

  *pLevel_Status = AppliLevelSet[elementIndex].Present_Level16;
  *(pLevel_Status+1) = AppliLevelSet[elementIndex].Present_Level16 >> 8;

  return MOBLE_RESULT_SUCCESS; 
}


/**
* @brief  Appli_Generic_GetPowerOnOffStatus: This function is callback for Application
*          when Generic Get Power status message is to be provided
* @param  pLevel_status: Pointer to the status message
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_GetPowerOnOffStatus(MOBLEUINT8* pPower_Status, MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex) 
{ 

  *pPower_Status = AppliPowerOnSet[elementIndex].PowerOnState;

  return MOBLE_RESULT_SUCCESS; 
}


/**
* @brief  Appli_Generic_GetDefaultTransitionStatus: This function is callback for 
*           Application when Generic Level status message is to be provided
* @param  pTransition_Status: Pointer to the status message
* @param  dstPeer: destination send by peer for this node. It can be a
*                     unicast or group address 
* @param  elementIndex: index of the element received from peer for this node which
*                     is elementNumber-1
* @retval MOBLE_RESULT
*/ 
MOBLE_RESULT Appli_Generic_GetDefaultTransitionStatus(MOBLEUINT8* pTransition_Status,MOBLEUINT16 dstPeer, MOBLEUINT8 elementIndex) 
{ 

  *pTransition_Status = AppliDefaultTransitionSet[elementIndex].DefaultTransitionTime;

  return MOBLE_RESULT_SUCCESS; 
}


/**
* @}
*/

/**
* @}
*/

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/

