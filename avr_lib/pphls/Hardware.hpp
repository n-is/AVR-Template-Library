/*
 * Hardware.hpp
 *
 * Created: 3/8/2018 12:16:11 PM
 *  Author: User
 */

#pragma once


enum class Hardware
{
        UART_0,         ///< Uart 0, in arduino it is connected to Serial
        UART_1,
        UART_2,
        UART_3,

        TWI_0,

        LAST   ///< Just a place-holder for static_assertion that the requested
               ///< hardware actually exists.
};
