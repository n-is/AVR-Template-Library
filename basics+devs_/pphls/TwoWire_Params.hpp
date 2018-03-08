/*
 * TwoWire_Params.hpp
 *
 * Created: 3/8/2018 12:13:17 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef PPHLS_TWO_WIRE_PARAMS_HPP_
#define PPHLS_TWO_WIRE_PARAMS_HPP_

#include <avr/pgmspace.h>
#include "Hardware.hpp"

namespace TWI {

        const u16 PROGMEM _NULL[] = {0, 0, 0, 0, 0, 0};

        const u16 PROGMEM _0[] = {(u16)&TWBR, (u16)&TWCR, (u16)&TWSR,
                                        (u16)&TWDR, (u16)&TWAR, (u16)&TWAMR};

        // Bits of TWCR(Control Register)
        const u8 twie = 0;
        const u8 twen = 2;
        const u8 twwc = 3;
        const u8 twsto = 4;
        const u8 twsta = 5;
        const u8 twea = 6;
        const u8 twint = 7;

        // Bits of TWSR(Status Register)
        const u8 twps0 = 0;
        const u8 twps1 = 1;
        const u8 tws3 = 3;
        const u8 tws4 = 4;
        const u8 tws5 = 5;
        const u8 tws6 = 6;
        const u8 tws7 = 7;

        // Conditions and corresponding value of TWI status registers
        const u8 started    = 0x08;    // Start condition transmitted
        const u8 slave_addw = 0x18;    // SLA+W transmitted, ACK received
        const u8 slave_addr = 0x40;    // SLA+R transmitted, ACK received
        const u8 data       = 0x28;    // Data transmitted, ACK received
        const u8 rep_start  = 0x10;    // Repeated start condition transmitted

}

struct TwoWire_Params
{
        volatile u8 * twbr_;
        volatile u8 * twcr_;
        volatile u8 * twsr_;
        volatile u8 * twdr_;
        volatile u8 * twar_;
        volatile u8 * twamr_;

        template <size_t N>
        TwoWire_Params( u8 (&arr)[N] ) {
                static_assert(N == 6, "Invalid Array sent to TWI.");
                set_params(arr);
        }

        template <size_t N>
        void set_params( u8 (&arr)[N] ) {
                twbr_  = (volatile u8 *)pgm_read_word(arr + 0);
                twcr_  = (volatile u8 *)pgm_read_word(arr + 1);
                twsr_  = (volatile u8 *)pgm_read_word(arr + 2);
                twdr_  = (volatile u8 *)pgm_read_word(arr + 3);
                twar_  = (volatile u8 *)pgm_read_word(arr + 4);
                twamr_ = (volatile u8 *)pgm_read_word(arr + 5);
        }

};


#endif /* PPHLS_TWO_WIRE_PARAMS_HPP_ */