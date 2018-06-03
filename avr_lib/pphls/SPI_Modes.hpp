/*
* SPI_Modes.hpp
*
* Created: 3/10/2018 11:51:31 AM
*  Author: Nirdesh
*   email: 073bex420.nirdesh@pcampus.edu.np
*/

#ifndef PPHLS_SPI_MODES_HPP
#define PPHLS_SPI_MODES_HPP

#include "SPI_Params.hpp"

namespace SPI {

	class Master
	{
	public:
		~Master() { }

		template<u32 baud>
		inline u8 initialize(const SPI_Params & s) const
		{
			pin_Mode(SPI::mosi_pin, DDR::OUTPUT);
			pin_Mode(SPI::miso_pin, DDR::INPUT);
			pin_Mode(SPI::sck_pin, DDR::OUTPUT);

			*(s.spcr_) = 0;

			if (baud >= (F_CPU / 2))
				*(s.spcr_) |= (SPI::clock::DIV_2);
			else if (baud >= (F_CPU / 4))
				*(s.spcr_) |= (SPI::clock::DIV_4);
			else if (baud >= (F_CPU / 8))
				*(s.spcr_) |= (SPI::clock::DIV_8);
			else if (baud >= (F_CPU / 16))
				*(s.spcr_) |= (SPI::clock::DIV_16);
			else if (baud >= (F_CPU / 32))
				*(s.spcr_) |= (SPI::clock::DIV_32);
			else if (baud >= (F_CPU / 64))
				*(s.spcr_) |= (SPI::clock::DIV_64);
			else
				*(s.spcr_) |= (SPI::clock::DIV_128);

			*(s.spcr_) |= _BV(SPI::spe) | _BV(SPI::mstr);

			return 0;
		}

		inline void terminate()
		{
			pin_Mode(SPI::mosi_pin, DDR::OFF);
			pin_Mode(SPI::miso_pin, DDR::OFF);
			pin_Mode(SPI::sck_pin, DDR::OFF);
		}
	};


	class Slave
	{
	public:
		inline u8 initialize(const SPI_Params & s) const
		{
			pin_Mode(SPI::mosi_pin, DDR::INPUT);
			pin_Mode(SPI::miso_pin, DDR::OUTPUT);
			pin_Mode(SPI::sck_pin, DDR::INPUT);
			*(s.spcr_) |= _BV(SPI::spe);

			return 0;
		}

		inline void terminate()
		{
			pin_Mode(SPI::mosi_pin, DDR::OFF);
			pin_Mode(SPI::miso_pin, DDR::OFF);
			pin_Mode(SPI::sck_pin, DDR::OFF);
		}

	};
}

#endif