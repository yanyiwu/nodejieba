#ifndef CPPJIEBA_POS_TAGGING_H
#define CPPJIEBA_POS_TAGGING_H

#include "MixSegment.hpp"
#include "Limonp/StringUtil.hpp"
#include "DictTrie.hpp"

namespace CppJieba
{
    using namespace Limonp;

    class PosTagger: public InitOnOff
    {
        private:
            MixSegment _segment;
            DictTrie _dictTrie;

        public:
            PosTagger(){_setInitFlag(false);};
            PosTagger(const string& dictPath, const string& hmmFilePath, const string& charStatus, const string& startProb, const string& emitProb, const string& endProb, const string& transProb)
            {
                _setInitFlag(init(dictPath, hmmFilePath, charStatus, startProb, emitProb, endProb, transProb));
            };
            ~PosTagger(){};
        public:
            bool init(const string& dictPath, const string& hmmFilePath, const string& charStatus, const string& startProb, const string& emitProb, const string& endProb, const string& transProb)
            {
                
                assert(!_getInitFlag());
                _dictTrie.init(dictPath);
                assert(_dictTrie);
                return _setInitFlag(_segment.init(dictPath, hmmFilePath));
            };

            bool tag(const string& src, vector<pair<string, string> >& res)
            {
                assert(_getInitFlag());
                vector<string> cutRes;
                if (!_segment.cut(src, cutRes))
                {
                    LogError("_mixSegment cut failed");
                    return false;
                }

                const DictUnit *tmp = NULL;
                Unicode unico;
                for (vector<string>::iterator itr = cutRes.begin(); itr != cutRes.end(); ++itr)
                {
                    if (!TransCode::decode(*itr, unico))
                    {
                        LogError("decode failed.");
                        return false;
                    }
                    tmp = _dictTrie.find(unico.begin(), unico.end());
                    res.push_back(make_pair(*itr, tmp == NULL ? "x" : tmp->tag));
                }
                tmp = NULL;
                return !res.empty();
            }
    };
}

#endif
