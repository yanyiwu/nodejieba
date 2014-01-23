#ifndef CPPJIEBA_FULLSEGMENT_H
#define CPPJIEBA_FULLSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "Limonp/logger.hpp"
#include "Trie.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"
#include "TransCode.hpp"
#include "TrieManager.hpp"

namespace CppJieba
{
    class FullSegment: public SegmentBase
    {
        private:
            Trie* _trie;

        public:
            FullSegment(){_setInitFlag(false);};
            explicit FullSegment(const string& dictPath){_setInitFlag(init(dictPath));}
            virtual ~FullSegment(){};
        public:
            bool init(const string& dictPath)
            {
                if(_getInitFlag())
                {
                    LogError("already inited before now.");
                    return false;
                }
                _trie = TrieManager::getInstance().getTrie(dictPath.c_str());
                if (NULL == _trie)
                {
                    LogError("get NULL pointor from getTrie(\"%s\")", dictPath.c_str());
                    return false;
                }
                return _setInitFlag(true);
            }

        public:
            using SegmentBase::cut;

        public:
            bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res) const
            {
                assert(_getInitFlag());
                if (begin >= end)
                {
                    LogError("begin >= end");
                    return false;
                }

                //resut of searching in trie tree
                vector<pair<uint, const TrieNodeInfo*> > tRes;

                //max index of res's words
                int maxIdx = 0;

                // always equals to (uItr - begin)
                int uIdx = 0;

                //tmp variables
                int wordLen = 0;
                for (Unicode::const_iterator uItr = begin; uItr != end; uItr++)
                {
                    //find word start from uItr
                    if (_trie->find(uItr, end, tRes))
                    {
                        for (vector<pair<uint, const TrieNodeInfo*> >::const_iterator itr = tRes.begin(); itr != tRes.end(); itr++)
                        {
                            wordLen = itr->second->word.size();
                            if (wordLen >= 2 || (tRes.size() == 1 && maxIdx <= uIdx))
                            {
                                res.push_back(itr->second->word);
                            }
                            maxIdx = uIdx+wordLen > maxIdx ? uIdx+wordLen : maxIdx;
                        }
                        tRes.clear();
                    }
                    else // not found word start from uItr
                    {
                        if (maxIdx <= uIdx) // never exist in prev results
                        {
                            //put itr itself in res
                            res.push_back(Unicode(1, *uItr));

                            //mark it exits
                            ++maxIdx;
                        }
                    }
                    ++uIdx;
                }

                return true;
            }

            bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res) const
            {
                assert(_getInitFlag());
                if (begin >= end)
                {
                    LogError("begin >= end");
                    return false;
                }

                vector<Unicode> uRes;
                if (!cut(begin, end, uRes))
                {
                    LogError("get unicode cut result error.");
                    return false;
                }

                string tmp;
                for (vector<Unicode>::const_iterator uItr = uRes.begin(); uItr != uRes.end(); uItr++)
                {
                    if (TransCode::encode(*uItr, tmp))
                    {
                        res.push_back(tmp);
                    }
                    else
                    {
                        LogError("encode failed.");
                    }
                }

                return true;
            }
    };
}

#endif
