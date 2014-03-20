#include "tasks.h"
#include "scheduler.h"
#include "led.h"
#include "yellow_led.h"
#include "red_led.h"

// NOTE: MENU task is in separate file menu.c

// extern GLOBALS


// periods
volatile uint16_t G_greenPeriod;
volatile uint16_t G_yellowPeriod;

void red_led_toggle();


void _set_up_pwm() {
	PORTD |= _BV(5);

	OCR1A = 255;
	ICR1 = 1000;

	TCCR1A |= _BV(WGM11);
	TCCR1B |= _BV(WGM13) | _BV(WGM12) | _BV(CS10) | _BV(CS12);
	TCCR1A |= _BV(COM1A1);
}

void initialize_tasks() {
	_set_up_pwm();

	initialize_scheduler();
}
//--------------------------- SCHEDULER ------------------------------//
	// 1 ms Software Clock Using Timer/Counter 3.
	// Uses flags to release red toggle and serial communication (i.e. menu task)



//--------------------------- YELLOW ---------------------------------//
	// 100 ms Softward Clock using 8-bit timer.
	// Period of task is multiple of 100ms.
	// Yellow toggled inside ISR.
	// Keep count of the number of toggles.
	//
	// You could use a single timer to schedule everything, but we are experimenting here.


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


// You don't have to use the code below, but this functionality is needed.
void setPeriod(char task, int ms) {
	// For each task, if ms is 0, turn it off, else turn it on and set appropriately
	
	if ( ( task == 'R' ) || ( task == 'A' ) ) {
		if ( ms == 0 ){
			
		} else {
			set_red_led_period(ms);
		}
	}
	
	if ( ( task == 'Y') || ( task =='A')) {
		if ( ms == 0 ) {
			
		} else {
			set_yellow_led_period(ms);
		}
	}
	
	if (( task == 'G') || ( task == 'A' )) {
		if ( ms == 0 ) {
			
		} else {
			// green has a limit on its period.
			if ( ms > 4000) ms = 4000;
			G_greenPeriod = ms;
			// set requested frequency.
		}
	}
}
