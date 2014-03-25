/*
 * Controller for the Green LED driven by hardware PWM
 */
#ifndef GREEN_LED_H_
#define GREEN_LED_H_

void init_green_led();

void set_green_led_period(uint16_t ms);

int get_green_toggles();

void clear_green_toggles();

#endif /* GREEN_LED_H_ */
