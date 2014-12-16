#ifndef LIMONP_BOUNDED_QUEUE_HPP
#define LIMONP_BOUNDED_QUEUE_HPP

#include <vector>
#include <fstream>
#include <cassert>

namespace Limonp
{
    using namespace std;
    template<class T>
        class BoundedQueue
        {
            private:
                size_t head_;
                size_t tail_;
                size_t size_;
                const size_t capacity_;
                vector<T> circular__buffer;
            public:
                explicit BoundedQueue(size_t capacity): capacity_(capacity), circular__buffer(capacity)
                {
                    head_ = 0;
                    tail_ = 0;
                    size_ = 0;
                    assert(capacity_);
                }
                ~BoundedQueue(){}
            public:
                void clear()
                {
                    head_ = 0;
                    tail_ = 0;
                    size_ = 0;
                }
                bool empty() const
                {
                    return !size_;
                }
                bool full() const
                {
                    return capacity_ == size_;
                }
                size_t size() const
                {
                    return size_;
                }
                size_t capacity() const
                {
                    return capacity_;
                }

                void push(const T& t)
                {
                    assert(!full());
                    circular__buffer[tail_] = t;
                    tail_ = (tail_ + 1) % capacity_;
                    size_ ++;
                }

                T pop()
                {
                    assert(!empty());
                    size_t oldPos = head_;
                    head_ = (head_ + 1) % capacity_;
                    size_ --;
                    return circular__buffer[oldPos];
                }

        };
}

#endif
