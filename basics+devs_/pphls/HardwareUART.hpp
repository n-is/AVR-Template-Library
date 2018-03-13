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
        virtual u8 transmitt(const char c) const = 0;
};

/** \class HardwareUART
 ** \param Mode : A template parameter that decides the mode of operation of
 **               the HardwareUART class.
 **
 ** \brief Models an actual uart of the AVR microcontroller.
 **
 ** This class is meant to model the actual hardware UART of the AVR
 ** microcontroller. Singleton pattern is used so that the client can only
 ** instantiate and use a fixed number of the object of this HardwareUART class
 ** since only a fixed number of hardware UARTs are present in a u-Controller.
 ** Furthermore, static factory is used to hide the object creation and supress
 ** the complexity involved in object creation.
 **
 ** To choose the required mode of operation, Policy Based Design Pattern is
 ** used. For details : https://en.wikipedia.org/wiki/Policy-based_design
 **
 ** \note If the same hardware UART is initialized multiple times, without
 **       terminating it, the Error Logger logs this error.
 **
 ** \note The client should call terminate() to close the UART if it is no
 **       longer required, so that some other client can use the same hardware.
 **/
template <class Mode>
class HardwareUART : public Communication, public Mode
{
// Data Member
private:
        UART_Params u_;     ///< The registers associated with the UART

// Member Functions

        template <typename T, size_t N>
        HardwareUART( const T (&arr)[N] ):
        u_(arr) { }

public:
        HardwareUART( const HardwareUART && tmp) :
        u_(tmp.u_) { }

        ~HardwareUART();

        template <Hardware H>
        inline static HardwareUART<Mode> getInstance() {

                /** If the UART is already used by some other client, just
                 ** assign a null UART to the requesting client. If the Error
                 ** Logging is enabled, the error is logged when trying to
                 ** access already used hardware.
                 **/
                if( Manager::record<H> () )
                        return HardwareUART<Mode>(UART::_NULL);

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

        /** A const function to initialize the UART with provided baud rate and
         ** configuration. A default configuration (config = data_len::_8 |
         ** parity::none | stop_bits::_1) is provided if the configuration is
         ** not specified.
         ** \param baud  : A template parameter that specifies the baud rate of
         **                the UART transmission. Baud rate can only be some
         **                specified values. The baud rate specified is checked
         **                against the baud rates for most AVRs as specified in
         **                the function is_baud_available(). If the baud you are
         **                trying to use is within the specification of AVR but
         **                not in the list, feel free to change the list.
         **                The baud is checked at compile time so any error is
         **                reported at compile time.
         **
         ** \param config: The configuration for the operation of the UART.
         **                Number of stop bits, the parity bits and the data
         **                length is client-configurable. The available choices
         **                are presented in the UART-namespace. The choices can
         **                be Or-ed to get the effect of multiple configurations
         **                at once.
         **
         ** \return 0 if initialized successfully else 1.
         **/
        template <u32 baud>
        inline u8
        initialize(const u8 config = 0b00011000) const;

        template <Hardware H>
        inline void terminate();

        inline u8 receive() const override {
                return const_cast<HardwareUART<Mode> *>(this)->receive_non_const ();
        }

        inline u8 transmitt(const char c) const override {
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

protected:
private:
        HardwareUART( const HardwareUART &c );
        HardwareUART& operator=( const HardwareUART &c );

        template <u32 baud>
        inline void basic_init(const u8 config)
                const __attribute__((__always_inline__));

        inline u8 receive_non_const() { return Mode::receive(u_); }

        inline u8 transmitt_non_const(const char c) {
                return Mode::transmitt(u_, c);
        }

        template <u32 baud>
        inline void check_baud() const;

}; //HardwareUART

/*******************************************************************/
/* Below are the definitions of function templates declared above. */
/*******************************************************************/

// default destructor
template <class Mode>
HardwareUART<Mode>::~HardwareUART<Mode>()
{
        u_.set_params (UART::_NULL);
} //~HardwareUART

constexpr u16 ubrr(const u32 baud)
{
        return ((F_CPU / baud / 16) - 1);
}

template <class Mode>
template <u32 baud>
inline void
HardwareUART<Mode>::basic_init(const u8 config) const
{
        u16 ubrr_val = ubrr(baud);

        /* -*- Setting Baud Rate -*- */
        *(u_.ubrrh_) = (u8)(ubrr_val >> 8);
        *(u_.ubrrl_) = (u8)ubrr_val;

        control (config);
}

template <class Mode>
template <u32 baud>
u8 HardwareUART<Mode>::initialize(const u8 config) const
{
        check_baud<baud>();
        // Initially, the basic initialization that is needed, whether the UART
        // is operated in the Polling mode or by the Interrupt mode is done.
        basic_init<baud>(config);
        // Then the initialization according to the mode, the UART is operated
        // in, is done.
        return Mode::initialize(u_);
}

template <class Mode>
template <Hardware H>
void HardwareUART<Mode>::terminate()
{
        /* Release the hardware if it is actually recorded else do nothing.
         * Checking a few parameters if they are null is enough.
         */
        if( u_.ucsra_ || u_.ucsrb_ ) {
                Manager::release<H>();
                u_.set_params (UART::_NULL);
        }
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

template <u32 baud>
constexpr bool is_baud_available()
{
      return ( baud == 2400     ||
               baud == 4800     ||
               baud == 9600     ||
               baud == 14400    ||
               baud == 19200    ||
               baud == 28800    ||
               baud == 38400    ||
               baud == 57600    ||
               baud == 76800    ||
               baud == 115200   ||
               baud == 230400   ||
               baud == 250000   ||
               baud == 500000   ||
               baud == 1000000     );
}


template <class Mode>
template <u32 baud>
void HardwareUART<Mode>::check_baud() const
{
        /* Check if the baud entered is a valid baud rate. Give Compile-time
         * error if an invalid baud rate is asked.
         */
        static_assert(is_baud_available<baud>(), "Requested Baud Rate is not "
                        "available.");
}

#endif //PPHLS_HARDWAREUART_HPP_
