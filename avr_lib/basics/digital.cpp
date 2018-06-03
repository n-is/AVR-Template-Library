/*
* digital.cpp
*
* Created: 1/20/2018 4:19:13 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/

#include "AVR.hpp"

void pin_Mode(const u8 pin, const u8 mode)
{
        const u8 bit = pin_To_Bit (pin);
        volatile u8 * ddr = pin_To_DDR (pin);
        volatile u8 * port = pin_To_Output_Port (pin);

        if( !ddr ) return;

        switch( mode ) {
                case DDR::INPUT: {
                        *ddr &= ~(bit);
                }break;

                case DDR::OUTPUT: {
                        *ddr |= bit;
                }break;

                case DDR::PULL_UP: { // || DDR::OFF: {
                        *port |= bit;
                        *ddr &= ~(bit);
                }break;

                case DDR::HIGH: {
                        *ddr |= bit;
                        *port |= bit;
                }break;

                case DDR::LOW: {
                        *ddr |= bit;
                        *port &= ~(bit);
                }break;
        }
}

void pin_Write(const u8 pin, const u8 status)
{
        const u8 bit = pin_To_Bit (pin);
        volatile u8 * port = pin_To_Output_Port(pin);

        if( !port ) return;

        switch( status ) {
                case PIN::LOW: {
                        *port &= ~(bit);
                }break;

                case PIN::HIGH: {
                        *port |= bit;
                }break;
                case PIN::TOGGLE: {
                        *port ^= bit;
                }break;
        }
}

bool pin_Read(const u8 pin)
{
        const u8 bit = pin_To_Bit (pin);
        volatile u8 * reg = pin_To_Input_Port(pin);

        if( !reg ) return 0;

        return (*reg & (bit));
}


void port_Mode(const u8 port, const u8 value)
{
	volatile u8 * reg = pin_To_DDR(port);

	if (!reg) return;

	*reg = value;
}

void port_Write(const u8 port, const u8 value)
{
	volatile u8 * reg = pin_To_Output_Port(port);

	if (!reg) return;

	*reg = value;
}

u8 port_Read(const u8 port)
{
	volatile u8 * reg = pin_To_Input_Port(port);

	return *reg;
}
