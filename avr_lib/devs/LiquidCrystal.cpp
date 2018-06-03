/*
* LiquidCrystal.cpp
*
* Created: 1/22/2018 7:33:19 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/

#include "LiquidCrystal.hpp"
#include <util/delay.h>

const u8 LiquidCrystal::Y[] = {0x80, 0xC0, 0x94, 0xD4};

LiquidCrystal::LiquidCrystal
(const u8 RS, const u8 E, const u8 D4, const u8 D5, const u8 D6, const u8 D7):
res_select_(RS), enable_(E), data4_(D4), data5_(D5), data6_(D6), data7_(D7)
{
        pin_Mode(data4_, DDR::LOW);
	pin_Mode(data5_, DDR::LOW);
	pin_Mode(data6_, DDR::LOW);
	pin_Mode(data7_, DDR::LOW);

	pin_Mode(res_select_, DDR::LOW);
	pin_Mode(enable_, DDR::LOW);
} //LiquidCrystal

// default destructor
LiquidCrystal::~LiquidCrystal()
{
} //~LiquidCrystal

u8 LiquidCrystal::initialize(const u8 column, const u8 row) const
{
        _delay_ms (50);
        nibble_Command (0x3);
        _delay_us (4200);
        nibble_Command (0x3);
        _delay_us (110);
        nibble_Command(0x3);
        _delay_us (4200);
        nibble_Command (LCD::data_length_4_bits >> 4);

        byte_Command (LCD::display_on | LCD::cursor_off | LCD::cursor_no_blink);
        byte_Command (LCD::rows_2 | LCD::font_8);
        byte_Command (LCD::return_home | LCD::clear);
        _delay_us (1700);
        return 0;
}

void LiquidCrystal::terminate() const
{
	pin_Mode(data4_, DDR::OFF);
	pin_Mode(data5_, DDR::OFF);
	pin_Mode(data6_, DDR::OFF);
	pin_Mode(data7_, DDR::OFF);
	pin_Mode(enable_, DDR::OFF);
	pin_Mode(res_select_, DDR::OFF);
}

void LiquidCrystal::_write_(const u8 c) const
{
        write (c);
}

inline u8 LiquidCrystal::write(const u8 character) const
{
	pin_Write(res_select_, PIN::HIGH);
        send (character);
        return 0;
}

void LiquidCrystal::control (const u8 command) const
{
        byte_Command (command);
        _delay_us (1700);
}

inline void LiquidCrystal::byte_Command(const u8 byte_cmd) const
{
	pin_Write(res_select_, PIN::LOW);
        send (byte_cmd);
}

inline void LiquidCrystal::send(const u8 value) const
{
        /** Well, it seems there is no need to wait for lcd. */
        //pin_mode (data7_, DDR::INPUT);
        //while( isBusy () );
        //pin_mode (data7_, DDR::OUTPUT);

        send_Nibble (value >> 4);
        send_Nibble (value);
}

inline void LiquidCrystal::enable () const
{
	pin_Write(enable_, PIN::HIGH);
        _delay_us (1);
	pin_Write(enable_, PIN::LOW);
}

inline bool LiquidCrystal::is_Busy () const
{
        return !pin_Read (data7_);
}

inline void LiquidCrystal::nibble_Command (const u8 nibble_cmd) const
{
	pin_Write(res_select_, PIN::LOW);
        send_Nibble (nibble_cmd);
        _delay_us (37);
}

void LiquidCrystal::send_Nibble (const u8 nibble_data) const
{
	pin_Write(data4_, (_BV(0) & nibble_data));
	pin_Write(data5_, (_BV(1) & nibble_data) >> 1);
	pin_Write(data6_, (_BV(2) & nibble_data) >> 2);
	pin_Write(data7_, (_BV(3) & nibble_data) >> 3);

        enable ();
}
