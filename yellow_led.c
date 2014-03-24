/*
 * yellow_led.c
 *
 *  Created on: Mar 18, 2014
 *      Author: root
 */
#include <avr/interrupt.h>
#include <util/delay.h>
#include "led.h"
#include "lab1.h"
#include <pololu/orangutan.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//--------------------------- YELLOW ---------------------------------//
	// 100 ms Softward Clock using 8-bit timer.
	// Period of task is multiple of 100ms.
	// Yellow toggled inside ISR.
	// Keep count of the number of toggles.
	//
	// You could use a single timer to schedule everything, but we are experimenting here.


volatile uint32_t yellow_toggles = 0;

volatile uint16_t yellow_interrupt_counter = 1;
volatile uint16_t yellow_interrupt = 1;

void init_yellow_led() {
	TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);
	OCR3A = 31250;
	TIMSK3 = _BV(OCIE3A);
}

ISR(TIMER3_COMPA_vect) {
#ifdef EXPERIMENT_6_2
	sei();
#endif
#ifdef EXPERIMENT_3_2
	delay_ms(90);
#endif
#ifdef EXPERIMENT_4_2
	delay_ms(110);
#endif
#if defined(EXPERIMENT_5_2) || defined(EXPERIMENT_6_2)
	delay_ms(510);
#endif
	if(yellow_interrupt_counter == yellow_interrupt) {
		LED_TOGGLE(YELLOW);
		yellow_toggles++;
		yellow_interrupt_counter = 1;
	} else {
		yellow_interrupt_counter++;
	}
}

void set_yellow_led_period(uint16_t ms) {
	if(ms == 0) {
		TIMSK3 &= ~_BV(OCIE3A);
		return;
	} else if(! (TIMSK3 & _BV(OCIE3A))) {
		TIMSK3 = _BV(OCIE3A);
	}
	cli();
	yellow_interrupt_counter = 0;
	yellow_interrupt = ceil(ms / 100);
	sei();
}

int get_yellow_toggles() {
	return yellow_toggles;
}

void clear_yellow_toggles() {
	yellow_toggles = 0;
}


