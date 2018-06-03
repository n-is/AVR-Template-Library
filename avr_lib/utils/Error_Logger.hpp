/*
 * Error_Logger.hpp
 *
 * Created: 3/8/2018 7:04:52 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */

#pragma once

#include "basics/typedefs.h"

//extern template Bluetooth<H,M> uart0;

//extern typename Bluetooth<Hardware::UART_0, UART::Interrupt_Mode> uart0;

/** Logs the error occured during program execution.
 ** We can output the error to the terminal through UART Interface or log it in
 ** a file for later use.
 **/
void log_Error(const char * err, u8 err_code);
