/*
 * yellow_led.h
 *
 *  Created on: Mar 18, 2014
 *      Author: root
 */

#ifndef YELLOW_LED_H_
#define YELLOW_LED_H_

void init_yellow_led();

void set_yellow_led_period(uint16_t ms);

int get_yellow_toggles();

void clear_yellow_toggles();

#endif /* YELLOW_LED_H_ */
