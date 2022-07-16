---
pagetitle: Release Notes for MotionAD Library
lang: en
header-includes: <link rel="icon" type="image/x-icon" href="_htmresc/favicon.png" />
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

<center>
# Release Notes for MotionAD Airplane Detection Library
Copyright &copy; 2021 STMicroelectronics\

[![ST logo](_htmresc/st_logo_2020.png)](https://www.st.com){.logo}
</center>

# License

This software component is licensed by ST under Software License Agreement SLA0077, the "License".
You may not use this component except in compliance with the License. You may obtain a copy of the License at:

[Software License Agreement SLA0077](https://www.st.com/content/ccc/resource/legal/legal_agreement/license_agreement/group0/62/6a/48/15/b4/12/47/7a/DM00367782/files/DM00367782.pdf/jcr:content/translations/en.DM00367782.pdf)

# Purpose

**What is MotionAD?**

- The MotionAD provides real-time airplane mode data.
- The library acquires data from the accelerometer, pressure and temperature sensors and performs the algorithm to detect the airplane mode from takeoff till landing.

The library is generated for each ARM Cortex-M core with EABI compiler thus the library might be used with any other compiler which supports ARM EABI specification.

The library is available for two different wchar variable lengths - 16 bit (wc16) and 32bit (wc32).

By default the libraries are compiled with option -mfloat-abi=softfp which allows use of floating-point instructions but maintains compatibility with the soft-float ABI. The libraries ending with suffix hard are compiled with option -mfloat-abi=hard and uses floating-point instructions and the floating-point ABI.

Here is the list of references to the user documents:

- [Getting started with MotionAD airplane detection library in X-CUBE-MEMS1 expansion for STM32Cube](https://www.st.com/resource/en/user_manual/dm00705943-getting-started-with-motionad-airplane-detection-library-in-xcubemems1-expansion-for-stm32cube-stmicroelectronics.pdf)
- [Getting started with the X-CUBE-MEMS1 motion MEMS and environmental sensor software expansion for STM32Cube](https://www.st.com/resource/en/user_manual/dm00157069-getting-started-with-the-xcubemems1-motion-mems-and-environmental-sensor-software-expansion-for-stm32cube-stmicroelectronics.pdf)
:::

::: {.col-sm-12 .col-lg-8}
# Update history

::: {.collapse}
<input type="checkbox" id="collapse-section12" checked aria-hidden="true">
<label for="collapse-section12" aria-hidden="true">V1.1.1 / 24-August-2021</label>
<div>			

## Main changes

### Patch release

- Changed F767 CPU to F722 in order to switch FPU DP to SP for CM7

## Development toolchains and compilers

- IAR Embedded Workbench for ARM (EWARM) toolchain V8.50.9
- RealView Microcontroller Development Kit (MDK-ARM) toolchain V5.32.0
- STM32CubeIDE V1.7.0

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section11" aria-hidden="true">
<label for="collapse-section11" aria-hidden="true">V1.1.0 / 21-April-2021</label>
<div>			

## Main changes

### Maintenance release

- Added CM33F support
- Updated Release Notes to new format

## Development toolchains and compilers

- IAR Embedded Workbench for ARM (EWARM) toolchain V8.50.9
- RealView Microcontroller Development Kit (MDK-ARM) toolchain V5.32.0
- STM32CubeIDE V1.6.1

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section9" aria-hidden="true">
<label for="collapse-section9" aria-hidden="true">V1.0.3 / 28-May-2020</label>
<div>			

## Main changes

### Patch release

- Library compiled in STM32CubeIDE

## Development toolchains and compilers

- STM32CubeIDE V1.3.1

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1" aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">V1.0.2 / 25-March-2020</label>
<div>			

## Main changes

### First release

- First official release

## Development toolchains and compilers

- System Workbench for STM32 V2.7.2

</div>
:::

:::
:::

<footer class="sticky">
::: {.columns}
::: {.column width="95%"}
For complete documentation on **MotionAD** ,
visit: [X-CUBE-MEMS1](https://www.st.com/en/embedded-software/x-cube-mems1.html)
:::
::: {.column width="5%"}
<abbr title="Based on template cx566953 version 2.0">Info</abbr>
:::
:::
</footer>
