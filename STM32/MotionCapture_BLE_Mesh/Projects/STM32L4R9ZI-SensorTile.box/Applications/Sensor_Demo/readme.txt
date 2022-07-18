/**
  ****************************************************************************
  * @file       readme.txt
  * @version    V1.4.0
  * @date       21-01-2022
  * @brief      This application contains an  application implements Sensor Model scenario,which you may modify according to your requirements.
  *             It uses BlueNRG-MS devices with Mesh stack APIs and related event callbacks.
  *             The SDK provides the Mesh stack in library form and a sample application in source code to demonstrate how to use the library.
  *             
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

Application Description 

 Main function is to show how to use BLE sensor model to receive sensor data from sensor expansion board over BLE mesh network. 
 User can see sensor value on UART and android application.

 After connection has been established:
 - the user can view the data from various on-board environment sensors like Temperature, Humidity, and Pressure.
 - the user can also view data from various on-board MEMS sensors as well like Accelerometer,Gyroscope, and Magnetometer.

@par Hardware and Software environment

  - This example runs on SensorTile.box, its a wireless multi sensor development kit with user friendly app for IoT and wearable sensor applications.
  - If you power the Nucleo board via USB 3.0 port, please check that you have flashed the last version of
    the firmware of ST-Link v2 inside the SensorTile.box. In order to flash the last available firmware of the
	ST-Link v2, you can use the STM32 ST Link Utility.


@par How to use it ?

This package contains projects for IAR IDEs viz. In order to make the
program work, you must do the following:
 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.

For IAR:
 - Open IAR toolchain (this firmware has been successfully tested with Embedded Workbench V9.20.1).
 - Open the IAR project file EWARM\Project.eww  according to the target board used.
 - Rebuild all files and load your image into target memory.
 - Run the example.

For µVision:
 - Open µVision 5 toolchain (this firmware has been successfully tested with MDK-ARM Professional Version: 5.32.0).
 - Open the µVision project file MDK-ARM\Project.uvprojx according the target board used.
 - Rebuild all files and load your image into target memory.
 - Run the example.

For STM32CubeIDE:
 - Open STM32CubeIDE (this firmware has been successfully tested with STM32CubeIDE V1.8.0).
 - Open the STM32CubeIDE project file STM32CubeIDE\Sensor-STBOX\.cproject 
 - Rebuild all files and load your image into target memory.
 - Run the example.
		
 /******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
