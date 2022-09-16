################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_crc.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_eth.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_exti.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_iwdg.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.c \
../Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.c 

C_DEPS += \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_crc.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_eth.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_exti.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_iwdg.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.d \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.d 

OBJS += \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_crc.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_eth.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_exti.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_iwdg.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.o \
./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F2xx_HAL_Driver/Src/%.o: ../Drivers/STM32F2xx_HAL_Driver/Src/%.c Drivers/STM32F2xx_HAL_Driver/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../Core/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-STM32F2xx_HAL_Driver-2f-Src

clean-Drivers-2f-STM32F2xx_HAL_Driver-2f-Src:
	-$(RM) ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_cortex.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_crc.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_crc.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_dma_ex.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_eth.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_eth.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_exti.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_exti.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_flash_ex.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_gpio.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_iwdg.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_iwdg.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_pwr_ex.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_rcc_ex.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_tim_ex.o ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.d ./Drivers/STM32F2xx_HAL_Driver/Src/stm32f2xx_hal_uart.o

.PHONY: clean-Drivers-2f-STM32F2xx_HAL_Driver-2f-Src

