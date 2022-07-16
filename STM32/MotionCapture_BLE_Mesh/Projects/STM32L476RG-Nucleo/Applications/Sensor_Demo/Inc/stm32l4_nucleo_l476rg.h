/**
******************************************************************************
* @file  : nucleo_l476rg.h
* @brief : header file for the BSP Common driver
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
 
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NUCLEO_L476RG_H
#define __NUCLEO_L476RG_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/ 
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include "stm32l4xx_nucleo.h" 
/** @addtogroup BSP
 * @{
 */

/** @addtogroup NUCLEO_L476RG
 * @{
 */

/** @addtogroup NUCLEO_L476RG_LOW_LEVEL
 * @{
 */ 

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_Exported_Types NUCLEO_L476RG LOW LEVEL Exported Types
 * @{
 */

typedef enum 
{
  COM1 = 0U,
} COM_TypeDef;
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
typedef struct
{
  pUART_CallbackTypeDef  pMspUartInitCb;
  pUART_CallbackTypeDef  pMspUartDeInitCb;
} BSP_UART_Cb_t;
#endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 1) */

/**
 * @}
 */ 

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_Exported_Constants NUCLEO_L476RG LOW LEVEL Exported Constants
 * @{
 */ 
/** 
 * @brief Define for NUCLEO_L476RG board  
 */ 
/* Common Error codes */
#define BSP_ERROR_NONE                    0
#define BSP_ERROR_NO_INIT                -1
#define BSP_ERROR_WRONG_PARAM            -2
#define BSP_ERROR_BUSY                   -3
#define BSP_ERROR_PERIPH_FAILURE         -4
#define BSP_ERROR_COMPONENT_FAILURE      -5
#define BSP_ERROR_UNKNOWN_FAILURE        -6
#define BSP_ERROR_UNKNOWN_COMPONENT      -7 
#define BSP_ERROR_BUS_FAILURE            -8 
#define BSP_ERROR_CLOCK_FAILURE          -9  
#define BSP_ERROR_MSP_FAILURE            -10  
#define BSP_ERROR_FEATURE_NOT_SUPPORTED  -11

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_LED NUCLEO_L476RG LOW LEVEL LED
 * @{
 */  
#define LED2_GPIO_PORT                    GPIOA
#define LED2_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()           __HAL_RCC_GPIOA_CLK_DISABLE()  
#define LED2_GPIO_PIN                     GPIO_PIN_5
/**
 * @}
 */ 

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_BUTTON NUCLEO_L476RG LOW LEVEL BUTTON
 * @{
 */ 
/* Button state */
#define BUTTON_RELEASED                   0U

/**
 * @brief Key push-button
 */

#define BSP_BUTTON_KEY_IT_PRIORITY        0xF
/**
 * @}
 */ 

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_COM NUCLEO_L476RG LOW LEVEL COM
 * @{
 */
/**
 * @brief Definition for COM portx, connected to USART2
 */
#define COMn                             1U 
#define COM1_UART                        USART2

#define COM_POLL_TIMEOUT                 1000

#define USE_COM_LOG                      1U

#define UartHandle huart2

typedef enum
{          
 COM_STOPBITS_1 =   UART_STOPBITS_1,                                 
 COM_STOPBITS_2 =   UART_STOPBITS_2,
} COM_StopBitsTypeDef;

typedef enum
{
 COM_PARITY_NONE =  UART_PARITY_NONE,                  
 COM_PARITY_EVEN =  UART_PARITY_EVEN,                  
 COM_PARITY_ODD  =  UART_PARITY_ODD,                   
} COM_ParityTypeDef;

typedef enum
{
 COM_HWCONTROL_NONE    =  UART_HWCONTROL_NONE,               
 COM_HWCONTROL_RTS     =  UART_HWCONTROL_RTS,                
 COM_HWCONTROL_CTS     =  UART_HWCONTROL_CTS,                
 COM_HWCONTROL_RTS_CTS =  UART_HWCONTROL_RTS_CTS, 
} COM_HwFlowCtlTypeDef;

typedef struct
{
  uint32_t             BaudRate;      
  uint32_t             WordLength;    
  COM_StopBitsTypeDef  StopBits;      
  COM_ParityTypeDef    Parity;               
  COM_HwFlowCtlTypeDef HwFlowCtl;                           
} COM_InitTypeDef;
/**
 * @}
 */
  
/** @defgroup NUCLEO_L476RG_LOW_LEVEL_Exported_Functions NUCLEO_L476RG LOW LEVEL Exported Functions
 * @{
 */ 
/* Exported Functions --------------------------------------------------------*/



void     BSP_PB_Callback(Button_TypeDef Button);
int32_t  BSP_COM_Init(COM_TypeDef COM);
int32_t  BSP_COM_DeInit(COM_TypeDef COM);

#if (USE_COM_LOG == 1)
int32_t  BSP_COM_SelectLogPort(COM_TypeDef COM);
#endif

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1) 
int32_t BSP_USART2_RegisterDefaultMspCallbacks(void);
int32_t BSP_USART2_RegisterMspCallbacks(BSP_UART_Cb_t *Callback);
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

/**
 * @}
 */ 

/**
 * @}
 */ 

/**
 * @}
 */

/**
 * @}
 */   
#ifdef __cplusplus
}
#endif

#endif /* __NUCLEO_L476RG__H */
    
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
