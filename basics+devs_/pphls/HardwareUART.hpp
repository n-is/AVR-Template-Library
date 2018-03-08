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
#include "Manager.hpp"

/** Since AVR is a low speed micro-controller so the communication in the AVR
 ** will be slow. Any class that will implement this interface must provide
 ** the transmission of 8-bit long data i.e a character.
 **/
class Communication
{
public:
        virtual u8 receive() const = 0;
        virtual u8 transmitt(const u8 c) const = 0;
};

template <class Mode>
class HardwareUART : public Communication, public Mode
{
// Data Member
private:
        UART_Params u_;
// Member Functions
public:
        template <typename T, size_t N>
        HardwareUART( const T (&arr)[N] ):
        u_(arr) { }

        HardwareUART( const HardwareUART && tmp) :
        u_(tmp.u_) { }

        ~HardwareUART();

        inline u8
        initialize(const u32 baud, const u8 config = 0b00011000) const;
        inline void terminate();
        inline u8 receive() const override {
                return const_cast<HardwareUART<Mode> *>(this)->receive_non_const ();
        }

        inline u8 transmitt(const u8 c) const override {
                return const_cast<HardwareUART<Mode> *>(this)->transmitt_non_const (c);
        }

        inline void transmitt_irq() { Mode::transmitt_irq(u_); }
        inline void receive_irq() { Mode::receive_irq(u_); }

        inline void tx_on()  const { *(u_.ucsrb_) |=  UART::tx_en; }
        inline void tx_off() const { *(u_.ucsrb_) &= ~UART::tx_en; }
        inline void rx_on()  const { *(u_.ucsrb_) |=  UART::rx_en; }
        inline void rx_off() const { *(u_.ucsrb_) &= ~UART::rx_en; }
        inline void flush()  const { *(u_.udr_) = 0; }

        inline u8 control(const u8 config) const;

        template <Hardware H>
        inline static HardwareUART<Mode> getInstance() {

                Manager::record<H> ();

                static_assert(H == Hardware::UART_0 || H == Hardware::UART_1 ||
                                H == Hardware::UART_2 || H == Hardware::UART_3,
                                "Non-existing UART requested.");

                switch( H ) {
                        case Hardware::UART_0 : {
                                return HardwareUART<Mode>(UART::_0);
                        } break;

                        case Hardware::UART_1 : {
                                return HardwareUART<Mode>(UART::_1);
                        } break;

                        case Hardware::UART_2 : {
                                return HardwareUART<Mode>(UART::_2);
                        } break;

                        case Hardware::UART_3 : {
                                return HardwareUART<Mode>(UART::_3);
                        } break;

                        default : {
                                return HardwareUART<Mode>(UART::_NULL);
                        }
                }
        }

protected:
private:
        //HardwareUART( const HardwareUART &c );
        HardwareUART& operator=( const HardwareUART &c );

        inline void basic_init(const u32 baud, const u8 config)
                const __attribute__((__always_inline__));

        inline u8 receive_non_const() { return Mode::receive(u_); }

        inline u8 transmitt_non_const(const u8 c) {
                return Mode::transmitt(u_, c);
        }

}; //HardwareUART

/*******************************************************************/
/* Below are the definitions of function templates declared above. */
/*******************************************************************/

// default destructor
template <class Mode>
HardwareUART<Mode>::~HardwareUART<Mode>()
{
        terminate ();
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
        *(u_.ubrrh_) = (u8)(ubrr_val >> 8);
        *(u_.ubrrl_) = (u8)ubrr_val;

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
        return Mode::initialize(u_);
}

template <class Mode>
void HardwareUART<Mode>::terminate()
{
        u_.set_params (UART::_NULL);
}

template <class Mode>
u8 HardwareUART<Mode>::control (const u8 config) const
{
        // All the configurations that are required by the user can be set up
        // in the UCSRCn register of the avr. Most useful configurations are
        // available through the flags provided in the UART_Params.hpp file.
        *(u_.ucsrc_) |= ((config & UART::stop::_2) << UART::usbs)
                |  (((config & UART::parity::odd) >> 1) << UART::upm)
                |  (((config & UART::data_len::_8) >> 3) << UART::ucsz);

        return 0;
}


#endif //PPHLS_HARDWAREUART_HPP_
