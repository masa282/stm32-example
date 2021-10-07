#include "board.h"

void task(void){
	uint8_t data;
	usart1_send("Hello World!\n");
	for(;;)
		data = usart1_recv();
}

int main(void)
{
	led_init();
	usart1_init();
	systick_init();

	task();
	return 0;
}
