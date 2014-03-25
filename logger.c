/**
 * A logging implementation to print to the LCD screen.
 */
#include <pololu/orangutan.h>
#include "logger.h"
#include "serial.h"

void log_msg(char* msg, LogLevel level) {
	if(level >= LOG_LEVEL) {
		clear();
		print(msg);
	}
}

