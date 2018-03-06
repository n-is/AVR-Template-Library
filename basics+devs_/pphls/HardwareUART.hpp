/*
* HardwareUART.hpp
*
* Created: 2/9/2018 3:36:42 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/


#ifndef PPHLS_HARDWAREUART_HPP_
#define PPHLS_HARDWAREUART_HPP_

#include "basics/AVR.hpp"
#include "UART_Params.hpp"
#include "UART_Modes.hpp"

/** Since AVR is a low speed micro-controller so the communication in the AVR
 ** will be slow. Any class that will implement this interface must provide
 ** the transmission of 8-bit long data i.e a character.
 **/
class Communication
{
public:
        virtual u8 _receive_() = 0;
        virtual u8 _transmitt_(const u8 c) = 0;
};

template <class Mode>
class HardwareUART : public Communication, public Mode
{
// Data Member
private:
        UART_Params u;
// Member Functions
public:
        HardwareUART(volatile u8 * ubrrl, volatile u8 * ubrrh,
                volatile u8 * ucsra, volatile u8 * ucsrb,
                volatile u8 * ucsrc, volatile u8 * udr) :
                u(ubrrl, ubrrh, ucsra, ucsrb, ucsrc, udr) { }

        ~HardwareUART();

        u8 initialize(const u32 baud, const u8 config = 0b00011000) const;
        void terminate();

        u8 _receive_() override { return Mode::receive(u); }
        u8 _transmitt_(const u8 c) override { return Mode::transmitt(u, c); }

        void transmitt_irq() { Mode::transmitt_irq(u); }
        void receive_irq() { Mode::receive_irq(u); }

        u8 control(const u8 config) const;

protected:
private:
        HardwareUART( const HardwareUART &c );
        HardwareUART& operator=( const HardwareUART &c );

        inline void basic_init(const u32 baud, const u8 config)
                const __attribute__((__always_inline__));

}; //HardwareUART

/*******************************************************************/
/* Below are the definitions of function templates declared above. */
/*******************************************************************/

// default destructor
template <class Mode>
HardwareUART<Mode>::~HardwareUART<Mode>()
{
} //~HardwareUART

constexpr u16 ubrr(const u32 baud)
{
        return ((F_CPU / 16 / baud) - 1);
}

template <class Mode>
inline void
HardwareUART<Mode>::basic_init(const u32 baud, const u8 config) const
{
        u16 ubrr_val = ubrr(baud);

        /* -*- Setting Baud Rate -*- */
        *(u.ubrrh_) = (u8)(ubrr_val >> 8);
        *(u.ubrrl_) = (u8)ubrr_val;

        control (config);
}

template <class Mode>
u8 HardwareUART<Mode>::initialize(const u32 baud, const u8 config) const
{
        // Initially, the basic initialization that is needed, whether the UART
        // is operated in the Polling mode or by the Interrupt mode is done.
        basic_init(baud, config);
        // Then the initialization according to the mode, the UART is operated
        // in, is done.
        return Mode::initialize(u);
}

template <class Mode>
u8 HardwareUART<Mode>::control (const u8 config) const
{
        // All the configurations that are required by the user can be set up
        // in the UCSRCn register of the avr. Most useful configurations are
        // available through the flags provided in the UART_Params.hpp file.
        *(u.ucsrc_) |= ((config & UART::stop::_2) << UART::usbs)
                |  (((config & UART::parity::odd) >> 1) << UART::upm)
                |  (((config & UART::data_len::_8) >> 3) << UART::ucsz);

        return 0;
}


#endif //PPHLS_HARDWAREUART_HPP_
