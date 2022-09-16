#ifndef NVMPG_H
#define NVMPG_H

#include "stm32f2xx_hal.h"

#include <cstdint>
#include <sys/errno.h>

#include "configuration.h"
#include "remora.h"
#include "../module.h"
#include "../moduleinterrupt.h"

#include "extern.h"

void createNVMPG(void);

class NVMPG : public Module
{
	friend class ModuleInterrupt;

	private:

		ModuleInterrupt*	interruptPtr;
		IRQn_Type			irq;

		volatile mpgData_t	*ptrMpgData;
		volatile uint16_t 	*ptrData;

		uint8_t txData[53] = {'\0'};
		uint8_t rxData;
		uint8_t i = 0;

		uint16_t mask;
		bool buttonState;

		bool serialReceived = false;
		bool payloadReceived = false;

		UART_HandleTypeDef uartHandle;
		DMA_HandleTypeDef hdma_usart1_rx;
		DMA_HandleTypeDef hdma_usart1_tx;

	public:

		NVMPG(volatile mpgData_t&, volatile uint16_t&);
		virtual void update(void);
		virtual void slowUpdate(void);
		virtual void configure(void);

		void handleInterrupt(void);
};

#endif
