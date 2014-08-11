/************************************
 * file enc : ASCII
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef CPPJIEBA_MPSEGMENT_H
#define CPPJIEBA_MPSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "Limonp/Logger.hpp"
#include "DictTrie.hpp"
#include "DictTrie.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"

namespace CppJieba
{

    struct SegmentChar 
    {
        uint16_t uniCh;
        DagType dag;
        const DictUnit * pInfo;
        double weight;
        size_t nextPos;
        SegmentChar():uniCh(0), pInfo(NULL), weight(0.0), nextPos(0)
        {}
    };

    class MPSegment: public SegmentBase
    {
        protected:
            DictTrie _dictTrie;

        public:
            MPSegment(){_setInitFlag(false);};
            explicit MPSegment(const string& dictPath, const string& userDictPath = "")
            {
                _setInitFlag(init(dictPath, userDictPath));
            };
            virtual ~MPSegment(){};
        public:
            bool init(const string& dictPath, const string& userDictPath = "")
            {
                if(_getInitFlag())
                {
                    LogError("already inited before now.");
                    return false;
                }
                _dictTrie.init(dictPath, userDictPath);
                assert(_dictTrie);
                LogInfo("MPSegment init(%s) ok", dictPath.c_str());
                return _setInitFlag(true);
            }
            bool isUserDictSingleChineseWord(const Unicode::value_type & value) const
            {
                return _dictTrie.isUserDictSingleChineseWord(value);
            }
        public:
            using SegmentBase::cut;
            virtual bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const
            {
                assert(_getInitFlag());
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
                    if(!TransCode::encode(words[i], res[i + offset]))
                    {
                        LogError("encode failed.");
                        res[i + offset].clear();
                    }
                }
                return true;
            }

            bool cut(Unicode::const_iterator begin , Unicode::const_iterator end, vector<Unicode>& res) const
            {
                if(end == begin)
                {
                    return false;
                }
                assert(_getInitFlag());
                vector<SegmentChar> segmentChars(end - begin);

                //calc DAG
                for(size_t i = 0; i < segmentChars.size(); i ++)
                {
                    segmentChars[i].uniCh = *(begin + i);
                    segmentChars[i].dag.clear();
                    _dictTrie.find(begin + i, end, segmentChars[i].dag, i);
                    segmentChars[i].dag.insert(make_pair<DagType::key_type, DagType::mapped_type>(i, NULL));
                }

                _calcDP(segmentChars);

                if(!_cut(segmentChars, res))
                {
                    LogError("_cut failed.");
                    return false;
                }

                return true;
            }
            const DictTrie* getDictTrie() const 
            {
                return &_dictTrie;
            }

        private:
            void _calcDP(vector<SegmentChar>& SegmentChars) const
            {
                size_t nextPos;
                const DictUnit* p;
                double val;

                for(int i = SegmentChars.size() - 1; i >= 0; i--)
                {
                    SegmentChars[i].pInfo = NULL;
                    SegmentChars[i].weight = MIN_DOUBLE;
                    for(DagType::const_iterator it = SegmentChars[i].dag.begin(); it != SegmentChars[i].dag.end(); it++)
                    {
                        nextPos = it->first;
                        p = it->second;
                        val = 0.0;
                        if(nextPos + 1 < SegmentChars.size())
                        {
                            val += SegmentChars[nextPos + 1].weight;
                        }

                        if(p)
                        {
                            val += p->weight; 
                        }
                        else
                        {
                            val += _dictTrie.getMinWeight();
                        }
                        if(val > SegmentChars[i].weight)
                        {
                            SegmentChars[i].pInfo = p;
                            SegmentChars[i].weight = val;
                        }
                    }
                }
            }
            bool _cut(const vector<SegmentChar>& segmentChars, vector<Unicode>& res)const
            {
                size_t i = 0;
                while(i < segmentChars.size())
                {
                    const DictUnit* p = segmentChars[i].pInfo;
                    if(p)
                    {
                        res.push_back(p->word);
                        i += p->word.size();
                    }
                    else//single chinese word
                    {
                        res.push_back(Unicode(1, segmentChars[i].uniCh));
                        i++;
                    }
                }
                return true;
            }


    };
}

#endif
