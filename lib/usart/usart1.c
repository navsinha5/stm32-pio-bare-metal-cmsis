#include "usart1.h"
#include "led.h"
#include "stm32f103xb.h"


void initUsart(void){
    /**
     * enable alternate funtion
     * enable clock for USART1
     * enable clock for PORTA
     */
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /**
     * configure PORTA pins
     * PA9 (TX) -> AF output push-pull
     * PA10 (RX) -> input floating
     */
    GPIOA->CRH &= ~(GPIO_CRH_CNF9  | GPIO_CRH_MODE9);   // reset PA9
    GPIOA->CRH &= ~(GPIO_CRH_CNF10 | GPIO_CRH_MODE10);  // reset PA10
    GPIOA->CRH |= GPIO_CRH_MODE9_1;
    GPIOA->CRH |= GPIO_CRH_MODE9_0;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    /**
     * set boud rate to 9600
     * 8MHz/(16*9600) = 52.08
     * DIV_Fraction = 16*0.08 = 1.28 -> 1 = 0x1
     * DIC_Mantissa = mantissa(52.08) = 52 = 0x34
     * BRR = 0x341
     */
    USART1->BRR = 0x341;

    /**
     * enable USART
     * word length 8 bits
     * no parity
     * enable Tx and Rx
     * enable Rx interrupt
     * one stop bit
     */
    USART1->CR1 |= USART_CR1_UE;
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;
    USART1->CR1 |= USART_CR1_RXNEIE;

    /* enable USART1 global interrupt */
    __disable_irq();
    __NVIC_EnableIRQ(USART1_IRQn);
    __enable_irq();
}


/* transmit data */
void send(char data){
    /* wait till TDR gets empty */
    while(!(USART1->SR & USART_SR_TXE));

    /* wite data to data register */
    USART1->DR = (data & 0xFF);
}


/* receive data */
char read(void){
    /* wait till data is loaded into RDR */
    while(!(USART1->SR & USART_SR_RXNE));

    /* read data from data register */
    return (uint8_t) (USART1->DR & 0xFF);
}
