/************************************
 * file enc : ascii
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef LIMONP_STR_FUNCTS_H
#define LIMONP_STR_FUNCTS_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <map>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory.h>
#include <functional> 
#include <locale>
#include <sstream>
#include <sys/types.h>
#include <iterator>
#include <algorithm>
#include "StdExtension.hpp"

namespace Limonp
{
    using namespace std;
    inline string string_format(const char* fmt, ...) 
    {
        int size = 256;
        std::string str;
        va_list ap;
        while (1) {
            str.resize(size);
            va_start(ap, fmt);
            int n = vsnprintf((char *)str.c_str(), size, fmt, ap);
            va_end(ap);
            if (n > -1 && n < size) {
                str.resize(n);
                return str;
            }
            if (n > -1)
              size = n + 1;
            else
              size *= 2;
        }
        return str;
    }

    template<class T>
        void join(T begin, T end, string& res, const string& connector)
        {
            if(begin == end)
            {
                return;
            }
            stringstream ss;
            ss<<*begin;
            begin++;
            while(begin != end)
            {
                ss << connector << *begin;
                begin ++;
            }
            res = ss.str();
        }

    template<class T>
        string join(T begin, T end, const string& connector)
        {
            string res;
            join(begin ,end, res, connector);
            return res;
        }



    inline bool split(const string& src, vector<string>& res, const string& pattern, size_t offset = 0, size_t len = string::npos)
    {
        if(src.empty())
        {
            return false;
        }
        res.clear();

        size_t start = 0;
        size_t end = 0;
        size_t cnt = 0;
        while(start < src.size() && res.size() < len)
        {
            end = src.find_first_of(pattern, start);
            if(string::npos == end)
            {
                if(cnt >= offset)
                {
                    res.push_back(src.substr(start));
                }
                return true;
            }
            //if(end == src.size() - 1)
            //{
            //    res.push_back("");
            //    return true;
            //}
            if(cnt >= offset)
            {
                res.push_back(src.substr(start, end - start));
            }
            cnt ++;
            start = end + 1;
        }
        return true;
    }

    inline string& upper(string& str)
    {
        transform(str.begin(), str.end(), str.begin(), (int (*)(int))toupper);
        return str;
    }

    inline string& lower(string& str)
    {
        transform(str.begin(), str.end(), str.begin(), (int (*)(int))tolower);
        return str;
    }

    inline std::string &ltrim(std::string &s) 
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

    inline std::string &rtrim(std::string &s) 
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
    }

    inline std::string &trim(std::string &s) 
    {
        return ltrim(rtrim(s));
    }

    inline std::string & ltrim(std::string & s, char x)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::bind2nd(std::equal_to<char>(), x))));
        return s;
    }

    inline std::string & rtrim(std::string & s, char x)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::bind2nd(std::equal_to<char>(), x))).base(), s.end());
        return s;
    }

    inline std::string &trim(std::string &s, char x)
    {
        return ltrim(rtrim(s, x), x);
    }

    inline bool startsWith(const string& str, const string& prefix)
    {
        if(prefix.length() > str.length())
        {
            return false;
        }
        return 0 == str.compare(0, prefix.length(), prefix);
    }

    inline bool endsWith(const string& str, const string& suffix)
    {
        if(suffix.length() > str.length())
        {
            return false;
        }
        return 0 == str.compare(str.length() -  suffix.length(), suffix.length(), suffix);
    }

    inline bool isInStr(const string& str, char ch)
    {
        return str.find(ch) != string::npos;
    }

    inline uint16_t twocharToUint16(char high, char low)
    {
        return (((uint16_t(high) & 0x00ff ) << 8) | (uint16_t(low) & 0x00ff));
    }

    template <class Uint16Container>
    bool utf8ToUnicode(const char * const str, size_t len, Uint16Container& vec)
    {
        if(!str)
        {
            return false;
        }
        char ch1, ch2;
        uint16_t tmp;
        vec.clear();
        for(size_t i = 0;i < len;)
        {
            if(!(str[i] & 0x80)) // 0xxxxxxx
            {
                vec.push_back(str[i]);
                i++;
            }
            else if ((uint8_t)str[i] <= 0xdf && i + 1 < len) // 110xxxxxx
            {
                ch1 = (str[i] >> 2) & 0x07;
                ch2 = (str[i+1] & 0x3f) | ((str[i] & 0x03) << 6 );
                tmp = (((uint16_t(ch1) & 0x00ff ) << 8) | (uint16_t(ch2) & 0x00ff));
                vec.push_back(tmp);
                i += 2;
            }
            else if((uint8_t)str[i] <= 0xef && i + 2 < len)
            {
                ch1 = ((uint8_t)str[i] << 4) | ((str[i+1] >> 2) & 0x0f );
                ch2 = (((uint8_t)str[i+1]<<6) & 0xc0) | (str[i+2] & 0x3f); 
                tmp = (((uint16_t(ch1) & 0x00ff ) << 8) | (uint16_t(ch2) & 0x00ff));
                vec.push_back(tmp);
                i += 3;
            }
            else
            {
                return false;
            }
        }
        return true;
    }
    template <class Uint16Container>
    bool utf8ToUnicode(const string& str, Uint16Container& vec)
    {
        return utf8ToUnicode(str.c_str(), str.size(), vec);
    }

    template <class Uint16ContainerConIter>
    bool unicodeToUtf8(Uint16ContainerConIter begin, Uint16ContainerConIter end, string& res)
    {
        if(begin >= end)
        {
            return false;
        }
        res.clear();
        uint16_t ui;
        while(begin != end)
        {
            ui = *begin;
            if(ui <= 0x7f)
            {
                res += char(ui);
            }
            else if(ui <= 0x7ff)
            {
                res += char(((ui>>6) & 0x1f) | 0xc0);
                res += char((ui & 0x3f) | 0x80);
            }
            else
            {
                res += char(((ui >> 12) & 0x0f )| 0xe0);
                res += char(((ui>>6) & 0x3f )| 0x80 );
                res += char((ui & 0x3f) | 0x80);
            }
            begin ++;
        }
        return true;
    }

    
    template <class Uint16Container>
    bool gbkTrans(const char* const str, size_t len, Uint16Container& vec)
    {
        vec.clear();
        if(!str)
        {
            return false;
        }
        size_t i = 0;
        while(i < len)
        {
            if(0 == (str[i] & 0x80))
            {
                vec.push_back(uint16_t(str[i]));
                i++;
            }
            else
            {
                if(i + 1 < len) //&& (str[i+1] & 0x80))
                {
                    uint16_t tmp = (((uint16_t(str[i]) & 0x00ff ) << 8) | (uint16_t(str[i+1]) & 0x00ff));
                    vec.push_back(tmp);
                    i += 2;
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    }

    template <class Uint16Container>
    bool gbkTrans(const string& str, Uint16Container& vec)
    {
        return gbkTrans(str.c_str(), str.size(), vec);
    }

    template <class Uint16ContainerConIter>
    bool gbkTrans(Uint16ContainerConIter begin, Uint16ContainerConIter end, string& res)
    {
        if(begin >= end)
        {
            return false;
        }
        res.clear();
        //pair<char, char> pa;
        char first, second;
        while(begin != end)
        {
            //pa = uint16ToChar2(*begin);
            first = ((*begin)>>8) & 0x00ff;
            second = (*begin) & 0x00ff;
            if(first & 0x80)
            {
                res += first;
                res += second;
            }
            else
            {
                res += second;
            }
            begin++;
        }
        return true;
    }

    /*
     * format example: "%Y-%m-%d %H:%M:%S"
     */
    inline void getTime(const string& format, string&  timeStr)
    {
        time_t timeNow;
        time(&timeNow);
        timeStr.resize(64);
        size_t len = strftime((char*)timeStr.c_str(), timeStr.size(), format.c_str(), localtime(&timeNow));
        timeStr.resize(len);
    }
}
#endif
