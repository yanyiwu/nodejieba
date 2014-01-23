#ifndef CPPJIBEA_HMMSEGMENT_H
#define CPPJIBEA_HMMSEGMENT_H

#include <iostream>
#include <fstream>
#include <memory.h>
#include <cassert>
#include "Limonp/str_functs.hpp"
#include "Limonp/logger.hpp"
#include "TransCode.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"
#include "Trie.hpp"

namespace CppJieba
{
    using namespace Limonp;
    typedef unordered_map<uint16_t, double> EmitProbMap;
    class HMMSegment: public SegmentBase
    {
        public:
            /*
             * STATUS:
             * 0:B, 1:E, 2:M, 3:S
             * */
            enum {B = 0, E = 1, M = 2, S = 3, STATUS_SUM = 4};
        private:
            char _statMap[STATUS_SUM];
            double _startProb[STATUS_SUM];
            double _transProb[STATUS_SUM][STATUS_SUM];
            EmitProbMap _emitProbB;
            EmitProbMap _emitProbE;
            EmitProbMap _emitProbM;
            EmitProbMap _emitProbS;
            vector<EmitProbMap* > _emitProbVec;

        public:
            HMMSegment(){_setInitFlag(false);}
            explicit HMMSegment(const string& filePath)
            {
                _setInitFlag(init(filePath));
            }
            virtual ~HMMSegment(){}
        public:
            bool init(const string& filePath)
            {
                if(_getInitFlag())
                {
                    LogError("inited already.");
                    return false;
                }
                memset(_startProb, 0, sizeof(_startProb));
                memset(_transProb, 0, sizeof(_transProb));
                _statMap[0] = 'B';
                _statMap[1] = 'E';
                _statMap[2] = 'M';
                _statMap[3] = 'S';
                _emitProbVec.push_back(&_emitProbB);
                _emitProbVec.push_back(&_emitProbE);
                _emitProbVec.push_back(&_emitProbM);
                _emitProbVec.push_back(&_emitProbS);
                if(!_setInitFlag(_loadModel(filePath.c_str())))
                {
                    LogError("_loadModel(%s) failed.", filePath.c_str());
                    return false;
                }
                LogInfo("HMMSegment init(%s) ok.", filePath.c_str());
                return true;
            }
        public:
            using SegmentBase::cut;
            bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res)const 
            {
                if(!_getInitFlag())
                {
                    LogError("not inited.");
                    return false;
                }
                vector<uint> status; 
                if(!_viterbi(begin, end, status))
                {
                    LogError("_viterbi failed.");
                    return false;
                }

                Unicode::const_iterator left = begin;
                Unicode::const_iterator right;
                for(uint i =0; i< status.size(); i++)
                {
                    if(status[i] % 2) //if(E == status[i] || S == status[i])
                    {
                        right = begin + i + 1;
                        res.push_back(Unicode(left, right));
                        left = right;
                    }
                }
                return true;
            }
        public:
            virtual bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const
            {
                assert(_getInitFlag());
                if(begin == end)
                {
                    return false;
                }
                vector<Unicode> words;
                if(!cut(begin, end, words))
                {
                    return false;
                }
                string tmp;
                for(uint i = 0; i < words.size(); i++)
                {
                    if(TransCode::encode(words[i], tmp))
                    {
                        res.push_back(tmp);
                    }
                }
                return true;
            }

        private:
            bool _viterbi(Unicode::const_iterator begin, Unicode::const_iterator end, vector<uint>& status)const
            {
                if(begin == end)
                {
                    return false;
                }

                size_t Y = STATUS_SUM;
                size_t X = end - begin;
                size_t XYSize = X * Y;
                int * path;
                double * weight;
                uint now, old, stat;
                double tmp, endE, endS;

                    path = new int [XYSize];
                    weight = new double [XYSize];
                if(NULL == path || NULL == weight)
                {
                    LogError("bad_alloc");
                    return false;
                }

                //start
                for(uint y = 0; y < Y; y++)
                {
                    weight[0 + y * X] = _startProb[y] + _getEmitProb(_emitProbVec[y], *begin, MIN_DOUBLE);
                    path[0 + y * X] = -1;
                }
                //process
                //for(; begin != end; begin++)
                for(uint x = 1; x < X; x++)
                {
                    for(uint y = 0; y < Y; y++)
                    {
                        now = x + y*X;
                        weight[now] = MIN_DOUBLE;
                        path[now] = E; // warning
                        for(uint preY = 0; preY < Y; preY++)
                        {
                            old = x - 1 + preY * X;
                            tmp = weight[old] + _transProb[preY][y] + _getEmitProb(_emitProbVec[y], *(begin+x), MIN_DOUBLE);
                            if(tmp > weight[now])
                            {
                                weight[now] = tmp;
                                path[now] = preY;
                            }
                        }
                    }
                }

                endE = weight[X-1+E*X];
                endS = weight[X-1+S*X];
                stat = 0;
                if(endE > endS)
                {
                    stat = E;
                }
                else
                {
                    stat = S;
                }

                status.assign(X, 0);
                for(int x = X -1 ; x >= 0; x--)
                {
                    status[x] = stat;
                    stat = path[x + stat*X];
                }

                delete [] path;
                delete [] weight;
                return true;
            }
            bool _loadModel(const char* const filePath)
            {
                LogDebug("loadModel [%s] start ...", filePath);
                ifstream ifile(filePath);
                string line;
                vector<string> tmp;
                vector<string> tmp2;
                //load _startProb
                if(!_getLine(ifile, line))
                {
                    return false;
                }
                split(line, tmp, " ");
                if(tmp.size() != STATUS_SUM)
                {
                    LogError("start_p illegal");
                    return false;
                }
                for(uint j = 0; j< tmp.size(); j++)
                {
                    _startProb[j] = atof(tmp[j].c_str());
                    //cout<<_startProb[j]<<endl;
                }

                //load _transProb
                for(uint i = 0; i < STATUS_SUM; i++)
                {
                    if(!_getLine(ifile, line))
                    {
                        return false;
                    }
                    split(line, tmp, " ");
                    if(tmp.size() != STATUS_SUM)
                    {
                        LogError("trans_p illegal");
                        return false;
                    }
                    for(uint j =0; j < STATUS_SUM; j++)
                    {
                        _transProb[i][j] = atof(tmp[j].c_str());
                        //cout<<_transProb[i][j]<<endl;
                    }
                }

                //load _emitProbB
                if(!_getLine(ifile, line) || !_loadEmitProb(line, _emitProbB))
                {
                    return false;
                }

                //load _emitProbE
                if(!_getLine(ifile, line) || !_loadEmitProb(line, _emitProbE))
                {
                    return false;
                }

                //load _emitProbM
                if(!_getLine(ifile, line) || !_loadEmitProb(line, _emitProbM))
                {
                    return false;
                }

                //load _emitProbS
                if(!_getLine(ifile, line) || !_loadEmitProb(line, _emitProbS))
                {
                    return false;
                }

                LogDebug("loadModel [%s] end.", filePath);

                return true;
            }
            bool _getLine(ifstream& ifile, string& line)
            {
                while(getline(ifile, line))
                {
                    trim(line);
                    if(line.empty())
                    {
                        continue;
                    }
                    if(startsWith(line, "#"))
                    {
                        continue;
                    }
                    return true;
                }
                return false;
            }
            bool _loadEmitProb(const string& line, EmitProbMap& mp)
            {
                if(line.empty())
                {
                    return false;
                }
                vector<string> tmp, tmp2;
                uint16_t unico = 0;
                split(line, tmp, ",");
                for(uint i = 0; i < tmp.size(); i++)
                {
                    split(tmp[i], tmp2, ":");
                    if(2 != tmp2.size())
                    {
                        LogError("_emitProb illegal.");
                        return false;
                    }
                    if(!_decodeOne(tmp2[0], unico))
                    {
                        LogError("TransCode failed.");
                        return false;
                    }
                    mp[unico] = atof(tmp2[1].c_str());
                }
                return true;
            }
            bool _decodeOne(const string& str, uint16_t& res)
            {
                Unicode ui16;
                if(!TransCode::decode(str, ui16) || ui16.size() != 1)
                {
                    return false;
                }
                res = ui16[0];
                return true;
            }
            double _getEmitProb(const EmitProbMap* ptMp, uint16_t key, double defVal)const 
            {
                EmitProbMap::const_iterator cit = ptMp->find(key);
                if(cit == ptMp->end())
                {
                    return defVal;
                }
                return cit->second;

            }


    };
}

#endif
