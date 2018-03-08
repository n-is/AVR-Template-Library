/*
 * UART_Params.hpp
 *
 * Created: 3/5/2018 8:11:52 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef PPHLS_UART_PARAMS_HPP_
#define PPHLS_UART_PARAMS_HPP_

#include <avr/pgmspace.h>
#include "Hardware.hpp"

namespace UART {

        const u16 PROGMEM _NULL[] = { 0, 0, 0, 0, 0, 0};

        const u16 PROGMEM _0[] = { (u16)&UBRR0L, (u16)&UBRR0H, (u16)&UCSR0A,
                                   (u16)&UCSR0B, (u16)&UCSR0C, (u16)&UDR0 };

        const u16 PROGMEM _1[] = { (u16)&UBRR1L, (u16)&UBRR1H, (u16)&UCSR1A,
                                   (u16)&UCSR1B, (u16)&UCSR1C, (u16)&UDR1 };

        const u16 PROGMEM _2[] = { (u16)&UBRR2L, (u16)&UBRR2H, (u16)&UCSR2A,
                                   (u16)&UCSR2B, (u16)&UCSR2C, (u16)&UDR2 };

        const u16 PROGMEM _3[] = { (u16)&UBRR3L, (u16)&UBRR3H, (u16)&UCSR3A,
                                   (u16)&UCSR3B, (u16)&UCSR3C, (u16)&UDR3 };

        const u8 rxcie = 7;
        const u8 udrie = 5;

        const u8 rx_en = 4;
        const u8 tx_en = 3;

        const u8 upm   = 4;
        const u8 usbs  = 3;
        const u8 ucsz  = 1;

        const u8 udre  = 5;
        const u8 rxc   = 7;

        typedef u8      buf_size_t;
        const buf_size_t tx_buf_size = 32;
        const buf_size_t rx_buf_size = 32;

        // Configuration is in the following format :
        // 0b   00            000              00             0;
        //   ---^^---     ----^^^----     -----^^----     ----^----
        //   reserved     data_length     parity_bits     stop_bits
        //
        // data_length : Length of the data in the frame
        // parity_bits : A bit added at the end to denote parity
        // stop_bits   : bits added to show the end of the frame
        //

        namespace stop {
                const u8 _1 = 0b0;
                const u8 _2 = 0b1;
        }

        namespace parity {
                const u8 none = 0x00;
                const u8 even = 0b100;
                const u8 odd  = 0b110;
        }

        namespace data_len {
                const u8 _5 = 0x00;
                const u8 _6 = 0b001000;
                const u8 _7 = 0b010000;
                const u8 _8 = 0b011000;
        }
}

struct UART_Params
{
        volatile u8 * ubrrl_;
        volatile u8 * ubrrh_;
        volatile u8 * ucsra_;
        volatile u8 * ucsrb_;
        volatile u8 * ucsrc_;
        volatile u8 * udr_;

        template <typename T, size_t N>
        UART_Params( const T (&arr)[N] ) {
                set_params (arr);
        }

        template <typename T, size_t N>
        inline void set_params( const T (&name)[N] ) {
                ubrrl_ = (volatile u8 *)pgm_read_word(name + 0);
                ubrrh_ = (volatile u8 *)pgm_read_word(name + 1);
                ucsra_ = (volatile u8 *)pgm_read_word(name + 2);
                ucsrb_ = (volatile u8 *)pgm_read_word(name + 3);
                ucsrc_ = (volatile u8 *)pgm_read_word(name + 4);
                udr_   = (volatile u8 *)pgm_read_word(name + 5);
        }

};


#endif /* PPHLS_UART_PARAMS_HPP_ */