#include "board.h"

void adc1_init(void)
{
	//GPIO register
	REG_RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	REG_GPIOC->MODER |= GPIO_MODER_ANALOG << (ADC_PIN*2);

	//ADC1 register
	REG_RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	REG_ADC->CCR |= ADC_CCR_ADCPRE0; 		//pre-scalar: divided by 2
	REG_ADC1->CR1 |= ADC_CR1_RES12;			//resolution: 12 bit
	REG_ADC1->CR2 |= ADC_CR2_CONT;			//Continuous mode
	REG_ADC1->SQR3 = 0; 					//clear all
	REG_ADC1->SQR3 |= 15;					//PC5 is channel 15
}

uint16_t adc1_getval(void)
{
	while(!(REG_ADC1->SR & ADC_SR_EOC));
	return REG_ADC1->DR;
}

void adc1_start(void)
{
	REG_ADC1->CR2 |= ADC_CR2_ADON;		//ADC is enable
	REG_ADC1->CR2 |= ADC_CR2_SWSTART;	//AD conversion starts
}

void adc1_stop(void)
{
	REG_ADC1->CR2 &= ~ADC_CR2_SWSTART;	//ADC is disabled
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
	uint16_t tmp = adc1_getval();
	usart1_send_val(tmp & 0xff);
	usart1_send_val((tmp>>8) & 0xff);
}

void usart1_init(void)
{
	//GPIO register
	REG_RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	REG_GPIOA->MODER 	|= (GPIO_MODER_AF << (UART_TX_PIN*2)) | (GPIO_MODER_AF << (UART_RX_PIN*2));
	REG_GPIOA->OSPEEDR 	|= (GPIO_OSPEEDR_HIGH << (UART_TX_PIN*2)) | (GPIO_OSPEEDR_HIGH << (UART_RX_PIN*2));
	REG_GPIOA->AFRH 	|= (GPIO_AF_USART1_TX << (4*(UART_TX_PIN-8))) | (GPIO_AF_USART1_RX << (4*(UART_RX_PIN-8)));

	//USART register
	REG_RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
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

void usart1_send(uint8_t *data)
{
	while(*data) _usart1_send_char(*data++);
}

void usart1_send_val(uint8_t c)
{
	REG_USART1->DR = c;
	while(!(REG_USART1->SR & USRAT_SR_TC));
}
