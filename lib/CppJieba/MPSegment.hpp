#ifndef CPPJIEBA_MPSEGMENT_H
#define CPPJIEBA_MPSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "limonp/Logger.hpp"
#include "DictTrie.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"

namespace CppJieba {

class MPSegment: public SegmentBase {
 public:
  MPSegment(const string& dictPath, const string& userDictPath = "") {
    dictTrie_ = new DictTrie(dictPath, userDictPath);
    isNeedDestroy_ = true;
    LogInfo("MPSegment init(%s) ok", dictPath.c_str());
  }
  MPSegment(const DictTrie* dictTrie)
    : dictTrie_(dictTrie), isNeedDestroy_(false) {
    assert(dictTrie_);
  }
  virtual ~MPSegment() {
    if(isNeedDestroy_) {
      delete dictTrie_;
    }
  }

  using SegmentBase::cut;
  void cut(Unicode::const_iterator begin , Unicode::const_iterator end, vector<Unicode>& words) const {
    vector<Dag> dags;

    dictTrie_->find(begin, end, dags);

    CalcDP(dags);

    Cut(dags, words);
  }
  bool cut(const string& sentence, 
        vector<string>& words, 
        size_t max_word_len) const {
    Unicode unicode;
    if (!TransCode::decode(sentence, unicode)) {
      return false;
    }
    vector<Unicode> unicodeWords;
    cut(unicode.begin(), unicode.end(), 
          unicodeWords, max_word_len);
    words.resize(unicodeWords.size());
    for (size_t i = 0; i < words.size(); i++) {
      TransCode::encode(unicodeWords[i], words[i]);
    }
    return true;
  }
  void cut(Unicode::const_iterator begin,
           Unicode::const_iterator end,
           vector<Unicode>& words,
           size_t max_word_len) const {
    vector<Dag> dags;
    dictTrie_->find(begin, 
          end, 
          dags,
          max_word_len);
    CalcDP(dags);
    Cut(dags, words);
  }
  const DictTrie* getDictTrie() const {
    return dictTrie_;
  }

  bool isUserDictSingleChineseWord(const Rune & value) const {
    return dictTrie_->isUserDictSingleChineseWord(value);
  }
 private:
  void CalcDP(vector<Dag>& dags) const {
    size_t nextPos;
    const DictUnit* p;
    double val;

    for(vector<Dag>::reverse_iterator rit = dags.rbegin(); rit != dags.rend(); rit++) {
      rit->pInfo = NULL;
      rit->weight = MIN_DOUBLE;
      assert(!rit->nexts.empty());
      for(LocalVector<pair<size_t, const DictUnit*> >::const_iterator it = rit->nexts.begin(); it != rit->nexts.end(); it++) {
        nextPos = it->first;
        p = it->second;
        val = 0.0;
        if(nextPos + 1 < dags.size()) {
          val += dags[nextPos + 1].weight;
        }

        if(p) {
          val += p->weight;
        } else {
          val += dictTrie_->getMinWeight();
        }
        if(val > rit->weight) {
          rit->pInfo = p;
          rit->weight = val;
        }
      }
    }
  }
  void Cut(const vector<Dag>& dags, 
        vector<Unicode>& words) const {
    size_t i = 0;
    while(i < dags.size()) {
      const DictUnit* p = dags[i].pInfo;
      if(p) {
        words.push_back(p->word);
        i += p->word.size();
      } else { //single chinese word
        words.push_back(Unicode(1, dags[i].rune));
        i++;
      }
    }
  }

  const DictTrie* dictTrie_;
  bool isNeedDestroy_;
}; // class MPSegment

} // namespace CppJieba

#endif
