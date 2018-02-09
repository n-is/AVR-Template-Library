/*
 * Integer.hpp
 *
 * Created: 2/9/2018 2:55:23 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef INTEGER_HPP_
#define INTEGER_HPP_

#include "basics/BasicInterfaces_iters.hpp"


template <class Item>
class Integer : public IIterable<Item>
{
public:
        Integer(Item value) {
                setValue (value);
        }

        inline size_t length () const { return len_; }

        inline Item getItemAt (const u8 index) const {
                return digits_[len_ - index - 1] + '0';
        }

        void setValue(Item value) {
                bool isNeg;
                len_ = 0;
                value_ = value;

                if( value < 0 ) {
                        value = - value;
                        isNeg = true;
                } else
                        isNeg = false;

                do {
                        digits_[len_++] = value % 10;
                        value /= 10;
                } while( value );

                if( isNeg )
                        digits_[len_++] = '-' - '0';
        }

        inline Item getValue() const { return value_; }

protected:
private:
        Item value_;
        u8 digits_[10];
        u8 len_;
};


#endif /* INTEGER_HPP_ */