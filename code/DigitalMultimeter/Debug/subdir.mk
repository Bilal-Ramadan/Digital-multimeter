################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../adc_Cfg.c \
../app.c \
../gpio.c \
../keypad.c \
../lcd.c \
../main.c 

OBJS += \
./adc.o \
./adc_Cfg.o \
./app.o \
./gpio.o \
./keypad.o \
./lcd.o \
./main.o 

C_DEPS += \
./adc.d \
./adc_Cfg.d \
./app.d \
./gpio.d \
./keypad.d \
./lcd.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


