#include "nvmpg.h"

#include <stdio.h>

/***********************************************************************
                MODULE CONFIGURATION AND CREATION FROM JSON
************************************************************************/

void createNVMPG()
{
    const char* comment = module["Comment"];
    printf("\n%s\n",comment);

    ptrNVMPGInputs = &txData.NVMPGinputs;
    MPG = new NVMPG(*ptrMpgData, *ptrNVMPGInputs);
    servoThread->registerModule(MPG);
}

/***********************************************************************
                METHOD DEFINITIONS
************************************************************************/

NVMPG::NVMPG(volatile mpgData_t &ptrMpgData, volatile uint16_t &ptrData) :
	ptrMpgData(&ptrMpgData),
	ptrData(&ptrData)
{

	this->irq = DMA2_Stream2_IRQn;
	interruptPtr = new ModuleInterrupt(this->irq, this);	// Instantiate a new Module Interrupt object and pass "this" pointer


	GPIO_InitTypeDef GPIO_InitStruct = {0};

	printf("Creating NVMPG module\n");

	this->uartHandle.Instance = USART1;

	if(this->uartHandle.Instance==USART1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();

		/**USART1 GPIO Configuration
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		__HAL_RCC_USART1_CLK_ENABLE();

		this->uartHandle.Init.BaudRate = 115200;
		this->uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
		this->uartHandle.Init.StopBits = UART_STOPBITS_1;
		this->uartHandle.Init.Parity = UART_PARITY_NONE;
		this->uartHandle.Init.Mode = UART_MODE_TX_RX;
		this->uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
		this->uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

		HAL_UART_Init(&this->uartHandle);

		__HAL_RCC_DMA2_CLK_ENABLE();

		this->hdma_usart1_rx.Instance = DMA2_Stream2;
		this->hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
		this->hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		this->hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		this->hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
		this->hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		this->hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		this->hdma_usart1_rx.Init.Mode = DMA_NORMAL;
		this->hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
		this->hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

		HAL_DMA_Init(&this->hdma_usart1_rx);

	    __HAL_LINKDMA(&this->uartHandle,hdmarx,this->hdma_usart1_rx);

	    HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

	    this->hdma_usart1_tx.Instance = DMA2_Stream7;
	    this->hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
	    this->hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	    this->hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	    this->hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
	    this->hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	    this->hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	    //this->hdma_usart1_tx.Init.Mode = DMA_NORMAL;
	    this->hdma_usart1_tx.Init.Mode = DMA_CIRCULAR;
	    this->hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
	    this->hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	    HAL_DMA_Init(&this->hdma_usart1_tx);

	    __HAL_LINKDMA(&this->uartHandle,hdmatx,this->hdma_usart1_tx);

		printf("UART1 DMA configured\n");
	}

	sprintf((char*)this->txData, "ZZ");
	HAL_UART_Transmit(&this->uartHandle, (uint8_t*)&this->txData, 53, 100);

	HAL_UART_Receive_DMA(&this->uartHandle, (uint8_t*)&this->rxData, 1);
}


void NVMPG::update()
{
	if (this->serialReceived)
	{
		// get the button number from the low nibble, subtract 2 (buttons start from #2), NVMPG start at bit 26 in the uint64_t output structure
		mask = 1 << ((rxData & 0x0f) - 2);

		// button state is from the high nibble, x0_ is button down (logical 1), x8_ is button up (logical 0)
		buttonState = (rxData & 0x80);

		if (buttonState)
		{
			*(this->ptrData) &= ~this->mask;
		}
		else
		{
			*(this->ptrData) |= this->mask;
		}

		rxData = 0;
		this->serialReceived = false;
	}

	if (this->payloadReceived)
	{
		// copy the data to txData buffer
		for (int i = 1; i < 53; i++)
		{
			this->txData[i] =  this->ptrMpgData->payload[i+4];
		}
		HAL_UART_Transmit_DMA(&this->uartHandle, (uint8_t*)&this->txData, 53);
		this->payloadReceived = false;
	}
}


void NVMPG::slowUpdate()
{
	return;
}

void NVMPG::configure()
{
	// use standard module configure method to set payload flag
	this->payloadReceived = true;
}

void NVMPG::handleInterrupt()
{
	this->serialReceived = true;
	HAL_DMA_IRQHandler(&this->hdma_usart1_rx);
	HAL_UART_Receive_DMA(&this->uartHandle, (uint8_t*)&this->rxData, 1);
}



