/*
 * Controller for the Green LED driven by hardware PWM
 */
#include <avr/interrupt.h>
#include <inttypes.h> //gives us uintX_t
#include <util/delay.h>
#include "lab1.h"

//--------------------------- GREEN ----------------------------------//

// Toggle with PWM signal on OCR1A. The period of the PWM IS the period of the toggle.
// Toggle period is limited by the range of the counter. Set prescaler and counter to maximize range.
// Use the corresponding interrupt to keep count of toggles.
//
// Don't forget to stop counting toggles when green turned off.


// When setting up timers or PWM signals, remember...
/*
 Set WGM bits in TCCR registers
 Set Clock Select Bits in TCCR registers
 Set COM bits, if needed, in TCCR registers
 Set OCRxx
 Enable Interrupt (if using)
 Define ISR() (if using)
 */
#define ONE_SEC_ICR1 19531
#define CALC_PERIOD(ms) (uint16_t)(((float) 19.531)  * ms)

volatile uint32_t green_toggles = 0;

void _turn_on_toggle() {
	TCCR1A |= _BV(COM1A0);
	TIMSK1 |= _BV(OCIE1A);
}

void _turn_off_toggle() {
	TCCR1A &= ~_BV(COM1A0);
	TIMSK1 &= ~_BV(OCIE1A);
}

void set_green_led_period(uint16_t ms) {
	if(ms == 0) {
		_turn_off_toggle();
		return;
	} else if(! (TIMSK1 &_BV(OCIE1A))) {
		_turn_on_toggle();
	}
	OCR1A = CALC_PERIOD(ms);
}

void _set_up_pwm() {
	PORTD |= _BV(5);

	set_green_led_period(1000);

	TCCR1A |= _BV(WGM11) | _BV(WGM10);
	TCCR1B |= _BV(WGM13) | _BV(WGM12) | _BV(CS10) | _BV(CS12);
	_turn_on_toggle();
}

void init_green_led() {
	_set_up_pwm();
}

int get_green_toggles() {
	return green_toggles;
}

void clear_green_toggles() {
	green_toggles = 0;
}

ISR(TIMER1_COMPA_vect) {
#ifdef EXPERIMENT_6_1
	sei();
#endif
#ifdef EXPERIMENT_3_1
	delay_ms(90);
#endif
#ifdef EXPERIMENT_4_1
	delay_ms(110);
#endif
#if defined(EXPERIMENT_5_1) || defined(EXPERIMENT_6_1)
	delay_ms(510);
#endif
	green_toggles++;
}

