################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Drivers/BSP/IKS01A3/iks01a3_env_sensors.c \
C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Drivers/BSP/IKS01A3/iks01a3_env_sensors_ex.c \
C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Drivers/BSP/IKS01A3/iks01a3_motion_sensors.c \
C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Drivers/BSP/IKS01A3/iks01a3_motion_sensors_ex.c 

OBJS += \
./Drivers/BSP/IKS01A3/iks01a3_env_sensors.o \
./Drivers/BSP/IKS01A3/iks01a3_env_sensors_ex.o \
./Drivers/BSP/IKS01A3/iks01a3_motion_sensors.o \
./Drivers/BSP/IKS01A3/iks01a3_motion_sensors_ex.o 

C_DEPS += \
./Drivers/BSP/IKS01A3/iks01a3_env_sensors.d \
./Drivers/BSP/IKS01A3/iks01a3_env_sensors_ex.d \
./Drivers/BSP/IKS01A3/iks01a3_motion_sensors.d \
./Drivers/BSP/IKS01A3/iks01a3_motion_sensors_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/IKS01A3/iks01a3_env_sensors.o: C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Drivers/BSP/IKS01A3/iks01a3_env_sensors.c Drivers/BSP/IKS01A3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Drivers/BSP/IKS01A3/iks01a3_env_sensors_ex.o: C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Drivers/BSP/IKS01A3/iks01a3_env_sensors_ex.c Drivers/BSP/IKS01A3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Drivers/BSP/IKS01A3/iks01a3_motion_sensors.o: C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Drivers/BSP/IKS01A3/iks01a3_motion_sensors.c Drivers/BSP/IKS01A3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Drivers/BSP/IKS01A3/iks01a3_motion_sensors_ex.o: C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Drivers/BSP/IKS01A3/iks01a3_motion_sensors_ex.c Drivers/BSP/IKS01A3/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STM32WBXX_NUCLEO -DUSE_IKS01A3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' '-DOPENTHREAD_CONFIG_FILE=<openthread_api_config_ftd.h>' -DUSE_HAL_DRIVER -DSTM32WB55xx -c -I../../../Core/Inc -I../../../STM32_WPAN/App -I../../../MEMS/App -I../../../MEMS/Target -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc -I../../../../../../../Drivers/STM32WBxx_HAL_Driver/Inc/Legacy -I../../../../../../../Middlewares/ST/STM32_WPAN -I../../../../../../../Middlewares/ST/STM32_WPAN/ble -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl -I../../../../../../../Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci -I../../../../../../../Middlewares/ST/STM32_WPAN/utilities -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/auto -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/core/template -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Inc -I../../../../../../../Middlewares/ST/STM32_WPAN/ble/svc/Src -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WBxx/Include -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/BSP/Components/lsm6dso/ -I../../../../../../../Drivers/BSP/Components/lis2dw12/ -I../../../../../../../Drivers/BSP/Components/lis2mdl/ -I../../../../../../../Drivers/BSP/Components/hts221/ -I../../../../../../../Drivers/BSP/Components/lps22hh/ -I../../../../../../../Drivers/BSP/Components/stts751/ -I../../../../../../../Drivers/BSP/IKS01A3/ -I../../../../../../../Drivers/BSP/Components/Common/ -I../../../../../../../Drivers/BSP/P-NUCLEO-WB55.Nucleo/ -I../../../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionCP_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionGR_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -O3 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-IKS01A3

clean-Drivers-2f-BSP-2f-IKS01A3:
	-$(RM) ./Drivers/BSP/IKS01A3/iks01a3_env_sensors.d ./Drivers/BSP/IKS01A3/iks01a3_env_sensors.o ./Drivers/BSP/IKS01A3/iks01a3_env_sensors.su ./Drivers/BSP/IKS01A3/iks01a3_env_sensors_ex.d ./Drivers/BSP/IKS01A3/iks01a3_env_sensors_ex.o ./Drivers/BSP/IKS01A3/iks01a3_env_sensors_ex.su ./Drivers/BSP/IKS01A3/iks01a3_motion_sensors.d ./Drivers/BSP/IKS01A3/iks01a3_motion_sensors.o ./Drivers/BSP/IKS01A3/iks01a3_motion_sensors.su ./Drivers/BSP/IKS01A3/iks01a3_motion_sensors_ex.d ./Drivers/BSP/IKS01A3/iks01a3_motion_sensors_ex.o ./Drivers/BSP/IKS01A3/iks01a3_motion_sensors_ex.su

.PHONY: clean-Drivers-2f-BSP-2f-IKS01A3
