################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate/heart_rate_client.c \
../Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate/heart_rate_service.c 

OBJS += \
./Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate/heart_rate_client.o \
./Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate/heart_rate_service.o 

C_DEPS += \
./Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate/heart_rate_client.d \
./Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate/heart_rate_service.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate/%.o: ../Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -Wall  -g3 -imacros "C:/SourceControl/kwproject/Sources/App/app_preinclude.h" -DDEBUG -DCPU_MKW41Z512VHT4 -I"C:/SourceControl/kwproject/Sources" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/controller/interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/hci_transport/interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/hci_transport/source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/host/config" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/host/interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/mesh/interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/alert_notification" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/battery" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/blood_pressure" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/cycling_power" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/cycling_speed_cadence" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/device_info" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/glucose" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/health_thermometer" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/hid" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/http_proxy" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/ipsp" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/otap" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/proximity" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/pulse_oximeter" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/running_speed_cadence" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/temperature" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/time" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/wireless_power_transfer" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/wireless_uart" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/smac_3.3.2/source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/smac_3.3.2/interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/smac_3.3.2/common" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/ieee_802_15_4_5.3.2/phy/interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/ieee_802_15_4_5.3.2/mac/interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/ieee_802_15_4_5.3.2/mac/source/App" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/ieee_802_15_4_5.3.2/phy/source/MKW41Z" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/XCVR/MKW41Z4" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/TimersManager/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/TimersManager/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Shell/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Shell/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/SerialManager/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/SerialManager/Source/SPI_Adapter" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/SerialManager/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/SecLib" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/RNG/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/RNG/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Panic/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Panic/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/OSAbstraction/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/OSAbstraction/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/MWSCoexistence/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/MWSCoexistence/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/ModuleInfo" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Messaging/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Messaging/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/MemManager/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/MemManager/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Lists" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/LED/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/LED/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Keyboard/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Keyboard/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/GPIO" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/FunctionLib" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Flash/Internal" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/DCDC/Interface" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/DCDC/Source" -I"C:/SourceControl/kwproject/Sources/Middleware/Wireless/framework_5.3.2/Common" -I"C:/SourceControl/kwproject/Sources/App" -I"C:/SourceControl/kwproject/Sources/App/Common" -I"C:/SourceControl/kwproject/Sources/App/Common/gatt_db" -I"C:/SourceControl/kwproject/Sources/App/Common/gatt_db/macros" -I"C:/SourceControl/kwproject/Sources/Middleware/RTOS/FreeRTOS/Source/portable/gcc/ARM_CM0" -I"C:/SourceControl/kwproject/Sources/Middleware/RTOS/FreeRTOS/Source/include" -I"C:/SourceControl/kwproject/Sources/Middleware/RTOS/FreeRTOS/Source" -I"C:/SourceControl/kwproject/Sources/SDK__Kinetis/Drivers" -I"C:/SourceControl/kwproject/Sources/SDK__Kinetis/MKW41Z4" -I"C:/SourceControl/kwproject/Sources/SDK__Kinetis/MKW41Z4/gcc" -I"C:/SourceControl/kwproject/Sources/SDK__Kinetis/CMSIS/Include" -std=c99 -DDEBUG  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


