/*
 * green_led.c
 *
 *  Created on: Mar 19, 2014
 *      Author: root
 */
#include <avr/interrupt.h>
#include <inttypes.h> //gives us uintX_t

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

void set_green_led_period(uint16_t ms) {
	OCR1A = CALC_PERIOD(ms);
}

void _set_up_pwm() {
	PORTD |= _BV(5);

	set_green_led_period(1000);

	TCCR1A |= _BV(WGM11) | _BV(WGM10);
	TCCR1B |= _BV(WGM13) | _BV(WGM12) | _BV(CS10) | _BV(CS12);
	TCCR1A |= _BV(COM1A0);// | _BV(COM1B1);
}

void init_green_led() {
	_set_up_pwm();
}

int get_green_toggles() {
	//todo
	return 0;
}

