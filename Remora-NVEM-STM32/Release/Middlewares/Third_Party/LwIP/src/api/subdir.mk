################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/api/api_lib.c \
../Middlewares/Third_Party/LwIP/src/api/api_msg.c \
../Middlewares/Third_Party/LwIP/src/api/err.c \
../Middlewares/Third_Party/LwIP/src/api/netbuf.c \
../Middlewares/Third_Party/LwIP/src/api/netdb.c \
../Middlewares/Third_Party/LwIP/src/api/netifapi.c \
../Middlewares/Third_Party/LwIP/src/api/sockets.c \
../Middlewares/Third_Party/LwIP/src/api/tcpip.c 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/api/api_lib.d \
./Middlewares/Third_Party/LwIP/src/api/api_msg.d \
./Middlewares/Third_Party/LwIP/src/api/err.d \
./Middlewares/Third_Party/LwIP/src/api/netbuf.d \
./Middlewares/Third_Party/LwIP/src/api/netdb.d \
./Middlewares/Third_Party/LwIP/src/api/netifapi.d \
./Middlewares/Third_Party/LwIP/src/api/sockets.d \
./Middlewares/Third_Party/LwIP/src/api/tcpip.d 

OBJS += \
./Middlewares/Third_Party/LwIP/src/api/api_lib.o \
./Middlewares/Third_Party/LwIP/src/api/api_msg.o \
./Middlewares/Third_Party/LwIP/src/api/err.o \
./Middlewares/Third_Party/LwIP/src/api/netbuf.o \
./Middlewares/Third_Party/LwIP/src/api/netdb.o \
./Middlewares/Third_Party/LwIP/src/api/netifapi.o \
./Middlewares/Third_Party/LwIP/src/api/sockets.o \
./Middlewares/Third_Party/LwIP/src/api/tcpip.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/api/%.o Middlewares/Third_Party/LwIP/src/api/%.su: ../Middlewares/Third_Party/LwIP/src/api/%.c Middlewares/Third_Party/LwIP/src/api/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../LWIP/App -I../LWIP/Target -I../Core/Inc -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-api

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-api:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/api/api_lib.d ./Middlewares/Third_Party/LwIP/src/api/api_lib.o ./Middlewares/Third_Party/LwIP/src/api/api_lib.su ./Middlewares/Third_Party/LwIP/src/api/api_msg.d ./Middlewares/Third_Party/LwIP/src/api/api_msg.o ./Middlewares/Third_Party/LwIP/src/api/api_msg.su ./Middlewares/Third_Party/LwIP/src/api/err.d ./Middlewares/Third_Party/LwIP/src/api/err.o ./Middlewares/Third_Party/LwIP/src/api/err.su ./Middlewares/Third_Party/LwIP/src/api/netbuf.d ./Middlewares/Third_Party/LwIP/src/api/netbuf.o ./Middlewares/Third_Party/LwIP/src/api/netbuf.su ./Middlewares/Third_Party/LwIP/src/api/netdb.d ./Middlewares/Third_Party/LwIP/src/api/netdb.o ./Middlewares/Third_Party/LwIP/src/api/netdb.su ./Middlewares/Third_Party/LwIP/src/api/netifapi.d ./Middlewares/Third_Party/LwIP/src/api/netifapi.o ./Middlewares/Third_Party/LwIP/src/api/netifapi.su ./Middlewares/Third_Party/LwIP/src/api/sockets.d ./Middlewares/Third_Party/LwIP/src/api/sockets.o ./Middlewares/Third_Party/LwIP/src/api/sockets.su ./Middlewares/Third_Party/LwIP/src/api/tcpip.d ./Middlewares/Third_Party/LwIP/src/api/tcpip.o ./Middlewares/Third_Party/LwIP/src/api/tcpip.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-api

