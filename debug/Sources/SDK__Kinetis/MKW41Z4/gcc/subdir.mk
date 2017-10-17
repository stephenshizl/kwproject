################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Sources/SDK__Kinetis/MKW41Z4/gcc/startup_MKW41Z4.S 

OBJS += \
./Sources/SDK__Kinetis/MKW41Z4/gcc/startup_MKW41Z4.o 

S_UPPER_DEPS += \
./Sources/SDK__Kinetis/MKW41Z4/gcc/startup_MKW41Z4.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/SDK__Kinetis/MKW41Z4/gcc/%.o: ../Sources/SDK__Kinetis/MKW41Z4/gcc/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -ffreestanding -fno-builtin -Wall  -g3 -imacros "C:/SourceControl/kwproject/Sources/App/app_preinclude.h" -x assembler-with-cpp -DDEBUG -I"C:\SourceControl\kwproject\Sources\Middleware\RTOS\FreeRTOS\Source" -DDEBUG  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


