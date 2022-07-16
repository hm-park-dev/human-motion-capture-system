/**
******************************************************************************
* @file    appli_light_lc.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Application interface for light LC Mesh Models 
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
#include "mesh_cfg.h"
#include "types.h"
#include "appli_generic.h"
#include "appli_light.h"
#include "common.h"
#include "mesh_cfg_usr.h"
#include "appli_light_lc.h"
#include "light_lc.h"

/** @addtogroup ST_BLE_Mesh
*  @{
*/
/** @addtogroup models_BlueNRG2
*  @{
*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variable ----------------------------------------------------------*/
__attribute__((aligned(4))) 
const light_lc_cb_t AppliLightLc_cb = 
{
  Appli_LightLCs_ModeGet,
  Appli_LightLCs_ModeSet,
  Appli_LightLCs_ModeSetUnack,
  Appli_LightLCs_OmGet,
  Appli_LightLCs_OmSet,
  Appli_LightLCs_OmSetUnack,
  Appli_LightLCs_OnOffGet,
  Appli_LightLCs_OnOffSet,
  Appli_LightLCs_OnOffSetUnack,
  Appli_LightLCs_PropertyGet,
  Appli_LightLCs_PropertySet,
  Appli_LightLCs_PropertySetUnack
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Callback corresponding to LightLCs_ModeGet_cb
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_ModeGet(MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_ModeSet_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_ModeSet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_ModeSetUnack_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_ModeSetUnack(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_OmGet_cb
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_OmGet(MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_OmSet_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_OmSet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_OmSetUnack_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_OmSetUnack(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_OnOffGet_cb
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_OnOffGet(MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}
 

/**
  * @brief  Callback corresponding to LightLC_OnOffSet_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_OnOffSet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_OnOffSetUnack_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_OnOffSetUnack(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_PropertyGet_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_PropertyGet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_PropertySet_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_PropertySet(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}


/**
  * @brief  Callback corresponding to LightLCs_PropertySetUnack_cb
  * @param  Data
  * @param  Message parameters
  * @retval None
  */
void Appli_LightLCs_PropertySetUnack(MOBLEUINT8 const* pRxData, MODEL_MessageHeader_t *pmsgParam)
{
  TRACE_M(TF_LIGHT_LC, "Element index %d peer addr %X dst peer %X\r\n",
          pmsgParam->elementIndex, pmsgParam->peer_addr, pmsgParam->dst_peer);
}

/**
  * @brief  
  * @param  
  * @retval 
  */
__weak MOBLE_RESULT Appli_Light_LCs_Init(void)
{
  MOBLE_RESULT result = MOBLE_RESULT_FAIL;
  MOBLEUINT8 lcsElementIndex = 0;
  
  /* Extract element index of LC server */
  result = ExtractLcServerElementIndex(&lcsElementIndex,
#ifdef APPLICATION_NUMBER_OF_ELEMENTS
                                       APPLICATION_NUMBER_OF_ELEMENTS,
#else
                                       0,
#endif
#ifdef ENABLE_LIGHT_MODEL_SERVER_LC
                                       ENABLE_LIGHT_MODEL_SERVER_LC,
                                       ENABLE_LIGHT_MODEL_SERVER_LC_SETUP,
#else
                                       0,
                                       0,
#endif
#ifdef ENABLE_GENERIC_MODEL_SERVER_ONOFF
                                       ENABLE_GENERIC_MODEL_SERVER_ONOFF,
#else
                                       0,
#endif
#ifdef ENABLE_GENERIC_MODEL_SERVER_POWER_ONOFF
                                       ENABLE_GENERIC_MODEL_SERVER_POWER_ONOFF,
#else
                                       0,
#endif
#ifdef ENABLE_SENSOR_MODEL_SERVER
                                       ENABLE_SENSOR_MODEL_SERVER,
#else
                                       0,
#endif
#ifdef ENABLE_LIGHT_MODEL_SERVER_LIGHTNESS
                                       ENABLE_LIGHT_MODEL_SERVER_LIGHTNESS);
#else
                                       0);
#endif
  
  if(MOBLE_SUCCEEDED(result))
  {
    result = Light_LCs_Init(&BufferLcServer, lcsElementIndex, &AppliLightLc_cb, SIZE_OF_LC_SERVER_T);
  }
  
  if(MOBLE_FAILED(result))
  {
    TRACE_M(TF_LIGHT_LC, "Light LC Server init failed\r\n");
  }
  
  return result; 
}


/**
  * @brief  
  * @param  
  * @retval 
  */
__weak MOBLE_RESULT Appli_Light_LC_SensorPropertyUpdate(MOBLEUINT8 elementIndex,
                                                 MOBLEUINT16 propertyId,
                                                 MOBLEUINT32 value)
{  
  return Light_LC_SensorPropertyUpdate(elementIndex,
                                       propertyId,
                                       value);
}

/**
* @}
*/

/**
* @}
*/

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

