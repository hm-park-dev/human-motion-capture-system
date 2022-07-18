/**
******************************************************************************
* @file    stm32xx_it.h
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Header file for  Interrupt Service Routine file
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
#ifndef __STM32xx_IT_H
#define __STM32xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
 
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void BNRG_SPI_EXTI_IRQHandler(void);
void PUSH_BUTTON_EXTI_IRQHandler(void);
#if defined(__GNUC__)
void hardfaultGetContext(unsigned long* stackedContextPtr) __asm("label_hardfaultGetContext");
#endif
 
#ifdef __cplusplus
}
#endif

#endif /* __STM32xx_IT_H */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
