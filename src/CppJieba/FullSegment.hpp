#ifndef CPPJIEBA_FULLSEGMENT_H
#define CPPJIEBA_FULLSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "Limonp/Logger.hpp"
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
  bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, 
        vector<Unicode>& res) const {
    //resut of searching in trie tree
    DagType tRes;

    //max index of res's words
    int maxIdx = 0;

    // always equals to (uItr - begin)
    int uIdx = 0;

    //tmp variables
    int wordLen = 0;
    assert(dictTrie_);
    for (Unicode::const_iterator uItr = begin; uItr != end; uItr++) {
      //find word start from uItr
      if (dictTrie_->find(uItr, end, tRes, 0)) {
        for(DagType::const_iterator itr = tRes.begin(); itr != tRes.end(); itr++)
          //for (vector<pair<size_t, const DictUnit*> >::const_iterator itr = tRes.begin(); itr != tRes.end(); itr++)
        {
          wordLen = itr->second->word.size();
          if (wordLen >= 2 || (tRes.size() == 1 && maxIdx <= uIdx)) {
            res.push_back(itr->second->word);
          }
          maxIdx = uIdx+wordLen > maxIdx ? uIdx+wordLen : maxIdx;
        }
        tRes.clear();
      } else { // not found word start from uItr
        if (maxIdx <= uIdx) { // never exist in prev results
          //put itr itself in res
          res.push_back(Unicode(1, *uItr));

          //mark it exits
          ++maxIdx;
        }
      }
      ++uIdx;
    }

    return true;
  }

  bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, 
        vector<string>& res) const {
    vector<Unicode> uRes;
    if (!cut(begin, end, uRes)) {
      LogError("get unicode cut result error.");
      return false;
    }

    string tmp;
    for (vector<Unicode>::const_iterator uItr = uRes.begin(); 
          uItr != uRes.end(); uItr++) {
      TransCode::encode(*uItr, tmp);
      res.push_back(tmp);
    }

    return true;
  }
 private:
  const DictTrie* dictTrie_;
  bool isNeedDestroy_;
};
}

#endif
