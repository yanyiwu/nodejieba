#ifndef CPPJIEBA_HMMMODEL_H
#define CPPJIEBA_HMMMODEL_H

#include "limonp/StringUtil.hpp"

namespace cppjieba {

using namespace limonp;
typedef unordered_map<uint16_t, double> EmitProbMap;

struct HMMModel {
  /*
   * STATUS:
   * 0: HMMModel::B, 1: HMMModel::E, 2: HMMModel::M, 3:HMMModel::S
   * */
  enum {B = 0, E = 1, M = 2, S = 3, STATUS_SUM = 4};

  HMMModel(const string& modelPath) {
    memset(startProb, 0, sizeof(startProb));
    memset(transProb, 0, sizeof(transProb));
    statMap[0] = 'B';
    statMap[1] = 'E';
    statMap[2] = 'M';
    statMap[3] = 'S';
    emitProbVec.push_back(&emitProbB);
    emitProbVec.push_back(&emitProbE);
    emitProbVec.push_back(&emitProbM);
    emitProbVec.push_back(&emitProbS);
    LoadModel(modelPath);
  }
  ~HMMModel() {
  }
  void LoadModel(const string& filePath) {
    ifstream ifile(filePath.c_str());
    if (!ifile.is_open()) {
      LogFatal("open %s failed.", filePath.c_str());
    }
    string line;
    vector<string> tmp;
    vector<string> tmp2;
    //Load startProb
    if (!GetLine(ifile, line)) {
      LogFatal("Load startProb");
    }
    split(line, tmp, " ");
    if (tmp.size() != STATUS_SUM) {
      LogFatal("start_p illegal");
    }
    for (size_t j = 0; j< tmp.size(); j++) {
      startProb[j] = atof(tmp[j].c_str());
    }

    //Load transProb
    for (size_t i = 0; i < STATUS_SUM; i++) {
      if (!GetLine(ifile, line)) {
        LogFatal("Load transProb failed.");
      }
      split(line, tmp, " ");
      if (tmp.size() != STATUS_SUM) {
        LogFatal("trans_p illegal");
      }
      for (size_t j =0; j < STATUS_SUM; j++) {
        transProb[i][j] = atof(tmp[j].c_str());
      }
    }

    //Load emitProbB
    if (!GetLine(ifile, line) || !LoadEmitProb(line, emitProbB)) {
      LogFatal("Load emitProbB failed.");
    }

    //Load emitProbE
    if (!GetLine(ifile, line) || !LoadEmitProb(line, emitProbE)) {
      LogFatal("Load emitProbE failed.");
    }

    //Load emitProbM
    if (!GetLine(ifile, line) || !LoadEmitProb(line, emitProbM)) {
      LogFatal("Load emitProbM failed.");
    }

    //Load emitProbS
    if (!GetLine(ifile, line) || !LoadEmitProb(line, emitProbS)) {
      LogFatal("Load emitProbS failed.");
    }
  }
  double GetEmitProb(const EmitProbMap* ptMp, uint16_t key, 
        double defVal)const {
    EmitProbMap::const_iterator cit = ptMp->find(key);
    if (cit == ptMp->end()) {
      return defVal;
    }
    return cit->second;
  }
  bool GetLine(ifstream& ifile, string& line) {
    while (getline(ifile, line)) {
      trim(line);
      if (line.empty()) {
        continue;
      }
      if (startsWith(line, "#")) {
        continue;
      }
      return true;
    }
    return false;
  }
  bool LoadEmitProb(const string& line, EmitProbMap& mp) {
    if (line.empty()) {
      return false;
    }
    vector<string> tmp, tmp2;
    Unicode unicode;
    split(line, tmp, ",");
    for (size_t i = 0; i < tmp.size(); i++) {
      split(tmp[i], tmp2, ":");
      if (2 != tmp2.size()) {
        LogError("emitProb illegal.");
        return false;
      }
      if (!TransCode::Decode(tmp2[0], unicode) || unicode.size() != 1) {
        LogError("TransCode failed.");
        return false;
      }
      mp[unicode[0]] = atof(tmp2[1].c_str());
    }
    return true;
  }

  char statMap[STATUS_SUM];
  double startProb[STATUS_SUM];
  double transProb[STATUS_SUM][STATUS_SUM];
  EmitProbMap emitProbB;
  EmitProbMap emitProbE;
  EmitProbMap emitProbM;
  EmitProbMap emitProbS;
  vector<EmitProbMap* > emitProbVec;
}; // struct HMMModel

} // namespace cppjieba

#endif
