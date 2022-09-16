#include "extern.h"


void createThreads(void)
{
    baseThread = new pruThread(TIM1, TIM1_UP_TIM10_IRQn, base_freq);
    NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2);

    servoThread = new pruThread(TIM2, TIM2_IRQn , servo_freq);
    NVIC_SetPriority(TIM2_IRQn , 3);
}
