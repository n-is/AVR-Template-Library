/*
* AVR.hpp
*
* Created: 1/20/2018 4:18:54 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/

#pragma once

#include "ext_hdrs.h"
#include "undefs.h"
#include "typedefs.h"

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



void pin_Mode(u8 pin, u8 mode);
void pin_Write(u8 pin, u8 state);
bool pin_Read(u8 pin);

void port_Mode(u8 port, u8 value);
void port_Write(u8 port, u8 value);
u8 port_Read(u8 port);

/// Converts the pin to appropriate bit
inline u8 pin_To_Bit(u8 pin)
{
        return ( pgm_read_byte( pin_to_bit_mask_PGM + (pin % 8) ) );
}

/// Converts the pin to appropriate output port register
inline volatile u8 * pin_To_Output_Port(u8 pin)
{
        return ( (volatile u8 *)(pgm_read_word( pin_to_port_mask_PGM + (pin / 8) ) ) );
}

/// Converts the pin to appropriate input port register
inline volatile u8 * pin_To_Input_Port(u8 pin)
{
        return ( (volatile u8 *)(pgm_read_word( pin_to_input_port_mask_PGM + (pin / 8) ) ) );
}

/// Converts the pin to appropriate data direction register
inline volatile u8 * pin_To_DDR(u8 pin)
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
