/*
 * PWM_Params.hpp
 *
 * Created: 3/10/2018 3:18:01 AM
 *  Author: RMS
 *   email: 073bex433.rishav@gmail.com
 */

#pragma once

#include "basics/AVR.hpp"


namespace PWM {

	const u16 PROGMEM _NULL[12] = { 0 };

	const u16 PROGMEM _1[] = { (u16)&TCCR1A, (u16)&TCCR1B, (u16)&TCCR1C,
		(u16)&OCR1AL, (u16)&OCR1AH, (u16)&OCR1BL, (u16)&OCR1BH,
		(u16)&OCR1CL, (u16)&OCR1CH, (u16)&ICR1L, (u16)&ICR1H,
		(u16)&TIMSK1 };

	const u16 PROGMEM _3[] = { (u16)&TCCR3A, (u16)&TCCR3B, (u16)&TCCR3C,
		(u16)&OCR3AL, (u16)&OCR3AH, (u16)&OCR3BL, (u16)&OCR3BH,
		(u16)&OCR3CL, (u16)&OCR3CH, (u16)&ICR3L, (u16)&ICR3H,
		(u16)&TIMSK3 };

	const u16 PROGMEM _4[] = { (u16)&TCCR4A, (u16)&TCCR4B, (u16)&TCCR4C,
		(u16)&OCR4AL, (u16)&OCR4AH, (u16)&OCR4BL, (u16)&OCR4BH,
		(u16)&OCR4CL, (u16)&OCR4CH, (u16)&ICR4L, (u16)&ICR4H,
		(u16)&TIMSK4 };

	const u16 PROGMEM _5[] = { (u16)&TCCR5A, (u16)&TCCR5B, (u16)&TCCR5C,
		(u16)&OCR5AL, (u16)&OCR5AH, (u16)&OCR5BL, (u16)&OCR5BH,
		(u16)&OCR5CL, (u16)&OCR5CH, (u16)&ICR5L, (u16)&ICR5H,
		(u16)&TIMSK5 };
}

struct PWM_Params  {

        volatile u8 * tccra_ ;
        volatile u8 * tccrb_ ;
        volatile u8 * tccrc_ ;

        volatile u8 * ocrla_ ;
        volatile u8 * ocrha_ ;
        volatile u8 * ocrlb_ ;
        volatile u8 * ocrhb_ ;
        volatile u8 * ocrlc_ ;
        volatile u8 * ocrhc_ ;

        volatile u8 * icrl_ ;
        volatile u8 * icrh_ ;

        volatile u8 * timsk_ ;

        template <typename T, size_t N>
        PWM_Params(const T (&arr)[N]){
                set_Params(arr);
        }

        template <typename T, size_t N>
        void set_Params(const T (&arr)[N]){

                tccra_ = (volatile u8 *)pgm_read_word(arr + 0);
                tccrb_ = (volatile u8 *)pgm_read_word(arr + 1);
                tccrc_ = (volatile u8 *)pgm_read_word(arr + 2);

                ocrla_ = (volatile u8 *)pgm_read_word(arr + 3);
                ocrha_ = (volatile u8 *)pgm_read_word(arr + 4);
                ocrlb_ = (volatile u8 *)pgm_read_word(arr + 5);
                ocrhb_ = (volatile u8 *)pgm_read_word(arr + 6);
                ocrlc_ = (volatile u8 *)pgm_read_word(arr + 7);
                ocrhc_ = (volatile u8 *)pgm_read_word(arr + 8);

                icrl_ = (volatile u8 *)pgm_read_word(arr + 9);
                icrh_ = (volatile u8 *)pgm_read_word(arr + 10);

                timsk_ = (volatile u8 *)pgm_read_word(arr + 11);
        }

	bool is_Null() const {
		return !(tccra_ || tccrb_ || tccrc_ ||
			 ocrla_ || ocrlb_ || ocrlc_ ||
			 ocrha_ || ocrhb_ || ocrhc_ ||
			 icrl_  || icrh_  || timsk_ );
	}

};
