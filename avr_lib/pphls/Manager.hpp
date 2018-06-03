/*
 * Manager.hpp
 *
 * Created: 3/8/2018 5:23:55 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */

#pragma once

#include "basics/AVR.hpp"
#include "Hardware.hpp"
#include "utils/Error_Logger.hpp"


class Manager
{
private:
        static const u8 hardware_no = (u8)(Hardware::LAST);
        static u8 hardwares[hardware_no]; 
public:
        template <Hardware H>
        inline static u8 record() {

                static_assert(H < Hardware::LAST && ((u8)H >= 0),
                                "Hardware Not Available.");

                if( is_Available<H> () ) {
                        hardwares[(u8)H] = 1;
                        return 0;
                }
		// Error
                log_Error ("Hardware in use.", (u8)H);
                return 1;
        }

        template <Hardware H>
        inline static u8 release() {

                static_assert(H < Hardware::LAST && ((u8)H >= 0),
                                "Hardware Not Available.");

                if( !is_Available<H> () ) {
                        hardwares[(u8)H] = 0;
                        return 0;
                }
		// Warning
                log_Error ("Hardware not in use.", (u8)H);
                return 1;
        }

        template <Hardware H>
        inline static u8 is_Available() {
                return !(hardwares[(u8)H]);
        }

};
