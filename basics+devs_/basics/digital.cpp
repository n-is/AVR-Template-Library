/*
* digital.cpp
*
* Created: 1/20/2018 4:19:13 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/
#include "AVR.hpp"

// Some Helper Functions to be used as function pointer in place of
// inline functions
//static volatile u8 * toDDR (u8 pin)  { return pinToDDR (pin); }
//static volatile u8 * toPORT (u8 pin) { return pinToOutputPort (pin); }
//static volatile u8 * toPIN (u8 pin)  { return pinToInputPort (pin); }

void pinMode(const u8 pin, const u8 pin_mode)
{
        const u8 bit = pinToBit (pin);
        volatile u8 * ddr = pinToDDR (pin);
        volatile u8 * port = pinToOutputPort (pin);

        if( !ddr ) return;

        switch( pin_mode ) {
                case DDR::INPUT: {
                        *ddr &= !(bit);
                }break;

                case DDR::OUTPUT: {
                        *ddr |= bit;
                }break;

                case DDR::PULL_UP: { // || DDR::OFF: {
                        *port |= bit;
                        *ddr &= !(bit);
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

void digitalWrite(const u8 pin, const u8 status)
{
        const u8 bit = pinToBit (pin);
        volatile u8 * port = pinToOutputPort (pin);

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

bool digitalRead(const u8 pin)
{
        const u8 bit = pinToBit (pin);
        volatile u8 * reg = pinToInputPort (pin);

        if( !reg ) return 0;

        return (*reg & (bit));
}
