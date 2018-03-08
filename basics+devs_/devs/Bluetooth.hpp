/*
* Bluetooth.hpp
*
* Created: 3/6/2018 9:49:56 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/


#ifndef DEVS_BLUETOOTH_HPP_
#define DEVS_BLUETOOTH_HPP_

#include "pphls/HardwareUART.hpp"
#include "basics/BasicInterfaces_iters.hpp"

template <Hardware H, class Mode>
class Bluetooth : public IWrite
{
// Data Members
private:
        HardwareUART<Mode> uart_;

//Member Functions
public:
	Bluetooth():
        uart_(HardwareUART<Mode>::template getInstance<H>()) { }

	~Bluetooth() { }

        inline u8
        initialize(const u32 baud, const u8 config = 0b00011000) const {
                return uart_.initialize (baud, config);
        }

        inline void terminate() { uart_.terminate (); }

        inline void _write_ (const u8 c) const { transmitt (c); }

        inline u8 receive() const { return uart_.receive (); }
        inline u8 transmitt(const u8 c) const { return uart_.transmitt (c); }

        inline void transmitt_irq() { uart_.transmitt_irq (); }
        inline void receive_irq() { uart_.receive_irq (); }

        inline u8 control(const u8 config) const {
                return uart_.control (config);
        }
protected:
private:
	Bluetooth( const Bluetooth &c );
	Bluetooth& operator=( const Bluetooth &c );

}; //Bluetooth

#endif //DEVS_BLUETOOTH_HPP_
