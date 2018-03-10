/*
* ExtInt.hpp
*
* Created: 3/9/2018 1:28:57 PM
*  Author: nirdesh
*   email: 073bex420.nirdesh@pcampus.edu.np
*/

#ifndef EXTINT_HPP_
#define EXTINT_HPP_

#include <avr/interrupt.h>
#include <util/delay.h>

#include "basics/AVR.hpp"
#include "../basics/typedefs.h"

typedef void (*voidFuncPtr)(void);

namespace INT {

	const u8 _0 = 0;
	const u8 _1 = 1;
	const u8 _2 = 2;
	const u8 _3 = 3;
	const u8 _4 = 4;
	const u8 _5 = 5;
	const u8 _6 = 6;
	const u8 _7 = 7;

	const u8 _NUM = 8;

        namespace Mode {
	        const u8 low = 0x0;
	        const u8 change = 1;
	        const u8 falling = 2;
	        const u8 rising = 3;
        }

}


static void nothing(void) { }

static volatile voidFuncPtr intFunc[INT::_NUM] = {
	#if (_NUM > 8)
	nothing,
	#endif
	};


template<const u8 interruptNum, voidFuncPtr userFunc, const u8 mode>
void attachInterrupt() {
	static_assert(interruptNum < INT::_NUM, "Interrupt Number Specified Higher Than Available.");

		intFunc[interruptNum] = userFunc;

		switch (interruptNum) {
			case 0:
			EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
			EIMSK |= (1 << INT0);
			break;
			case 1:
			EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
			EIMSK |= (1 << INT1);
			break;
			case 2:
			EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
			EIMSK |= (1 << INT2);
			break;
			case 3:
			EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
			EIMSK |= (1 << INT3);
			break;
			case 4:
			EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
			EIMSK |= (1 << INT4);
			break;
			case 5:
			EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
			EIMSK |= (1 << INT5);
			break;
			case 6:
			EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
			EIMSK |= (1 << INT6);
			break;
			case 7:
			EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
			EIMSK |= (1 << INT7);
			break;
		}

}


template<const u8 interruptNum>
void detachInterrupt() {
	if(interruptNum < INT::_NUM) {

		switch(interruptNum)
		{
			case 0:
			EIMSK &= ~(1 << INT0);
			break;
			case 1:
			EIMSK &= ~(1 << INT1);
			break;
			case 2:
			EIMSK &= ~(1 << INT2);
			break;
			case 3:
			EIMSK &= ~(1 << INT3);
			break;
			case 4:
			EIMSK &= ~(1 << INT4);
			break;
			case 5:
			EIMSK &= ~(1 << INT5);
			break;
			case 6:
			EIMSK &= ~(1 << INT6);
			break;
			case 7:
			EIMSK &= ~(1 << INT7);
			break;
		}
		intFunc[interruptNum] = nothing;
	}
}


ISR(INT0_vect) {
	intFunc[INT::_0]();
}

ISR(INT1_vect) {
	intFunc[INT::_1]();
}

ISR(INT2_vect) {
	intFunc[INT::_2]();
}

ISR(INT3_vect) {
	intFunc[INT::_3]();
}

ISR(INT4_vect) {
	intFunc[INT::_4]();
}

ISR(INT5_vect) {
	intFunc[INT::_5]();
}

ISR(INT6_vect) {
	intFunc[INT::_6]();
}

ISR(INT7_vect) {
	intFunc[INT::_7]();
}


#endif