#ifndef LS_SYS_H_
#define LS_SYS_H_

/** \brief Post a function to be called in the main loop with specific parameter
 *  \param[in] func The pointer to the function
 *  \param[in] param The pointer of the object with global lifecycle that will be passed to func
 */
void func_post(void (*func)(void *),void *param);

void rtos_ble_task_func_post(void (*func)(void *),void *param);
#endif

