/*
 * logger.h
 *
 *  Created on: Mar 18, 2014
 *      Author: root
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#define LOG_LEVEL INFO

typedef enum {
  DEBUG = 0,
  INFO = 1,
  WARN = 2,
  ERROR = 3
} LogLevel;

#define LOG()

void log_msg(char* msg, LogLevel level);

#endif /* LOGGER_H_ */