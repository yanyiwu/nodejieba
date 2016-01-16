/************************************
 * file enc : utf-8
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef CPPJIEBA_TRANSCODE_H
#define CPPJIEBA_TRANSCODE_H


#include "limonp/StringUtil.hpp"
#include "limonp/LocalVector.hpp"

namespace cppjieba {

using namespace limonp;

typedef uint16_t Rune;
typedef limonp::LocalVector<Rune> Unicode;

namespace TransCode {
inline bool Decode(const string& str, Unicode& res) {
#ifdef CPPJIEBA_GBK
  return gbkTrans(str, res);
#else
  return Utf8ToUnicode(str, res);
#endif
}

inline void Encode(Unicode::const_iterator begin, Unicode::const_iterator end, string& res) {
#ifdef CPPJIEBA_GBK
  gbkTrans(begin, end, res);
#else
  UnicodeToUtf8(begin, end, res);
#endif
}

inline void Encode(const Unicode& uni, string& res) {
  Encode(uni.begin(), uni.end(), res);
}

// compiler is expected to optimized this function to avoid return value copy
inline string Encode(Unicode::const_iterator begin, Unicode::const_iterator end) {
  string res;
  res.reserve(end - begin);
  Encode(begin, end, res);
  return res;
}

inline string Encode(const Unicode& unicode) {
  return Encode(unicode.begin(), unicode.end());
}

// compiler is expected to optimized this function to avoid return value copy
inline Unicode Decode(const string& str) {
  Unicode unicode;
  unicode.reserve(str.size());
  Decode(str, unicode);
  return unicode;
}

inline void Encode(const vector<Unicode>& input, vector<string>& output) {
  output.resize(input.size());
  for (size_t i = 0; i < output.size(); i++) {
    Encode(input[i], output[i]);
  }
}

} // namespace TransCode
} // namespace cppjieba

#endif
