/*
* LiquidCrystal.cpp
*
* Created: 1/22/2018 7:33:19 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/


#include "LiquidCrystal.hpp"
#include <util/delay.h>

LiquidCrystal::LiquidCrystal
(const u8 RS, const u8 E, const u8 D4, const u8 D5, const u8 D6, const u8 D7):
res_select_(RS), enable_(E), data4_(D4), data5_(D5), data6_(D6), data7_(D7)
{
        pinMode (data4_, DDR::LOW);
        pinMode (data5_, DDR::LOW);
        pinMode (data6_, DDR::LOW);
        pinMode (data7_, DDR::LOW);

        pinMode (res_select_, DDR::LOW);
        pinMode (enable_, DDR::LOW);
} //LiquidCrystal

// default destructor
LiquidCrystal::~LiquidCrystal()
{
} //~LiquidCrystal

u8 LiquidCrystal::initialize(const u8 column, const u8 row) const
{
        _delay_ms (50);
        nibble_command (0x3);
        _delay_us (4200);
        nibble_command (0x3);
        _delay_us (110);
        nibble_command(0x3);
        _delay_us (4200);
        nibble_command (LCD::data_length_4_bits >> 4);

        byte_command (LCD::display_on | LCD::cursor_off | LCD::cursor_no_blink);
        byte_command (LCD::rows_2 | LCD::font_8);
        byte_command (LCD::return_home | LCD::clear);
        _delay_us (1700);
        return 0;
}

void LiquidCrystal::terminate() const
{

}

u8 LiquidCrystal::read() const
{
        return 0;
}

void LiquidCrystal::_write_(const u8 c) const
{
        write (c);
}

inline u8 LiquidCrystal::write(const u8 character) const
{
        digitalWrite (res_select_, PIN::HIGH);
        send (character);
        return 0;
}

void LiquidCrystal::control (const u8 command) const
{
        byte_command (command);
        _delay_us (1700);
}

inline void LiquidCrystal::byte_command(const u8 byte_cmd) const
{
        digitalWrite (res_select_, PIN::LOW);
        send (byte_cmd);
}

inline void LiquidCrystal::send(const u8 value) const
{
        //pinMode (data7_, DDR::INPUT);
        //while( isBusy () );
        //pinMode (data7_, DDR::OUTPUT);

        send_nibble (value >> 4);
        send_nibble (value);
}

inline void LiquidCrystal::enable () const
{
        digitalWrite (enable_, PIN::HIGH);
        _delay_us (1);
        digitalWrite (enable_, PIN::LOW);
}

inline bool LiquidCrystal::isBusy () const
{
        return !digitalRead (data7_);
}

inline void LiquidCrystal::nibble_command (const u8 nibble_cmd) const
{
        digitalWrite (res_select_, PIN::LOW);
        send_nibble (nibble_cmd);
        _delay_us (37);
}

void LiquidCrystal::send_nibble (const u8 nibble_data) const
{
        digitalWrite (data4_, (_BV(0) & nibble_data));
        digitalWrite (data5_, (_BV(1) & nibble_data) >> 1);
        digitalWrite (data6_, (_BV(2) & nibble_data) >> 2);
        digitalWrite (data7_, (_BV(3) & nibble_data) >> 3);

        enable ();
}
