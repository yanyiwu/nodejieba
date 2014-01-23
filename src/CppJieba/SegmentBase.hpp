#ifndef CPPJIEBA_SEGMENTBASE_H
#define CPPJIEBA_SEGMENTBASE_H

#include "TransCode.hpp"
#include "Limonp/logger.hpp"
#include "ISegment.hpp"
#include <cassert>


namespace CppJieba
{
    using namespace Limonp;
    class SegmentBase: public ISegment
    {
        public:
            SegmentBase(){_setInitFlag(false);};
            virtual ~SegmentBase(){};
        protected:
            bool _isInited;
            bool _getInitFlag()const{return _isInited;};
            bool _setInitFlag(bool flag){return _isInited = flag;};
        public:
            operator bool(){return _getInitFlag();};

        public:
            virtual bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const = 0;
            virtual bool cut(const string& str, vector<string>& res)const
            {
                assert(_getInitFlag());
                //if(!_getInitFlag())
                //{
                //    LogError("not inited.");
                //    return false;
                //}
                Unicode unico;
#ifdef NO_FILTER
                if(!TransCode::decode(str, unico))
                {
                    LogFatal("str[%s] decode failed.", str.c_str());
                    return false;
                }
                return cut(unico.begin(), unico.end(), res);
#else
                const char * const cstr = str.c_str();
                uint size = str.size();
                uint offset = 0;
                string subs;
                int ret;
                uint len;
                while(offset < size)
                {
                    const char * const nstr = cstr + offset;
                    uint nsize = size - offset;
                    if(-1 == (ret = filterAscii(nstr, nsize, len)) || 0 == len || len > nsize)
                    {
                        LogFatal("str[%s] illegal.", cstr);
                        return false;
                    }
                    subs.assign(nstr, len);
                    if(!ret)
                    {
                        res.push_back(subs);
                    }
                    else
                    {
                        unico.clear();
                        if(!TransCode::decode(subs, unico))
                        {
                            LogFatal("str[%s] decode failed.", subs.c_str());
                            return false;
                        }
                        cut(unico.begin(), unico.end(), res);
                    }
                    offset += len;
                }
                return true;
#endif
            }
        public:

            /*
             * if char is ascii, count the ascii string's length and return 0;
             * else count the nonascii string's length and return 1;
             * if errors, return -1;
             * */
            static int filterAscii(const char* str, uint len, uint& resLen)
            {
                if(!str || !len)
                {
                    return -1;
                }
                char x = 0x80;
                int resFlag = (str[0] & x ? 1 : 0);
                resLen = 0;
                if(!resFlag)
                {
                    while(resLen < len && !(str[resLen] & x))
                    {
                        resLen ++;
                    }
                }
                else
                {
                    while(resLen < len && (str[resLen] & x))
                    {
#ifdef CPPJIEBA_GBK
                        resLen += 2;
#else
                        resLen ++;
#endif
                    }
                }
                if(resLen > len)
                {
                    return -1;
                }
                return resFlag;
            }

    };
}

#endif
