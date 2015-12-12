#ifndef CPPJIEBA_PRE_FILTER_H
#define CPPJIEBA_PRE_FILTER_H

#include "TransCode.hpp"

namespace cppjieba {

//class PreFilterIterator {
// public:
//  PreFilterIterator() {
//  }
//  ~PreFilterIterator() {
//  }
//  
// private:
//  const unordered_set<Rune>& specialSymbols_;
//}; // PreFilterIterator

class PreFilter {
 public:
  struct Range {
    Unicode::const_iterator begin;
    Unicode::const_iterator end;
  }; // struct Range

  PreFilter(const unordered_set<Rune>& symbols, 
        const string& sentence)
    : symbols_(symbols) {
    TransCode::Decode(sentence, sentence_);
    cursor_ = sentence_.begin();
  }
  ~PreFilter() {
  }
  bool HasNext() const {
    return cursor_ != sentence_.end();
  }
  Range Next() {
    Range range;
    range.begin = cursor_;
    while (cursor_ != sentence_.end()) {
      if (IsIn(symbols_, *cursor_)) {
        if (range.begin == cursor_) {
          cursor_ ++;
        }
        range.end = cursor_;
        return range;
      }
      cursor_ ++;
    }
    range.end = sentence_.end();
    return range;
  }
 private:
  Unicode::const_iterator cursor_;
  Unicode sentence_;
  const unordered_set<Rune>& symbols_;
}; // class PreFilter

} // namespace cppjieba

#endif // CPPJIEBA_PRE_FILTER_H
