#ifndef CPPJIEBA_SEGMENTBASE_H
#define CPPJIEBA_SEGMENTBASE_H

#include "limonp/Logging.hpp"
#include "PreFilter.hpp"
#include <cassert>


namespace cppjieba {

//const char* const SPECIAL_CHARS = " \t\n，。";
const Rune SPECIAL_SYMBOL[] = {32u, 9u, 10u, 65292u, 12290u};

using namespace limonp;

class SegmentBase {
 public:
  SegmentBase() {
    LoadSpecialSymbols();
  }
  ~SegmentBase() {
  }

 protected:
  void LoadSpecialSymbols() {
    size_t size = sizeof(SPECIAL_SYMBOL)/sizeof(*SPECIAL_SYMBOL);
    for (size_t i = 0; i < size; i ++) {
      symbols_.insert(SPECIAL_SYMBOL[i]);
    }
    assert(symbols_.size());
  }
  unordered_set<Rune> symbols_;
}; // class SegmentBase

} // cppjieba

#endif
