/**
******************************************************************************
* @file    light_lc.h
* @author  BLE Mesh Team
* @version V1.14.000
* @date    19-11-2021
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
* Initial BlueNRG-Mesh is built over Motorola’s Mesh over Bluetooth Low Energy 
* (MoBLE) technology. The present solution is developed and maintained for both 
* Mesh library and Applications solely by STMicroelectronics.
*
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIGHT_LC_H
#define __LIGHT_LC_H

/* Includes ------------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables  -------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define LC_PROPERTY_TABLE_COUNT                  18
#define LIGHT_LC_DEFAULT_TRANSITION_RES_MS       100 /* Recommended value is 100 milliseconds */

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  MOBLEUINT8 LC_modeState;
}Light_LC_ModeParam_t; 

typedef struct
{
  MOBLEUINT8 LC_OMState;
}Light_LC_OccupancyModeParam_t; 

typedef struct
{
  MOBLEUINT8 LC_OnOffState;
  MOBLEUINT8 Tid;
  MOBLEUINT8 Transition_Time;
  MOBLEUINT8 Delay_Time;
}Light_LC_OnOffParam_t; 

/**
  * LC callback structure
 */
typedef struct
{
  void (*LightLCs_ModeGet_cb)(MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_ModeSet_cb)(MOBLEUINT8 const* pRxData,
                              MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_ModeSetUnack_cb)(MOBLEUINT8 const* pRxData,
                                   MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_OmGet_cb)(MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_OmSet_cb)(MOBLEUINT8 const* pRxData,
                            MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_OmSetUnack_cb)(MOBLEUINT8 const* pRxData,
                                      MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_OnOffGet_cb)(MODEL_MessageHeader_t *pmsgParam);
  void (*LightLC_OnOffSet_cb)(MOBLEUINT8 const* pRxData,
                                      MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_OnOffSetUnack_cb)(MOBLEUINT8 const* pRxData,
                                    MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_PropertyGet_cb)(MOBLEUINT8 const* pRxData,
                                    MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_PropertySet_cb)(MOBLEUINT8 const* pRxData,
                                       MODEL_MessageHeader_t *pmsgParam);
  void (*LightLCs_PropertySetUnack_cb)(MOBLEUINT8 const* pRxData,
                                      MODEL_MessageHeader_t *pmsgParam);
} light_lc_cb_t;


/* Exported functions ------------------------------------------------------- */
MOBLE_RESULT LightLcServer_GetOpcodeTableCb(const MODEL_OpcodeTableParam_t **data,
                                            MOBLEUINT16 *length);
MOBLE_RESULT LightLcServer_GetStatusRequestCb(MODEL_MessageHeader_t *pmsgParam,
                                              MOBLEUINT16 opcode,
                                              MOBLEUINT8 *pResponsedata,
                                              MOBLEUINT32 *plength,
                                              MOBLEUINT8 const *pRxData,
                                              MOBLEUINT32 dataLength,
                                              MOBLEBOOL response);
MOBLE_RESULT LightLcServer_ProcessMessageCb(MODEL_MessageHeader_t *pmsgParam,
                                            MOBLEUINT16 opcode,
                                            MOBLEUINT8 const *pRxData,
                                            MOBLEUINT32 dataLength,
                                            MOBLEBOOL response);
void LightLC_SaveModelStates(MOBLEUINT8 elementIndex,
                             MOBLEUINT8* lightLcNvmParamsBuff, 
                             MOBLEUINT8 lcNvmParamsSize);
MOBLEUINT8 Light_LC_OnPowerUp(MOBLEUINT8 elementIndex,
                              MOBLEUINT8 const *pModelValue_Load,
                              MOBLEUINT8 genericOnPowerUp,
                              MOBLEUINT16 lightDefault,
                              MOBLEUINT16 lightLast,
                              MOBLEUINT16 lightActualLKV,
                              MOBLEUINT16* pLightActualToBeSet);
MOBLE_RESULT Light_LC_SetTransitionTimeZero(MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_LC_SensorPropertyUpdate(MOBLEUINT8 lcsElementIndex,
                                           MOBLEUINT16 sensorPropertyId,
                                           MOBLEUINT32 value);
void Light_LC_LigtnessLinearUnsolicitedChange(MOBLEUINT8 lightnessLinearelementIndex);
MOBLEUINT32 Light_LC_SleepDurationMs_Get(void);
MOBLE_RESULT Light_LC_Send(MOBLEUINT8 elementIndex);
MOBLE_RESULT Light_LC_LcOnOffUpdate(MOBLEUINT8 elementIndex, 
                                    MOBLEUINT8 onOff,
                                    MOBLEUINT8 optionalParams,
                                    MOBLEUINT32 delayMsOnOffMsg,
                                    MOBLEUINT32 stepResMsOnOffMsg,
                                    MOBLEUINT32 trTimeMsOnOffMsg);
void Light_LC_Process(void);
MOBLE_RESULT Light_LCs_Init(void* lcsBuff, 
                            MOBLEUINT8 lcsElementIndex, 
                            const light_lc_cb_t* lcs_cb, 
                            MOBLEUINT16 sizeBuff);
MOBLE_RESULT ExtractLcServerElementIndex(MOBLEUINT8* pLcsElementIndex,
                                         MOBLEUINT8 noOfElements,
                                         MOBLEUINT8 lcServer,
                                         MOBLEUINT8 lcSetupServer,
                                         MOBLEUINT8 genericOnOffServer,
                                         MOBLEUINT8 genericPowerOnOffServer,
                                         MOBLEUINT8 sensorServer,
                                         MOBLEUINT8 lightLightnessServer);
void Light_LC_PropertyValueBuffGet(void *pBuff, MOBLEUINT8 elementIndex);
void Light_LC_PropertyValueBuffSet(void *pBuff);
#endif /* __LIGHT_LC_H */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

