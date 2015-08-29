#ifndef CPPJIEBA_SEGMENTBASE_H
#define CPPJIEBA_SEGMENTBASE_H

#include "TransCode.hpp"
#include "limonp/Logger.hpp"
#include "limonp/NonCopyable.hpp"
#include "limonp/HandyMacro.hpp"
#include "ISegment.hpp"
#include <cassert>


namespace CppJieba {
using namespace limonp;

//const char* const SPECIAL_CHARS = " \t\n";
#ifndef CPPJIEBA_GBK
const Rune SPECIAL_SYMBOL[] = {32u, 9u, 10u, 12290u, 65292u};
#else
const Rune SPECIAL_SYMBOL[] = {32u, 9u, 10u};
#endif

class SegmentBase: public ISegment, public NonCopyable {
 public:
  SegmentBase() {
    LoadSpecialSymbols();
  };
  virtual ~SegmentBase() {
  };
 public:
  virtual void cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res) const = 0;
  virtual bool cut(const string& str, vector<string>& res) const {
    res.clear();

    Unicode unicode;
    unicode.reserve(str.size());

    TransCode::decode(str, unicode);

    Unicode::const_iterator left = unicode.begin();
    Unicode::const_iterator right;

    for(right = unicode.begin(); right != unicode.end(); right++) {
      if(isIn(specialSymbols_, *right)) {
        if(left != right) {
          cut(left, right, res);
        }
        res.resize(res.size() + 1);
        TransCode::encode(right, right + 1, res.back());
        left = right + 1;
      }
    }
    if(left != right) {
      cut(left, right, res);
    }

    return true;
  }
  void cut(Unicode::const_iterator begin, 
                   Unicode::const_iterator end, 
                   vector<string>& res) const {
    vector<Unicode> uRes;
    uRes.reserve(end - begin);
    cut(begin, end, uRes);

    size_t offset = res.size();
    res.resize(res.size() + uRes.size());
    for(size_t i = 0; i < uRes.size(); i ++, offset++) {
      TransCode::encode(uRes[i], res[offset]);
    }
  }
 private:
  void LoadSpecialSymbols() {
    size_t size = sizeof(SPECIAL_SYMBOL)/sizeof(*SPECIAL_SYMBOL);
    for(size_t i = 0; i < size; i ++) {
      specialSymbols_.insert(SPECIAL_SYMBOL[i]);
    }
    assert(specialSymbols_.size());
  }

  unordered_set<Rune> specialSymbols_;

}; // class SegmentBase

} // CppJieba

#endif
