/**
 * File contains all necessary routines for context switching.
 */



/**
 * @brief full machine context.
 *
 * This structure will be mapped to the current stack pointer position
 *  and resemble the current machine state for the task.
 */

#include <stdlib.h>


struct aos_machine_ctx {

  /**
   * @brief since stack pointer is post incremented the machine context must by one byte padded
   */
  uint8_t __sp_post_incr_padding;

  /// general purpose registers
  uint8_t r[32];

  /// status register
  uint8_t sreg;

  /// program counter is pushed first, thus last in the map
  union {
    /// as 8 bit register values
    struct {
      /// SPL
      uint8_t lo;

      /// SPH
      uint8_t hi;
    } pc8;

    /// as a 16 bit value
    uint16_t pc16;
  } pc;
};


struct aos_ctx {

  /**
   * @brief this pointer will be updated to current stack pointer value
   */
  volatile struct aos_machine_ctx *sp;
};


#define AOS_MACHINE_CTX_SIZE()  (sizeof(struct aos_machine_ctx))

/**
 * @brief defines how much additional space in the process's work area for interrupt call stack
 *  is needed
 */
#define AOS_IRQ_CTX_SIZE() 8


/**
 * @brief switches stack pointer to the specified task context
 */
#define AOS_CTX_SP_SET(__task)  SP = (uint16_t)__task->ctx.sp


/**
 * @brief saves current stack pointer value to stack context of the current task
 */
#define AOS_CTX_SP_GET(__task) __task->ctx.sp = (struct aos_machine_ctx *)SP


/**
 * @brief update the program counter with a value from the stack
 */
#define AOS_CTX_POP_PC() __asm__ volatile ("ret" ::)


/**
 * @brief save machine context
 */
#define AOS_CTX_SAVE() \
  __asm__ volatile("push r31\n\t" \
    "in r31, 0x3f\n\t" \
    "push r31\n\t" \
    "push r30\n\t" \
    "push r29\n\t" \
    "push r28\n\t" \
    "push r27\n\t" \
    "push r26\n\t" \
    "push r25\n\t" \
    "push r24\n\t" \
    "push r23\n\t" \
    "push r22\n\t" \
    "push r21\n\t" \
    "push r20\n\t" \
    "push r19\n\t" \
    "push r18\n\t" \
    "push r17\n\t" \
    "push r16\n\t" \
    "push r15\n\t" \
    "push r14\n\t" \
    "push r13\n\t" \
    "push r12\n\t" \
    "push r11\n\t" \
    "push r10\n\t" \
    "push r9\n\t" \
    "push r8\n\t" \
    "push r7\n\t" \
    "push r6\n\t" \
    "push r5\n\t" \
    "push r4\n\t" \
    "push r3\n\t" \
    "push r2\n\t" \
    "push r1\n\t" \
    "clr r1\n\t" \
    "push r0\n\t" \
    ::)


/**
 * @brief restore machine context
 */
#define AOS_CTX_RESTORE() \
  __asm__ volatile ("pop r0\n\t" \
    "pop r1\n\t" \
    "pop r2\n\t" \
    "pop r3\n\t" \
    "pop r4\n\t" \
    "pop r5\n\t" \
    "pop r6\n\t" \
    "pop r7\n\t" \
    "pop r8\n\t" \
    "pop r9\n\t" \
    "pop r10\n\t" \
    "pop r11\n\t" \
    "pop r12\n\t" \
    "pop r13\n\t" \
    "pop r14\n\t" \
    "pop r15\n\t" \
    "pop r16\n\t" \
    "pop r17\n\t" \
    "pop r18\n\t" \
    "pop r19\n\t" \
    "pop r20\n\t" \
    "pop r21\n\t" \
    "pop r22\n\t" \
    "pop r23\n\t" \
    "pop r24\n\t" \
    "pop r25\n\t" \
    "pop r26\n\t" \
    "pop r27\n\t" \
    "pop r28\n\t" \
    "pop r29\n\t" \
    "pop r30\n\t" \
    "pop r31\n\t" \
    "out 0x3f, r31\n\t" \
    "pop r31\n\t" \
    ::)
