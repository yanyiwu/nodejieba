/************************************
 * file enc : utf-8
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef CPPJIEBA_TRANSCODE_H
#define CPPJIEBA_TRANSCODE_H


#include "limonp/StringUtil.hpp"
#include "limonp/LocalVector.hpp"

namespace CppJieba {

using namespace limonp;

typedef uint16_t Rune;
typedef limonp::LocalVector<Rune> Unicode;

namespace TransCode {
inline bool decode(const string& str, Unicode& res) {
#ifdef CPPJIEBA_GBK
  return gbkTrans(str, res);
#else
  return utf8ToUnicode(str, res);
#endif
}

inline void encode(Unicode::const_iterator begin, Unicode::const_iterator end, string& res) {
#ifdef CPPJIEBA_GBK
  gbkTrans(begin, end, res);
#else
  unicodeToUtf8(begin, end, res);
#endif
}

inline void encode(const Unicode& uni, string& res) {
  encode(uni.begin(), uni.end(), res);
}

// compiler is expected to optimized this function to avoid return value copy
inline string encode(Unicode::const_iterator begin, Unicode::const_iterator end) {
  string res;
  res.reserve(end - begin);
  encode(begin, end, res);
  return res;
}

inline string encode(const Unicode& unicode) {
  return encode(unicode.begin(), unicode.end());
}

// compiler is expected to optimized this function to avoid return value copy
inline Unicode decode(const string& str) {
  Unicode unicode;
  unicode.reserve(str.size());
  decode(str, unicode);
  return unicode;
}

} // namespace TransCode
} // namespace CppJieba

#endif
