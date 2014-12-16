#ifndef CPPJIEBA_MPSEGMENT_H
#define CPPJIEBA_MPSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "Limonp/Logger.hpp"
#include "DictTrie.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"

namespace CppJieba
{

    class MPSegment: public SegmentBase
    {
        private:
            DictTrie _dictTrie;

        public:
            MPSegment(){};
            MPSegment(const string& dictPath, const string& userDictPath = "")
            {
                LIMONP_CHECK(init(dictPath, userDictPath));
            };
            virtual ~MPSegment(){};
        public:
            bool init(const string& dictPath, const string& userDictPath = "")
            {
                LIMONP_CHECK(_dictTrie.init(dictPath, userDictPath));
                LogInfo("MPSegment init(%s) ok", dictPath.c_str());
                return true;
            }
            bool isUserDictSingleChineseWord(const Unicode::value_type & value) const
            {
                return _dictTrie.isUserDictSingleChineseWord(value);
            }
        public:
            using SegmentBase::cut;
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
                vector<SegmentChar> segmentChars;

                _dictTrie.find(begin, end, segmentChars);

                _calcDP(segmentChars);

                _cut(segmentChars, res);

                return true;
            }
            const DictTrie* getDictTrie() const 
            {
                return &_dictTrie;
            }

        private:
            void _calcDP(vector<SegmentChar>& segmentChars) const
            {
                size_t nextPos;
                const DictUnit* p;
                double val;

                for(ssize_t i = segmentChars.size() - 1; i >= 0; i--)
                {
                    segmentChars[i].pInfo = NULL;
                    segmentChars[i].weight = MIN_DOUBLE;
                    assert(!segmentChars[i].dag.empty());
                    for(DagType::const_iterator it = segmentChars[i].dag.begin(); it != segmentChars[i].dag.end(); it++)
                    {
                        nextPos = it->first;
                        p = it->second;
                        val = 0.0;
                        if(nextPos + 1 < segmentChars.size())
                        {
                            val += segmentChars[nextPos + 1].weight;
                        }

                        if(p)
                        {
                            val += p->weight; 
                        }
                        else
                        {
                            val += _dictTrie.getMinWeight();
                        }
                        if(val > segmentChars[i].weight)
                        {
                            segmentChars[i].pInfo = p;
                            segmentChars[i].weight = val;
                        }
                    }
                }
            }
            void _cut(const vector<SegmentChar>& segmentChars, vector<Unicode>& res) const
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
            }


    };
}

#endif
