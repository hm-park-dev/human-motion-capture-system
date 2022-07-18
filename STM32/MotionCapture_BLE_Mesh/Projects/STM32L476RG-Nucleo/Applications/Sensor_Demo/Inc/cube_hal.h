/**
******************************************************************************
* @file    cube_hal.h
* @author  AMS VMA RF Application team
* @version V1.4.0
* @date    21-01-2022
* @brief   Common cube HAL header file 
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

#ifndef _CUBE_HAL_H_
#define _CUBE_HAL_H_

/* Includes ------------------------------------------------------------------*/

#ifdef USE_STM32L1XX_STEVAL_IDB00xV1 
  #include "stm32l1xx_hal.h"
  #include "stm32l1xx_hal_conf.h"
#endif
#ifdef USE_STM32F4XX_STEVAL_IDB00xV1
  #include "stm32f4xx_hal.h"
  #include "stm32f4xx_hal_conf.h"
/*  #include "SDK_EVAL_Config.h" */
#endif
#ifdef USE_STM32L4XX_STEVAL_IDB00xV1
  #include "stm32l4xx_hal.h"
  #include "stm32l4xx_hal_conf.h"
#endif
#ifdef USE_STM32F3XX_STEVAL_IDB00xV1
  #include "stm32f3xx_hal.h"
  #include "stm32f3xx_hal_conf.h"
/*  #include "SDK_EVAL_Config.h" */
#endif
  

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA

#define UART_TX_TIMEOUT 5 

#define Uart_Irq_Handler      USART2_IRQHandler


void SystemClock_Config(void);
void Init_Device(void);
void MX_USART2_UART_Init(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* _CUBE_HAL_H_ */
