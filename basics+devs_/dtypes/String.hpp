/*
 * String.hpp
 *
 * Created: 2/9/2018 6:32:42 AM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef STRING_HPP_
#define STRING_HPP_

#include "basics/BasicInterfaces_iters.hpp"

template <typename T>
size_t len(const T * ptr)
{
        u8 length = 0;
        while(*ptr++) ++length;
        return length;
}

template <typename T>
void copy(T * dest, const T * src)
{
        for(; *src; ++src, ++dest)
                *dest = *src;
}


template <class Item>
class String : public IIterable<Item>
{
public:
        String( const Item * c ) {
                copy (str_ptr_, c);
                len_ = len (c);
        }

        size_t length() const { return len_; }

        Item getItemAt(const u8 index) const { return str_ptr_[index]; }

        //IIterator<Item> getIterator() const;

private:
        Item str_ptr_[50];
        size_t len_;
};


#endif /* STRING_HPP_ */