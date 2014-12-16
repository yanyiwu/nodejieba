/*
https://github.com/chenshuo/muduo/blob/master/muduo/base/BlockingQueue.h
*/

#ifndef LIMONP_BLOCKINGQUEUE_HPP
#define LIMONP_BLOCKINGQUEUE_HPP

#include <queue>
#include "BoundedQueue.hpp"
#include "Condition.hpp"

namespace Limonp
{
    template<class T>
        class BlockingQueue: NonCopyable
        {
            public:
                BlockingQueue()
                    : mutex_(), notEmpty_(mutex_), queue_()
                {
                }

                void push(const T& x)
                {
                    MutexLockGuard lock(mutex_);
                    queue_.push(x);
                    notEmpty_.notify(); // wait morphing saves us
                }

                T pop()
                {
                    MutexLockGuard lock(mutex_);
                    // always use a while-loop, due to spurious wakeup
                    while (queue_.empty())
                    {
                        notEmpty_.wait();
                    }
                    assert(!queue_.empty());
                    T front(queue_.front());
                    queue_.pop();
                    return front;
                }

                size_t size() const
                {
                    MutexLockGuard lock(mutex_);
                    return queue_.size();
                }
                bool empty() const
                {
                    return size() == 0;
                }

            private:
                mutable MutexLock mutex_;
                Condition         notEmpty_;
                std::queue<T>     queue_;
        };

    template<typename T>
        class BoundedBlockingQueue : NonCopyable
        {
            public:
                explicit BoundedBlockingQueue(size_t maxSize)
                    : mutex_(),
                    notEmpty_(mutex_),
                    notFull_(mutex_),
                    queue_(maxSize)
                {}

                void push(const T& x)
                {
                    MutexLockGuard lock(mutex_);
                    while (queue_.full())
                    {
                        notFull_.wait();
                    }
                    assert(!queue_.full());
                    queue_.push(x);
                    notEmpty_.notify();
                }

                T pop()
                {
                    MutexLockGuard lock(mutex_);
                    while (queue_.empty())
                    {
                        notEmpty_.wait();
                    }
                    assert(!queue_.empty());
                    T res = queue_.pop();
                    notFull_.notify();
                    return res;
                }

                bool empty() const
                {
                    MutexLockGuard lock(mutex_);
                    return queue_.empty();
                }

                bool full() const
                {
                    MutexLockGuard lock(mutex_);
                    return queue_.full();
                }

                size_t size() const
                {
                    MutexLockGuard lock(mutex_);
                    return queue_.size();
                }

                size_t capacity() const
                {
                    return queue_.capacity();
                }

            private:
                mutable MutexLock          mutex_;
                Condition                  notEmpty_;
                Condition                  notFull_;
                BoundedQueue<T>  queue_;
        };

}

#endif
