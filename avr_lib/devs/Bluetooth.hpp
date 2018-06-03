/*
* Bluetooth.hpp
*
* Created: 3/6/2018 9:49:56 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/

#pragma once

#include "pphls/HardwareUART.hpp"
#include "basics/BasicInterfaces_iters.hpp"


/** \class Bluetooth
 ** \brief A class that models a bluetooth module.
 **
 ** \param H    : A template parameter to denote the hardware to use for the
 **               bluetooth. Since bluetooth uses UART for data and instruction
 **               transmssion, a valid Hardware name as specified in enum class
 **               Hardware is expected.
 **
 ** \param UART_Mode : A template parameter to denote the mode the UART used
 **		       by the bluetooth for transmission. Both Polling mode
 **		       and the Interrupt mode can be used for this purpose.
 **/
template <Hardware H, class UART_Mode>
class Bluetooth : public IWrite
{
// Data Members
private:
        HardwareUART<UART_Mode> uart_;

//Member Functions
public:
	Bluetooth():
        uart_(HardwareUART<UART_Mode>::template get_Instance<H>()) { }

	~Bluetooth() { terminate(); }

        template <u32 baud>
        inline u8
        initialize(const u8 config = 0b00011000) const {
                return uart_.initialize<baud>(config);
        }

        inline void terminate() { uart_.template terminate<H>(); }

        inline void _write_ (const u8 c) const { transmit (c); }

        inline u8 receive() const { return uart_.receive (); }
        inline u8 transmit(const u8 c) const { return uart_.transmit (c); }

        inline void transmit_Irq() const { uart_.transmit_Irq (); }
        inline void receive_Irq() const { uart_.receive_Irq (); }

        inline u8 control(const u8 config) const {
                return uart_.control (config);
        }

	inline bool is_Null() const {
		return uart_.is_Null();
	}

protected:
private:
	Bluetooth( const Bluetooth &c ) = delete;
	Bluetooth& operator=( const Bluetooth &c ) = delete;

}; //Bluetooth
