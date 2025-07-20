################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/display/oled_display.c \
../Core/Src/display/ssd1306.c \
../Core/Src/display/ssd1306_fonts.c 

OBJS += \
./Core/Src/display/oled_display.o \
./Core/Src/display/ssd1306.o \
./Core/Src/display/ssd1306_fonts.o 

C_DEPS += \
./Core/Src/display/oled_display.d \
./Core/Src/display/ssd1306.d \
./Core/Src/display/ssd1306_fonts.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/display/oled_display.o: ../Core/Src/display/oled_display.c Core/Src/display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Core/Src/display" -I"../Core/Inc/display" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/display/%.o Core/Src/display/%.su Core/Src/display/%.cyclo: ../Core/Src/display/%.c Core/Src/display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../USB_HOST/App -I../USB_HOST/Target -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Core/Src/display" -I"../Core/Inc/display" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-display

clean-Core-2f-Src-2f-display:
	-$(RM) ./Core/Src/display/oled_display.cyclo ./Core/Src/display/oled_display.d ./Core/Src/display/oled_display.o ./Core/Src/display/oled_display.su ./Core/Src/display/ssd1306.cyclo ./Core/Src/display/ssd1306.d ./Core/Src/display/ssd1306.o ./Core/Src/display/ssd1306.su ./Core/Src/display/ssd1306_fonts.cyclo ./Core/Src/display/ssd1306_fonts.d ./Core/Src/display/ssd1306_fonts.o ./Core/Src/display/ssd1306_fonts.su

.PHONY: clean-Core-2f-Src-2f-display

