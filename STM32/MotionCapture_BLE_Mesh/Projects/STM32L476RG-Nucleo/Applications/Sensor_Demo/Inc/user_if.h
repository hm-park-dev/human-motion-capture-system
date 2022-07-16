/**
******************************************************************************
* @file    user_if.h
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Header file for User interface file 
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
#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
#ifdef STM32_BLUENRG1
#include "clock.h"
#else
#include "ble_clock.h" 
#endif
#include "hci.h"

#define BUTTON_PRESSED GPIO_PIN_RESET

/* Exported typedefs ---------------------------------------------*/
typedef GPIO_PinState BUTTON_STATE;
typedef void (* IO_RECEIVE_DATA_USER_CALLBACK_TYPE) (uint8_t * rx_data, uint16_t data_size);

/* Exported Functions Prototypes ---------------------------------------------*/
void SdkEval_IO_Receive_Data(uint8_t * rx_data, uint16_t data_size);

#endif /* _USER_INTERFACE_H_ */

/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

