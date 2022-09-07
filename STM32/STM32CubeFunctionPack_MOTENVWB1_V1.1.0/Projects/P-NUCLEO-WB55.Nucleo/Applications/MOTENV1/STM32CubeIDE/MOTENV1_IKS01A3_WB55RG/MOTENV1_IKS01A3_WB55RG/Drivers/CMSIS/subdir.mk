################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/system_stm32wbxx.c 

OBJS += \
./Drivers/CMSIS/system_stm32wbxx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32wbxx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32wbxx.o: C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/Core/Src/system_stm32wbxx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32wbxx.d ./Drivers/CMSIS/system_stm32wbxx.o ./Drivers/CMSIS/system_stm32wbxx.su

.PHONY: clean-Drivers-2f-CMSIS

