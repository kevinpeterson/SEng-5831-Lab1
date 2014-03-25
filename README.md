Timer Experiement Lab Results and Notes
=======================================

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


lds: 8 x 2 = 16
adiw: 1 x 2 = 2
adc: 2 x 1 = 2
sts: 4 x 2 = 8
cpi: 1 x 1 = 1
ldi: 1 x 1 = 1
cpc: 3 x 1 = 3
==================
                33
               
20000000 / (33 * 100) = 6060
```

Experiment 1
------------
```
Menu: {TPZ} {RGYA} <int>: ta1000
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 59
G toggles: 66
Y toggles: 66
```

Experiment 2
------------
```
Menu: {TPZ} {RGYA} <int>: ta1000
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 60
G toggles: 61
Y toggles: 60
```
 
Experiment 3
------------
```              
Menu: {TPZ} {RGYA} <int>: ta500
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 97
G toggles: 120
Y toggles: 119
```

```
Menu: {TPZ} {RGYA} <int>: ta500
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 13
G toggles: 120
Y toggles: 120
```

 
Experiment 4
------------
```     
Menu: {TPZ} {RGYA} <int>: ta500
Menu: {TPZ} {RGYA} <int>: za
Menu: {TPZ} {RGYA} <int>: pa
R toggles: 93
G toggles: 120
Y toggles: 120
```

```
R toggles ~1*
G toggles ~120*
Y toggles ~110*
```
\* menu inoperable, toggles manually counted

Experiment 5
------------
```
R toggles 0*
G toggles ~120*
Y toggles 0*
```

```
R toggles 0*
G toggles ~120*
Y toggles 24*
```
\* menu inoperable, toggles manually counted

Experiment 6
------------
```
R toggles 0*
G toggles ~120*
Y toggles ~120*
```

```
R toggles 0*
G toggles ~120*
Y toggles 0*
```
\* menu inoperable, toggles manually counted
