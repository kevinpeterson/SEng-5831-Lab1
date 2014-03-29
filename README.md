Timer Experiement Lab Notes
=======================================

Project Stucture
----------------
The project is divided into these major modules:

**lab1.c/h** - Where the cyclic executive is, and where the various experiment conditions are set.

**led.h** - Helper functions for interacting with the LEDs.

**logger.c/h** - Logging/debug functionality (printing to the LCD).

**menu.c/h** - Parses and receieves serial communication commands.

**serial.c/h** - Centrailized serial communication functionality.

**tasks.c/h** - Interprets commands from the menu module and calls the necessary application logic.

**scheduler.c/h** - A simple non-preemptive task scheduler.

**(yellow)|(red)|(green)_led.c/h** - LED functionality to include counting toggles, setting toggle rate, etc.


WCET
----
To create a busy-wait loop that accurately reflected the amount of time, I disassembled the program code and looked for the method ```busy_wait_10ms```.

The function in ```red_led.c```:
```
void busy_wait_10ms() {
	WAIT_10MS;
}
```

with ```WAIT_10MS``` defined in ```tasks.h```:
```
volatile uint32_t __ii;

#define WAIT_10MS { for ( __ii=0; __ii < FOR_COUNT_10MS; __ii++ ); }
```

The results of the disassembly were as follows:
```
000002f6 <busy_wait_10ms>:
     2f6:	a0 e0       	ldi	r26, 0x00	; 0
     2f8:	b0 e0       	ldi	r27, 0x00	; 0
     2fa:	e1 e8       	ldi	r30, 0x81	; 129
     2fc:	f1 e0       	ldi	r31, 0x01	; 1
     2fe:	0c 94 5a 11 	jmp	0x22b4	; 0x22b4 <__prologue_saves__+0x20>
     302:	10 92 51 02 	sts	0x0251, r1
     306:	10 92 52 02 	sts	0x0252, r1
     30a:	10 92 53 02 	sts	0x0253, r1
     30e:	10 92 54 02 	sts	0x0254, r1
     312:	13 c0       	rjmp	.+38     	; 0x33a <busy_wait_10ms+0x44>
     ------------
     314:	80 91 51 02 	lds	r24, 0x0251
     318:	90 91 52 02 	lds	r25, 0x0252
     31c:	a0 91 53 02 	lds	r26, 0x0253
     320:	b0 91 54 02 	lds	r27, 0x0254
     324:	01 96       	adiw	r24, 0x01	; 1
     326:	a1 1d       	adc	r26, r1
     328:	b1 1d       	adc	r27, r1
     32a:	80 93 51 02 	sts	0x0251, r24
     32e:	90 93 52 02 	sts	0x0252, r25
     332:	a0 93 53 02 	sts	0x0253, r26
     336:	b0 93 54 02 	sts	0x0254, r27
     33a:	80 91 51 02 	lds	r24, 0x0251
     33e:	90 91 52 02 	lds	r25, 0x0252
     342:	a0 91 53 02 	lds	r26, 0x0253
     346:	b0 91 54 02 	lds	r27, 0x0254
     34a:	80 31       	cpi	r24, 0x10	; 16
     34c:	27 e2       	ldi	r18, 0x27	; 39
     34e:	92 07       	cpc	r25, r18
     350:	a1 05       	cpc	r26, r1
     352:	b1 05       	cpc	r27, r1
     ---------------
     354:	f8 f2       	brcs	.-66     	; 0x314 <busy_wait_10ms+0x1e>
     356:	e2 e0       	ldi	r30, 0x02	; 2
     358:	0c 94 76 11 	jmp	0x22ec	; 0x22ec <__epilogue_restores__+0x20>
```
I tried to identify the part of the machine instructions actually looped, as that would give the most accurate results. Between instructions 314 and 352 seems to be the actual for loop instructions.


I next counted the instructions within this loop, and consulted the datasheet to find the number of machine instructions needed to execute these commands. I multipled them and added the result:

```
lds:  8 x 2 = 16
adiw: 1 x 2 = 2
adc:  2 x 1 = 2
sts:  4 x 2 = 8
cpi:  1 x 1 = 1
ldi:  1 x 1 = 1
cpc:  3 x 1 = 3
================
              33
```
To find the number of loops needed for 10ms, I divided the CPU clock time by the machine instructions times the desired freqeuncy (100 Hz): 

```
20000000 / (33 * 100) = 6060
```

Resulting in an estimated 6060 loops through the for loop.


Experiment 1
------------
Use your original version of toggling the red LED that uses for-loops. Toggle all 3 at 1Hz. (Do not type in any menu options while you are toggling until the 1 minute is up). How good was your WCET analysis of the for loop? If it is very far off, adjust it. Why did I not want you to use the menu while running the experiment? 

####Results
My WCET was a little bit overestimated. 6060 loops took about 111% more time than I had estimated.
(59 /66) * 6060 = ~5417 -- so this would be a better number based on experiments.

Sending/receiving serial commands would take CPU cycles, which would skew the results.
```
Menu: {TPZ} {RGYA} <int>: ta1000
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 59
G toggles: 66
Y toggles: 66
```

As shown above, 1HZ toggling displays a slower frequency for the green LED.

Experiment 2
------------
Use your software timer to toggle the red LED. Toggle all 3 at 1Hz. Simply observe the final toggle count. All should be about 60 (maybe the red is off by 1). If this is not the case, you probably set something up wrong, and you should fix it. 

####Results
The toggle results below show equal (or almost equal) toggle frequency for all LEDs.
```
Menu: {TPZ} {RGYA} <int>: ta1000
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 59
G toggles: 60
Y toggles: 60
```
 
Experiment 3
------------
Set all LEDs to toggle at 2Hz (500ms). Place a 90ms busy-wait for-loop into the ISR for the green LED. Toggle for 1 minute and record results. Now place a 90ms busy-wait for-loop into the ISR for the yellow LED. Toggle for 1 minute and record results. What did you observe? Did the busy-wait disrupt any of the LEDs? Explain your results. 

####Results
#####Green LED busy-wait
Placing the busy-wait loop in the green LED reduced the red LED frequency by about 1/3. I am assuming that because the busy-wait is in the ISR for the green LED, interrupts are being disabled during that time, and the for the scheduler (which is triggred by an interrupt) is being blocked from releasing the red LED.

The green LED is uneffected as it is running on hardware PWM.

```              
Menu: {TPZ} {RGYA} <int>: ta500
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 97
G toggles: 120
Y toggles: 120
```

#####Yellow LED busy-wait
This is the same effect as above, except more pronounced.

The yellow LED is uneffected because the busy-wait does not effect the yellow LED ISR from happening -- it just introduces a delay within it. The yellow ISR should still trigger at the normal frequency.

```
Menu: {TPZ} {RGYA} <int>: ta500
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 7
G toggles: 120
Y toggles: 120
```

 
Experiment 4
------------
Repeat #3, except use a 110ms busy-wait. You probably won't be able to use the menu functions. If not, report that, and discuss what you observed from the blinking. Explain your results.

####Results
#####Green LED busy-wait
This is similar to the results in experiment 3, but slightly less toggles for the red LED. This seems to make sense.

Comparing experiment 3 / experiment 4
93 toggles is 96% of 97 toggles
90 is 82% of 110ms

I would have expected that increasing the ms delay by a certain percentage would have that same percentage impact on the number of toggles. It is *close*, but not quite what I expected. I was able to use the serial menu commands for this first part of this experiement.
```     
Menu: {TPZ} {RGYA} <int>: ta500
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 93
G toggles: 120
Y toggles: 120
```

#####Yellow LED busy-wait
The serial menu commands were inoperable during this experiment. The red LED was almost completely disabled. Interestingly, this is the first time that introducing the busy-wait in the yellow LED had a noticable effect on the yellow LED frequency.
```
R toggles ~1*
G toggles ~120*
Y toggles ~105*
```
\* menu inoperable, toggles manually counted

Experiment 5
------------
Repeat #3, except use a 510ms busy-wait. Explain your results.

####Results
#####Green LED busy-wait
The yellow and red LEDs are completely disabled, as well as the serial menu. With a 510ms busy-wait, the all CPU time seems to be used in the ISR, and not allowing the red LED to be scheduled by the cyclic executive, or for the yellow ISR to fire.
```
R toggles 0*
G toggles ~120*
Y toggles 0*
```

#####Yellow LED busy-wait
The red LED is completely disabled, as well as the serial menu. Again, the cyclic executive does not have enough CPU cycles to schedule the red LED task. The yellow LED does eventually toggle, as the ISR is at least getting called (and then delayed within it).

If there is a 510ms delay in the yellow LED ISR, that would mean that if nested interrupts aren't turned on, in one minute the ISR would run to completion at most (one minute / 510ms) times, or around ~117 times. The observed toggles is significantly lower than that, so I assume that context swapping and other contention is the factor.

```
R toggles 0*
G toggles ~120*
Y toggles 24*
```
\* menu inoperable, toggles manually counted

Experiment 6
------------
Repeat #5 (i.e. 2Hz toggle with 510ms busy-wait), except place an sei() at the top of the ISR with the for-loop in it. Explain your results.

####Results
#####Green LED busy-wait
With the sei() in the green LED, it allows the yellow LED interrupt to happen (as a nested interrupt), so the yellow LED toggles are back to normal. The scheduler (and the red LED) seems to be disabled. This is probably because with the busy wait and the allowance of nested interrupts, all CPU time is being used in interrupts an not allowing the cyclic executive (and the scheduler) to release the red LED task.
```
R toggles 0*
G toggles ~120*
Y toggles ~120*
```

#####Yellow LED busy-wait
With the busy-wait (and the sei()) in the yellow interrupt, neither the red or the yellow LEDs toggle. I think that the yellow LED ISR is interrupting itself, as the busy-wait time is longer than the ISR period. I assmume that it continues to interrupt itself and never reaches the actual toggle. The scheudler (and the red LED released by it) never has a chance then to release the red LED task.
```
R toggles 0*
G toggles ~120*
Y toggles 0*
```
\* menu inoperable, toggles manually counted
