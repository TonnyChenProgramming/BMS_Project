################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/eeprom_at24c16/epprom_processings.c 

OBJS += \
./Core/Src/eeprom_at24c16/epprom_processings.o 

C_DEPS += \
./Core/Src/eeprom_at24c16/epprom_processings.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/eeprom_at24c16/%.o Core/Src/eeprom_at24c16/%.su Core/Src/eeprom_at24c16/%.cyclo: ../Core/Src/eeprom_at24c16/%.c Core/Src/eeprom_at24c16/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Core/Inc/display" -I"../Core/Src/display" -I../Core/Inc/sensing -I../Core/Src/sensing -I../Core/Inc/buzzer -I../Core/Src/buzzer -I../Core/Inc/processings -I../Core/Src/processings -I../Core/Inc/eeprom_at24c16 -I../Core/Src/eeprom_at24c16 -I../Core/Inc/bms_data -I../Core/Src/bms_data -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-eeprom_at24c16

clean-Core-2f-Src-2f-eeprom_at24c16:
	-$(RM) ./Core/Src/eeprom_at24c16/epprom_processings.cyclo ./Core/Src/eeprom_at24c16/epprom_processings.d ./Core/Src/eeprom_at24c16/epprom_processings.o ./Core/Src/eeprom_at24c16/epprom_processings.su

.PHONY: clean-Core-2f-Src-2f-eeprom_at24c16

