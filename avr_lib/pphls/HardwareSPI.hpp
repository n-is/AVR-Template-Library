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

template <class Mode>
class HardwareSPI : public Mode
{
private:
	SPI_Params s_;
public:
	template <typename T, size_t N>
	HardwareSPI(T(&arr)[N]) :
		s_(arr) { }

	~HardwareSPI() { }

	template<u32 baud>
	inline u8 initialize() {
		Mode::template initialize<baud>(s_);
		return 0;
	}

	inline u8 exchange(const u8 c);

	inline void terminate();

};

/*
template <class Mode>
template<u32 baud>
inline u8 HardwareSPI<Mode>::initialize()
{
}
*/

template <class Mode>
inline u8 HardwareSPI<Mode>::exchange(const u8 c)
{
	*(s_.spdr_) = c;
	while (!(*(s_.spsr_) & (_BV(SPI::spif))));

	return *(s_.spdr_);
}


//template <class Mode>
//inline u8 HardwareSPI<Mode>::receive()
//{
//	*(s_.spdr_) = 0x00;
//	while (!(*(s_.spsr_) & (_BV(SPI::spif))));
//	return (*(s_.spdr_));
//}


template<class Mode>
inline void HardwareSPI<Mode>::terminate()
{
	Mode::template terminate();
	s_.set_params(SPI::_NULL);
}
