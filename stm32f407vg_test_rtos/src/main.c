#include "board.h"
#include "rtos.h"

void busy_wait(int32_t ms)
{
	int32_t	cnt = ms/10;
	volatile int32_t i = 0;
	while(cnt-- > 0){
		for(i=0; i<15000; i++);
	}
}


//TASK_ID: 0
void led_green_task(void)
{
	static int32_t count;
	count = 20;
	while(count--){
		led_on(LED_GREEN);
		dly_tsk(100);
		led_off(LED_GREEN);
		dly_tsk(100);
	}
	ext_tsk();
}


//TASK_ID: 1
void led_red_task(void)
{
	static int32_t count;
	for(;;){
		count = 20;
		while(count--){
			led_on(LED_RED);
			dly_tsk(200);
			led_off(LED_RED);
			dly_tsk(200);
		}
		act_tsk(0);
	}
}


//TASK_ID: 2
void calc_task(void)
{
	for (;;) {
		led_on(LED_ORANGE);
	    busy_wait(30);
	    led_off(LED_ORANGE);
	    busy_wait(30);
	};
}


//TASK_ID: 3
void idle_task(void)
{
	for(;;);
}

int main(void)
{
	led_init();
	systick_init();
	_os_start(); //never return
	return 0;
}
