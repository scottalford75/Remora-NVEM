################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/modules/nvmpg/nvmpg.cpp 

OBJS += \
./Core/Src/modules/nvmpg/nvmpg.o 

CPP_DEPS += \
./Core/Src/modules/nvmpg/nvmpg.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/modules/nvmpg/%.o Core/Src/modules/nvmpg/%.su: ../Core/Src/modules/nvmpg/%.cpp Core/Src/modules/nvmpg/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -DUSE_HAL_DRIVER -DSTM32F207xx -c -I../LWIP/App -I../LWIP/Target -I../Core/Inc -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/STM32F2xx_HAL_Driver/Inc -I../Drivers/STM32F2xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Drivers/CMSIS/Device/ST/STM32F2xx/Include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/posix -I../Middlewares/Third_Party/LwIP/src/include/posix/sys -I../Middlewares/Third_Party/LwIP/system/arch -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-modules-2f-nvmpg

clean-Core-2f-Src-2f-modules-2f-nvmpg:
	-$(RM) ./Core/Src/modules/nvmpg/nvmpg.d ./Core/Src/modules/nvmpg/nvmpg.o ./Core/Src/modules/nvmpg/nvmpg.su

.PHONY: clean-Core-2f-Src-2f-modules-2f-nvmpg

