#ifndef CPPJIEBA_MIXSEGMENT_H
#define CPPJIEBA_MIXSEGMENT_H

#include <cassert>
#include "MPSegment.hpp"
#include "HMMSegment.hpp"
#include "Limonp/str_functs.hpp"

namespace CppJieba
{
    class MixSegment: public SegmentBase
    {
        private:
            MPSegment _mpSeg;
            HMMSegment _hmmSeg;
        public:
            MixSegment(){_setInitFlag(false);};
            explicit MixSegment(const string& mpSegDict, const string& hmmSegDict)
            {
                _setInitFlag(init(mpSegDict, hmmSegDict));
            }
            virtual ~MixSegment(){}
        public:
            bool init(const string& mpSegDict, const string& hmmSegDict)
            {
                if(_getInitFlag())
                {
                    LogError("inited.");
                    return false;
                }
                if(!_mpSeg.init(mpSegDict))
                {
                    LogError("_mpSeg init");
                    return false;
                }
                if(!_hmmSeg.init(hmmSegDict))
                {
                    LogError("_hmmSeg init");
                    return false;
                }
                LogInfo("MixSegment init(%s, %s)", mpSegDict.c_str(), hmmSegDict.c_str());
                return _setInitFlag(true);
            }
        public:
            using SegmentBase::cut;
        public:
            virtual bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res) const
            {
                assert(_getInitFlag());
                if(begin >= end)
                {
                    LogError("begin >= end");
                    return false;
                }

                vector<TrieNodeInfo> infos;
                if(!_mpSeg.cut(begin, end, infos))
                {
                    LogError("mpSeg cutDAG failed.");
                    return false;
                }

                vector<Unicode> hmmRes;
                Unicode piece;
                for (uint i = 0, j = 0; i < infos.size(); i++)
                {
                    //if mp get a word, it's ok, put it into result
                    if (1 != infos[i].word.size())
                    {
                        res.push_back(infos[i].word);
                        continue;
                    }

                    // if mp get a single one, collect it in sequence
                    j = i;
                    while (j < infos.size() && infos[j].word.size() == 1)
                    {
                        piece.push_back(infos[j].word[0]);
                        j++;
                    }

                    // cut the sequence with hmm
                    if (!_hmmSeg.cut(piece.begin(), piece.end(), hmmRes))
                    {
                        LogError("_hmmSeg cut failed.");
                        return false;
                    }

                    //put hmm result to return
                    for (uint k = 0; k < hmmRes.size(); k++)
                    {
                        res.push_back(hmmRes[k]);
                    }

                    //clear tmp vars
                    piece.clear();
                    hmmRes.clear();

                    //let i jump over this piece
                    i = j - 1;
                }

                return true;
            }

            virtual bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res)const
            {
                assert(_getInitFlag());
                if(begin >= end)
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
