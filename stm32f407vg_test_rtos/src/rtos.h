#include "defines.h"

#define TICK_MS	(10) //msec

extern void _os_start(void);
void _os_entint(void);
void _os_retint(void);

extern ER act_tsk(int32_t tskid);
extern void ext_tsk(void);
extern ER dly_tsk(int32_t dlytim);
extern ER isig_tim(void);

extern void led_green_task(void);
extern void led_red_task(void);
extern void calc_task(void);
extern void idle_task(void);
