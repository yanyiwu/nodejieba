#ifndef CPPJIEBA_LEVELSEGMENT_H
#define CPPJIEBA_LEVELSEGMENT_H

#include "MPSegment.hpp"

namespace cppjieba {

class LevelSegment: public SegmentBase{
 public:
  LevelSegment(const string& dictPath, 
               const string& userDictPath = "")
    : mpSeg_(dictPath, userDictPath) {
  }
  LevelSegment(const DictTrie* dictTrie) 
    : mpSeg_(dictTrie) {
  }
  ~LevelSegment() {
  }

  void Cut(Unicode::const_iterator begin,
        Unicode::const_iterator end, 
        vector<pair<Unicode, size_t> >& res) const {
    res.clear();
    vector<Unicode> words;
    vector<Unicode> smallerWords;
    words.reserve(end - begin);
    mpSeg_.Cut(begin, end, words);
    smallerWords.reserve(words.size());
    res.reserve(words.size());

    size_t level = 0;
    while (!words.empty()) {
      smallerWords.clear();
      for (size_t i = 0; i < words.size(); i++) {
        if (words[i].size() >= 3) {
          size_t len = words[i].size() - 1;
          mpSeg_.Cut(words[i].begin(), words[i].end(), smallerWords, len); // buffer.push_back without clear 
        }
        if (words[i].size() > 1) {
          res.push_back(pair<Unicode, size_t>(words[i], level));
        }
      }

      words.swap(smallerWords);
      level++;
    }
  }

  void Cut(const string& sentence, 
        vector<pair<string, size_t> >& words) const {
    words.clear();
    Unicode unicode;
    TransCode::Decode(sentence, unicode);
    vector<pair<Unicode, size_t> > unicodeWords;
    Cut(unicode.begin(), unicode.end(), unicodeWords);
    words.resize(unicodeWords.size());
    for (size_t i = 0; i < words.size(); i++) {
      TransCode::Encode(unicodeWords[i].first, words[i].first);
      words[i].second = unicodeWords[i].second;
    }
  }

  bool Cut(const string& sentence, 
        vector<string>& res) const {
    vector<pair<string, size_t> > words;
    Cut(sentence, words);
    res.clear();
    res.reserve(words.size());
    for (size_t i = 0; i < words.size(); i++) {
      res.push_back(words[i].first);
    }
    return true;
  }

 private:
  MPSegment mpSeg_;
}; // class LevelSegment

} // namespace cppjieba

#endif // CPPJIEBA_LEVELSEGMENT_H
