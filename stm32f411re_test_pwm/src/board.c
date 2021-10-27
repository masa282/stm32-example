#include "board.h"

void tim2_init(void)
{
	REG_RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	REG_TIM2->PSC = 16-1;
	REG_TIM2->ARR = 0xffff;
	REG_TIM2->EGR |= TIM_EGR_UG;
	while(!(REG_TIM2->SR & TIM_SR_UIE));
	REG_TIM2->CR1|= TIM_CR1_CEN;
}

void led_init(void)
{
	REG_RCC->AHB1ENR	|= RCC_AHB1ENR_GPIOCEN;
	REG_GPIOC->MODER 	|= GPIO_MODER_OUTPUT << (LED_PIN*2);
	REG_GPIOC->OSPEEDR 	|= GPIO_OSPEEDR_HIGH << (LED_PIN*2);
	//REG_GPIOC->ODR 		= (0x1 << LED_PIN);
}

void led_toggle(void)
{
	REG_GPIOC->ODR ^= (0x1 << LED_PIN);
}

void delay_ms(uint16_t ms)
{
	for (uint16_t i=0; i<ms; i++){
		delay_us(1000);
	}
}

void delay_us(uint16_t us)
{
	REG_TIM2->CNT = 0;
	while(REG_TIM2->CNT < us);
}


void pwm_init(void)
{
	REG_RCC->AHB1ENR 	|= RCC_AHB1ENR_GPIOCEN;
	REG_GPIOC->MODER	|= GPIO_MODER_AF << (PWM_PIN*2);
	REG_GPIOC->OSPEEDR	|= GPIO_OSPEEDR_HIGH <<(PWM_PIN*2);
	REG_GPIOC->AFRH		|= GPIO_AF_TIM3_CH3 << (4*(PWM_PIN-8));

	REG_RCC->APB1ENR 	|= RCC_APB1ENR_TIM3EN;
	REG_TIM3->PSC = 267-1;	//PCLK1=16MHz, frequency of TIMER is approx. 60KHz
	REG_TIM3->ARR = 1000;	//Then, period became 16.666ms (=60Hz)

	/*********************************************/
	// In case of SF3218MG,
	// The control frequency is 60Hz
	// Pulse Width Range: 500 ~ 2500 usec
	// Neutral Position: 1500 usec
	// 0.5ms / 16.666ms * 100 = 3%
	// 1.5ms / 16.666ms * 100 = 9%
	// 2.5ms / 16.666ms * 100 = 15%
	// So CCRx value should be between 30 and 150
	/**********************************************/

	REG_TIM3->CCR3 	 = 30;
	REG_TIM3->CCMR2 |= TIM_CCMR2_CC3S_OC;	//CH3 is configured as output
	REG_TIM3->CCMR2 |= TIM_CCMR2_OC3M_PWM1; //PWM Mode 1(up-count)
	REG_TIM3->CCMR2 |= TIM_CCMR2_OC3PE;		//Enable CCR3
	REG_TIM3->CCER	&= ~TIM_CCER_CC3P;		//Active High
	REG_TIM3->CCER 	|= TIM_CCER_CC3E;		//output from PWM_PIN is enable
	REG_TIM3->CR1	|= TIM_CR1_APRE;

	REG_TIM3->EGR |= TIM_EGR_UG;			//Re-initialize the counter and generates an update of the registers
	while(!(REG_TIM3->SR & TIM_SR_UIE));	//Update interrupt flag
	REG_TIM3->CR1|= TIM_CR1_CEN;			//count starts
}
