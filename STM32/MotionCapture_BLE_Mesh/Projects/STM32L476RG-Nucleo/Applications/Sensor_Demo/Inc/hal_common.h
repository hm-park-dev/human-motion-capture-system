/**
******************************************************************************
* @file    hal_common.h
* @author  BLE Mesh Team
* @version V1.4.0
* @date    21-01-2022
* @brief   Common functions of HAL file 
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
#ifndef _HAL_H_
#define _HAL_H_

/* Includes ------------------------------------------------------------------*/

#if defined(NUCLEO_L152RE) || defined(NUCLEO_F401RE) || defined(NUCLEO_L476RG) || defined(NUCLEO_F303RE)
#include "user_if.h" 
#else
#error "Unsupported board"
#endif 

#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stdbool.h>

#include "types.h"

void SetLed(int state);
BUTTON_STATE GetButtonState(void);
bool Accel_Process(uint8_t *evt);
bool Temperature_Read(int16_t *data);
void InitDevice(void);

void ShouldSleepFunc(void);

#endif /* _HAL_H_ */
/******************* (C) COPYRIGHT 2017 STMicroelectronics *****END OF FILE****/

