#include "rtos.h"


/********************************/
// 課題
/********************************/
//xPSRレジスタを個々のタスク毎にtask_stkつまりbss領域に入れているが、必要なのか？→xPSRも自動退避されるがなぜ？タスク毎に何か個別の情報があるのか？
//ASMで＋４とか適当にしてみて、期待通りに動作しｊないことを確認せよ




/********************************/
// OS configuration
/********************************/
#define TASK_NUM		(4)
#define TASK_PRI_NUM	(4)
#define TASK_STACK_SIZE (128)

#define STATE_DORMANT	(0)
#define STATE_WAITING	(1)
#define STATE_READY		(2)
#define STATE_RUNNING	(3)

#define SVC_ACT_TSK		(0)
#define SVC_EXT_TSK		(1)
#define SVC_DLY_TSK		(2)

#define _str(a) _st(a)
#define _st(a)	#a

typedef struct{
	FP		p_func;
	int32_t pri;
} task_init_t;

task_init_t _task_cfg[TASK_NUM] = {
	{led_green_task, 1},
	{led_red_task, 1},
	{calc_task, 2},
	{idle_task, 3},
};

uint32_t _task_stk[TASK_NUM][TASK_STACK_SIZE];

// Bi-directional list: previous pointer, next pointer and property
typedef struct tcb{
	uint32_t	*p_sp;
	struct tcb	*p_prev;
	struct tcb	*p_next;
	int32_t		id;
	int32_t		pri;
	int32_t		state;
	uint32_t	time_up;
} tcb_t;

tcb_t _tcb_tbl[TASK_NUM];
tcb_t _queue_ready[TASK_PRI_NUM]; // use only *p_next
tcb_t _queue_waiting;

typedef struct {
	int32_t		running;
	uint32_t	systime;
} sysinfo_t;

static sysinfo_t _sysinfo;


/********************************/
// Prototype declaration
/********************************/
static void    _q_add(tcb_t *p_queue, int32_t task_id);
static void    _q_add_waiting(int32_t task_id);
static void    _q_add_ready(int32_t task_id);
static void    _q_remove(int32_t task_id);
static int32_t _q_top_ready(void);
static void    _schedule_svc(uint8_t svc_num, uint32_t *svc_args);
static void    _schedule_time(void);
static void    _task_init(int32_t id);
static void    _task_init_all(void);
static void    _task_start(void);


/********************************/
// OS
/********************************/
void _os_start(void)
{
	_task_init_all();
	_sysinfo.running = _q_top_ready();
	_tcb_tbl[_sysinfo.running].state = STATE_RUNNING;
	_task_start();
}

ER act_tsk(int32_t tskid)
{
	if(tskid<0 || tskid>=TASK_NUM) return E_ID;
	if(_tcb_tbl[tskid].state != STATE_DORMANT) return E_OBJ;

	__asm("SVC "_str(SVC_ACT_TSK));
	return E_OK;
}

void ext_tsk(void)
{
	__asm("SVC "_str(SVC_EXT_TSK));
	//never return here
}

ER dly_tsk(int32_t dlytim)
{
	__asm("svc "_str(SVC_DLY_TSK));
	return E_OK;
}

ER isig_tim(void)
{
	_sysinfo.systime += TICK_MS;
	return E_OK;
}


/********************************/
// Interrupt handle
/********************************/

__NAKED void _os_entint(void)
{
	__asm("mrs		r1, psp");			//	application routines work under thread mode
	__asm("stmdb	r1!, {r4-r11}");	//	r4-r11 are not stored automatically
	__asm("mov		%0, r1" : "=r"(_tcb_tbl[_sysinfo.running].p_sp) : :);  // save psp
	__asm("bx		lr");
}

__NAKED void _os_retint(void)
{
	_schedule_time();
	__asm("b _dispatch");
}

__NAKED void svc_handler(void)
{
	uint32_t	*svc_args;
	uint8_t 	svc_num;
	_os_entint();					// store manually r4-r11 registers and stack pointer to memory

	__asm("mrs	r1, psp");

	//	svc_args[0]: r0
	//	svc_args[1]: r1
	//	svc_args[2]: r2
	//	svc_args[3]: r3
	//	svc_args[4]: r12
	//	svc_args[5]: r14(LR)
	//	svc_args[6]: r15(PC)
	__asm("mov	%0, r1" : "=r"(svc_args) : :);

	//	svc #<imm8>
	svc_num = ((uint8_t *)(svc_args[6]))[-2];

	_schedule_svc(svc_num, svc_args);
	__asm("b _dispatch");	//	never return
}

__NAKED void _dispatch(void)
{
	__asm("ldr		lr, =0xFFFFFFFD");
	__asm("mov		r0, %0" : :"r"(_tcb_tbl[_sysinfo.running].p_sp) :);
	__asm("ldmfd	r0!, {r4-r11}");
	__asm("msr		psp, r0");
	__asm("bx		lr");
}

/********************************/
// scheduler
/********************************/

static void _schedule_svc(uint8_t svc_num, uint32_t *svc_args)
{
	switch(svc_num){
	case SVC_ACT_TSK:
		_task_init(svc_args[0]);
		_q_add_ready(svc_args[0]);
		break;
	case SVC_EXT_TSK:
		_q_remove(_sysinfo.running);
		_tcb_tbl[_sysinfo.running].state = STATE_DORMANT;
		break;
	case SVC_DLY_TSK:
		_q_remove(_sysinfo.running);
		_tcb_tbl[_sysinfo.running].time_up = _sysinfo.systime + svc_args[0];
		_tcb_tbl[_sysinfo.running].state = STATE_WAITING;
		_q_add_waiting(_sysinfo.running);
		break;
	default:
		break;
	}

	_sysinfo.running = _q_top_ready();
	_tcb_tbl[_sysinfo.running].state = STATE_RUNNING;
}

static void _schedule_time(void)
{
	tcb_t *p_task = _queue_waiting.p_next;
	while(p_task != 0){
		if(_sysinfo.systime > p_task->time_up){
			_q_remove(p_task->id);
			_q_add_ready(p_task->id);
		}
		p_task = p_task->p_next;
	}
	_sysinfo.running = _q_top_ready();
	_tcb_tbl[_sysinfo.running].state = STATE_RUNNING;
}


/********************************/
// operations of tasks
/********************************/
static void _task_init(int32_t id)
{
	_tcb_tbl[id].id = id;
	_tcb_tbl[id].pri =_task_cfg[id].pri;
	_tcb_tbl[id].p_sp = &_task_stk[id][TASK_STACK_SIZE-16];					//	registers:16*4byte
	_tcb_tbl[id].state = STATE_READY;
	_task_stk[id][TASK_STACK_SIZE - 1] = 0x01000000;						//	EPSR[24]=1, Thumb
	_task_stk[id][TASK_STACK_SIZE - 2] = (uint32_t)(_task_cfg[id].p_func);	//
}

static void _task_init_all(void)
{
	int32_t id;
	for(id=0; id<TASK_NUM; id++){
		_task_init(id);
		_q_add_ready(id);
	}
}

static void _task_start(void)
{
	__asm("msr	psp, %0" : : "r"(_tcb_tbl[_sysinfo.running].p_sp) :);
	__asm("mrs	r0, control");
	__asm("orr	r0, r0, #0x02");
	__asm("msr	control, r0");
	__asm("pop	{r4-r11}");
	__asm("pop	{r0-r3}");
	__asm("pop	{r12}");
	__asm("add	sp, sp, #4");
	__asm("pop	{lr}");
	__asm("bx	lr");
}

/********************************/
// operations of queue
/********************************/
static void _q_add(tcb_t *p_queue, int32_t task_id)
{
	tcb_t *p_task = &_tcb_tbl[task_id];
	tcb_t *p_ptr = p_queue;
	while(p_ptr->p_next != 0){
		p_ptr = p_ptr->p_next;
	}
	p_ptr->p_next	= p_task;
	p_task->p_prev	= p_ptr;
	p_task->p_next	= 0;
}

static void _q_add_waiting(int32_t task_id)
{
	_q_add(&_queue_waiting, task_id);
}

static void _q_add_ready(int32_t task_id)
{
	tcb_t *p_task = &_tcb_tbl[task_id];
	_q_add(&_queue_ready[p_task->pri], task_id);
}

static void _q_remove(int32_t task_id)
{
	tcb_t *p_task = &_tcb_tbl[task_id];
	p_task->p_prev->p_next = p_task->p_next;
	p_task->p_next->p_prev = p_task->p_prev;
	p_task->p_prev = 0;
	p_task->p_next = 0;
}

static int32_t _q_top_ready(void)
{
	int32_t pri;
	for(pri=0; pri<TASK_PRI_NUM; pri++){
		if(_queue_ready[pri].p_next != 0){
			return _queue_ready[pri].p_next->id;
		}
	}
	return 0;
}
