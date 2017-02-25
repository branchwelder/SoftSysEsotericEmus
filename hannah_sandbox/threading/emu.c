#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#include "emu.h"

volatile struct aos_sys _g_sys;
static void _aos_task_launcher(void);

void _aos_task_exit(void) {
	// we will land up here if the task will exit suddenly
  printf("Inside task_exit.\n");
  //while (1);
}

__attribute__((naked))
static void _aos_task_launcher(void) {
  __asm__ volatile ("movw    r24, r4");
  __asm__ volatile ("movw    r30, r2");
  __asm__ volatile ("icall");
  // task is running now

  __asm__ volatile ("call _aos_task_exit");
}


void init() {
	printf("Inside init.\n");

  printf("Initializing system data struct.\n");
	// initialize system data struct
	memset((void *)&_g_sys, 0x00, sizeof(struct aos_sys));

	printf("Creating and storing system stack pointer value...\n");
	// store system stack pointer value
	_g_sys.ctx.sp = (struct aos_machine_ctx *)SP;
	printf("Success!\n");

}

struct task_cb* aos_task_create(task_proc_t a_task_proc, size_t a_stack) {

	printf("Inside task_create!\n");

	uint16_t blk_size = AOS_CALC_TASK_WA_SIZE(a_stack);


	struct task_cb *cb = (struct task_cb *)malloc(blk_size);


	memset(cb, 0x00, blk_size);
	cb->wa = (void *)((uint8_t *)cb + sizeof(struct task_cb));
	cb->wa_size = (blk_size - sizeof(struct task_cb));

	cb->proc = a_task_proc;

	// initialize stack pointer
	cb->ctx.sp = (struct aos_machine_ctx *)((uint8_t *)cb +
			blk_size -
			AOS_MACHINE_CTX_SIZE() -
			AOS_IRQ_CTX_SIZE());

	// setup initial context
	// callback
	cb->ctx.sp->r[2]  = ((uint16_t)a_task_proc) & 0xff;
  	cb->ctx.sp->r[3]  = ((uint16_t)a_task_proc >> 8) & 0xff;

	// read status register
	cb->ctx.sp->sreg = SREG;

	// task launcher will be first called
	cb->ctx.sp->pc.pc8.lo = ((uint16_t)_aos_task_launcher >> 8) & 0xff;
	cb->ctx.sp->pc.pc8.hi = ((uint16_t)_aos_task_launcher) & 0xff;

	// mark as suspended
	aos_task_state_set(cb, AOS_TASK_SUSPENDED);

	return cb;
}

void run() {
	printf("Inside run!\n");
	printf("_g_sys.current: %s\n", _g_sys.current);

	// set sp to current task's context and restore it
	AOS_CTX_SP_SET(_g_sys.current);
	printf("Set sp to current task's context.\n");
	AOS_CTX_RESTORE();
	printf("Restore sp.\n");

	printf("About to jump to first task.\n");
	// jump to first task
	AOS_CTX_POP_PC();

}

__inline__
void aos_task_state_set(struct task_cb *a_task, uint8_t a_state) {
	a_task->prio_state &= 0xf0;
	a_task->prio_state |= (a_state & 0x0f);
}
