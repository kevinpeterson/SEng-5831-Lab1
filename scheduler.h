/*
 * scheduler.h
 *
 *  Created on: Mar 14, 2014
 *      Author: kevin
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <inttypes.h>

typedef struct task_t {
	uint16_t period;
	void (*interrupt_function)(void);
	char released;
	char* name;
} Task;

void initialize_scheduler();

void release_ready_tasks();

void recalculate_hyperperiod();

void register_task(volatile Task* task);

#endif /* SCHEDULER_H_ */
