/*
 * SPI.hpp
 *
 * Created: 3/10/2018 11:51:31 AM
 *  Author: Nirdesh
 *   email: 073bex420.nirdesh@pcampus.edu.np
 */

#pragma once

#include "basics/AVR.hpp"
#include "SPI_Params.hpp"
#include "SPI_Modes.hpp"


 /** \class HardwareSPI
 ** \param Relation : A template parameter that decides whether to operate
 **		      HardwareSPI in Master or Slave mode.
 **
 ** \param Mode : A template parameter that decides the mode of operation of
 **               the HardwareSPI class.
 **
 ** \brief Models an actual spi of the AVR microcontroller.
 **
 ** This class is meant to model the actual hardware SPI of the AVR
 ** microcontroller.
 **
 ** To choose the required mode of operation, Policy Based Design Pattern is
 ** used. For details : https://en.wikipedia.org/wiki/Policy-based_design
 **
 ** \note If used as Master, multi-slave is supported in Polling mode.
 **	  Multi-Slaves in Interrupt mode is not yet fully supported.
 **
 ** \note It is recommeded to use Master in Polling mode and the Slave in the
 **	  Interrupt mode. Since SPI can be used at very high frequencies, using
 **	  Master in Polling mode will not create much delay.
 **	  
 ** \note If used as Slave, the SCK(baud) of Master can't be more than F_CPU/4
 **/
template<class Relation, class Mode>
class HardwareSPI
{
private:
	SPI_Params s_;
	const u8 slave_select_;
public:
	HardwareSPI(u8 slave_select) :
		s_(SPI::_REG), slave_select_(slave_select) { }

	~HardwareSPI() { }

	template<u32 baud = 1000000>
	inline u8 initialize() {
		return Relation::template initialize<baud>(s_, slave_select_);
	}

	inline u8 exchange(u8 c) {
		return Mode::exchange(s_, slave_select_, c);
	}

	inline void terminate();

	inline u8 control(u8 config) const;

	inline u8 spi_Irq() { return Mode::spi_Irq(s_, slave_select_); }

	inline bool is_Null() const { return s_.is_Null();  }

};

template<class Relation, class Mode>
inline u8 HardwareSPI<Relation, Mode>::control(u8 config) const
{
	u8 ctrl = (  (config & _BV(SPI::dord))
		   | (config & _BV(SPI::cpol))
		   | (config & _BV(SPI::cpha)) );

	*(s_.spcr_) &= ~ctrl;
	*(s_.spcr_) |= ctrl;

	return 0;
}

template<class Relation, class Mode>
inline void HardwareSPI<Relation, Mode>::terminate()
{
	pin_Mode(SPI::mosi_pin, DDR::OFF);
	pin_Mode(SPI::miso_pin, DDR::OFF);
	pin_Mode(SPI::sck_pin, DDR::OFF);
	pin_Mode(slave_select_, DDR::OFF);

	s_.set_params(SPI::_NULL);
}
