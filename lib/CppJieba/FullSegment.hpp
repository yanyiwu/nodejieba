#ifndef CPPJIEBA_FULLSEGMENT_H
#define CPPJIEBA_FULLSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "limonp/Logger.hpp"
#include "DictTrie.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"
#include "TransCode.hpp"

namespace CppJieba {
class FullSegment: public SegmentBase {
 public:
  FullSegment(const string& dictPath) {
    dictTrie_ = new DictTrie(dictPath);
    isNeedDestroy_ = true;
    LogInfo("FullSegment init %s ok", dictPath.c_str());
  }
  FullSegment(const DictTrie* dictTrie)
    : dictTrie_(dictTrie), isNeedDestroy_(false) {
    assert(dictTrie_);
  }
  virtual ~FullSegment() {
    if(isNeedDestroy_) {
      delete dictTrie_;
    }
  }
  using SegmentBase::cut;
  virtual void cut(Unicode::const_iterator begin, 
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
    dictTrie_->find(begin, end, dags);
    for (size_t i = 0; i < dags.size(); i++) {
      for (size_t j = 0; j < dags[i].nexts.size(); j++) {
        const DictUnit* du = dags[i].nexts[j].second;
        if (du == NULL) {
          continue;
        }
        wordLen = du->word.size();
        if (wordLen >= 2 || (dags[i].nexts.size() == 1 && maxIdx <= uIdx)) {
          res.push_back(du->word);
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
