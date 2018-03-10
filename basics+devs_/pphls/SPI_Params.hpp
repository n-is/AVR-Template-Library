/*
 * SPI_Params.hpp
 *
 * Created: 3/10/2018 11:51:31 AM
 *  Author: Nirdesh
 *   email: 073bex420.nirdesh@pcampus.edu.np
 */

#ifndef PPHLS_SPI_PARAMS_HPP_
#define  PPHLS_SPI_PARAMS_HPP_

#include "basics/AVR.hpp"
#include <avr/pgmspace.h>

namespace SPI
{
	const u16 PROGMEM _NULL[] = { 0, 0, 0};
	const u16 PROGMEM _REG[] = { (u16)&SPCR, (u16)&SPSR, (u16)&SPDR };

	const u8 mosi_pin = PB2;
	const u8 miso_pin  = PB3;
	const u8 sck_pin = PB1;

	//Bits of SPCR(Control Register)
	const u8 spr0 = 0;
	const u8 spr1 = 1;
	const u8 cpha = 2;
	const u8 cpol = 3;
	const u8 mstr = 4;
	const u8 dord = 5;
	const u8 spe = 6;
	const u8 spie = 7;

	//Bits of SPSR(Status Register)
	const u8 spi2x = 0;
	const u8 wcol = 6;
	const u8 spif = 7;

	//Bits of SPDR(Data Register)
	const u8 lsb = 0;
	const u8 msb = 7;


	namespace clock {

		const u8 DIV_2 = 0x04;
		const u8 DIV_4 = 0x00;
		const u8 DIV_8 = 0x05;
		const u8 DIV_16 = 0x01;
		const u8 DIV_32 = 0x06;
		const u8 DIV_64 = 0x02;
		const u8 DIV_128 = 0x03;

		const u8 _DEFAULT = DIV_4;
	}

	namespace order {

		const u8 _MSB = 0;
		const u8 _LSB = 1;

		const u8 _DEFAULT = _MSB;
	}

	namespace ckpol {

		const u8 active_low = 0;
		const u8 active_high = 1;
		const u8 pulse_low = 2;
		const u8 pulse_high = 3;

		const u8 _DEFAUT = active_low;
	}
}

struct SPI_Params
{
	volatile u8 * spcr_;
	volatile u8 * spsr_;
	volatile u8 * spdr_;

	template <typename T, size_t N>
	SPI_Params( T (&arr)[N] ) {
		set_params(arr);
	}

	template <typename T, size_t N>
	void set_params( T (&arr)[N] ) {
		 spcr_ = (volatile u8 *)pgm_read_word(arr + 0);
		 spsr_ = (volatile u8 *)pgm_read_word(arr + 1);
		 spdr_ = (volatile u8 *)pgm_read_word(arr + 2);
	}
};

#endif