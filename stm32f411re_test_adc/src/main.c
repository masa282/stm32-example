#include "board.h"

void task(void)
{
	for(;;)
		;
}

int main(void)
{
	adc1_init();
	adc1_start();
	usart1_init();
	systick_init();
	task();
	adc1_stop();
	return 0;
}
