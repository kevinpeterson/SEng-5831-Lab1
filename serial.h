/*
 * serial.h
 *
 *  Created on: Mar 18, 2014
 *      Author: root
 */

#ifndef SERIAL_H_
#define SERIAL_H_

void init_serial();

void serial_to_send( char *buffer, int n );

void register_incoming_callback(void (*callback)(char c));


#endif /* SERIAL_H_ */
