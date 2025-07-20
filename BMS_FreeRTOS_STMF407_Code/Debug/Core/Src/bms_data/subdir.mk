################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/bms_data/bms_data.c 

OBJS += \
./Core/Src/bms_data/bms_data.o 

C_DEPS += \
./Core/Src/bms_data/bms_data.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/bms_data/%.o Core/Src/bms_data/%.su Core/Src/bms_data/%.cyclo: ../Core/Src/bms_data/%.c Core/Src/bms_data/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"../Core/Inc/display" -I"../Core/Src/display" -I"../Core/Src/buzzer" -I"../Core/Inc/buzzer" -I"../Core/Inc/sensing" -I"../Core/Src/sensing" -I"../Core/Inc/processings" -I"../Core/Src/processings" -I"../Core/Src/bms_data" -I"../Core/Inc/bms_data" -I"../Core/Src/eeprom_at24c16" -I"../Core/Inc/eeprom_at24c16" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-bms_data

clean-Core-2f-Src-2f-bms_data:
	-$(RM) ./Core/Src/bms_data/bms_data.cyclo ./Core/Src/bms_data/bms_data.d ./Core/Src/bms_data/bms_data.o ./Core/Src/bms_data/bms_data.su

.PHONY: clean-Core-2f-Src-2f-bms_data

