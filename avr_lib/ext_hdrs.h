/*
* ext_hdrs.h
*
* Created : 5/15/2018 10:30:14 PM
*  Author : n-is
*   email : 073bex422.nischal@pcampus.edu.np
*/

/// Contains all the headers that are to be included from external sources.
/// The headers are included here in order so that this file can be added in
/// any files that require any of the external headers.

#pragma once

/// The frequency of the microcontroller
#define F_CPU	16000000UL
/// This header file contains all the basic function definitions.
#include <avr/io.h>

/// This header file need not actually be included but is preferred, otherwise
/// the intellisense in Visual Studio 2017/Code will not work properly.
/// Note::
///		The header file included here must be the same as for the uC in use.
#ifndef __AVR_ATmega2560__
#	define __AVR_ATmega2560__
#endif
#include "uC/m2560.h"

/// This is for interrupt macros.
#include <avr/interrupt.h>

/// This provides static software delays.
#include <util/delay.h>

/** This part helps to remove intellisense error in visual studio. If this
 ** construct(#ifdef _MSC_VER ... #endif) is used anywhere in the code, it is
 ** to prevent intellisense error.
 ** Note : This is only applicable here because we are using GNU GCC compiler
 **	   instead of Visual C++.
 */
#ifdef _MSC_VER
#define sei()
#define pgm_read_byte(x)	0
#define pgm_read_word(x)	0
#endif
