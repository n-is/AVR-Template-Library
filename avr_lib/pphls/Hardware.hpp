/*
 * Hardware.hpp
 *
 * Created: 3/8/2018 12:16:11 PM
 *  Author: User
 */

#pragma once


enum class Hardware
{
        UART_0,         ///< Uart 0, in arduino is connected to Serial
        UART_1,
        UART_2,
        UART_3,

        TWI_0,

	/// These are 16-bit PWM in m2560
	PWM_1,
	PWM_3,
	PWM_4,
	PWM_5,

        LAST   ///< Just a place-holder for static_assert-ion that the requested
               ///< hardware actually exists.
};
