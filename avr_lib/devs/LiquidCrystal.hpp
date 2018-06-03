/*
* LiquidCrystal.hpp
*
* Created: 1/22/2018 7:33:19 PM
*  Author: n-is
*   email: 073bex422.nischal@pcampus.edu.np
*/

#pragma once

#ifndef _LIQUID_CRYSTAL_HPP_
#define _LIQUID_CRYSTAL_HPP_

#include "basics/AVR.hpp"
#include "basics/BasicInterfaces_iters.hpp"


namespace LCD {

        const u8 clear = 0x01;
        const u8 return_home = 0x02;

        const u8 display_off = 0b1000;
        const u8 display_on = 0b1100;
        const u8 cursor_off = 0b1100;
        const u8 cursor_on = 0b1110;
        const u8 cursor_no_blink = 0b1110;
        const u8 cursor_blink = 0b1111;

        const u8 data_length_4_bits = 0b100000;
        const u8 data_length_8_bits = 0b110000;
        const u8 rows_1 = 0b100000;
        const u8 rows_2 = 0b101000;
        const u8 font_8 = 0b100000;
        const u8 font_10 = 0b100100;

}

class LiquidCrystal : public IWrite
{
//variables
public:
protected:
private:
        const u8 res_select_, enable_, data4_, data5_, data6_, data7_;
        static const u8 Y[4];

//functions
public:
	LiquidCrystal(const u8 RS, const u8 E,
                const u8 D4, const u8 D5, const u8 D6, const u8 D7);
	~LiquidCrystal();

        u8 initialize(const u8 column, const u8 row) const;
        void terminate() const;

        void control(const u8 command) const;

        void _write_(const u8 c) const;

        inline void xy(const u8 x, const u8 y) const { control (Y[y] + x); }

protected:
private:
        LiquidCrystal( const LiquidCrystal &c ) = delete;
        LiquidCrystal& operator=( const LiquidCrystal &c ) = delete;

        inline void byte_Command(const u8 byte_cmd) const;
        inline void nibble_Command(const u8 nibble_cmd) const;

        void send_Nibble(const u8 nibble_data) const;

        inline void send(const u8 value) const;

        inline void enable() const;

        inline bool is_Busy() const;

        inline u8 write(const u8 character) const
        __attribute__((__always_inline__));

}; //LiquidCrystal

#endif
