/*
 * calc.hpp
 *
 * Created: 2/9/2018 6:23:45 AM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef UTILS_CALC_HPP_
#define UTILS_CALC_HPP_

#include <stddef.h>

/** A constexpr function that gives the length of an array at compile time.
 **
 ** \param arr  a reference to an array.
 ** \return     size of the array.
 **/
template <typename T, size_t N>
constexpr size_t arraySize( const T(&arr)[N] )
{
        return N;
}

/** A function template taking two arguments and returning a u8 value.
 ** It decomposes a number into it's digits and fill the array.
 **
 ** \param num  an integral type argument(u8, u16, int, long, ...).
 ** \param arr  a refrence to an array.
 ** \return     length of the number passed(+1 if negative)
 **/
template <typename T, size_t N>
u8 decompose_number( T num, u8 (&arr)[N] )
{
        bool is_neg;
        u8 length = 0;
        u8 digits[10];          ///< A temporary array to hold the array of
                                ///< digits in reverse order.
        if( num < 0 ) {
                is_neg = true;
                num = -num;
        } else
                is_neg = false;

        /** A loop to fill up the array(in reverse order). */
        do {
                digits[length++] = num % 10;
                num /= 10;
        } while( num );

        /** Enter '-' sign if the input number was negative. */
        if( is_neg )
                digits[length++] = '-' - '0';

        /** Fill the input array in the reverse order of the digits[] array
         ** so that the number are filled in order.
         **/
        for( u8 i = 0; i < length; ++i )
                arr[i] = digits[length - i - 1] + '0';

        return length;
}


#endif /* UTILS_CALC_HPP_ */