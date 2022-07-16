/**
******************************************************************************
* @file    BLESensors\Inc\SensorTile.box_conf.h
* @author  SRA - Central Labs
* @version V1.4.0
* @date    21-01-2022
* @brief   This file define the SensorTile.box configuration
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
#ifndef __SENSORTILE_BOX_CONF_H__
#define __SENSORTILE_BOX_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "SensorTile.box_bus.h"
#include "SensorTile.box_errno.h"

#define USE_MOTION_SENSOR_LIS2DW12_0        0U
#define USE_MOTION_SENSOR_LIS2MDL_0         1U
#define USE_MOTION_SENSOR_LIS3DHH_0         0U 
#define USE_MOTION_SENSOR_LSM6DSOX_0        1U
#define USE_ENV_SENSOR_HTS221_0             1U
#define USE_ENV_SENSOR_LPS22HH_0            1U
#define USE_ENV_SENSOR_STTS751_0            1U
#define USE_AUDIO_IN                        0U
  
//set to 1 if you want to use the implemented irq handler, 0 to use the one in your project files
#define USE_BC_IRQ_HANDLER                  0

//set to 1 if you want to use the implemented irq callback, 0 to use the one in your project files
#define USE_BC_IRQ_CALLBACK                 0

#define AUDIO_SAMPLING_FREQUENCY  16000
#define AUDIO_VOLUME_INPUT      50U
#define BSP_AUDIO_IN_IT_PRIORITY 6U

#define BSP_AUDIO_IN_INSTANCE 1U   /* Audio instance */

#ifdef __cplusplus
}
#endif

#endif /* __SENSORTILE_BOX_CONF_H__*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

