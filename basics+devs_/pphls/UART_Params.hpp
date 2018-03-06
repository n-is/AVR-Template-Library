/*
 * UART_Params.hpp
 *
 * Created: 3/5/2018 8:11:52 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef PPHLS_UART_PARAMS_HPP_
#define PPHLS_UART_PARAMS_HPP_


enum class Hardware
{
        UART_0,
        UART_1,
        UART_2,
        UART_3
};

namespace UART {

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
        volatile u8 * const ubrrl_;
        volatile u8 * const ubrrh_;
        volatile u8 * const ucsra_;
        volatile u8 * const ucsrb_;
        volatile u8 * const ucsrc_;
        volatile u8 * const udr_;

//protected:
        UART_Params(volatile u8 * ubrrl, volatile u8 * ubrrh,
                volatile u8 * ucsra, volatile u8 * ucsrb,
                volatile u8 * ucsrc, volatile u8 * udr) :
                ubrrl_(ubrrl), ubrrh_(ubrrh), ucsra_(ucsra),
                ucsrb_(ucsrb), ucsrc_(ucsrc), udr_(udr) { }

};


#endif /* PPHLS_UART_PARAMS_HPP_ */