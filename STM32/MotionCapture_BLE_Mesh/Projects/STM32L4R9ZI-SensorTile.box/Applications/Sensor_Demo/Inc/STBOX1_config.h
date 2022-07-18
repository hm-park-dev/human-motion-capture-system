/**
******************************************************************************
* @file    BLESensors\Inc\STBOX1_config.h
* @author  SRA - Central Labs
* @version V1.4.0
* @date    21-01-2022
* @brief   FP-SNS-STBOX1 configuration
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
#ifndef __STBOX1_CONFIG_H
#define __STBOX1_CONFIG_H
#include "TargetFeatures.h"
/* Exported define ------------------------------------------------------------*/

/* For enabling the printf using USBD.
 * After the Initialization of USBD the board will wait 5 seconds for having
 * the possibility to take a look on the Initialization phase */


/**************************************
 *  Lab/Experimental section defines  *
***************************************/

#define STBOX1_SAVE_BOARD_NAME


/* For enabling the capability to restart in DFU mode */
//#define STBOX1_RESTART_DFU

/* For enabling connection and notification subscriptions debug */
#define STBOX1_DEBUG_CONNECTION

/* Uncomment the following define for forcing a full BLE rescan for the Android/iOS "ST BLE Sensor" application*/
#define BLE_FORCE_RESCAN

/**************************************
 * Don't Change the following defines *
***************************************/

/* Package Version only numbers 0->9 */
#define STBOX1_VERSION_MAJOR '1'
#define STBOX1_VERSION_MINOR '0'
#define STBOX1_VERSION_PATCH '0'

/* Define the STBOX1 Name MUST be 7 char long */
#define NAME_BLUEMS 'B','B','S','_',STBOX1_VERSION_MAJOR,STBOX1_VERSION_MINOR,STBOX1_VERSION_PATCH

/* Package Name */
#define STBOX1_PACKAGENAME "AssetTrackingDemo"

#ifdef STBOX1_ENABLE_PRINTF
  #define STBOX1_PRINTF(...) {\
    VComBytesToWrite = sprintf((char *)VComBufferToWrite, __VA_ARGS__);\
    CDC_Fill_Buffer(VComBufferToWrite, VComBytesToWrite);\
      }
 //     CDC_Transmit_FS(VComBufferToWrite, VComBytesToWrite); //SB Code Modification
  
#else /* STBOX1_ENABLE_PRINTF */
  #define STBOX1_PRINTF(...)  
#endif /* STBOX1_ENABLE_PRINTF */

/* STM32 Unique ID */
#define STM32_UUID ((uint32_t *)0x1FFF7590)

/* STM32 MCU_ID */
#define STM32_MCU_ID ((uint32_t *)0xE0042000)

/* BlueNRG SPI Port */
#define BNRG_SPI_INSTANCE               SPI2
/* BlueNRG SPI Clock */
#define BNRG_SPI_CLK_ENABLE()           __SPI2_CLK_ENABLE()
#define BNRG_SPI_CLK_DISABLE()          __SPI2_CLK_DISABLE()

/* SPI Configuration */
#define BNRG_SPI_MODE                   SPI_MODE_MASTER
#define BNRG_SPI_DIRECTION              SPI_DIRECTION_2LINES
#define BNRG_SPI_DATASIZE               SPI_DATASIZE_8BIT
#define BNRG_SPI_CLKPOLARITY            SPI_POLARITY_LOW
#define BNRG_SPI_CLKPHASE               SPI_PHASE_2EDGE
#define BNRG_SPI_NSS                    SPI_NSS_SOFT
#define BNRG_SPI_FIRSTBIT               SPI_FIRSTBIT_MSB
#define BNRG_SPI_TIMODE                 SPI_TIMODE_DISABLED
#define BNRG_SPI_CRCPOLYNOMIAL          7
#define BNRG_SPI_BAUDRATEPRESCALER      SPI_BAUDRATEPRESCALER_128
#define BNRG_SPI_CRCCALCULATION         SPI_CRCCALCULATION_DISABLED
                                              
/* BlueNRG SPI SCLK define values */
#define BNRG_SPI_SCLK_PIN               GPIO_PIN_1                 /* PD.1 */
#define BNRG_SPI_SCLK_MODE              GPIO_MODE_AF_PP
#define BNRG_SPI_SCLK_PULL              GPIO_NOPULL
#define BNRG_SPI_SCLK_SPEED             GPIO_SPEED_FREQ_HIGH       /* GPIOD */
#define BNRG_SPI_SCLK_ALTERNATE         GPIO_AF5_SPI2
#define BNRG_SPI_SCLK_PORT              GPIOD
#define BNRG_SPI_SCLK_CLK_ENABLE()      __GPIOD_CLK_ENABLE()
/* Defines for MISO pin */
#define BNRG_SPI_MISO_PIN               GPIO_PIN_3                 /* PD.3 */
#define BNRG_SPI_MISO_MODE              GPIO_MODE_AF_PP
#define BNRG_SPI_MISO_PULL              GPIO_NOPULL
#define BNRG_SPI_MISO_SPEED             GPIO_SPEED_MEDIUM
#define BNRG_SPI_MISO_ALTERNATE         GPIO_AF5_SPI2
#define BNRG_SPI_MISO_PORT              GPIOD
#define BNRG_SPI_MISO_CLK_ENABLE()      __GPIOD_CLK_ENABLE()
/* Defines for MOSI pin */
#define BNRG_SPI_MOSI_PIN               GPIO_PIN_3                 /* PC.3 */
#define BNRG_SPI_MOSI_MODE              GPIO_MODE_AF_PP
#define BNRG_SPI_MOSI_PULL              GPIO_NOPULL
#define BNRG_SPI_MOSI_SPEED             GPIO_SPEED_MEDIUM
#define BNRG_SPI_MOSI_ALTERNATE         GPIO_AF5_SPI2
#define BNRG_SPI_MOSI_PORT              GPIOC
#define BNRG_SPI_MOSI_CLK_ENABLE()      __GPIOC_CLK_ENABLE()
/* BlueNRG SPI CS define values */
#define BNRG_SPI_CS_PIN                 GPIO_PIN_0                  /* PD.0 */
#define BNRG_SPI_CS_MODE                GPIO_MODE_OUTPUT_PP
#define BNRG_SPI_CS_PULL                GPIO_NOPULL
#define BNRG_SPI_CS_SPEED               GPIO_SPEED_MEDIUM
#define BNRG_SPI_CS_ALTERNATE           0
#define BNRG_SPI_CS_PORT                GPIOD
#define BNRG_SPI_CS_CLK_ENABLE()        __GPIOD_CLK_ENABLE()
/* BlueNRG SPI IRQ line define values */
#define BNRG_SPI_IRQ_PIN                GPIO_PIN_4                  /* PD.4 */
#define BNRG_SPI_IRQ_MODE               GPIO_MODE_IT_RISING
#define BNRG_SPI_IRQ_PULL               GPIO_NOPULL
#define BNRG_SPI_IRQ_SPEED              GPIO_SPEED_MEDIUM
#define BNRG_SPI_IRQ_ALTERNATE          0
#define BNRG_SPI_IRQ_PORT               GPIOD
#define BNRG_SPI_IRQ_CLK_ENABLE()       __GPIOD_CLK_ENABLE()

/*EXTI External Interrupt for SPI*/
/* NOTE: if you change the IRQ pin remember to implement a corresponding handler */
/* function like EXTI15_10_IRQn in the user project*/
#define BNRG_SPI_EXTI_IRQn              EXTI4_IRQn
#define BNRG_SPI_EXTI_IRQHandler        EXTI4_IRQHandler
#define BNRG_SPI_EXTI_PIN               BNRG_SPI_IRQ_PIN
#define BNRG_SPI_EXTI_PORT              BNRG_SPI_IRQ_PORT
#define RTC_WAKEUP_IRQHandler           RTC_IRQHandler

/* BlueNRG SW reset line define values */
#define BNRG_SPI_RESET_PIN              GPIO_PIN_8      /* PA.8 */
#define BNRG_SPI_RESET_MODE             GPIO_MODE_OUTPUT_PP
#define BNRG_SPI_RESET_PULL             GPIO_NOPULL
#define BNRG_SPI_RESET_SPEED            GPIO_SPEED_LOW
#define BNRG_SPI_RESET_ALTERNATE        0
#define BNRG_SPI_RESET_PORT             GPIOA
#define BNRG_SPI_RESET_CLK_ENABLE()     __GPIOA_CLK_ENABLE()

#endif /* __STBOX1_CONFIG_H */

/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
