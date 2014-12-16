#ifndef CPPJIEBA_QUERYSEGMENT_H
#define CPPJIEBA_QUERYSEGMENT_H

#include <algorithm>
#include <set>
#include <cassert>
#include "Limonp/Logger.hpp"
#include "DictTrie.hpp"
#include "ISegment.hpp"
#include "SegmentBase.hpp"
#include "FullSegment.hpp"
#include "MixSegment.hpp"
#include "TransCode.hpp"
#include "DictTrie.hpp"

namespace CppJieba
{
    class QuerySegment: public SegmentBase
    {
    private:
        MixSegment _mixSeg;
        FullSegment _fullSeg;
        size_t _maxWordLen;

    public:
        QuerySegment(){};
        QuerySegment(const string& dict, const string& model, size_t maxWordLen)
        {
            init(dict, model, maxWordLen);
        };
        virtual ~QuerySegment(){};
    public:
        bool init(const string& dict, const string& model, size_t maxWordLen)
        {
            LIMONP_CHECK(_mixSeg.init(dict, model));
            LIMONP_CHECK(_fullSeg.init(_mixSeg.getDictTrie()));
            assert(maxWordLen);
            _maxWordLen = maxWordLen;
            return true;
        }

    public:
        using SegmentBase::cut;

    public:
        bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<Unicode>& res) const
        {
            if (begin >= end)
            {
                LogError("begin >= end");
                return false;
            }

            //use mix cut first
            vector<Unicode> mixRes;
            if (!_mixSeg.cut(begin, end, mixRes))
            {
                LogError("_mixSeg cut failed.");
                return false;
            }

            vector<Unicode> fullRes;
            for (vector<Unicode>::const_iterator mixResItr = mixRes.begin(); mixResItr != mixRes.end(); mixResItr++)
            {
                
                // if it's too long, cut with _fullSeg, put fullRes in res
                if (mixResItr->size() > _maxWordLen)
                {
                    if (_fullSeg.cut(mixResItr->begin(), mixResItr->end(), fullRes))
                    {
                       for (vector<Unicode>::const_iterator fullResItr = fullRes.begin(); fullResItr != fullRes.end(); fullResItr++)
                       {
                           res.push_back(*fullResItr);
                       }

                       //clear tmp res
                       fullRes.clear();
                    }
                }
                else // just use the mix result
                {
                    res.push_back(*mixResItr);
                }
            }

            return true;
        }


        bool cut(Unicode::const_iterator begin, Unicode::const_iterator end, vector<string>& res) const
        {
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
