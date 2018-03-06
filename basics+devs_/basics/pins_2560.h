/*
* pins_2560.h
*
* Created: 1/20/2018 2:44:33 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/


#ifndef BASICS_PINS_2560_H_
#define BASICS_PINS_2560_H_

#include <avr/io.h>
#include <avr/pgmspace.h>

#define _ATMEGA_2560_

#include "typedefs.h"

#define _BV( bit )	(1 << (bit))

#define NOT_A_PORT 0
#define NOT_A_DDR  0
#define NOT_A_PIN  0

// The registers in these arrays should be placed in
// alphabetical order since the pins are defined alphabetically.

const u16 PROGMEM pin_to_ddr_mask_PGM[] = {
        ( u16 )&DDRA,
        ( u16 )&DDRB,
        ( u16 )&DDRC,
        ( u16 )&DDRD,
        ( u16 )&DDRE,
        ( u16 )&DDRF,
        ( u16 )&DDRG,
        ( u16 )&DDRH,
        NOT_A_DDR,
        ( u16 )&DDRJ,
        ( u16 )&DDRK,
        ( u16 )&DDRL
};

const u16 PROGMEM pin_to_port_mask_PGM[] = {
        ( u16 )&PORTA,
        ( u16 )&PORTB,
        ( u16 )&PORTC,
        ( u16 )&PORTD,
        ( u16 )&PORTE,
        ( u16 )&PORTF,
        ( u16 )&PORTG,
        ( u16 )&PORTH,
        NOT_A_PORT,
        ( u16 )&PORTJ,
        ( u16 )&PORTK,
        ( u16 )&PORTL
};

const u16 PROGMEM pin_to_input_port_mask_PGM[] = {
        ( u16 )&PINA,
        ( u16 )&PINB,
        ( u16 )&PINC,
        ( u16 )&PIND,
        ( u16 )&PINE,
        ( u16 )&PINF,
        ( u16 )&PING,
        ( u16 )&PINH,
        NOT_A_PIN,
        ( u16 )&PINJ,
        ( u16 )&PINK,
        ( u16 )&PINL
};

const u8 PROGMEM pin_to_bit_mask_PGM[] = {
        _BV(0),
        _BV(1),
        _BV(2),
        _BV(3),
        _BV(4),
        _BV(5),
        _BV(6),
        _BV(7)
};


#endif /* BASICS_PINS_2560_H_ */
