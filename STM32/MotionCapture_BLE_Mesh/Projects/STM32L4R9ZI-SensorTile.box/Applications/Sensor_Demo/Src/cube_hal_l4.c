/**
******************************************************************************
* @file    cube_hal_l4.c
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Cube HAL File for STM32L4 
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

/* Includes ------------------------------------------------------------------*/
#ifdef STM32_SENSORTILEBOX
  #include "SensorTile.box_bc.h"
  #include "SensorTile.box.h"
  #include "TargetFeatures.h"
  #include "stm32_bluenrg_ble.h"
#else
  #include "stm32l4xx_nucleo.h"
  #include "stm32l4xx_nucleo_bluenrg.h"
#endif

#include "cube_hal.h"
#include "user_if.h"



UART_HandleTypeDef huart2;
uint8_t read_data; 

volatile int hci_event = 0;
#ifdef STM32_SENSORTILEBOX
  volatile int ButtonPressed = 0;
  volatile int PowerButtonPressed = 0;
  volatile uint32_t SendMCL_FSM_EMB = 0;
#endif
/**
* @brief  System Clock Configuration
* @param  None
* @retval None
*/
/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows :
  *            System Clock source            = PLL (MSI)
  *            SYSCLK(Hz)                     = 80000000
  *            HCLK(Hz)                       = 80000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            MSI Frequency(Hz)              = 4000000
  *            PLL_M                          = 1
  *            PLL_N                          = 40
  *            PLL_R                          = 2
  *            PLL_P                          = 7
  *            PLL_Q                          = 4
  *            Flash Latency(WS)              = 4
  * @param  None
  * @retval None
  */
  
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

#ifdef STM32_SENSORTILEBOX
  RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };
  
  /** Configure the main internal regulator output voltage */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST) != HAL_OK) {
      /* Initialization Error */
      while (1);
  }

  /**Configure LSE Drive Capability
   */
  HAL_PWR_EnableBkUpAccess();

  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /**Initializes the CPU, AHB and APB busses clocks
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48 |
  RCC_OSCILLATORTYPE_LSE |
  RCC_OSCILLATORTYPE_HSE |
  RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_11;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
      /* Initialization Error */
      while (1);
  }

  /**Initializes the CPU, AHB and APB busses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
  RCC_CLOCKTYPE_SYSCLK |
  RCC_CLOCKTYPE_PCLK1 |
  RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
      /* Initialization Error */
      while (1);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_SAI1 |
  RCC_PERIPHCLK_DFSDM1 |
  RCC_PERIPHCLK_USB |
  RCC_PERIPHCLK_RTC |
  RCC_PERIPHCLK_SDMMC1 |
  RCC_PERIPHCLK_ADC;

  PeriphClkInit.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI1;
  PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
  PeriphClkInit.Dfsdm1ClockSelection = RCC_DFSDM1CLKSOURCE_PCLK2;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLLP;
  PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_HSE;
  PeriphClkInit.PLLSAI1.PLLSAI1M = 5;
  PeriphClkInit.PLLSAI1.PLLSAI1N = 96;
  PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV25;
  PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV4;
  PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV4;
  PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK | RCC_PLLSAI1_SAI1CLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        /* Initialization Error */
        while (1);
  }
#else
  /**
  * Enable clock on PWR block
  * This is used to setup registers when entering low power mode
  */    
  __PWR_CLK_ENABLE();
  /* MSI is enabled after System reset, activate PLL with MSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLP = 7;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    /* Initialization Error */
    while(1);
  }
#endif
}


/**
* @brief  Device initialization
* @param  None
* @retval None
*/

void Init_Device(void)
{
  
  /* STM32Cube HAL library initialization */
  HAL_Init();
  
  /* Configure the system clock */
  SystemClock_Config(); 
  HAL_FLASH_Unlock();
    __HAL_RCC_CRC_CLK_ENABLE();
  
  /* pin configuration for LED2 */
  LED2_GPIO_CLK_ENABLE();
  
  GPIO_InitTypeDef init;
  init.Pin = LED2_PIN;
  init.Mode = GPIO_MODE_OUTPUT_PP;
  init.Pull = GPIO_NOPULL;
  init.Speed = GPIO_SPEED_LOW;
  init.Alternate = 0;
  HAL_GPIO_Init(LED2_GPIO_PORT, &init);
  
#ifdef USE_X_NUCLEO_LED61A1
  __HAL_RCC_GPIOB_CLK_ENABLE();
  init.Pin = GPIO_PIN_10;
  HAL_GPIO_Init(GPIOB, &init);
#endif
  
#ifdef STM32_SENSORTILEBOX
  InitTargetPlatform();
#endif
}  


/**
* @brief  USART2 MSP Init function
* @param  None
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART2)
  {
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
    
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
}

/**
* @brief  USART2 Deinit function
* @param  None
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  if(uartHandle->Instance==USART2)
  {
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
    
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, USART_TX_Pin|USART_RX_Pin);
  }
} 
/**
* @brief  Serial IRQ handler body to be put on user USARTx_IRQHandler() (stm32l1xx_it.c)
* @param  None
* @retval None.
*/
void Uart_Irq_Handler(void)
{
 // HAL_UART_IRQHandler(&huart2);
}


/**
* @brief  UART error callbacks
* @param  UartHandle: UART handle
* @retval None
*/
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle)
{
  /* Transfer error occured in reception and/or transmission process */
  __NOP();
}
/**
* @brief  AHB Peripheral Clock handling
* @param  None
* @retval None
*/
void RCC_AHBPeriphClockCmd(void)
{
    while (1) ;
}

/**
 * @brief  EXTI line detection callback.
 * @param  Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  switch (GPIO_Pin) {
#ifdef STM32_SENSORTILEBOX
      case USER_BUTTON_PIN:
            ButtonPressed = 1;
            break;
      case POWER_BUTTON_PIN: //SB Code: this IRQ Handler is shared with the INT1 of the LSM6DSOX sensor
            Disable_SPI_IRQ();
            Clear_SPI_IRQ();
            Clear_SPI_EXTI_Flag();
            SendMCL_FSM_EMB = 1;
            PowerButtonPressed = 1;
            break;
      case STBC02_CHG_PIN:
            /* For understanding if is under charge or not */
            BSP_BC_ChgPinHasToggled();
            break;
#endif
      case BNRG_SPI_IRQ_PIN:
            HCI_Isr();
//              hci_event = 1;
            break;
      default:
            break;
    }
}

/******************* (C) COPYRIGHT 2020 STMicroelectronics *****END OF FILE****/
