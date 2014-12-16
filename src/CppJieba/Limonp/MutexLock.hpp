#ifndef LIMONP_MUTEX_LOCK_HPP
#define LIMONP_MUTEX_LOCK_HPP

#include <pthread.h>
#include "NonCopyable.hpp"
#include "HandyMacro.hpp"

namespace Limonp
{
    class MutexLock: NonCopyable
    {
        private:
            pthread_mutex_t mutex_;
        public:
            pthread_mutex_t* getPthreadMutex()
            {
                return &mutex_;
            }
        public:
            MutexLock()
            {
                LIMONP_CHECK(!pthread_mutex_init(&mutex_, NULL));
            }
            ~MutexLock()
            {
                LIMONP_CHECK(!pthread_mutex_destroy(&mutex_));
            }
        private:
            void lock()
            {
                LIMONP_CHECK(!pthread_mutex_lock(&mutex_));
            }
            void unlock()
            {
                LIMONP_CHECK(!pthread_mutex_unlock(&mutex_));
            }
            friend class MutexLockGuard;
    };
    class MutexLockGuard: NonCopyable
    {
        public:
            explicit MutexLockGuard(MutexLock & mutex)
                : mutex_(mutex)
            {
                mutex_.lock();
            }
            ~MutexLockGuard()
            {
                mutex_.unlock();
            }
        private:
            MutexLock & mutex_;
    };
#define MutexLockGuard(x) assert(false);
}

#endif
