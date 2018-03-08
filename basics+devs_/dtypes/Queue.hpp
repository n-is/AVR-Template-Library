/*
 * Queue.hpp
 *
 * Created: 3/6/2018 8:29:24 PM
 *  Author: n-is
 *   email: 073bex422.nischal@pcampus.edu.np
 */


#ifndef DTYPES_QUEUE_HPP_
#define DTYPES_QUEUE_HPP_

#include <stddef.h>

typedef u8 queue_size_t;

template <class T, queue_size_t q_size>
class Queue
{
// Data Members
private:
        T queue_[q_size];
        queue_size_t head_, tail_;
        queue_size_t curr_size_;

// Member Functions
public:
        Queue():head_(0), tail_(0), curr_size_(0) { }

        void insert(T elem) {
                ++curr_size_;
                queue_[head_++] = elem;
                head_ %= q_size;
        }

        T lookup() {
                if( curr_size_ ) {
                        --curr_size_;
                        T elem = queue_[tail_++];
                        tail_ %= q_size;
                        return elem;
                }
                return 0;
        }

        queue_size_t length() const { return curr_size_; }
};


#endif /* DTYPES_QUEUE_HPP_ */