/************************************
 * file enc : utf8
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef LIMONP_LOGGER_H
#define LIMONP_LOGGER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <cassert>
#include "io_functs.hpp"
#include "str_functs.hpp"

#define FILE_BASENAME strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

#define LogDebug(fmt, ...) Logger::LoggingF(LL_DEBUG, FILE_BASENAME, __LINE__, fmt, ## __VA_ARGS__)
#define LogInfo(fmt, ...) Logger::LoggingF(LL_INFO, FILE_BASENAME, __LINE__, fmt, ## __VA_ARGS__)
#define LogWarn(fmt, ...) Logger::LoggingF(LL_WARN, FILE_BASENAME, __LINE__, fmt, ## __VA_ARGS__)
#define LogError(fmt, ...) Logger::LoggingF(LL_ERROR, FILE_BASENAME, __LINE__, fmt, ## __VA_ARGS__)
#define LogFatal(fmt, ...) Logger::LoggingF(LL_FATAL, FILE_BASENAME, __LINE__, fmt, ## __VA_ARGS__)



namespace Limonp
{
    using namespace std;
    enum {LL_DEBUG = 0, LL_INFO = 1, LL_WARN = 2, LL_ERROR = 3, LL_FATAL = 4, LEVEL_ARRAY_SIZE = 5, CSTR_BUFFER_SIZE = 1024};
    static const char * LOG_LEVEL_ARRAY[LEVEL_ARRAY_SIZE]= {"DEBUG","INFO","WARN","ERROR","FATAL"};
    static const char * LOG_FORMAT = "%s %s:%d %s %s\n";
    static const char * LOG_TIME_FORMAT = "%Y-%m-%d %H:%M:%S";

    class Logger
    {
        public:
            static bool Logging(uint level, const string& msg, const char* fileName, int lineNo)
            {
                assert(level <= LL_FATAL);
                char buf[CSTR_BUFFER_SIZE];
                time_t timeNow;
                time(&timeNow);
                if(!strftime(buf, sizeof(buf), LOG_TIME_FORMAT, localtime(&timeNow)))
                {
                    fprintf(stderr, "stftime failed.\n");
                    return false;
                }
                fprintf(stderr, LOG_FORMAT, buf, fileName, lineNo,LOG_LEVEL_ARRAY[level], msg.c_str());
                return true;
            }
            static bool LoggingF(uint level, const char* fileName, int lineNo, const string& fmt, ...)
            {
#ifdef LOGGER_LEVEL
                if(level < LOGGER_LEVEL) return true;
#endif
                int size = 256;
                string msg;
                va_list ap;
                while (1) {
                    msg.resize(size);
                    va_start(ap, fmt);
                    int n = vsnprintf((char *)msg.c_str(), size, fmt.c_str(), ap);
                    va_end(ap);
                    if (n > -1 && n < size) {
                        msg.resize(n);
                        break;
                    }
                    if (n > -1)
                      size = n + 1;
                    else
                      size *= 2;
                }
                return Logging(level, msg, fileName, lineNo);
            }
    };
}

#endif
