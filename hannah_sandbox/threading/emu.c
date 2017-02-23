#include "emu.h"

void init() {
	// // timer pre-scaler values
	// uint32_t pocr = 0x00;

	// // lock interrupts
	// AOS_LOCK();

	// initialize system data struct
	memset((void *)&_g_sys, 0x00, sizeof(struct aos_sys));

	// // setup initial system status
	// _aos_common_sys_state_set(AOS_SYS_UNINITIALIZED);
  //
	// store system stack pointer value
	_g_sys.ctx.sp = (struct aos_machine_ctx *)SP;
  //
	// // timer setup
	// _timer_init_ctc(AOS_SCHED_TIMER);
	// if (E_TIMER1 == AOS_SCHED_TIMER) {
	// 	pocr = _timer_freq_prescale(E_TIMER1, a_freq, 65535);
	// }
	// else {
	// 	pocr = _timer_freq_prescale(AOS_SCHED_TIMER, a_freq, 255);
	// }
	//
	// _timer_setup_ctc(AOS_SCHED_TIMER, pocr);
  //
	// // select active task list
	// _g_sys.rl.active = 0;
  //
	// // create idle task
	// _g_sys.current = aos_task_create(_aos_idle_task,
	// 		NULL,
	// 		AOS_TASK_PRIORITY_IDLE,
	// 		AOS_COMMON_IDLE_TASK_STACK_SIZE);
  //
	// // setup as idle task
	// _g_sys.rl.idle = _g_sys.current;
	// _g_sys.rl.idle->quanta = AOS_SCHED_TASK_QUANTA_PRIORITY_IDLE;
  //
	// // mark as running
	// aos_task_state_set(_g_sys.current, AOS_TASK_RUNNING);
  //
	// // setup system status
	// _aos_common_sys_state_set(AOS_SYS_READY);
  //
	// // unlock interrupts
	// AOS_UNLOCK();
}

struct task_cb* aos_task_create(task_proc_t a_task_proc, size_t a_stack) {

	uint16_t blk_size = AOS_CALC_TASK_WA_SIZE(a_stack);

	AOS_LOCK();

	struct task_cb *cb = (struct task_cb *)malloc(blk_size);

	if (!cb) {
		_aos_common_hook_exec(AOS_HOOK_OOM);
		return NULL;
	}

	memset(cb, 0x00, blk_size);
	cb->wa = (void *)((uint8_t *)cb + sizeof(struct task_cb));
	cb->wa_size = (blk_size - sizeof(struct task_cb));

	cb->proc = a_task_proc;
	cb->pdata = a_pdata;
	cb->systicks = 0x00;

	// initialize stack pointer
	cb->ctx.sp = (struct aos_machine_ctx *)((uint8_t *)cb +
			blk_size -
			AOS_MACHINE_CTX_SIZE() -
			AOS_IRQ_CTX_SIZE());

	// setup initial context
	// callback
	cb->ctx.sp->r[2]  = ((uint16_t)a_task_proc) & 0xff;
  	cb->ctx.sp->r[3]  = ((uint16_t)a_task_proc >> 8) & 0xff;

	// arguments
  	cb->ctx.sp->r[4]  = ((uint16_t)a_pdata) & 0xff;
  	cb->ctx.sp->r[5]  = ((uint16_t)a_pdata >> 8) & 0xff;

	// read status register
	cb->ctx.sp->sreg = SREG;

	// task launcher will be first called
	cb->ctx.sp->pc.pc8.lo = ((uint16_t)_aos_task_launcher >> 8) & 0xff;
	cb->ctx.sp->pc.pc8.hi = ((uint16_t)_aos_task_launcher) & 0xff;

	// mark as suspended
	aos_task_state_set(cb, AOS_TASK_SUSPENDED);

	// add to run list
	aos_sched_task_resume(cb);

	AOS_UNLOCK();
	return cb;
}
