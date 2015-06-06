#ifndef CPPJIEBA_DICT_TRIE_HPP
#define CPPJIEBA_DICT_TRIE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include <stdint.h>
#include <cmath>
#include <limits>
#include "Limonp/StringUtil.hpp"
#include "Limonp/Logger.hpp"
#include "TransCode.hpp"
#include "Trie.hpp"



namespace CppJieba {
using namespace Limonp;
const double MIN_DOUBLE = -3.14e+100;
const double MAX_DOUBLE = 3.14e+100;
const size_t DICT_COLUMN_NUM = 3;
const char* const UNKNOWN_TAG = "";

class DictTrie {
 public:

  DictTrie() {
    trie_ = NULL;
    minWeight_ = MAX_DOUBLE;
  }
  DictTrie(const string& dictPath, const string& userDictPath = "") {
    new (this) DictTrie();
    init(dictPath, userDictPath);
  }
  ~DictTrie() {
    if(trie_) {
      delete trie_;
    }
  }

  void init(const string& dictPath, const string& userDictPath = "") {
    if(trie_ != NULL) {
      LogFatal("trie already initted");
    }
    loadDict_(dictPath);
    calculateWeight_(nodeInfos_);
    minWeight_ = findMinWeight_(nodeInfos_);

    if(userDictPath.size()) {
      double maxWeight = findMaxWeight_(nodeInfos_);
      loadUserDict_(userDictPath, maxWeight, UNKNOWN_TAG);
    }
    shrink_(nodeInfos_);
    trie_ = createTrie_(nodeInfos_);
    assert(trie_);
  }

  const DictUnit* find(Unicode::const_iterator begin, Unicode::const_iterator end) const {
    return trie_->find(begin, end);
  }
  bool find(Unicode::const_iterator begin, Unicode::const_iterator end, DagType& dag, size_t offset = 0) const {
    return trie_->find(begin, end, dag, offset);
  }
  void find(
    Unicode::const_iterator begin,
    Unicode::const_iterator end,
    vector<SegmentChar>& res
  ) const {
    trie_->find(begin, end, res);
  }
  bool isUserDictSingleChineseWord(const Unicode::value_type& word) const {
    return isIn(userDictSingleChineseWord_, word);
  }
  double getMinWeight() const {
    return minWeight_;
  };


 private:
  Trie * createTrie_(const vector<DictUnit>& dictUnits) {
    assert(dictUnits.size());
    vector<Unicode> words;
    vector<const DictUnit*> valuePointers;
    for(size_t i = 0 ; i < dictUnits.size(); i ++) {
      words.push_back(dictUnits[i].word);
      valuePointers.push_back(&dictUnits[i]);
    }

    Trie * trie = new Trie(words, valuePointers);
    return trie;
  }
  void loadUserDict_(const string& filePath, double defaultWeight, const string& defaultTag) {
    ifstream ifs(filePath.c_str());
    if(!ifs.is_open()) {
      LogFatal("file %s open failed.", filePath.c_str());
    }
    string line;
    DictUnit nodeInfo;
    vector<string> buf;
    size_t lineno;
    for(lineno = 0; getline(ifs, line); lineno++) {
      buf.clear();
      split(line, buf, " ");
      if(buf.size() < 1) {
        LogFatal("split [%s] result illegal", line.c_str());
      }
      if(!TransCode::decode(buf[0], nodeInfo.word)) {
        LogError("line[%u:%s] illegal.", lineno, line.c_str());
        continue;
      }
      if(nodeInfo.word.size() == 1) {
        userDictSingleChineseWord_.insert(nodeInfo.word[0]);
      }
      nodeInfo.weight = defaultWeight;
      nodeInfo.tag = (buf.size() == 2 ? buf[1] : defaultTag);
      nodeInfos_.push_back(nodeInfo);
    }
    LogInfo("load userdict[%s] ok. lines[%u]", filePath.c_str(), lineno);
  }
  void loadDict_(const string& filePath) {
    ifstream ifs(filePath.c_str());
    if(!ifs.is_open()) {
      LogFatal("file %s open failed.", filePath.c_str());
    }
    string line;
    vector<string> buf;

    DictUnit nodeInfo;
    for(size_t lineno = 0; getline(ifs, line); lineno++) {
      split(line, buf, " ");
      if(buf.size() != DICT_COLUMN_NUM) {
        LogFatal("split result illegal, line: %s, result size: %u", line.c_str(), buf.size());
      }

      if(!TransCode::decode(buf[0], nodeInfo.word)) {
        LogError("line[%u:%s] illegal.", lineno, line.c_str());
        continue;
      }
      nodeInfo.weight = atof(buf[1].c_str());
      nodeInfo.tag = buf[2];

      nodeInfos_.push_back(nodeInfo);
    }
  }
  double findMinWeight_(const vector<DictUnit>& nodeInfos) const {
    double ret = MAX_DOUBLE;
    for(size_t i = 0; i < nodeInfos.size(); i++) {
      ret = min(nodeInfos[i].weight, ret);
    }
    return ret;
  }
  double findMaxWeight_(const vector<DictUnit>& nodeInfos) const {
    double ret = MIN_DOUBLE;
    for(size_t i = 0; i < nodeInfos.size(); i++) {
      ret = max(nodeInfos[i].weight, ret);
    }
    return ret;
  }

  void calculateWeight_(vector<DictUnit>& nodeInfos) const {
    double sum = 0.0;
    for(size_t i = 0; i < nodeInfos.size(); i++) {
      sum += nodeInfos[i].weight;
    }
    assert(sum);
    for(size_t i = 0; i < nodeInfos.size(); i++) {
      DictUnit& nodeInfo = nodeInfos[i];
      assert(nodeInfo.weight);
      nodeInfo.weight = log(double(nodeInfo.weight)/double(sum));
    }
  }

  void shrink_(vector<DictUnit>& units) const {
    vector<DictUnit>(units.begin(), units.end()).swap(units);
  }

 private:
  vector<DictUnit> nodeInfos_;
  Trie * trie_;

  double minWeight_;
  unordered_set<Unicode::value_type> userDictSingleChineseWord_;
};
}

#endif
