/**
******************************************************************************
* @file    stm32xx_it.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Main Interrupt Service Routines
*          This file provides template for all exceptions handler and
*          peripherals interrupt service routine
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
#include "stm32l4xx_it.h" 
#include "hci.h"
#include "appli_mesh.h"
#include "stm32l4xx_nucleo.h"
#include "stdio.h"    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint8_t button_event = 0;
#ifdef ENABLE_USB
extern PCD_HandleTypeDef hpcd;
#endif 
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0+ Processor Exceptions Handlers                         */
/******************************************************************************/

/**
* @brief  NMI_Handler This function handles NMI exception.
* @param  None
* @retval None
*/
void NMI_Handler(void)
{
}
/**
* @brief  Copies system stacked context into function local variables.
* @param  None
* @retval None
*/

void hardfaultGetContext(unsigned long* stackedContextPtr)
{
  volatile unsigned long stacked_r0;
  volatile unsigned long stacked_r1;
  volatile unsigned long stacked_r2;
  volatile unsigned long stacked_r3;
  volatile unsigned long stacked_r12;
  volatile unsigned long stacked_lr;
  volatile unsigned long stacked_pc;
  volatile unsigned long stacked_psr;
  volatile unsigned long _CFSR;
  volatile unsigned long _HFSR;
  volatile unsigned long _DFSR;
  volatile unsigned long _AFSR;
  volatile unsigned long _BFAR;
  volatile unsigned long _MMAR;
#if !defined(DISABLE_TRACES)
  printf("HardFault %p\r\n", stackedContextPtr);
#endif
  if (stackedContextPtr)
  {
    
    stacked_r0  = stackedContextPtr[0];
    stacked_r1  = stackedContextPtr[1];
    stacked_r2  = stackedContextPtr[2];
    stacked_r3  = stackedContextPtr[3];
    stacked_r12 = stackedContextPtr[4];
    stacked_lr  = stackedContextPtr[5];
    stacked_pc  = stackedContextPtr[6];
    stacked_psr = stackedContextPtr[7];
    
    /* Configurable Fault Status Register */

    _CFSR = (*((volatile unsigned long *)(0xE000ED28))) ;
    _HFSR = (*((volatile unsigned long *)(0xE000ED2C))) ;
    _DFSR = (*((volatile unsigned long *)(0xE000ED30))) ;
    _AFSR = (*((volatile unsigned long *)(0xE000ED3C))) ;
    _MMAR = (*((volatile unsigned long *)(0xE000ED34))) ;
    _BFAR = (*((volatile unsigned long *)(0xE000ED38))) ;
#if !defined(DISABLE_TRACES)
    printf("HardFault");
#endif
    stackedContextPtr[0] = stacked_r0;
    stackedContextPtr[1] = stacked_r1;
    stackedContextPtr[2] = stacked_r2;
    stackedContextPtr[3] = stacked_r3;
    stackedContextPtr[4] = stacked_r12;
    stackedContextPtr[5] = stacked_lr;
    stackedContextPtr[6] = stacked_pc;
    stackedContextPtr[7] = stacked_psr;
    (*((volatile unsigned long *)(0xE000ED28))) = _CFSR;
    (*((volatile unsigned long *)(0xE000ED2C))) = _HFSR;
    (*((volatile unsigned long *)(0xE000ED30))) = _DFSR;
    (*((volatile unsigned long *)(0xE000ED3C))) = _AFSR;
    (*((volatile unsigned long *)(0xE000ED34))) = _MMAR;
    (*((volatile unsigned long *)(0xE000ED38))) = _BFAR;
  }
  while (1)
  {}
}
/**
* @brief  HARD_FAULT interrupt service routine..
* @param  None
* @retval None
*/
#if defined(__GNUC__)
void __attribute__((naked, interrupt)) HardFault_Handler(void)
{
  __asm__ volatile  (
                     "     MOVS   R0, #4             \n" /* Determine if processor uses PSP or MSP by checking bit.4 at LR register.   */
                       "   MOV    R1, LR             \n"
                         "   TST    R0, R1             \n"
                           "   BEQ    _IS_MSP              \n" /* Jump to '_MSP' if processor uses MSP stack.                  */
                             "   MRS    R0, PSP              \n" /* Prepare PSP content as parameter to the calling function below.        */
                               "   BL     label_hardfaultGetContext    \n" /* Call 'hardfaultGetContext' passing PSP content as stackedContextPtr value. */
                                 "_IS_MSP:                   \n"
                                   "   MRS    R0, MSP              \n" /* Prepare MSP content as parameter to the calling function below.        */
                                     "   BL     label_hardfaultGetContext    \n" /* Call 'hardfaultGetContext' passing MSP content as stackedContextPtr value. */
                                       ::  );
}
#else
void HardFault_Handler(void)
{	
#if !defined(DISABLE_TRACES)
  printf("HardFault\r\n");
#endif
  while(1) {}
}

#endif

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/**
* @brief  This function handles USB Low Priority interrupts  requests.
* @param  None
* @retval None
*/
void USB_LP_IRQHandler(void)
{
#ifdef ENABLE_USB
  HAL_PCD_IRQHandler(&hpcd);
#endif 
}
/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  HCI_Isr();
}

/**
  * @brief This function handles EXTI line1 interrupt.
  */
void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}

/**
  * @brief This function handles EXTI line4 interrupt.
  */
void EXTI4_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_IRQn 0 */

  /* USER CODE END EXTI4_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
  /* USER CODE BEGIN EXTI4_IRQn 1 */

  /* USER CODE END EXTI4_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
 HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
//  HAL_EXTI_IRQHandler(&H_EXTI_13);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
