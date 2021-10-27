#include "board.h"

void pwm_task(void)
{
	pwm_init();
	//for(;;);

	//should consider the speed of rotation of servo motor
	//SF3218MG from Sunfounder :0.18 sec/60° - 0.14 sec/60°
	while(1){
		for(int i=30; i<=150; i+=1){
			REG_TIM3->SR &= ~TIM_SR_UIE;
			REG_TIM3->CCR3 = i;
			while(!(REG_TIM3->SR & TIM_SR_UIE));
		}
		for(int i=150; i>=30; i-=1){
			REG_TIM3->SR &= ~TIM_SR_UIE;
			REG_TIM3->CCR3 = i;
			while(!(REG_TIM3->SR & TIM_SR_UIE));
		}
	}
}


void led_task(void)
{
	led_init();
	tim2_init();
	for(;;){
		delay_ms(1000);
		led_toggle();
	}
}

int main(void)
{
	pwm_task();
	//led_task();
	return 0;
}
