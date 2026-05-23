################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/modem_cmd_handler.c \
../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_ble.c \
../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_common.c \
../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_mqtt.c \
../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_net.c \
../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_sys.c \
../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_wifi.c 

OBJS += \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/modem_cmd_handler.o \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_ble.o \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_common.o \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_mqtt.o \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_net.o \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_sys.o \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_wifi.o 

C_DEPS += \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/modem_cmd_handler.d \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_ble.d \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_common.d \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_mqtt.d \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_net.d \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_sys.d \
./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_wifi.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/%.o Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/%.su Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/%.cyclo: ../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/%.c Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DconfigTASK_NOTIFICATION_ARRAY_ENTRIES=8 -DST67_ARCH=W6X_ARCH_T01 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../ST67W6X/App -I../Appli/App -I../Appli/Target -I../ST67W6X/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/NoVendor_DataOoExchange_cJSON/cJSON -I../Utilities/lpm/tiny_lpm -I../Middlewares/ST/ST67W6X_Network_Driver/Api -I../Middlewares/ST/ST67W6X_Network_Driver/Core -I../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at -I../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_bus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-ST67W6X_Network_Driver-2f-Driver-2f-W61_at

clean-Middlewares-2f-ST-2f-ST67W6X_Network_Driver-2f-Driver-2f-W61_at:
	-$(RM) ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/modem_cmd_handler.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/modem_cmd_handler.d ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/modem_cmd_handler.o ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/modem_cmd_handler.su ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_ble.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_ble.d ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_ble.o ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_ble.su ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_common.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_common.d ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_common.o ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_common.su ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_mqtt.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_mqtt.d ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_mqtt.o ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_mqtt.su ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_net.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_net.d ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_net.o ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_net.su ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_sys.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_sys.d ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_sys.o ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_sys.su ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_wifi.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_wifi.d ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_wifi.o ./Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at/w61_at_wifi.su

.PHONY: clean-Middlewares-2f-ST-2f-ST67W6X_Network_Driver-2f-Driver-2f-W61_at

