/**
******************************************************************************
* @file  : nucleo_l476rg.c
* @brief : Source file for the BSP Common driver
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
#include "stm32l4xx_hal.h"
#include "stm32l4xx_it.h"
#include "stm32l4_nucleo_l476rg.h"
#include "stm32l4xx_hal_exti.h"
#include "main.h"
/** @defgroup BSP BSP
 * @{
 */ 

/** @defgroup NUCLEO_L476RG NUCLEO_L476RG
 * @{
 */   
    
/** @defgroup NUCLEO_L476RG_LOW_LEVEL NUCLEO_L476RG LOW LEVEL
 *  @brief This file provides set of firmware functions to manage Leds and push-button
 *         available on STM32L4xx-Nucleo Kit from STMicroelectronics.
 * @{
 */ 

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_Private_TypesDefinitions NUCLEO_L476RG LOW LEVEL Private TypesDefinitions
 * @{
 */
typedef void (* BSP_EXTI_LineCallback)(void);

/**
 * @}
 */ 

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_Private_Defines NUCLEO_L476RG LOW LEVEL Private Defines
 * @{
 */ 

/**
 * @brief STM32L4XX NUCLEO BSP Driver version number V1.2.6
 */  
#define __NUCLEO_L476RG_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __NUCLEO_L476RG_BSP_VERSION_SUB1   (0x02) /*!< [23:16] sub1 version */
#define __NUCLEO_L476RG_BSP_VERSION_SUB2   (0x06) /*!< [15:8]  sub2 version */
#define __NUCLEO_L476RG_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __NUCLEO_L476RG_BSP_VERSION        ((__NUCLEO_L476RG_BSP_VERSION_MAIN << 24)\
                                                    |(__NUCLEO_L476RG_BSP_VERSION_SUB1 << 16)\
                                                    |(__NUCLEO_L476RG_BSP_VERSION_SUB2 << 8 )\
                                                    |(__NUCLEO_L476RG_BSP_VERSION_RC))
/**
 * @}
 */ 

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_FunctionPrototypes NUCLEO_L476RG LOW LEVEL Private Function Prototypes
 * @{
 */
//static void BUTTON_KEY_EXTI_Callback(void);
static void USART2_MspInit(UART_HandleTypeDef *huart);
static void USART2_MspDeInit(UART_HandleTypeDef *huart); 
/**
 * @}
 */ 

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_Private_Variables NUCLEO_L476RG LOW LEVEL Private Variables
 * @{
 */
/* Private Variables -----------------------------------------------------------*/

EXTI_HandleTypeDef *hExtiButtonHandle[BUTTONn];
USART_TypeDef* COM_USART[COMn] = {COM1_UART};
UART_HandleTypeDef hComHandle[COMn];
#if (USE_COM_LOG == 1)
static COM_TypeDef COM_ActiveLogPort;
#endif
#if (USE_HAL_UART_REGISTER_CALLBACKS == 1)
static uint32_t IsUsart2MspCbValid = 0;
#endif
EXTI_HandleTypeDef hexti13;
const uint32_t BUTTON_EXTI_LINE[BUTTONn] = {KEY_BUTTON_EXTI_LINE};
/**
 * @}
 */ 

/** @defgroup NUCLEO_L476RG_LOW_LEVEL_Private_Functions NUCLEO_L476RG LOW LEVEL Private Functions
 * @{
 */ 



/**
 * @brief  BSP Push Button callback
 * @param  Button Specifies the pin connected EXTI line
 * @retval None.
 */
__weak void BSP_PB_Callback(Button_TypeDef Button)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(Button);
  
  /* This function should be implemented by the user application.
     It is called into this driver when an event on Button is triggered. */   
}
/**
 * @brief  Configures COM port.
 * @param  COM: COM port to be configured.
 *              This parameter can be COM1
 * @param  UART_Init: Pointer to a UART_HandleTypeDef structure that contains the
 *                    configuration information for the specified USART peripheral.
 * @retval BSP error code
 */
int32_t BSP_COM_Init(COM_TypeDef COM) 
{
#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)
  /* Init the UART Msp */
  USART2_MspInit(&hComHandle[COM]);
#else
  if(IsUsart2MspCbValid == 0U)
  {
    if(BSP_USART2_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
    {
      return BSP_ERROR_MSP_FAILURE;
    }
  }
#endif


  return BSP_ERROR_NONE;
}

/**
 * @brief  DeInit COM port.
 * @param  COM COM port to be configured.
 *             This parameter can be COM1
 * @retval BSP status
 */
int32_t BSP_COM_DeInit(COM_TypeDef COM)
{
  /* USART configuration */
  hComHandle[COM].Instance = COM_USART[COM];
  
#if (USE_HAL_UART_REGISTER_CALLBACKS == 0)  
  USART2_MspDeInit(&hComHandle[COM]);  
#endif /* (USE_HAL_UART_REGISTER_CALLBACKS == 0) */
  
  if(HAL_UART_DeInit(&hComHandle[COM]) != HAL_OK)
  {
    return BSP_ERROR_PERIPH_FAILURE;
  }
  
  return BSP_ERROR_NONE;
}


/**
 * @brief  Initializes USART2 MSP.
 * @param  huart USART2 handle
 * @retval None
 */

static void USART2_MspInit(UART_HandleTypeDef* uartHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* Enable Peripheral clock */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
}

static void USART2_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, USART_TX_Pin|USART_RX_Pin);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
}

#if (USE_HAL_UART_REGISTER_CALLBACKS == 1) 
/**
 * @brief Register Default USART2 Bus Msp Callbacks
 * @retval BSP status
 */
int32_t BSP_USART2_RegisterDefaultMspCallbacks(void)
{
  int32_t ret = BSP_ERROR_NONE;
  
  __HAL_UART_RESET_HANDLE_STATE(&hComHandle[COM1]);
  
  /* Register default MspInit/MspDeInit Callback */
  if(HAL_UART_RegisterCallback(&hComHandle[COM1], HAL_UART_MSPINIT_CB_ID, USART2_MspInit) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else if(HAL_UART_RegisterCallback(&hComHandle[COM1], HAL_UART_MSPDEINIT_CB_ID, USART2_MspDeInit) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    IsUsart2MspCbValid = 1U;
  }
  
  /* BSP status */  
  return ret;
}

/**
 * @brief Register USART2 Bus Msp Callback registering
 * @param Callbacks pointer to USART2 MspInit/MspDeInit callback functions
 * @retval BSP status
 */
int32_t BSP_USART2_RegisterMspCallbacks (BSP_UART_Cb_t *Callback)
{
  int32_t ret = BSP_ERROR_NONE;
  
  __HAL_UART_RESET_HANDLE_STATE(&hComHandle[COM1]);
  
  /* Register MspInit/MspDeInit Callbacks */
  if(HAL_UART_RegisterCallback(&hComHandle[COM1], HAL_UART_MSPINIT_CB_ID, Callback->pMspUsartInitCb) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else if(HAL_UART_RegisterCallback(&hComHandle[COM1], HAL_UART_MSPDEINIT_CB_ID, Callback->pMspUsartDeInitCb) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    IsUsart2MspCbValid = 1U;
  }
  
  /* BSP status */  
  return ret; 
}
#endif /* USE_HAL_UART_REGISTER_CALLBACKS */

#if (USE_COM_LOG == 1)
/**
 * @brief  Select the active COM port.
 * @param  COM COM port to be activated.
 *             This parameter can be COM1
 * @retval BSP status
 */
int32_t BSP_COM_SelectLogPort(COM_TypeDef COM)
{ 
  if(COM_ActiveLogPort != COM)
  {
    COM_ActiveLogPort = COM;
  } 
  return BSP_ERROR_NONE; 
}
#if 0
#ifdef __GNUC__
 int __io_putchar (int ch)
#else 
 int fputc (int ch, FILE *f) 
#endif /* __GNUC__ */ 
{ 
  HAL_UART_Transmit(&hComHandle[COM_ActiveLogPort], (uint8_t *)&ch, 1, COM_POLL_TIMEOUT); 
  return ch;
}
#endif /* USE_COM_LOG */ 
#endif
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
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

