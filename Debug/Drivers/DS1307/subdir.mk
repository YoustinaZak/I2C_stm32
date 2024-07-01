################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DS1307/ds1307.c 

OBJS += \
./Drivers/DS1307/ds1307.o 

C_DEPS += \
./Drivers/DS1307/ds1307.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DS1307/%.o Drivers/DS1307/%.su Drivers/DS1307/%.cyclo: ../Drivers/DS1307/%.c Drivers/DS1307/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-DS1307

clean-Drivers-2f-DS1307:
	-$(RM) ./Drivers/DS1307/ds1307.cyclo ./Drivers/DS1307/ds1307.d ./Drivers/DS1307/ds1307.o ./Drivers/DS1307/ds1307.su

.PHONY: clean-Drivers-2f-DS1307

