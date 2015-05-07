#ifndef CPPJIBEA_HMMSEGMENT_H
#define CPPJIBEA_HMMSEGMENT_H

#include <iostream>
#include <fstream>
#include <memory.h>
#include <cassert>
#include "Limonp/StringUtil.hpp"
#include "TransCode.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"
#include "DictTrie.hpp"

namespace CppJieba {
using namespace Limonp;
typedef unordered_map<uint16_t, double> EmitProbMap;
class HMMSegment: public SegmentBase {
 public:
  /*
   * STATUS:
   * 0:B, 1:E, 2:M, 3:S
   * */
  enum {B = 0, E = 1, M = 2, S = 3, STATUS_SUM = 4};

 public:
  HMMSegment() {}
  explicit HMMSegment(const string& filePath) {
    init(filePath);
  }
  virtual ~HMMSegment() {}
 public:
  void init(const string& filePath) {
    memset(startProb_, 0, sizeof(startProb_));
    memset(transProb_, 0, sizeof(transProb_));
    statMap_[0] = 'B';
    statMap_[1] = 'E';
    statMap_[2] = 'M';
    statMap_[3] = 'S';
    emitProbVec_.push_back(&emitProbB_);
    emitProbVec_.push_back(&emitProbE_);
    emitProbVec_.push_back(&emitProbM_);
    emitProbVec_.push_back(&emitProbS_);
    loadModel_(filePath.c_str());
    LogInfo("HMMSegment init(%s) ok.", filePath.c_str());
  }
 public:
  using SegmentBase::cut;
 public:
  bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res)const {
    Unicode::const_iterator left = begin;
    Unicode::const_iterator right = begin;
    while(right != end) {
      if(*right < 0x80) {
        if(left != right && !cut_(left, right, res)) {
          return false;
        }
        left = right;
        do {
          right = sequentialLetterRule_(left, end);
          if(right != left) {
            break;
          }
          right = numbersRule_(left, end);
          if(right != left) {
            break;
          }
          right ++;
        } while(false);
        res.push_back(Unicode(left, right));
        left = right;
      } else {
        right++;
      }
    }
    if(left != right && !cut_(left, right, res)) {
      return false;
    }
    return true;
  }
 public:
  virtual bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const {
    if(begin == end) {
      return false;
    }
    vector<Unicode> words;
    words.reserve(end - begin);
    if(!cut(begin, end, words)) {
      return false;
    }
    size_t offset = res.size();
    res.resize(res.size() + words.size());
    for(size_t i = 0; i < words.size(); i++) {
      if(!TransCode::encode(words[i], res[offset + i])) {
        LogError("encode failed.");
      }
    }
    return true;
  }
 private:
  // sequential letters rule
  Unicode::const_iterator sequentialLetterRule_(Unicode::const_iterator begin, Unicode::const_iterator end) const {
    Unicode::value_type x = *begin;
    if (('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z')) {
      begin ++;
    } else {
      return begin;
    }
    while(begin != end) {
      x = *begin;
      if(('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z') || ('0' <= x && x <= '9')) {
        begin ++;
      } else {
        break;
      }
    }
    return begin;
  }
  //
  Unicode::const_iterator numbersRule_(Unicode::const_iterator begin, Unicode::const_iterator end) const {
    Unicode::value_type x = *begin;
    if('0' <= x && x <= '9') {
      begin ++;
    } else {
      return begin;
    }
    while(begin != end) {
      x = *begin;
      if( ('0' <= x && x <= '9') || x == '.') {
        begin++;
      } else {
        break;
      }
    }
    return begin;
  }
  bool cut_(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res) const {
    vector<size_t> status;
    if(!viterbi_(begin, end, status)) {
      LogError("viterbi_ failed.");
      return false;
    }

    Unicode::const_iterator left = begin;
    Unicode::const_iterator right;
    for(size_t i = 0; i < status.size(); i++) {
      if(status[i] % 2) { //if(E == status[i] || S == status[i])
        right = begin + i + 1;
        res.push_back(Unicode(left, right));
        left = right;
      }
    }
    return true;
  }

  bool viterbi_(Unicode::const_iterator begin, Unicode::const_iterator end, vector<size_t>& status)const {
    if(begin == end) {
      return false;
    }

    size_t Y = STATUS_SUM;
    size_t X = end - begin;

    size_t XYSize = X * Y;
    size_t now, old, stat;
    double tmp, endE, endS;

    vector<int> path(XYSize);
    vector<double> weight(XYSize);

    //start
    for(size_t y = 0; y < Y; y++) {
      weight[0 + y * X] = startProb_[y] + getEmitProb_(emitProbVec_[y], *begin, MIN_DOUBLE);
      path[0 + y * X] = -1;
    }


    double emitProb;

    for(size_t x = 1; x < X; x++) {
      for(size_t y = 0; y < Y; y++) {
        now = x + y*X;
        weight[now] = MIN_DOUBLE;
        path[now] = E; // warning
        emitProb = getEmitProb_(emitProbVec_[y], *(begin+x), MIN_DOUBLE);
        for(size_t preY = 0; preY < Y; preY++) {
          old = x - 1 + preY * X;
          tmp = weight[old] + transProb_[preY][y] + emitProb;
          if(tmp > weight[now]) {
            weight[now] = tmp;
            path[now] = preY;
          }
        }
      }
    }

    endE = weight[X-1+E*X];
    endS = weight[X-1+S*X];
    stat = 0;
    if(endE >= endS) {
      stat = E;
    } else {
      stat = S;
    }

    status.resize(X);
    for(int x = X -1 ; x >= 0; x--) {
      status[x] = stat;
      stat = path[x + stat*X];
    }

    return true;
  }
  void loadModel_(const char* const filePath) {
    ifstream ifile(filePath);
    if(!ifile.is_open()) {
      LogFatal("open %s failed.", filePath);
    }
    string line;
    vector<string> tmp;
    vector<string> tmp2;
    //load startProb_
    if(!getLine_(ifile, line)) {
      LogFatal("load startProb_");
    }
    split(line, tmp, " ");
    if(tmp.size() != STATUS_SUM) {
      LogFatal("start_p illegal");
    }
    for(size_t j = 0; j< tmp.size(); j++) {
      startProb_[j] = atof(tmp[j].c_str());
    }

    //load transProb_
    for(size_t i = 0; i < STATUS_SUM; i++) {
      if(!getLine_(ifile, line)) {
        LogFatal("load transProb_ failed.");
      }
      split(line, tmp, " ");
      if(tmp.size() != STATUS_SUM) {
        LogFatal("trans_p illegal");
      }
      for(size_t j =0; j < STATUS_SUM; j++) {
        transProb_[i][j] = atof(tmp[j].c_str());
      }
    }

    //load emitProbB_
    if(!getLine_(ifile, line) || !loadEmitProb_(line, emitProbB_)) {
      LogFatal("load emitProbB_ failed.");
    }

    //load emitProbE_
    if(!getLine_(ifile, line) || !loadEmitProb_(line, emitProbE_)) {
      LogFatal("load emitProbE_ failed.");
    }

    //load emitProbM_
    if(!getLine_(ifile, line) || !loadEmitProb_(line, emitProbM_)) {
      LogFatal("load emitProbM_ failed.");
    }

    //load emitProbS_
    if(!getLine_(ifile, line) || !loadEmitProb_(line, emitProbS_)) {
      LogFatal("load emitProbS_ failed.");
    }
  }
  bool getLine_(ifstream& ifile, string& line) {
    while(getline(ifile, line)) {
      trim(line);
      if(line.empty()) {
        continue;
      }
      if(startsWith(line, "#")) {
        continue;
      }
      return true;
    }
    return false;
  }
  bool loadEmitProb_(const string& line, EmitProbMap& mp) {
    if(line.empty()) {
      return false;
    }
    vector<string> tmp, tmp2;
    Unicode unicode;
    split(line, tmp, ",");
    for(size_t i = 0; i < tmp.size(); i++) {
      split(tmp[i], tmp2, ":");
      if(2 != tmp2.size()) {
        LogError("emitProb_ illegal.");
        return false;
      }
      if(!TransCode::decode(tmp2[0], unicode) || unicode.size() != 1) {
        LogError("TransCode failed.");
        return false;
      }
      mp[unicode[0]] = atof(tmp2[1].c_str());
    }
    return true;
  }
  double getEmitProb_(const EmitProbMap* ptMp, uint16_t key, double defVal)const {
    EmitProbMap::const_iterator cit = ptMp->find(key);
    if(cit == ptMp->end()) {
      return defVal;
    }
    return cit->second;

  }

 private:
  char statMap_[STATUS_SUM];
  double startProb_[STATUS_SUM];
  double transProb_[STATUS_SUM][STATUS_SUM];
  EmitProbMap emitProbB_;
  EmitProbMap emitProbE_;
  EmitProbMap emitProbM_;
  EmitProbMap emitProbS_;
  vector<EmitProbMap* > emitProbVec_;

};
}

#endif
