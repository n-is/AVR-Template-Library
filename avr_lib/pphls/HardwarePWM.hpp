/*
* HardwarePWM.hpp
*
* Created : $time$
*  Author : n-is
*   email : 073bex422.nischal@pcampus.edu.np
*/

#pragma once

#include "PWM_Params.hpp"
#include "PWM_Modes.hpp"

#include "Hardware.hpp"
#include "Manager.hpp"


/** \class HardwarePWM
** \param Mode : A template parameter that decides the mode of operation of
**               the HardwarePWM class.
**
** \brief Models an actual pulse width modulation unit of the AVR
**	  microcontroller.
**
** This class is meant to model the actual hardware PWM of the AVR
** microcontroller. Singleton pattern is used so that the client can only
** instantiate and use a fixed number of the object of this HardwarePWM class
** since only a fixed number of hardware PWMs are present in a u-Controller.
** Furthermore, static factory is used to hide the object creation and supress
** the complexity involved in object creation.
**
** To choose the required mode of operation, Policy Based Design Pattern is
** used. For details : https://en.wikipedia.org/wiki/Policy-based_design
**
** \note If the same hardware PWM is initialized multiple times, without
**       terminating it, the Error Logger logs this error.
**
** \note The client should call terminate() to close the PWM if it is no
**       longer required, so that some other client can use the same hardware.
**/
template <class Mode>
class HardwarePWM final : public Mode
{
// Data Member
private:
	PWM_Params pwm_;     //< The registers associated with the PWM

// Member Functions
	template <typename T, size_t N>
	HardwarePWM(const T(&arr)[N]) :
		pwm_(arr) { }

public:
	HardwarePWM(const HardwarePWM && tmp) :
		pwm_(tmp.pwm_) { }

	~HardwarePWM() { }

	template <Hardware H>
	inline static HardwarePWM<Mode> get_Instance() {

		/** If the PWM is already used by some other client, just
		** assign a null PWM to the requesting client. If the Error
		** Logging is enabled, the error is logged when trying to
		** access already used hardware.
		**/
		if (Manager::record<H>())
			return HardwarePWM<Mode>(PWM::_NULL);

		switch (H) {
			case Hardware::PWM_1: {
				return HardwarePWM<Mode>(PWM::_1);
			} break;

			case Hardware::PWM_3: {
				return HardwarePWM<Mode>(PWM::_3);
			} break;

			case Hardware::PWM_4: {
				return HardwarePWM<Mode>(PWM::_4);
			} break;

			case Hardware::PWM_5: {
				return HardwarePWM<Mode>(PWM::_5);
			} break;

			default: {
				return HardwarePWM<Mode>(PWM::_NULL);
			}
		}
	}

	/** A const function to initialize the PWM with provided frequency.
	**
	** \param frequency :
	**		The frequency for the operation of the PWM.
	**		A PWM can only have one frequency for all the channels.
	**
	** \return 0 if initialized successfully else 1.
	**/
	inline u8 initialize(const u16 frequency) const {
		return Mode::initialize(frequency);
	}

	inline void terminate() const {

	}

	inline u8 start() const { return Mode::start(); }
	inline void stop() const { Mode::stop(); }

	template <PWM::Channel C>
	inline void set_Duty(const u16 duty_cycle) const {
		Mode::set_Duty<C>(duty_cycle);
	}

	inline void set_Freq(const u16 frequency) const {
		Mode::set_Freq(frequency);
	}

	inline bool is_Null() const {
		return pwm_.is_Null();
	}

protected:
private:
	HardwarePWM(const HardwarePWM &c) = delete;
	HardwarePWM& operator=(const HardwarePWM &c) = delete;

};
