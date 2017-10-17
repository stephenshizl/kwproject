################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Sources/SDK__Kinetis/MKW41Z4/gcc/subdir.mk
-include Sources/SDK__Kinetis/MKW41Z4/subdir.mk
-include Sources/SDK__Kinetis/Drivers/subdir.mk
-include Sources/Middleware/Wireless/smac_3.3.2/source/subdir.mk
-include Sources/Middleware/Wireless/ieee_802_15_4_5.3.2/phy/source/MKW41Z/subdir.mk
-include Sources/Middleware/Wireless/ieee_802_15_4_5.3.2/mac/source/App/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/XCVR/MKW41Z4/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/TimersManager/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/Shell/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/SerialManager/Source/SPI_Adapter/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/SerialManager/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/SecLib/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/Reset/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/RNG/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/Panic/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/OSAbstraction/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/Messaging/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/MemManager/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/MWSCoexistence/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/Lists/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/LED/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/Keyboard/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/GPIO/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/FunctionLib/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/Flash/Internal/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/DCDC/Source/subdir.mk
-include Sources/Middleware/Wireless/framework_5.3.2/Common/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/wireless_uart/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/wireless_power_transfer/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/time/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/temperature/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/running_speed_cadence/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/pulse_oximeter/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/proximity/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/otap/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/ipsp/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/http_proxy/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/hid/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/heart_rate/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/health_thermometer/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/glucose/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/device_info/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/cycling_speed_cadence/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/cycling_power/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/blood_pressure/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/battery/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/profiles/alert_notification/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/host/config/subdir.mk
-include Sources/Middleware/Wireless/bluetooth_1.2.2/hci_transport/source/subdir.mk
-include Sources/Middleware/Segger/subdir.mk
-include Sources/Middleware/RTOS/FreeRTOS/Source/portable/gcc/ARM_CM0/subdir.mk
-include Sources/Middleware/RTOS/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Sources/Middleware/RTOS/FreeRTOS/Source/subdir.mk
-include Sources/Middleware/RTOS/subdir.mk
-include Sources/Middleware/MM100/subdir.mk
-include Sources/App/Common/gatt_db/subdir.mk
-include Sources/App/Common/subdir.mk
-include Sources/App/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
kwproject.siz \


# All Target
all: kwproject.elf secondary-outputs

# Tool invocations
kwproject.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -Wall  -g3 -T "C:\SourceControl\kwproject\gcc\MKW41Z512xxx4_connectivity.ld" -Xlinker --gc-sections -Wl,-Map,"output.map" --specs=nano.specs -Xlinker -z -Xlinker muldefs  -Xlinker -defsym -Xlinker __ram_vector_table__=1  -Wall -mapcs -Xlinker -static -o "kwproject.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

kwproject.siz: kwproject.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "kwproject.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_UPPER_DEPS)$(C_DEPS) kwproject.elf
	-@echo ' '

post-build:
	-arm-none-eabi-objcopy -O binary "kwproject.elf" "kwproject.bin"
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents post-build

-include ../makefile.targets
