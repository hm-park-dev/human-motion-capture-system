################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/app_entry.c \
C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/hw_timerserver.c \
C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/hw_uart.c \
C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/main.c \
C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/stm32_lpm_if.c \
C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/stm32wbxx_hal_msp.c \
C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/stm32wbxx_it.c \
C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/stm32wbxx_nucleo_bus.c 

OBJS += \
./Application/User/Core/app_entry.o \
./Application/User/Core/hw_timerserver.o \
./Application/User/Core/hw_uart.o \
./Application/User/Core/main.o \
./Application/User/Core/stm32_lpm_if.o \
./Application/User/Core/stm32wbxx_hal_msp.o \
./Application/User/Core/stm32wbxx_it.o \
./Application/User/Core/stm32wbxx_nucleo_bus.o 

C_DEPS += \
./Application/User/Core/app_entry.d \
./Application/User/Core/hw_timerserver.d \
./Application/User/Core/hw_uart.d \
./Application/User/Core/main.d \
./Application/User/Core/stm32_lpm_if.d \
./Application/User/Core/stm32wbxx_hal_msp.d \
./Application/User/Core/stm32wbxx_it.d \
./Application/User/Core/stm32wbxx_nucleo_bus.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/app_entry.o: C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/app_entry.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Application/User/Core/hw_timerserver.o: C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/hw_timerserver.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Application/User/Core/hw_uart.o: C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/hw_uart.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Application/User/Core/main.o: C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/main.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Application/User/Core/stm32_lpm_if.o: C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/stm32_lpm_if.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Application/User/Core/stm32wbxx_hal_msp.o: C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/stm32wbxx_hal_msp.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Application/User/Core/stm32wbxx_it.o: C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/stm32wbxx_it.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Application/User/Core/stm32wbxx_nucleo_bus.o: C:/Users/dys05/gitttttt/human-motion-capture-system/STM32/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/stm32wbxx_nucleo_bus.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core

clean-Application-2f-User-2f-Core:
	-$(RM) ./Application/User/Core/app_entry.d ./Application/User/Core/app_entry.o ./Application/User/Core/app_entry.su ./Application/User/Core/hw_timerserver.d ./Application/User/Core/hw_timerserver.o ./Application/User/Core/hw_timerserver.su ./Application/User/Core/hw_uart.d ./Application/User/Core/hw_uart.o ./Application/User/Core/hw_uart.su ./Application/User/Core/main.d ./Application/User/Core/main.o ./Application/User/Core/main.su ./Application/User/Core/stm32_lpm_if.d ./Application/User/Core/stm32_lpm_if.o ./Application/User/Core/stm32_lpm_if.su ./Application/User/Core/stm32wbxx_hal_msp.d ./Application/User/Core/stm32wbxx_hal_msp.o ./Application/User/Core/stm32wbxx_hal_msp.su ./Application/User/Core/stm32wbxx_it.d ./Application/User/Core/stm32wbxx_it.o ./Application/User/Core/stm32wbxx_it.su ./Application/User/Core/stm32wbxx_nucleo_bus.d ./Application/User/Core/stm32wbxx_nucleo_bus.o ./Application/User/Core/stm32wbxx_nucleo_bus.su

.PHONY: clean-Application-2f-User-2f-Core

