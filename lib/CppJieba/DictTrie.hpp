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
    calculateWeight_(staticNodeInfos_);
    minWeight_ = findMinWeight_(staticNodeInfos_);
    maxWeight_ = findMaxWeight_(staticNodeInfos_);

    if(userDictPath.size()) {
      loadUserDict_(userDictPath);
    }
    shrink_(staticNodeInfos_);
    createTrie_(staticNodeInfos_);
  }
  
  bool insertUserWord(const string& word, const string& tag = UNKNOWN_TAG) {
    DictUnit nodeInfo;
    if(!makeUserNodeInfo_(nodeInfo, word, tag)) {
      return false;
    }
    activeNodeInfos_.push_back(nodeInfo);
    trie_->insertNode(nodeInfo.word, &activeNodeInfos_.back());
    return true;
  }

  const DictUnit* find(Unicode::const_iterator begin, Unicode::const_iterator end) const {
    return trie_->find(begin, end);
  }
  bool find(Unicode::const_iterator begin, Unicode::const_iterator end, DagType& dag, size_t offset = 0) const {
    return trie_->find(begin, end, dag, offset);
  }
  void find(Unicode::const_iterator begin,
    Unicode::const_iterator end,
    vector<SegmentChar>& res) const {
    trie_->find(begin, end, res);
  }
  bool isUserDictSingleChineseWord(const Unicode::value_type& word) const {
    return isIn(userDictSingleChineseWord_, word);
  }
  double getMinWeight() const {
    return minWeight_;
  };

 private:
  void createTrie_(const vector<DictUnit>& dictUnits) {
    assert(dictUnits.size());
    vector<Unicode> words;
    vector<const DictUnit*> valuePointers;
    for(size_t i = 0 ; i < dictUnits.size(); i ++) {
      words.push_back(dictUnits[i].word);
      valuePointers.push_back(&dictUnits[i]);
    }

    trie_ = new Trie(words, valuePointers);
  }
  void loadUserDict_(const string& filePath) {
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
      makeUserNodeInfo_(nodeInfo, buf[0], 
            (buf.size() == 2 ? buf[1] : UNKNOWN_TAG));
      staticNodeInfos_.push_back(nodeInfo);
    }
    LogInfo("load userdict[%s] ok. lines[%u]", filePath.c_str(), lineno);
  }
  bool makeNodeInfo(DictUnit& nodeInfo,
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
  bool makeUserNodeInfo_(DictUnit& nodeInfo, 
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
      makeNodeInfo(nodeInfo, 
            buf[0], 
            atof(buf[1].c_str()), 
            buf[2]);
      staticNodeInfos_.push_back(nodeInfo);
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
  vector<DictUnit> staticNodeInfos_;
  deque<DictUnit> activeNodeInfos_; // must not be vector
  Trie * trie_;

  double minWeight_;
  double maxWeight_;
  unordered_set<Unicode::value_type> userDictSingleChineseWord_;
};
}

#endif
