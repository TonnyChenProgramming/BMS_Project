################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/processings/processings.c 

OBJS += \
./Core/Src/processings/processings.o 

C_DEPS += \
./Core/Src/processings/processings.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/processings/%.o Core/Src/processings/%.su Core/Src/processings/%.cyclo: ../Core/Src/processings/%.c Core/Src/processings/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Core/Inc/display" -I"../Core/Src/display" -I../Core/Inc/sensing -I../Core/Src/sensing -I../Core/Inc/buzzer -I../Core/Src/buzzer -I../Core/Inc/processings -I../Core/Src/processings -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-processings

clean-Core-2f-Src-2f-processings:
	-$(RM) ./Core/Src/processings/processings.cyclo ./Core/Src/processings/processings.d ./Core/Src/processings/processings.o ./Core/Src/processings/processings.su

.PHONY: clean-Core-2f-Src-2f-processings

