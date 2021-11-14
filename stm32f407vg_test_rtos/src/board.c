#include "board.h"
#include "rtos.h"

/********************************/
// LED
/********************************/
void led_init(void)
{
	(*REG_RCC_AHB1ENR)	|= RCC_AHB1ENR_GPIODEN;
	REG_GPIOD->MODER	|= ((GPIO_MODER_OUTPUT<<30) |
							(GPIO_MODER_OUTPUT<<28) |
							(GPIO_MODER_OUTPUT<<26) |
							(GPIO_MODER_OUTPUT<<24));
	REG_GPIOD->OSPEEDR	|= ((GPIO_OSPEEDR_HIGH<<30) |
							(GPIO_OSPEEDR_HIGH<<28) |
							(GPIO_OSPEEDR_HIGH<<26) |
							(GPIO_OSPEEDR_HIGH<<24));
}

void led_on(uint32_t mask)
{
	REG_GPIOD->ODR	|= (mask & 0xf) << 12;
}

void led_off(uint32_t mask)
{
	REG_GPIOD->ODR &= ~((mask & 0xf) << 12) ;
}

/********************************/
// Systick
/********************************/
#define LOAD_VALUE	(16000*TICK_MS) //Core_clk = 16MHz

__NAKED void systick_handler(void)
{
	_os_entint();
	if((REG_SYSTICK->CTRL & 0x00010000UL)!=0UL){
		isig_tim();
	}
	_os_retint();
}

void systick_init(void)
{
	REG_SYSTICK->CTRL	=	0x00000000UL;
	REG_SYSTICK->VAL	=	0UL;
	REG_SYSTICK->LOAD	=	LOAD_VALUE - 1UL;
	REG_SYSTICK->CTRL	=	0x00000007UL;
}
