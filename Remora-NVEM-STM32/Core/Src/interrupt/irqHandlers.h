#include "interrupt.h"

extern "C" {

	void TIM1_UP_TIM10_IRQHandler()
	{
	  if(TIM1->SR & TIM_SR_UIF) // if UIF flag is set
	  {
		TIM1->SR &= ~TIM_SR_UIF; // clear UIF flag

		Interrupt::TIM1_Wrapper();
	  }
	}

	void TIM2_IRQHandler()
	{
	  if(TIM2->SR & TIM_SR_UIF) // if UIF flag is set
	  {
		TIM2->SR &= ~TIM_SR_UIF; // clear UIF flag

		Interrupt::TIM2_Wrapper();
	  }
	}


	void DMA2_Stream2_IRQHandler(void)
	{
		Interrupt::DMA2_Stream2_Wrapper();
	}
}
