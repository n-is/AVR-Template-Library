/*
 * BasicInterfaces_iters.h
 *
 * Created: 2/4/2018 5:39:45 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef BASICINTERFACES_ITERS_HPP_
#define BASICINTERFACES_ITERS_HPP_

#include "AVR.hpp"


class IWrite;
class IRead;
class IStream;
class IBuffer;

template <class Item>
class IIterable;

template <class Item>
class IIterator;


template <class Item>
class IIterable
{
public:
        virtual Item getItemAt(const u8 index) const = 0;
        virtual size_t length() const = 0;
        inline virtual IIterator<Item> getIterator() const
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

        void first() { curr_ = 0; }

        void next() { ++curr_; }

        bool isDone() const { return curr_ >= iter_->length(); }

        Item current() const { return iter_->getItemAt(curr_); }

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
        IWrite( const IWrite &c );
        IWrite& operator=( const IWrite &c );

        template <typename Item>
        friend void
        operator<<(const IWrite & writer, IIterator<Item> & iter) {
                iter.first ();
                while( !iter.isDone() ) {
                        writer._write_ (iter.current ());
                        iter.next ();
                }
        }

        template <typename Item>
        friend void
        operator<<(const IWrite & writer, const IIterable<Item> & itble) {
                auto iter = IIterator<Item>(&itble);
                writer << iter;
        }
};


template <class Item>
IIterator<Item> IIterable<Item>::getIterator() const
{
        return IIterator<Item>(this);
}

#endif /* BASICINTERFACES_ITERS_HPP_ */