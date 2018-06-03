/*
 * PWM_Modes.h
 *
 * Created: 3/10/2018 5:25:17 AM
 *  Author: Prashant
 */

#pragma once

#include "PWM_Params.hpp"

namespace PWM {

	enum class Channel {
		A,
		B,
		C
	};

	class PWM_Modes
	{
	private:

	public:
		virtual ~PWM_Modes() { }

		virtual u8 initialize(const u16 frequency) const = 0;

		virtual u8 start() const = 0;
		virtual void stop() const = 0;

		template <Channel ch>
		void set_Duty(const u16 duty_cycle) const;

		virtual void set_Freq(const u16 frequency) const = 0;
	};

	class Normal : public PWM_Modes
	{

	};

	class CTC : public PWM_Modes
	{

	};

	class Fast : public PWM_Modes
	{

	};

	class Phase : public PWM_Modes
	{

	};
}
