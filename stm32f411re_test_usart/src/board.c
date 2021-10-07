#include "board.h"
#include <math.h>

void led_init(void)
{
	(*REG_RCC_AHB1ENR)	|= RCC_AHB1ENR_GPIOAEN;
	REG_GPIOA->MODER 	|= GPIO_MODER_OUTPUT << (LED_PIN*2);
	REG_GPIOA->OSPEEDR 	|= GPIO_OSPEEDR_HIGH << (LED_PIN*2);
}

void led_toggle(void)
{
	REG_GPIOA->ODR ^= (0x1 << LED_PIN);
}

void usart1_init(void){
	//GPIO register
	(*REG_RCC_AHB1ENR)	|= RCC_AHB1ENR_GPIOAEN;
	REG_GPIOA->MODER 	|= (GPIO_MODER_AF << (UART_TX_PIN*2)) | (GPIO_MODER_AF << (UART_RX_PIN*2));
	REG_GPIOA->OSPEEDR 	|= (GPIO_OSPEEDR_HIGH << (UART_TX_PIN*2)) | (GPIO_OSPEEDR_HIGH << (UART_RX_PIN*2));
	REG_GPIOA->AFRH 	|= (GPIO_AF_USART1_TX << (4*(UART_TX_PIN-8))) | (GPIO_AF_USART1_RX << (4*(UART_RX_PIN-8)));

	//USART register
	(*REG_RCC_APB2ENR) |= RCC_APB2ENR_USART1EN;
	REG_USART1->CR1 = 	0x0UL; 				//clear all
	REG_USART1->CR1 |= 	USART_CR1_UE; 		//enable the USART
	REG_USART1->CR1 &= 	~USART_CR1_M; 		//1 start_bit, 8 data_bit, n stop_bit
	REG_USART1->CR2 |= 	USART_CR2_STOP_1; 	//n = 1
	REG_USART1->CR3 &= ~USART_CR3_DMAT;		//DMA for transmission is disabled
	REG_USART1->CR3 &= ~USART_CR3_DMAR;		//DMA for reception is disabled
	REG_USART1->BRR |=	(11<<0)|(8<<4);		//_baud_rate(115200);	//baud rate
	REG_USART1->CR1 |= 	USART_CR1_TE; 		//Transmitter is enable
	REG_USART1->CR1 |= 	USART_CR1_RE;		//Receiver is enable
}

unsigned long _baud_rate(uint32_t b)
{
	uint32_t pclk2 = 16000000; //APB1 clock: 16MHz
	float usartdiv = pclk2 / (8*2*b); //8.6805
	float div_fraction = roundf(16 * 0.6805);//11
	float div_mantissa = roundf(8);
	return ((11<<0)|(8<<4));
}

void usart1_send(uint8_t *str)
{
	while(*str) _usart1_send_char(*str++);
}

void _usart1_send_char(uint8_t c)
{
	REG_USART1->DR = c;
	while(!(REG_USART1->SR & USRAT_SR_TC));
}

uint8_t usart1_recv(void)
{
	while(!(REG_USART1->SR & USART_SR_RXNE));
	return REG_USART1->DR;
}

void systick_init(void)
{
	REG_SYSTICK->CSR 	= 0x0UL;
	REG_SYSTICK->VAL 	= 0x0UL;
	REG_SYSTICK->LOAD 	= LOAD_VAL - 1U;
	REG_SYSTICK->CSR 	= 0x7UL;
}

void systick_handler(void)
{
	led_toggle();
	usart1_send("Send Data\n");
}
