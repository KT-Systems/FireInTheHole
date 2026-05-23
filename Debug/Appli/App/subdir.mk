################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Appli/App/httpserver.c \
../Appli/App/main_app.c 

OBJS += \
./Appli/App/httpserver.o \
./Appli/App/main_app.o 

C_DEPS += \
./Appli/App/httpserver.d \
./Appli/App/main_app.d 


# Each subdirectory must supply rules for building sources it contributes
Appli/App/%.o Appli/App/%.su Appli/App/%.cyclo: ../Appli/App/%.c Appli/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DconfigTASK_NOTIFICATION_ARRAY_ENTRIES=8 -DST67_ARCH=W6X_ARCH_T01 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../ST67W6X/App -I../Appli/App -I../Appli/Target -I../ST67W6X/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/NoVendor_DataOoExchange_cJSON/cJSON -I../Utilities/lpm/tiny_lpm -I../Middlewares/ST/ST67W6X_Network_Driver/Api -I../Middlewares/ST/ST67W6X_Network_Driver/Core -I../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at -I../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_bus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Appli-2f-App

clean-Appli-2f-App:
	-$(RM) ./Appli/App/httpserver.cyclo ./Appli/App/httpserver.d ./Appli/App/httpserver.o ./Appli/App/httpserver.su ./Appli/App/main_app.cyclo ./Appli/App/main_app.d ./Appli/App/main_app.o ./Appli/App/main_app.su

.PHONY: clean-Appli-2f-App

