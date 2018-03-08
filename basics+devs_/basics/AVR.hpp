/*
* AVR.hpp
*
* Created: 1/20/2018 4:18:54 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/
#define F_CPU	16000000UL

#ifndef BASICS_AVR_HPP_
#define BASICS_AVR_HPP_

#include <avr/io.h>

#include "pins_2560.h"
#include "undefs.h"

/// Data Directions
namespace DDR {
        const u8 INPUT = 0;
        const u8 OUTPUT = 1;
        const u8 PULL_UP = 2;
        const u8 HIGH = 3;
        const u8 LOW = 4;
        const u8 OFF = PULL_UP;
}

/// Pin States
namespace PIN {
        const u8 LOW = 0;
        const u8 HIGH = 1;
        const u8 TOGGLE = 2;
}



void pinMode(u8 pin, u8 state);
void digitalWrite(u8 pin, u8 state);
bool digitalRead(u8 pin);

/// Converts the pin to appropriate bit
inline const u8 pinToBit(u8 pin) __attribute__((__always_inline__));
const u8 pinToBit(u8 pin)
{
        return ( pgm_read_byte( pin_to_bit_mask_PGM + (pin % 8) ) );
}

/// Converts the pin to appropriate output port register
inline volatile u8 * pinToOutputPort(u8 pin) __attribute__((__always_inline__));
volatile u8 * pinToOutputPort(u8 pin)
{
        return ( (volatile u8 *)(pgm_read_word( pin_to_port_mask_PGM + (pin / 8) ) ) );
}

/// Converts the pin to appropriate input port register
inline volatile u8 * pinToInputPort(u8 pin) __attribute__((__always_inline__));
volatile u8 * pinToInputPort(u8 pin)
{
        return ( (volatile u8 *)(pgm_read_word( pin_to_input_port_mask_PGM + (pin / 8) ) ) );
}

/// Converts the pin to appropriate data direction register
inline volatile u8 * pinToDDR(u8 pin) __attribute__((__always_inline__));
volatile u8 * pinToDDR(u8 pin)
{
        return ( (volatile u8 *)(pgm_read_word( pin_to_ddr_mask_PGM + (pin / 8) ) ) );
}

/* Waiting By Calculation */
#define CLOCK_CYCLES_PER_MICRO_SECOND   ((F_CPU)/1000000L)

inline void nop() { __asm__ volatile ("nop"); }

inline const u32 clockCyclesToMicroSeconds(const u32 clockCycles)
{
        return (const u32)(clockCycles / CLOCK_CYCLES_PER_MICRO_SECOND);
}

inline const u32 microSecondsToClockCycles(const u32 microSeconds)
{
        return (const u32)(microSeconds * CLOCK_CYCLES_PER_MICRO_SECOND);
}

#endif /* BASICS_AVR_HPP_ */