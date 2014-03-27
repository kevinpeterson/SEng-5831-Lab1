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
#define FOR_COUNT_10MS 6060

volatile uint32_t __ii;

#define WAIT_10MS { for ( __ii=0; __ii < FOR_COUNT_10MS; __ii++ ); }

volatile uint32_t __jj;

#define WAIT_10MS_TIMES(TENS) { for ( __jj=0; __jj < TENS; __jj++ ) { WAIT_10MS; } }

void initialize_tasks();

void setPeriod(char task, int ms);

#endif

