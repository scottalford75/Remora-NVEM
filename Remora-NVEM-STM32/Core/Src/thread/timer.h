#ifndef TIMER_H
#define TIMER_H

#include "stm32f2xx_hal.h"
#include <stdint.h>

#define TIM_PSC 1
#define APB1CLK SystemCoreClock/2
#define APB2CLK SystemCoreClock

class TimerInterrupt; // forward declaration
class pruThread; // forward declaration

class pruTimer
{
	friend class TimerInterrupt;

	private:

		TimerInterrupt* 	interruptPtr;
		TIM_TypeDef* 	    timer;
		IRQn_Type 			irq;
		uint32_t 			frequency;
		pruThread* 			timerOwnerPtr;

		void startTimer(void);
		void timerTick();			// Private timer tiggered method

	public:

		pruTimer(TIM_TypeDef* timer, IRQn_Type irq, uint32_t frequency, pruThread* ownerPtr);
        void stopTimer(void);

};

#endif
