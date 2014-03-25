/*
 * Controller for the Red LED driven by a cyclic executor released task.
 */
#ifndef RED_LED_H_
#define RED_LED_H_

void init_red_led();

void set_red_led_period(uint16_t ms);

int get_red_toggles();

void clear_red_toggles();

void toggle_red_led_busy_wait();

#endif /* RED_LED_H_ */
