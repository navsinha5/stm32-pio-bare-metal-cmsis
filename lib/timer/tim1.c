#include "tim1.h"
#include "stm32f103xb.h"


void tim1Init(void){
    /**
     * disable the counter, stop counting
     */
    TIM1->CR1 &= ~ TIM_CR1_CEN;

    /**
     * enable clock for TIM1
     * APB2ENR[11] = 1
     * enable auto-reload preload
     * enable update interrupt
     */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->CR1    |= TIM_CR1_ARPE;
    TIM1->DIER   |= TIM_DIER_UIE;

    /**
     * load prescaler with 8000 for 1ms (8MHz)
     * TIM1->CR1[4] = 0, upcounter
     * clear the counter current value
     */
    TIM1->PSC = 8000U - 1U;
    TIM1->CNT = 0U;

    /* configure Update Interrupt */
    __disable_irq();
    __NVIC_EnableIRQ(TIM1_UP_IRQn);
    __enable_irq();
}


void counterInit(unsigned int ms){
    /**
     * disable the counter, stop counting
     */
    TIM1->CR1 &= ~ TIM_CR1_CEN;

    /* load auto-reload for desired delay (ms) */
    TIM1->ARR = ms - 1U;
    
    /**
     * generate update event
     * enable the counter, start counting 
     */
    TIM1->EGR |= TIM_EGR_UG;
    TIM1->CR1 |= TIM_CR1_CEN;
}


// void delayMs(unsigned int ms){
//     /**
//      * enable clock for TIM1
//      * APB2ENR[11] = 1
//      */
//     RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

//     /**
//      * load prescaler with 8000 for 1ms (8MHz)
//      * load auto-reload for desired delay (ms)
//      * TIM1->CR1[4] = 0, upcounter
//      * clear the counter current value
//      */
//     TIM1->PSC = 8000U - 1U; 
//     TIM1->ARR = ms - 1U;
//     TIM1->CNT = 0U;

//     /* enable the counter, start counting */
//     TIM1->CR1 |= TIM_CR1_CEN;

//     /* hang while counting */
//     while(!(TIM1->SR & TIM_SR_UIF));

//     /**
//      * disable the counter, stop counting
//      * clear the update flag
//      */
//     TIM1->SR  &= ~ TIM_SR_UIF;
//     TIM1->CR1 &= ~ TIM_CR1_CEN;
// }