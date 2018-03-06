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

/** This constexpr function gives the length of an array at compile time so
 ** there is no need to worry about the space and time complexity for this
 ** function at run time.
 **/
template <typename T, size_t N>
constexpr size_t arraySize( const T(&name)[N] )
{
        return N;
}


#endif /* UTILS_CALC_HPP_ */