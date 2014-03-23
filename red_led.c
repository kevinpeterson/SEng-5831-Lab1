/*
 * red_led.c
 *
 *  Created on: Mar 19, 2014
 *      Author: root
 */
#include "scheduler.h"
#include "led.h"
#include <inttypes.h>
#include "tasks.h"

volatile uint32_t red_toggles = 0;

void red_led_toggle();

void busy_wait_10ms() {
	WAIT_10MS;
}

volatile Task red_led_task = { .period = 250, .interrupt_function =
		&red_led_toggle, .released = 0, .name = "Red Button Task" };

// -------------------------  RED ------------------------------------//
	// Scheduler releases with flag. Executes inside  cyclic executive.
	// Keep count of the number of toggles.
void red_led_toggle() {
	LED_TOGGLE(RED);
	red_toggles++;
}

void init_red_led() {
	register_task(&red_led_task);
}

void set_red_led_period(uint16_t ms) {
	red_led_task.period = ms;
	recalculate_hyperperiod();
}

int get_red_toggles() {
	return red_toggles;
}

void clear_red_toggles() {
	red_toggles = 0;
}

void toggle_red_led_busy_wait() {
	int i = 0;
	for (i = 0;i < red_led_task.period / 10;i++) {
		busy_wait_10ms();
	}
	red_led_toggle();
}
