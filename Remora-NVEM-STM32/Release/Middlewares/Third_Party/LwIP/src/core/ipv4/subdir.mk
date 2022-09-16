################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.c \
../Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.c 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.d \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.d 

OBJS += \
./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.o \
./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/core/ipv4/%.o Middlewares/Third_Party/LwIP/src/core/ipv4/%.su: ../Middlewares/Third_Party/LwIP/src/core/ipv4/%.c Middlewares/Third_Party/LwIP/src/core/ipv4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../LWIP/App -I../LWIP/Target -I../Core/Inc -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv4

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv4:
	-$(RM) ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.su ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.d ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.o ./Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-src-2f-core-2f-ipv4

