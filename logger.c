#include <pololu/orangutan.h>

#include "logger.h"
/*
 * logger.c
 *
 *  Created on: Mar 18, 2014
 *      Author: root
 */

void log_msg(char* msg, LogLevel level) {
	if(level >= LOG_LEVEL) {
		clear();
		print(msg);
	}
}

