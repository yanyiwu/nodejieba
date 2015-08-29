#ifndef CPPJIEBA_QUERYSEGMENT_H
#define CPPJIEBA_QUERYSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "limonp/Logger.hpp"
#include "DictTrie.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"
#include "FullSegment.hpp"
#include "MixSegment.hpp"
#include "TransCode.hpp"
#include "DictTrie.hpp"

namespace CppJieba {
class QuerySegment: public SegmentBase {
 public:
  QuerySegment(const string& dict, const string& model, const string& userDict = "", size_t maxWordLen = 4)
    : mixSeg_(dict, model, userDict),
      fullSeg_(mixSeg_.getDictTrie()),
      maxWordLen_(maxWordLen) {
    assert(maxWordLen_);
  }
  QuerySegment(const DictTrie* dictTrie, const HMMModel* model, size_t maxWordLen = 4)
    : mixSeg_(dictTrie, model), fullSeg_(dictTrie), maxWordLen_(maxWordLen) {
  }
  virtual ~QuerySegment() {
  }
  using SegmentBase::cut;
  void cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res) const {
    //use mix cut first
    vector<Unicode> mixRes;
    mixSeg_.cut(begin, end, mixRes);

    vector<Unicode> fullRes;
    for (vector<Unicode>::const_iterator mixResItr = mixRes.begin(); mixResItr != mixRes.end(); mixResItr++) {
      // if it's too long, cut with fullSeg_, put fullRes in res
      if (mixResItr->size() > maxWordLen_) {
        fullSeg_.cut(mixResItr->begin(), mixResItr->end(), fullRes);
        for (vector<Unicode>::const_iterator fullResItr = fullRes.begin(); fullResItr != fullRes.end(); fullResItr++) {
          res.push_back(*fullResItr);
        }

        //clear tmp res
        fullRes.clear();
      } else { // just use the mix result
        res.push_back(*mixResItr);
      }
    }
  }
 private:
  MixSegment mixSeg_;
  FullSegment fullSeg_;
  size_t maxWordLen_;

};
}

#endif
