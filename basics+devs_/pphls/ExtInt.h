#ifndef EXTINT_H_
#define EXTINT_H_

#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL

#include <util/delay.h>

const uint8_t LOW = 0x0;
const uint8_t HIGH = 0x1;
const uint8_t CHANGE = 1;
const uint8_t FALLING = 2;
const uint8_t RISING = 3;
	   
const uint8_t EXTERNAL_NUM_INTERRUPTS = 8;
	 
const uint8_t EXTERNAL_INT_0 = 0;
const uint8_t EXTERNAL_INT_1 = 1;
const uint8_t EXTERNAL_INT_2 = 2;
const uint8_t EXTERNAL_INT_3 = 3;
const uint8_t EXTERNAL_INT_4 = 4;
const uint8_t EXTERNAL_INT_5 = 5;
const uint8_t EXTERNAL_INT_6 = 6;
const uint8_t EXTERNAL_INT_7 = 7;

typedef void (*voidFuncPtr)(void);

void attachInterrupt(uint8_t, void (*)(void), int mode);
void detachInterrupt(uint8_t);

#endif