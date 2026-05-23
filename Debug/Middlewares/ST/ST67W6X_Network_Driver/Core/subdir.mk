################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ble.c \
../Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_http.c \
../Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_mqtt.c \
../Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_net.c \
../Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_netif.c \
../Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ota.c \
../Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_sys.c \
../Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_wifi.c 

OBJS += \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ble.o \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_http.o \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_mqtt.o \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_net.o \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_netif.o \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ota.o \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_sys.o \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_wifi.o 

C_DEPS += \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ble.d \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_http.d \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_mqtt.d \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_net.d \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_netif.d \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ota.d \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_sys.d \
./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_wifi.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/ST67W6X_Network_Driver/Core/%.o Middlewares/ST/ST67W6X_Network_Driver/Core/%.su Middlewares/ST/ST67W6X_Network_Driver/Core/%.cyclo: ../Middlewares/ST/ST67W6X_Network_Driver/Core/%.c Middlewares/ST/ST67W6X_Network_Driver/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DconfigTASK_NOTIFICATION_ARRAY_ENTRIES=8 -DST67_ARCH=W6X_ARCH_T01 -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../ST67W6X/App -I../Appli/App -I../Appli/Target -I../ST67W6X/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/NoVendor_DataOoExchange_cJSON/cJSON -I../Utilities/lpm/tiny_lpm -I../Middlewares/ST/ST67W6X_Network_Driver/Api -I../Middlewares/ST/ST67W6X_Network_Driver/Core -I../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_at -I../Middlewares/ST/ST67W6X_Network_Driver/Driver/W61_bus -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-ST67W6X_Network_Driver-2f-Core

clean-Middlewares-2f-ST-2f-ST67W6X_Network_Driver-2f-Core:
	-$(RM) ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ble.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ble.d ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ble.o ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ble.su ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_http.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_http.d ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_http.o ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_http.su ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_mqtt.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_mqtt.d ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_mqtt.o ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_mqtt.su ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_net.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_net.d ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_net.o ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_net.su ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_netif.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_netif.d ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_netif.o ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_netif.su ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ota.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ota.d ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ota.o ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_ota.su ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_sys.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_sys.d ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_sys.o ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_sys.su ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_wifi.cyclo ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_wifi.d ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_wifi.o ./Middlewares/ST/ST67W6X_Network_Driver/Core/w6x_wifi.su

.PHONY: clean-Middlewares-2f-ST-2f-ST67W6X_Network_Driver-2f-Core

