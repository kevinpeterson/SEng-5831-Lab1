#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"
#include "ints.h"

#define MAX_TASKS 10
#define NUM_TASKS 2

volatile Task* tasks[NUM_TASKS];

volatile INT32 counter = 0;

void initialize_scheduler() {
	// timer interrupt
	TIMSK3 = _BV(OCIE3A);
	TCCR3A = _BV(COM3A1);
	TCCR3B = _BV(CS31) | _BV(WGM32);
	OCR3A = 2500;
}

void release_ready_tasks() {
	int i;
	for (i = 0; i < NUM_TASKS; i++) {
		volatile Task* task = tasks[i];
		// if a task has been marked as released, fire its function
		if (task != NULL && task->released) {
			task->interrupt_function();
			task->released = 0;
		}
	}
}

void register_task(volatile Task* task) {
	uint8_t i;
	for(i = 0;i < MAX_TASKS; i++){
		if(tasks[i] == NULL){
			tasks[i] = task;
			break;
		}
	}
}

// assume a 1000 tick hyperperiod -- release tasks (jobs) as necessary
ISR(TIMER3_COMPA_vect) {
	if (counter == 1000) {
		counter = 0;
	}

	int i;
	for (i = 0; i < NUM_TASKS; i++) {
		volatile Task* task = tasks[i];
		// release a job at the start of its period
		if (task->period && (counter % task->period == 0)) {
			task->released = 1;
		}
	}

	counter++;
}
