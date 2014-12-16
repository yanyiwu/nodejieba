#ifndef CPPJIBEA_HMMSEGMENT_H
#define CPPJIBEA_HMMSEGMENT_H

#include <iostream>
#include <fstream>
#include <memory.h>
#include <cassert>
#include "Limonp/StringUtil.hpp"
#include "Limonp/Logger.hpp"
#include "TransCode.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"
#include "DictTrie.hpp"

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
            HMMSegment(){}
            explicit HMMSegment(const string& filePath)
            {
                LIMONP_CHECK(init(filePath));
            }
            virtual ~HMMSegment(){}
        public:
            bool init(const string& filePath)
            {
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
                LIMONP_CHECK(_loadModel(filePath.c_str()));
                LogInfo("HMMSegment init(%s) ok.", filePath.c_str());
                return true;
            }
        public:
            using SegmentBase::cut;
        public:
            bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res)const 
            {
                Unicode::const_iterator left = begin;
                Unicode::const_iterator right = begin;
                while(right != end)
                {
                    if(*right < 0x80) 
                    {
                        if(left != right && !_cut(left, right, res))
                        {
                            return false;
                        }
                        left = right;
                        do {
                            right = _sequentialLetterRule(left, end);
                            if(right != left)
                            {
                                break;
                            }
                            right = _numbersRule(left, end);
                            if(right != left)
                            {
                                break;
                            }
                            right ++;
                        } while(false);
                        res.push_back(Unicode(left, right));
                        left = right;
                    }
                    else
                    {
                        right++;
                    }
                }
                if(left != right && !_cut(left, right, res))
                {
                    return false;
                }
                return true;
            }
        private:
            // sequential letters rule
            Unicode::const_iterator _sequentialLetterRule(Unicode::const_iterator begin, Unicode::const_iterator end) const
            {
                Unicode::value_type x;
                while(begin != end)
                {
                    x = *begin;
                    if(('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z'))
                    {
                        begin ++;
                    }
                    else
                    {
                        break;
                    }
                }
                return begin;
            }
            // 
            Unicode::const_iterator _numbersRule(Unicode::const_iterator begin, Unicode::const_iterator end) const
            {
                Unicode::value_type x = *begin;
                if('0' <= x && x <= '9')
                {
                    begin ++;
                }
                else
                {
                    return begin;
                }
                while(begin != end)
                {
                    x = *begin;
                    if( ('0' <= x && x <= '9') || x == '.')
                    {
                        begin++;
                    }
                    else
                    {
                        break;
                    }
                }
                return begin;
            }
            bool _cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res) const 
            {
                vector<size_t> status; 
                if(!_viterbi(begin, end, status))
                {
                    LogError("_viterbi failed.");
                    return false;
                }

                Unicode::const_iterator left = begin;
                Unicode::const_iterator right;
                for(size_t i = 0; i < status.size(); i++)
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
                if(begin == end)
                {
                    return false;
                }
                vector<Unicode> words;
                words.reserve(end - begin);
                if(!cut(begin, end, words))
                {
                    return false;
                }
                size_t offset = res.size();
                res.resize(res.size() + words.size());
                for(size_t i = 0; i < words.size(); i++)
                {
                    if(!TransCode::encode(words[i], res[offset + i]))
                    {
                        LogError("encode failed.");
                    }
                }
                return true;
            }

        private:
            bool _viterbi(Unicode::const_iterator begin, Unicode::const_iterator end, vector<size_t>& status)const
            {
                if(begin == end)
                {
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
                for(size_t y = 0; y < Y; y++)
                {
                    weight[0 + y * X] = _startProb[y] + _getEmitProb(_emitProbVec[y], *begin, MIN_DOUBLE);
                    path[0 + y * X] = -1;
                }


                double emitProb;

                for(size_t x = 1; x < X; x++)
                {
                    for(size_t y = 0; y < Y; y++)
                    {
                        now = x + y*X;
                        weight[now] = MIN_DOUBLE;
                        path[now] = E; // warning
                        emitProb = _getEmitProb(_emitProbVec[y], *(begin+x), MIN_DOUBLE);
                        for(size_t preY = 0; preY < Y; preY++)
                        {
                            old = x - 1 + preY * X;
                            tmp = weight[old] + _transProb[preY][y] + emitProb;
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
                if(endE >= endS)
                {
                    stat = E;
                }
                else
                {
                    stat = S;
                }

                status.resize(X);
                for(int x = X -1 ; x >= 0; x--)
                {
                    status[x] = stat;
                    stat = path[x + stat*X];
                }

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
                for(size_t j = 0; j< tmp.size(); j++)
                {
                    _startProb[j] = atof(tmp[j].c_str());
                }

                //load _transProb
                for(size_t i = 0; i < STATUS_SUM; i++)
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
                    for(size_t j =0; j < STATUS_SUM; j++)
                    {
                        _transProb[i][j] = atof(tmp[j].c_str());
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
                Unicode unicode;
                split(line, tmp, ",");
                for(size_t i = 0; i < tmp.size(); i++)
                {
                    split(tmp[i], tmp2, ":");
                    if(2 != tmp2.size())
                    {
                        LogError("_emitProb illegal.");
                        return false;
                    }
                    if(!TransCode::decode(tmp2[0], unicode) || unicode.size() != 1)
                    {
                        LogError("TransCode failed.");
                        return false;
                    }
                    mp[unicode[0]] = atof(tmp2[1].c_str());
                }
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
