#include "tasks.h"
#include "scheduler.h"
#include "led.h"
#include "yellow_led.h"
#include "red_led.h"
#include "green_led.h"

// NOTE: MENU task is in separate file menu.c

// extern GLOBALS

void initialize_tasks() {
	initialize_scheduler();
}

// You don't have to use the code below, but this functionality is needed.
void setPeriod(char task, int ms) {
	// For each task, if ms is 0, turn it off, else turn it on and set appropriately
	
	if ( ( task == 'R' ) || ( task == 'A' ) ) {
		set_red_led_period(ms);
	}
	
	if ( ( task == 'Y') || ( task =='A')) {
		set_yellow_led_period(ms);
	}
	
	if (( task == 'G') || ( task == 'A' )) {
		// green has a limit on its period.
		if ( ms > 4000) {
			ms = 4000;
		}
		set_green_led_period(ms);
	}
}
