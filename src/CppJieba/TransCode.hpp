/************************************
 * file enc : utf-8
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef CPPJIEBA_TRANSCODE_H
#define CPPJIEBA_TRANSCODE_H


#include "Limonp/StringUtil.hpp"
#include "Limonp/LocalVector.hpp"

namespace CppJieba
{

    using namespace Limonp;
    typedef uint16_t UnicodeValueType;
    typedef Limonp::LocalVector<UnicodeValueType> Unicode;
    namespace TransCode
    {
        inline bool decode(const string& str, Unicode& res)
        {
#ifdef CPPJIEBA_GBK
            return gbkTrans(str, res);
#else
            return utf8ToUnicode(str, res);
#endif
        }

        inline bool encode(Unicode::const_iterator begin, Unicode::const_iterator end, string& res)
        {
#ifdef CPPJIEBA_GBK
            return gbkTrans(begin, end, res);
#else
            return unicodeToUtf8(begin, end, res);
#endif
        }
        
        inline bool encode(const Unicode& uni, string& res)
        {
            return encode(uni.begin(), uni.end(), res);
        }
    }
}

#endif
