/*
 * BasicInterfaces_iters.hpp
 *
 * Created: 2/4/2018 5:39:45 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */

#pragma once

#include "AVR.hpp"
#include "utils/calc.hpp"


template <class Item>
class IIterator;


template <class Item>
class IIterable
{
public:
        virtual Item get_Item_At(const u8 index) const = 0;
        virtual size_t length() const = 0;
        inline virtual IIterator<Item> get_Iterator() const
                __attribute__((__always_inline__));
protected:
        IIterable<Item>() { }
private:
};


template <class Item>
class IIterator
{
public:
        IIterator(const IIterable<Item> * iter):
        iter_(iter), curr_(0) { }

        inline void first() { curr_ = 0; }

        inline void next() { ++curr_; }

        inline bool is_Done() const { return curr_ >= iter_->length(); }

        inline Item current() const { return iter_->get_Item_At(curr_); }

        //~IIterator() { free(iter_); }

protected:
private:
        const IIterable<Item> * iter_;
        u8 curr_;
};

class IWrite
{
public:
        virtual void _write_(const u8 c) const  = 0;

protected:
        IWrite() { }
private:
        IWrite( const IWrite &c ) = delete;
        IWrite& operator=( const IWrite &c ) = delete;

        inline friend void
        operator<<(const IWrite & writer, IIterator<char> & iter) {
                iter.first ();
                while( !iter.is_Done() ) {
                        writer._write_ (iter.current ());
                        iter.next ();
                }
        }

        inline friend void
        operator<<(const IWrite & writer, const IIterable<char> & itble) {
                auto iter = IIterator<char>(&itble);
                writer << iter;
        }

        inline friend void
	operator<<(const IWrite & writer, const char c) {
                writer._write_ (c);
        }

        inline friend void
	operator<<(const IWrite & writer, const char * c) {
                while(*c)
                        writer._write_ (*c++);
        }

        inline friend void
	operator<<(const IWrite & writer, int num) {
                u8 digits[6];
                u8 len = decompose_Number (num, digits);
                for(u8 i = 0; i < len; ++i)
                writer._write_ (digits[i]);
        }

	inline friend void
	operator<<(const IWrite & writer, u16 num) {
		u8 digits[6];
		u8 len = decompose_Number(num, digits);
		for (u8 i = 0; i < len; ++i)
			writer._write_(digits[i]);
	}

        inline friend void
	operator<<(const IWrite & writer, long num) {
                u8 digits[11];
                u8 len = decompose_Number (num, digits);
                for(u8 i = 0; i < len; ++i)
                writer._write_ (digits[i]);
        }

};


template <class Item>
IIterator<Item> IIterable<Item>::get_Iterator() const
{
        return IIterator<Item>(this);
}
