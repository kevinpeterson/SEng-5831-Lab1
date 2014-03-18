/*******************************************
*
* Header file for Task Code
*
*******************************************/
#ifndef __TASK_H
#define __TASK_H

#include <inttypes.h> //gives us uintX_t
#include "led.h"

extern uint32_t G_redToggles;
extern uint32_t G_greenToggles;
extern uint32_t G_yelloToggles;

// number of empty for loops to eat up about 1 ms
#define FOR_COUNT_10MS 10000

volatile uint32_t __ii;

#define WAIT_10MS { for ( __ii=0; __ii < FOR_COUNT_10MS; __ii++ ); }

void initialize_tasks();

void setPeriod(char task, int ms);

#endif

