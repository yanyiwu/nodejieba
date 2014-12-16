/*
 * https://github.com/chenshuo/muduo/blob/master/muduo/base/Condition.h
 */

#ifndef LIMONP_CONDITION_HPP
#define LIMONP_CONDITION_HPP

#include "MutexLock.hpp"

namespace Limonp
{
    class Condition : NonCopyable
    {
        public:
            explicit Condition(MutexLock& mutex)
                : mutex_(mutex)
            {
                LIMONP_CHECK(!pthread_cond_init(&pcond_, NULL));
            }

            ~Condition()
            {
                LIMONP_CHECK(!pthread_cond_destroy(&pcond_));
            }

            void wait()
            {
                LIMONP_CHECK(!pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
            }

            void notify()
            {
                LIMONP_CHECK(!pthread_cond_signal(&pcond_));
            }

            void notifyAll()
            {
                LIMONP_CHECK(!pthread_cond_broadcast(&pcond_));
            }

        private:
            MutexLock& mutex_;
            pthread_cond_t pcond_;
    };

}

#endif
