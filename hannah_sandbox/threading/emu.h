
#include <stdlib.h>

/**
 * @brief initialize the system
 *
 * Initializes the internal system data structures to known conditions. Zeros _g_sys static variable,
 * creates an idle task and sets everything up, so the system is ready to accept new tasks being created
 * and to be started
 *
 * @param a_freq tick frequency
 */
void init();

typedef void (*task_proc_t)(void *a_data);

/**
 * @brief launch the scheduler and all tasks
 *
 * From now on, the system will start execution. This call is blocking and should never return.
 */
void run();


/**
 * @file aos_task.h
 *
 * @brief task control block interface
 *
 * Declares task control block and task related routines and interface
 */


// ================================================================================

/**
 * @brief this macro is used to determine the task "work area" size.
 *
 * @param __size stack size requested by the task
 *
 * It returns how much memory is needed for a task, which wants to have
 * a stack of size __size for it's private needs
 */
#define AOS_CALC_TASK_WA_SIZE(__size) \
	(__size + AOS_IRQ_CTX_SIZE() + AOS_MACHINE_CTX_SIZE() + sizeof(struct task_cb))

// ================================================================================

/**
 * @brief task procedure type declaration
 *
 * @param a_data private data for the task callback
 */
typedef void (*task_proc_t)(void *a_data);


/**
 * @brief task context block
 */
struct task_cb {

	/// task list pointers must be on top
	struct task_cb *prv, *nxt;

	/// holds current stack pointer, and reference to machine state

	/// task priority / task state combined field
	uint8_t prio_state;

	/// number of time quanta's task can consume
	uint8_t quanta;

	/// task execution handler
	task_proc_t proc;

	/// number of systicks consumed by the task

	/// work area size
	uint16_t wa_size;

	/// work area pointer
	void *wa;

	/// task private data
	void *pdata;
};


// ================================================================================

/**
 * @brief Creates a system task and ads it to system runlist
 *
 * Creates the system task, returns the freshly created task control block and adds
 * the task to system runlist.
 *
 * @param a_task_proc function callback for the task
 * @param a_pdata any private data which will be passed as tasks argument, NULL if none.
 * @param a_prio task priority
 * @param a_stack stack for the task, a value of 32 bytes is recommended
 *
 * @return task control block
 */
struct task_cb* aos_task_create(task_proc_t a_task_proc, size_t a_stack);


/**
 * @brief configures task priority to a given value
 *
 * @param a_task task which priority will be changed
 * @param a_prio priority
 */
void aos_task_priority_set(struct task_cb *a_task, uint8_t a_prio);


/**
 * @brief set task state
 *
 * This function shouldn't be used outside of the system.
 *
 * @param a_task task
 * @param a_state state
 */
void aos_task_state_set(struct task_cb *a_task, uint8_t a_state);


/**
 * @brief return the priority of a specified task
 *
 * @param a_task task to be examined
 *
 * @return priority
 */
uint8_t aos_task_priority_get(struct task_cb *a_task);


/**
 * @brief returns task state
 *
 * @param a_task task
 *
 * @return state
 */
uint8_t aos_task_state_get(struct task_cb *a_task);
