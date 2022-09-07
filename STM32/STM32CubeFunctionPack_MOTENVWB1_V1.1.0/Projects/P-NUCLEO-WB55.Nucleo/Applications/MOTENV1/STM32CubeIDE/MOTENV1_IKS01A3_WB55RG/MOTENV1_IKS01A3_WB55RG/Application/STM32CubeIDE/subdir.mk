################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/STM32CubeIDE/startup_stm32wb55xx_cm4.s 

OBJS += \
./Application/STM32CubeIDE/startup_stm32wb55xx_cm4.o 

S_DEPS += \
./Application/STM32CubeIDE/startup_stm32wb55xx_cm4.d 


# Each subdirectory must supply rules for building sources it contributes
Application/STM32CubeIDE/startup_stm32wb55xx_cm4.o: C:/Users/cude/STM32CubeIDE/wbsensorplussns/STM32CubeFunctionPack_MOTENVWB1_V1.1.0/Projects/P-NUCLEO-WB55.Nucleo/Applications/MOTENV1/STM32CubeIDE/startup_stm32wb55xx_cm4.s Application/STM32CubeIDE/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@" "$<"

clean: clean-Application-2f-STM32CubeIDE

clean-Application-2f-STM32CubeIDE:
	-$(RM) ./Application/STM32CubeIDE/startup_stm32wb55xx_cm4.d ./Application/STM32CubeIDE/startup_stm32wb55xx_cm4.o

.PHONY: clean-Application-2f-STM32CubeIDE

