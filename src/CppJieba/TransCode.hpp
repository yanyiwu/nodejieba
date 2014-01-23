/************************************
 * file enc : utf-8
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef CPPJIEBA_TRANSCODE_H
#define CPPJIEBA_TRANSCODE_H


#include "Limonp/str_functs.hpp"

namespace CppJieba
{

    using namespace Limonp;
    typedef std::vector<uint16_t> Unicode;
    namespace TransCode
    {
        inline bool decode(const string& str, vector<uint16_t>& vec)
        {
#ifdef CPPJIEBA_GBK
            return gbkTrans(str, vec);
#else
            return utf8ToUnicode(str, vec);
#endif
        }

        inline bool encode(vector<uint16_t>::const_iterator begin, vector<uint16_t>::const_iterator end, string& res)
        {
#ifdef CPPJIEBA_GBK
            return gbkTrans(begin, end, res);
#else
            return unicodeToUtf8(begin, end, res);
#endif
        }
        
        inline bool encode(const vector<uint16_t>& uni, string& res)
        {
            return encode(uni.begin(), uni.end(), res);
        }
    }
}

#endif
