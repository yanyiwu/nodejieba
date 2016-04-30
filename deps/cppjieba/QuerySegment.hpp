#ifndef CPPJIEBA_QUERYSEGMENT_H
#define CPPJIEBA_QUERYSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "limonp/Logging.hpp"
#include "DictTrie.hpp"
#include "SegmentBase.hpp"
#include "FullSegment.hpp"
#include "MixSegment.hpp"
#include "Unicode.hpp"
#include "DictTrie.hpp"

namespace cppjieba {
class QuerySegment: public SegmentBase {
 public:
  QuerySegment(const string& dict, const string& model, const string& userDict = "", size_t maxWordLen = 4)
    : mixSeg_(dict, model, userDict),
      fullSeg_(mixSeg_.GetDictTrie()),
      maxWordLen_(maxWordLen) {
    assert(maxWordLen_);
  }
  QuerySegment(const DictTrie* dictTrie, const HMMModel* model, size_t maxWordLen = 4)
    : mixSeg_(dictTrie, model), fullSeg_(dictTrie), maxWordLen_(maxWordLen) {
  }
  ~QuerySegment() {
  }
  void Cut(const string& sentence, vector<string>& words, bool hmm = true) const {
    vector<Word> tmp;
    Cut(sentence, tmp, hmm);
    GetStringsFromWords(tmp, words);
  }
  void Cut(const string& sentence, vector<Word>& words, bool hmm = true) const {
    PreFilter pre_filter(symbols_, sentence);
    PreFilter::Range range;
    vector<WordRange> wrs;
    wrs.reserve(sentence.size()/2);
    while (pre_filter.HasNext()) {
      range = pre_filter.Next();
      Cut(range.begin, range.end, wrs, hmm);
    }
    words.clear();
    words.reserve(wrs.size());
    GetWordsFromWordRanges(sentence, wrs, words);
  }
  void Cut(RuneStrArray::const_iterator begin, RuneStrArray::const_iterator end, vector<WordRange>& res, bool hmm) const {
    //use mix Cut first
    vector<WordRange> mixRes;
    mixSeg_.Cut(begin, end, mixRes, hmm);

    vector<WordRange> fullRes;
    for (vector<WordRange>::const_iterator mixResItr = mixRes.begin(); mixResItr != mixRes.end(); mixResItr++) {
      // if it's too long, Cut with fullSeg_, put fullRes in res
      if (mixResItr->Length() > maxWordLen_ && !mixResItr->IsAllAscii()) {
        fullSeg_.Cut(mixResItr->left, mixResItr->right + 1, fullRes);
        for (vector<WordRange>::const_iterator fullResItr = fullRes.begin(); fullResItr != fullRes.end(); fullResItr++) {
          res.push_back(*fullResItr);
        }

        //clear tmp res
        fullRes.clear();
      } else { // just use the mix result
        res.push_back(*mixResItr);
      }
    }
  }
  void SetMaxWordLen(size_t len) {
    maxWordLen_ = len;
  }
  size_t GetMaxWordLen() const {
    return maxWordLen_;
  }
 private:
  bool IsAllAscii(const Unicode& s) const {
   for(size_t i = 0; i < s.size(); i++) {
     if (s[i] >= 0x80) {
       return false;
     }
   }
   return true;
  }
  MixSegment mixSeg_;
  FullSegment fullSeg_;
  size_t maxWordLen_;
}; // QuerySegment

} // namespace cppjieba

#endif
