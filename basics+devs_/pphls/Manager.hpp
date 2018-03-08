/*
 * Manager.hpp
 *
 * Created: 3/8/2018 5:23:55 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef PPHLS_MANAGER_HPP_
#define PPHLS_MANAGER_HPP_

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
                        "Unavailable Hardware Requested.");

                if( is_available<H> () ) {
                        hardwares[(u8)H] = 1;
                        return 0;
                }
                log_error ("Hardware requested is already in use.", (u8)H);
                return 1;
        }

        template <Hardware H>
        inline static u8 is_available() {
                return !(hardwares[(u8)H]);
        }

};

#endif /* MANAGER_H_ */