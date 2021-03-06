/**
 * MSSE SEng 5831 Lab1 main file.
 */
#define ECHO2LCD
#define WELCOME_MSG

#include <pololu/orangutan.h>
#include "lab1.h"
#include "scheduler.h"
#include "led.h"
#include "tasks.h"
#include "menu.h"
#include "scheduler.h"
#include "serial.h"
#include "logger.h"
#include "yellow_led.h"
#include "red_led.h"
#include "green_led.h"

//Gives us uintX_t (e.g. uint32_t - unsigned 32 bit int)
//On the ATMega128 int is actually 16 bits, so it is better to use
//  the int32_t or int16_t so you know exactly what is going on
#include <inttypes.h> //gives us uintX_t

// useful stuff from libc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Green : Port D, pin 5.
 * Yellow: Port A, pin 0.
 * Red: Port A, pin 2.
 */
void init_io() {
	DDRD |= _BV(5);
	DDRA |= _BV(0);
	DDRA |= _BV(2);
}

/**
 * Test a LED by toggling it a few times.
 */
void _test_led(volatile uint8_t* port, char port_value){
	int i = 0;
	for(i = 0;i < 5;i++){
		*port ^= port_value;
		delay_ms(100);
	}
}

#ifdef WELCOME_MSG
/**
 * A quite unnecessary welcome screen display.
 * I wanted to learn some pointer math...
 */
void print_welcome_message() {
	char* msg = "Kevin's Lab 1";
	int8_t i = -strlen(msg);
	for(;i < 16;i++){
		clear();
		char* m;
		int x = i;
		if(i < 0){
			x = 0;
			m = msg+abs(i);
		} else {
			m = msg;
		}
		lcd_goto_xy(x,0);
		print(m);
		lcd_goto_xy(1,1);
		print("MSSE SEng 5831");
		delay_ms(300);
	}
}
#endif

/**
 * A simple LED/LCD check to make sure things are working.
 */
void system_check() {
	clear();
	print("Checking Status...");
	delay_ms(2000);
	clear();
	print("Check Green LED");
	_test_led(&PORT_GREEN, BIT_GREEN);
	clear();
	print("Check Yellow LED");
	_test_led(&PORT_YELLOW, BIT_YELLOW);
	clear();
	print("Check Red LED");
	_test_led(&PORT_RED, BIT_RED);
	clear();
}

void serial_lcd_log_callback(char c) {
	char str[2] = {c,'\0'};
	log_msg(str, DEBUG);
}

int main(void) {
	// -------------------------------------------------------------
	// This program teaches you about the various ways to "schedule" tasks.
	// You can think of the three blinking LEDs as separate tasks with 
	// strict timing constraints.
	//
	// As you build your program, think about the guarantees that you can 
	// make regarding the meeting of deadlines. Think about how the CPU
	// is "communicating" with the LEDs. Obviously, everything is output,
	// but what if it was input? Also think about how data can be passed
	// among tasks and how conflicts might arise.
	//
	// TASKS
	//
	// Establish WCET analysis on a for loop to use for timing.
	// Use the for loop to blink the red LED.
	//
	// Set up a system 1 ms software timer (16-bit) and use that to "schedule" 
	// tasks.
	//
	// Toggle the red LED inside a cyclic executive.
	//
	// Toggle the yellow LED using a separate timer (8-bit) with a 100ms resolution.
	// Toggle the LED inside the ISR.
	//
	// Toggle the green LED by toggling the output on a pin using
	// a Compare Match. This is the creation of a PWM signal with a very long period.
	// Count toggles inside the corresponding ISR (don't forget to turn this
	// off when the green LED is turned off.
	//
	// Scheduler releases the menu task.
	// The menu allows the user to modify the period of each task.
	//
	// --------------------------------------------------------------
	init_io();

#ifndef BUSY_WAIT_LOOP
	lcd_init_printf();
	
	init_serial();
	init_menu();
	register_incoming_callback(&serial_lcd_log_callback);

	// Turn all LEDs on for a second or two then turn off to confirm working properly
	// Send a message to LCD to confirm proper start. ( interrupts might need to be on for this ?? )
	// Send a message through serial comm to confirm working properly.
#ifdef WELCOME_MSG
	print_welcome_message();
#endif
	system_check();
	initialize_tasks();
	init_yellow_led();
#ifndef EXPERIMENT_1
	init_red_led();
#endif
	init_green_led();

	// clear the LCD
	clear();

	// For these experiments, the serial menu doesn't work, so I'll
	// set the necessary values here.
#if defined(EXPERIMENT_4_1) || defined(EXPERIMENT_4_2) || \
	defined(EXPERIMENT_5_1) || defined(EXPERIMENT_5_2) || \
	defined(EXPERIMENT_6_1) || defined(EXPERIMENT_6_2)
	set_green_led_period(500);
	set_yellow_led_period(500);
	set_red_led_period(500);

	clear_green_toggles();
	clear_yellow_toggles();
	clear_red_toggles();
#endif

	//enable interrupts
	sei();
#endif

	// The Cyclic Executive. That sounds important... like something you'd
	// have on a business card.
	while (1) {

#if defined(BUSY_WAIT_LOOP) || defined(EXPERIMENT_1)
		toggle_red_led_busy_wait();
#endif

#ifndef BUSY_WAIT_LOOP
		release_ready_tasks();
#endif

	} //end while loop
} //end main
