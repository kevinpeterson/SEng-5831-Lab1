/*
 * red_led.c
 *
 *  Created on: Mar 19, 2014
 *      Author: root
 */
#include "scheduler.h"
#include "led.h"
#include <inttypes.h>

void red_led_toggle();

volatile Task red_led_task = { .period = 250, .interrupt_function =
		&red_led_toggle, .released = 0, .name = "Red Button Task" };

// -------------------------  RED ------------------------------------//
	// Scheduler releases with flag. Executes inside  cyclic executive.
	// Keep count of the number of toggles.
void red_led_toggle() {
	LED_TOGGLE(RED);
}

void init_red_led() {
	register_task(&red_led_task);
}

void set_red_led_period(uint16_t ms) {
	red_led_task.period = ms;
}



