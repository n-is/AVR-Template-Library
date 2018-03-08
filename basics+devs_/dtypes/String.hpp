/*
 * String.hpp
 *
 * Created: 2/9/2018 6:32:42 AM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef DTYPES_STRING_HPP_
#define DTYPES_STRING_HPP_

#include "basics/BasicInterfaces_iters.hpp"

template <typename T>
constexpr size_t ptr_len(const T * ptr)
{
        return (*ptr)?(1 + ptr_len (ptr + 1)) : 0 ;
}

template <typename T>
constexpr size_t num_len(const T num)
{
        return (num)? (1 + num_len (num / 10)) : 0 ;
}

template <typename T>
constexpr void ptr_copy(T * dest, const T * src)
{
        for(; *src; ++src, ++dest)
                *dest = *src;
}

template <typename T, size_t N>
constexpr void decompose( T num, char (&arr)[N], size_t index = 0 )
{
        do {
                arr[index++] = num % 10;
                num /= 10;
        } while( num );
}

/** String is an array of null-terminated characters. So we can consider String
 ** as a char-iterable array. So String implements IIterable<char> interface.
 ** If needed we can extend this class or modify it to a class template for any
 ** kind of null-terminated array of any data type.

 ** String class is a static length array of characters so the length of the
 ** string can not increase without limit. The limit is 50 characters including
 ** the null character. Since AVR does not contain heap memory by default so
 ** dynamically growing String is not supported by this class.
 **/
class String : public IIterable<char>
{
// Attributes
private:
        char str_ptr_[50];
        size_t len_;

// Methods
public:
        String( const char * c ) {
                setValue (c);
        }

        inline void setValue( const char * c) {
                ptr_copy (str_ptr_, c);
                len_ = ptr_len (c);
        }

        inline size_t length() const { return len_; }

        inline char getItemAt(const u8 index) const { return str_ptr_[index]; }

        //IIterator<Item> getIterator() const;
};


#endif /* DTYPES_STRING_HPP_ */