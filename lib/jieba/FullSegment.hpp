#ifndef CPPJIEBA_FULLSEGMENT_H
#define CPPJIEBA_FULLSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "limonp/Logging.hpp"
#include "DictTrie.hpp"
#include "SegmentBase.hpp"
#include "TransCode.hpp"

namespace cppjieba {
class FullSegment: public SegmentBase {
 public:
  FullSegment(const string& dictPath) {
    dictTrie_ = new DictTrie(dictPath);
    isNeedDestroy_ = true;
  }
  FullSegment(const DictTrie* dictTrie)
    : dictTrie_(dictTrie), isNeedDestroy_(false) {
    assert(dictTrie_);
  }
  ~FullSegment() {
    if (isNeedDestroy_) {
      delete dictTrie_;
    }
  }
  void Cut(const string& sentence, 
        vector<string>& words) const {
    PreFilter pre_filter(symbols_, sentence);
    PreFilter::Range range;
    vector<Unicode> uwords;
    uwords.reserve(sentence.size());
    while (pre_filter.HasNext()) {
      range = pre_filter.Next();
      Cut(range.begin, range.end, uwords);
    }
    TransCode::Encode(uwords, words);
  }
  void Cut(Unicode::const_iterator begin, 
        Unicode::const_iterator end, 
        vector<Unicode>& res) const {
    //resut of searching in trie tree
    LocalVector<pair<size_t, const DictUnit*> > tRes;

    //max index of res's words
    int maxIdx = 0;

    // always equals to (uItr - begin)
    int uIdx = 0;

    //tmp variables
    int wordLen = 0;
    assert(dictTrie_);
    vector<struct Dag> dags;
    dictTrie_->Find(begin, end, dags);
    for (size_t i = 0; i < dags.size(); i++) {
      for (size_t j = 0; j < dags[i].nexts.size(); j++) {
        const DictUnit* du = dags[i].nexts[j].second;
        if (du == NULL) {
          if (dags[i].nexts.size() == 1 && maxIdx <= uIdx) {
            res.push_back(Unicode(1, dags[i].rune));
          }
        } else {
          wordLen = du->word.size();
          if (wordLen >= 2 || (dags[i].nexts.size() == 1 && maxIdx <= uIdx)) {
            res.push_back(du->word);
          }
        }
        maxIdx = uIdx + wordLen > maxIdx ? uIdx + wordLen : maxIdx;
      }
      uIdx++;
    }
  }
 private:
  const DictTrie* dictTrie_;
  bool isNeedDestroy_;
};
}

#endif
