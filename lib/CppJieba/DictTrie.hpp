#ifndef CPPJIEBA_DICT_TRIE_HPP
#define CPPJIEBA_DICT_TRIE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include <stdint.h>
#include <cmath>
#include <limits>
#include "limonp/StringUtil.hpp"
#include "limonp/Logger.hpp"
#include "TransCode.hpp"
#include "Trie.hpp"

namespace CppJieba {
using namespace limonp;
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
    delete trie_;
  }

  void init(const string& dictPath, const string& userDictPath = "") {
    if(trie_ != NULL) {
      LogFatal("trie already initted");
    }
    LoadDict(dictPath);
    CalculateWeight(staticNodeInfos_);
    minWeight_ = FindMinWeight(staticNodeInfos_);
    maxWeight_ = FindMaxWeight(staticNodeInfos_);

    if(userDictPath.size()) {
      LoadUserDict(userDictPath);
    }
    Shrink(staticNodeInfos_);
    CreateTrie(staticNodeInfos_);
  }
  
  bool insertUserWord(const string& word, const string& tag = UNKNOWN_TAG) {
    DictUnit nodeInfo;
    if(!MakeUserNodeInfo(nodeInfo, word, tag)) {
      return false;
    }
    activeNodeInfos_.push_back(nodeInfo);
    trie_->insertNode(nodeInfo.word, &activeNodeInfos_.back());
    return true;
  }

  const DictUnit* find(Unicode::const_iterator begin, Unicode::const_iterator end) const {
    return trie_->find(begin, end);
  }

  void find(Unicode::const_iterator begin, 
        Unicode::const_iterator end, 
        vector<struct Dag>&res,
        size_t max_word_len = MAX_WORD_LENGTH) const {
    trie_->find(begin, end, res, max_word_len);
  }

  bool isUserDictSingleChineseWord(const Rune& word) const {
    return isIn(userDictSingleChineseWord_, word);
  }

  double getMinWeight() const {
    return minWeight_;
  }

 private:
  void CreateTrie(const vector<DictUnit>& dictUnits) {
    assert(dictUnits.size());
    vector<Unicode> words;
    vector<const DictUnit*> valuePointers;
    for(size_t i = 0 ; i < dictUnits.size(); i ++) {
      words.push_back(dictUnits[i].word);
      valuePointers.push_back(&dictUnits[i]);
    }

    trie_ = new Trie(words, valuePointers);
  }
  void LoadUserDict(const string& filePath) {
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
      DictUnit nodeInfo;
      MakeUserNodeInfo(nodeInfo, buf[0], 
            (buf.size() == 2 ? buf[1] : UNKNOWN_TAG));
      staticNodeInfos_.push_back(nodeInfo);
    }
    LogInfo("load userdict[%s] ok. lines[%u]", filePath.c_str(), lineno);
  }
  bool MakeNodeInfo(DictUnit& nodeInfo,
        const string& word, 
        double weight, 
        const string& tag) {
    if(!TransCode::decode(word, nodeInfo.word)) {
      LogError("decode %s failed.", word.c_str());
      return false;
    }
    nodeInfo.weight = weight;
    nodeInfo.tag = tag;
    return true;
  }
  bool MakeUserNodeInfo(DictUnit& nodeInfo, 
        const string& word, 
        const string& tag = UNKNOWN_TAG) {
    if(!TransCode::decode(word, nodeInfo.word)) {
      LogError("decode %s failed.", word.c_str());
      return false;
    }
    if(nodeInfo.word.size() == 1) {
      userDictSingleChineseWord_.insert(nodeInfo.word[0]);
    }
    nodeInfo.weight = maxWeight_;
    nodeInfo.tag = tag;
    return true;
  }
  void LoadDict(const string& filePath) {
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
      MakeNodeInfo(nodeInfo, 
            buf[0], 
            atof(buf[1].c_str()), 
            buf[2]);
      staticNodeInfos_.push_back(nodeInfo);
    }
  }
  double FindMinWeight(const vector<DictUnit>& nodeInfos) const {
    double ret = MAX_DOUBLE;
    for(size_t i = 0; i < nodeInfos.size(); i++) {
      ret = min(nodeInfos[i].weight, ret);
    }
    return ret;
  }
  double FindMaxWeight(const vector<DictUnit>& nodeInfos) const {
    double ret = MIN_DOUBLE;
    for(size_t i = 0; i < nodeInfos.size(); i++) {
      ret = max(nodeInfos[i].weight, ret);
    }
    return ret;
  }

  void CalculateWeight(vector<DictUnit>& nodeInfos) const {
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

  void Shrink(vector<DictUnit>& units) const {
    vector<DictUnit>(units.begin(), units.end()).swap(units);
  }

  vector<DictUnit> staticNodeInfos_;
  deque<DictUnit> activeNodeInfos_; // must not be vector
  Trie * trie_;

  double minWeight_;
  double maxWeight_;
  unordered_set<Rune> userDictSingleChineseWord_;
};
}

#endif
