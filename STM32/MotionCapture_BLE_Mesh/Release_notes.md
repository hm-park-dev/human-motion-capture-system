::: {.row}
::: {.col-sm-12 .col-lg-4}
Release Notes for {#release-notes-for-fp-sns-blemesh1}
=================

FP-SNS-BLEMESH1 {#release-notes-for-fp-sns-blemesh1}
===============

Copyright © 2022 STMicroelectronics\

[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}

Purpose
=======

The FP-SNS-BLEMESH1 software package is an expansion for STM32Cube. This
software provides demonstration firmware for using the BlueNRG-MS and
BlueNRG2 for creating BLE-Mesh network. It is built on top of STM32Cube
software technology that ease portability across different STM32
micro-controllers. The software lets you easily create your own
application for extending BLE Mesh networks (by offering a ready-to-use
Mesh core library), a complete set of compatible APIs, and a Sensor demo
application running on either X-NUCLEO-IDB05A1 or X-NUCLEO-BNRG2A1 with
IKS01A3 expansion boards connected to NUCLEO-L476RG development
board.Smart Sensor demo application has been provided in the Firmware
folder which can be used to demonstrate real-time environmental sensor
data on Android or iOS application.

FP-SNS-BLEMESH1 software features:

-   Firmware demo for BlueNRG-M0, BlueNRG2A1 with IKS01A3
-   BLE Mesh Stack in library format, to generate different applications
-   Easy portability across different MCU families thanks to STM32Cube
-   Free user-friendly license terms
-   Complete software to build Mesh network with Bluetooth low energy
    (BLE) nodes supporting the "BLE Mesh Sensor Model", defined in BLE
    Mesh Specification V1.0

\[![The FP-SNS-BLEMESH1 package
contents](_htmresc/BLE_Mesh_Sensor_Model.png)\]

Here is the list of references to user documents:

-   [X-NUCLEO-IKS01A3
    SCHEMATIC](https://www.st.com/content/ccc/resource/technical/layouts_and_diagrams/schematic_pack/group1/0d/b2/51/b1/82/cd/44/42/X-NUCLEO-IKS01A3_SCHEMATIC/files/x-nucleo-iks01a3_schematic.pdf/jcr:content/translations/en.x-nucleo-iks01a3_schematic.pdf)
-   [X-NUCLEO-BNRG2A1
    SCHEMATIC](https://www.st.com/content/ccc/resource/technical/layouts_and_diagrams/schematic_pack/group1/71/cf/2c/3a/24/07/42/7b/X-NUCLEO-BNRG2A1_SCHEMATIC/files/x-nucleo-bnrg2a1_schematic.pdf/jcr:content/translations/en.x-nucleo-bnrg2a1_schematic.pdf)
-   [X-NUCLEO-IDB05A2
    SCHEMATIC](https://www.st.com/resource/en/schematic_pack/x-nucleo-idb05a2_schematic.pdf)
-   [STEVAL-MKSBOX1V1
    SCHEMATIC](https://www.st.com/resource/en/schematic_pack/steval-mksbox1v1_schematic.pdf)
-   [STM32 Nucleo expansion
    boards](https://www.st.com/en/evaluation-tools/stm32-nucleo-expansion-boards.html)
:::

::: {#update-history .section .col-sm-12 .col-lg-8}
Update History
==============

::: {.collapse}
V1.4.0 / 31-JAN-2022

<div>

Main Changes
------------

### Product update

  Headline
  --------------------------------------------------------------------------------------------
  Integrated latest BlueNRG-Mesh library (version 1.14.000)
  Aligned and developed over X-CUBE-BLEMESH1 v2.1.3
  Updated Sensor Model application
  MOBLE\_USER\_BLE\_CB\_MAP split into two structs: MESH\_USER\_CB\_MAP & MESH\_BLE\_CB\_MAP
  Aligned firmware with latest HAL,BLE and senor drivers
  Neutral license file added

Contents
--------

The FP-SNS-BLEMESH1 expansion software package comes with a rich set of
examples running on STMicroelectronics boards, provided with
preconfigured projects for the main supported toolchains.

Documentation

Name

</div>
:::
:::
:::

Version

Document

FP-SNS-BLEMESH1 API Description

V1.4.0

[CHM](Documentation\FP-SNS-BLEMESH1.chm)

BlueNRG-Mesh Library

V1.14.000

[Release Notes](Middlewares\ST\ST_BLE_Mesh\Release_Notes.html)

Drivers

  Name                    Version   Release note
  ----------------------- --------- -----------------------------------------------------------------------
  STM32L4xx CMSIS         V1.7.1    [release notes](Drivers\CMSIS\Device\ST\STM32L4xx\Release_Notes.html)
  STM32L4xx HAL           V1.13.0   [release notes](Drivers\STM32L4xx_HAL_Driver\Release_Notes.html)
  BSP STM32L4xx\_Nucleo   V2.1.7    [release notes](Drivers\BSP\STM32L4xx_Nucleo\Release_Notes.html)
  X-NUCLEO-IDB05A2        V1.0.0    [release notes](Drivers\BSP\X-NUCLEO-IDB05A2\Release_Notes.html)
  X-NUCLEO-BNRG2A1        V1.0.0    [release notes](Drivers\BSP\X-NUCLEO-BNRG2A1\Release_Notes.html)
  IKS01A3                 V1.7.0    [release notes](Drivers\BSP\IKS01A3\Release_Notes.html)
  SensorTile.box          V1.3.3    [release notes](Drivers\BSP\SensorTile.box\Release_Notes.html)

Projects

  Name       Version   Release note
  ---------- --------- ----------------------------------------------
  Projects   V1.4.0    [release notes](Projects\Release_Notes.html)

Known Limitations
-----------------

-   Not Any

Development Toolchains and Compilers
------------------------------------

-   IAR Embedded Workbench for ARM (EWARM) toolchain V9.20.1
-   RealView Microcontroller Development Kit (MDK-ARM) toolchain V5.32.0
-   STM32CubeIDE V1.8.0

Supported Devices and Boards
----------------------------

-   NUCLEO-L476RG MB1136 rev.C
-   X-NUCLEO-IDB05A2
-   X-NUCLEO-BNRG2A1
-   X-NUCLEO-IKS01A3
-   STEVAL-MKSBOX1V1

Dependencies
------------

None

::: {.collapse}
V1.3.0 / 01-Dec-2020

<div>

Main Changes {#main-changes}
------------

### Product update {#product-update}

  Headline
  -----------------------------------------------------------
  Integrated latest BlueNRG-Mesh library (version 1.13.000)
  Aligned and developed over X-CUBE-BLEMESH1 v2.1.0
  Updated Sensor Model application
  Fixed Some Bugs

Contents {#contents}
--------

The FP-SNS-BLEMESH1 expansion software package comes with a rich set of
examples running on STMicroelectronics boards, provided with
preconfigured projects for the main supported toolchains.

Documentation

Name

</div>
:::

Version

Document

FP-SNS-BLEMESH1 API Description

V1.3.0

[CHM](Documentation\FP-SNS-BLEMESH1.chm)

BlueNRG-Mesh Library

V1.13.000

[Release Notes](Middlewares\ST\ST_BLE_Mesh\Release_Notes.html)

Drivers

  Name                    Version   Release note
  ----------------------- --------- -----------------------------------------------------------------------
  STM32L4xx CMSIS         V1.5.1    [release notes](Drivers\CMSIS\Device\ST\STM32L4xx\Release_Notes.html)
  STM32L4xx HAL           V1.10.0   [release notes](Drivers\STM32L4xx_HAL_Driver\Release_Notes.html)
  BSP STM32L4xx\_Nucleo   V2.1.5    [release notes](Drivers\BSP\STM32L4xx_Nucleo\Release_Notes.html)
  X-NUCLEO-IDB05A2        V1.0.0    [release notes](Drivers\BSP\X-NUCLEO-IDB05A2\Release_Notes.html)
  X-NUCLEO-BNRG2A1        V1.0.0    [release notes](Drivers\BSP\X-NUCLEO-BNRG2A1\Release_Notes.html)
  IKS01A3                 V1.2.1    [release notes](Drivers\BSP\IKS01A3\Release_Notes.html)
  SensorTile.box          V1.3.1    [release notes](Drivers\BSP\SensorTile.box\Release_Notes.html)

Projects

  Name       Version   Release note
  ---------- --------- ----------------------------------------------
  Projects   V1.3.0    [Release Notes](Projects\Release_Notes.html)

Known Limitations {#known-limitations}
-----------------

-   Not Any

Development Toolchains and Compilers {#development-toolchains-and-compilers}
------------------------------------

-   IAR Embedded Workbench for ARM (EWARM) toolchain V8.50.5
-   RealView Microcontroller Development Kit (MDK-ARM) toolchain V5.32.0
-   STM32CubeIDE V1.7.0

Supported Devices and Boards {#supported-devices-and-boards}
----------------------------

-   NUCLEO-L476RG MB1136 rev.C
-   X-NUCLEO-IDB05A2
-   X-NUCLEO-BNRG2A1
-   X-NUCLEO-IKS01A3
-   STEVAL-MKSBOX1V1

Dependencies {#dependencies}
------------

None

::: {.collapse}
:::

::: {.columns}
::: {.column style="width:95%;"}
For complete documentation on **X-CUBE-EEPRMA1**, visit:
[www.st.com](https://www.st.com/content/st_com/en/products/embedded-software/mcu-mpu-embedded-software/stm32-embedded-software/stm32cube-expansion-packages/x-cube-eeprma1.html)
:::

::: {.column style="width:5%;"}
Info
:::
:::
