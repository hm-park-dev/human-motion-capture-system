/**
******************************************************************************
* @file    stm32xx_it.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Main Interrupt Service Routines
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
#include "stm32xx_it.h" 
#include "hci.h"
#include "appli_mesh.h"

#ifdef STM32_SENSORTILEBOX
  #include "TargetFeatures.h"
  #include "lsm6dsox_reg.h"
#else
  #include "stm32l4xx_nucleo.h"
#endif
    
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint8_t button_event = 0;
#ifdef ENABLE_USB
extern PCD_HandleTypeDef hpcd;
#endif 

#ifdef STM32_SENSORTILEBOX
  #ifdef STBOX1_ENABLE_PRINTF
  extern PCD_HandleTypeDef hpcd;
  #endif /* STBOX1_ENABLE_PRINTF */
  extern volatile uint32_t SendMCL_FSM_EMB;
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
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
* @brief  SVC_Handler This function handles SVCall exception.
* @param  None
* @retval None
*/
void SVC_Handler(void)
{
}

/**
* @brief  DebugMon_Handler This function handles Debug Monitor exception.
* @param  None
* @retval None
*/
void DebugMon_Handler(void)
{
}

/**
* @brief  PendSV_Handler This function handles PendSVC exception.
* @param  None
* @retval None
*/
void PendSV_Handler(void)
{
}

/**
* @brief  SysTick_Handler This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler(void)
{
  HAL_IncTick();
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
/**
* @brief  This function handles External line interrupt request for BlueNRG.
* @param  None
* @retval None
*/
#ifdef STM32_SENSORTILEBOX
void EXTI4_IRQHandler(void)               //SB Code Modification
{
  //HCI_Isr();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4); //SB Code Modification
}

#else
void EXTI0_IRQHandler(void)
{
  //HCI_Isr();
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}
#endif

/* Start of SB Code Modification */
#ifdef STBOX1_ENABLE_PRINTF
/**
 * @brief  This function handles USB-On-The-Go FS global interrupt request.
 * @param  None
 * @retval None
 */
void OTG_FS_IRQHandler(void) {
	HAL_PCD_IRQHandler(&hpcd);
}
#endif /* STBOX1_ENABLE_PRINTF */

/**
 * @brief  This function handles External line 1 interrupt request.
 * @param  None
 * @retval None
 */
void EXTI1_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
}

#ifdef STM32_SENSORTILEBOX
/**
 * @brief  EXTI2_IRQHandler This function handles External line
 *         interrupt request for Power Button
 * @param  None
 * @retval None
 */
void EXTI2_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(POWER_BUTTON_PIN);
}

/**
 * @brief  EXTI3_IRQHandler This function handles External line
 *         interrupt request for Battery Charger.
 * @param  None
 * @retval None
 */
void EXTI3_IRQHandler(void) {
	HAL_GPIO_EXTI_IRQHandler(STBC02_CHG_PIN);
}

/**
 * @brief  This function handles TIM1 Interrupt request
 * @param  None
 * @retval None
 */
void TIM1_CC_IRQHandler(void) {
	HAL_TIM_IRQHandler(&TimCCHandle);
}
#endif

/* End of SB Code Modification */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/
