#include "led.h"
#include "stm32f103xb.h"


void ledInit(void){
    /** 
    * Enable clock for GPIOC
    **/
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    /**
     * Set GPIOC PIN 13 OUTPUT
     * GPIOC_CRH --> BIT(23,22,21,20) = (0,0,0,1)
     * MODE13[1:0] = 0 1
     * CNF13[1:0] = 0 0
     */
    GPIOC->CRH |= GPIO_CRH_MODE13_0;
    GPIOC->CRH &= ~ GPIO_CRH_CNF13;
}


void toggle(void){
    /* toggle the led */
    GPIOC->ODR ^= GPIO_ODR_ODR13;
}