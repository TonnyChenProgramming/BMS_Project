################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/buzzer/buzzer.c 

OBJS += \
./Core/Src/buzzer/buzzer.o 

C_DEPS += \
./Core/Src/buzzer/buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/buzzer/%.o Core/Src/buzzer/%.su Core/Src/buzzer/%.cyclo: ../Core/Src/buzzer/%.c Core/Src/buzzer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"../Core/Inc/display" -I"../Core/Src/display" -I"../Core/Src/buzzer" -I"../Core/Inc/buzzer" -I"../Core/Inc/sensing" -I"../Core/Src/sensing" -I"../Core/Inc/processings" -I"../Core/Src/processings" -I"../Core/Src/bms_data" -I"../Core/Inc/bms_data" -I"../Core/Src/eeprom_at24c16" -I"../Core/Inc/eeprom_at24c16" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-buzzer

clean-Core-2f-Src-2f-buzzer:
	-$(RM) ./Core/Src/buzzer/buzzer.cyclo ./Core/Src/buzzer/buzzer.d ./Core/Src/buzzer/buzzer.o ./Core/Src/buzzer/buzzer.su

.PHONY: clean-Core-2f-Src-2f-buzzer

