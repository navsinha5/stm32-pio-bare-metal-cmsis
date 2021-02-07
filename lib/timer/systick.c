#include "systick.h"
#include "stm32f103xb.h"


void delayMs(int ms){
    /**
     * Confiure SysTick timer 8MHz
     * Set reload value to (ms * 8000)
     * Set clock source to internal
     * Enable Timer to start counting
     */
    SysTick->LOAD = (unsigned long) ms * 8000UL - 1UL;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    /* hang while counting */
    while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));

    /**
     * stop counter
     * clear counter flag
     */
    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
    SysTick->CTRL &= ~ SysTick_CTRL_COUNTFLAG_Msk;
}