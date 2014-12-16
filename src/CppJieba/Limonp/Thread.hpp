#ifndef LIMONP_THREAD_HPP
#define LIMONP_THREAD_HPP

#include "HandyMacro.hpp"
#include "NonCopyable.hpp"

namespace Limonp
{
    class IThread: NonCopyable
    {
        private:
            pthread_t thread_;
            bool isStarted;
            bool isJoined;
        public:
            IThread(): isStarted(false), isJoined(false)
            {
            }
            virtual ~IThread()
            {
                if(isStarted && !isJoined)
                {
                    LIMONP_CHECK(!pthread_detach(thread_));
                }
            };
        public:
            virtual void run() = 0;
            void start()
            {
                assert(!isStarted);
                LIMONP_CHECK(!pthread_create(&thread_, NULL, worker_, this));
                isStarted = true;
            }
            void join()
            {
                assert(!isJoined);
                LIMONP_CHECK(!pthread_join(thread_, NULL));
                isJoined = true;
            }
        private:
            static void * worker_(void * data)
            {
                IThread * ptr = (IThread* ) data;
                ptr->run();
                return NULL;
            }
    };
}

#endif
