/*
 * yellow_led.c
 *
 *  Created on: Mar 18, 2014
 *      Author: root
 */
#include <avr/interrupt.h>
#include "led.h"
#include <pololu/orangutan.h>

#define OVERFLOWS 976
volatile uint16_t overflows = 0;

volatile uint16_t yellow_led_period = 100;
volatile uint16_t _100_ms_counter = 0;

void init_yellow_led() {
	TCCR0B = _BV(CS01);
	TIMSK0 = _BV(TOIE0);
}

ISR(TIMER0_OVF_vect) {
	if(_100_ms_counter * 100 >= yellow_led_period){
		LED_TOGGLE(YELLOW);
		_100_ms_counter = 0;
	}

	if(overflows == OVERFLOWS){
		_100_ms_counter++;
		overflows = 0;
	} else {
		overflows++;
	}
}

void set_yellow_led_period(uint16_t ms) {
	yellow_led_period = ms;
}

