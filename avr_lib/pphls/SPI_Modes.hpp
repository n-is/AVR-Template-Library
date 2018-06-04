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
#include "dtypes/Queue.hpp"

namespace SPI {

	class Master
	{
	public:
		template<u32 baud>
		static inline u8 initialize(const SPI_Params & s, u8 slave_pin)
		{
			static_assert(baud <= 8000000, "More speed requested from SPI!!");

			pin_Mode(SPI::mosi_pin, DDR::OUTPUT);
			pin_Mode(SPI::sck_pin, DDR::OUTPUT);
			pin_Mode(slave_pin, DDR::OUTPUT);
			pin_Mode(SPI::miso_pin, DDR::INPUT);

			*(s.spcr_) = 0x00;

			if (baud >= (F_CPU / 2)) {
				*(s.spsr_) |= _BV(SPI::spi2x);
				*(s.spcr_) |= (SPI::clock::DIV_2);
			}
			else if (baud >= (F_CPU / 4))
				*(s.spcr_) |= (SPI::clock::DIV_4);

			else if (baud >= (F_CPU / 8)) {
				*(s.spsr_) |= _BV(SPI::spi2x);
				*(s.spcr_) |= (SPI::clock::DIV_8);
			}
			else if (baud >= (F_CPU / 16))
				*(s.spcr_) |= (SPI::clock::DIV_16);

			else if (baud >= (F_CPU / 32)) {
				*(s.spsr_) |= _BV(SPI::spi2x);
				*(s.spcr_) |= (SPI::clock::DIV_32);
			}
			else if (baud >= (F_CPU / 64))
				*(s.spcr_) |= (SPI::clock::DIV_64);
			else
				*(s.spcr_) |= (SPI::clock::DIV_128);

			*(s.spcr_) |= _BV(SPI::spe) | _BV(SPI::mstr) | _BV(SPI::spie) | _BV(SPI::cpha);

			return 0;
		}
	};

	class Slave
	{
	public:
		template<u32 baud>
		static inline u8 initialize(const SPI_Params & s, u8 slave_pin)
		{
			static_assert(baud <= 8000000, "More speed requested from SPI!!");

			pin_Mode(SPI::mosi_pin, DDR::INPUT);
			pin_Mode(SPI::miso_pin, DDR::OUTPUT);
			pin_Mode(SPI::sck_pin, DDR::INPUT);
			pin_Mode(slave_pin, DDR::INPUT);

			*(s.spcr_) = _BV(SPI::spe) | _BV(SPI::spie) | _BV(SPI::cpha);

			*(s.spdr_) = 0x00;

			return 0;
		}
	};

	// SPI can be operated in either polling or interrupt mode.
	class Polling
	{
	public:
		static inline u8 exchange(const SPI_Params & s, u8 slave_pin, u8 c) {

			pin_Write(slave_pin, PIN::LOW);

			*(s.spdr_) = c;
			while (!(*(s.spsr_) & (_BV(spif))));

			pin_Write(slave_pin, PIN::HIGH);

			return *(s.spdr_);
		}
	};

	class Master_Interrupt
	{
	private:
		static Queue<u8, buf_size_t, buf_size>
			input_buffer, output_buffer;

		static bool is_first;

	public:
		static inline u8 exchange(const SPI_Params & s, u8 slave_pin, u8 c) {

			u8 data;

			if (is_first) {
				pin_Write(slave_pin, PIN::LOW);
				data = *(s.spdr_);
				is_first = false;
				*(s.spdr_) = c;
			}
			else {
				output_buffer.insert(c);
				data = input_buffer.lookup();
			}

			return data;

		}

		static inline u8 spi_Irq(const SPI_Params & s, u8 slave_pin) {

			input_buffer.insert(*(s.spdr_));
			if (output_buffer.length())
				*(s.spdr_) = output_buffer.lookup();
			else {
				is_first = true;
				pin_Write(slave_pin, PIN::HIGH);
			}

			return 0;
		}
	};

	class Slave_Interrupt
	{
	private:
		static Queue<u8, buf_size_t, buf_size>
			input_buffer, output_buffer;

	public:
		static inline u8 exchange(const SPI_Params & s, u8 slave_pin, u8 c) {

			output_buffer.insert(c);

			return input_buffer.lookup();
		}

		static inline u8 spi_Irq(const SPI_Params & s, u8 slave_pin) {

			input_buffer.insert(*(s.spdr_));

			if (output_buffer.length())
				*(s.spdr_) = output_buffer.lookup();

			return 0;
		}
	};

	Queue<u8, buf_size_t, buf_size> Master_Interrupt::input_buffer, Master_Interrupt::output_buffer;
	bool Master_Interrupt::is_first = true;

	Queue<u8, buf_size_t, buf_size> Slave_Interrupt::input_buffer, Slave_Interrupt::output_buffer;

}

#endif