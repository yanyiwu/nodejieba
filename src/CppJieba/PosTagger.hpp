#ifndef CPPJIEBA_POS_TAGGING_H
#define CPPJIEBA_POS_TAGGING_H

#include "MixSegment.hpp"
#include "Limonp/StringUtil.hpp"
#include "DictTrie.hpp"

namespace CppJieba
{
    using namespace Limonp;

    static const char* const POS_M = "m";
    static const char* const POS_ENG = "eng";
    static const char* const POS_X = "x";

    class PosTagger
    {
        private:
            MixSegment _segment;
            const DictTrie * _dictTrie;

        public:
            PosTagger()
            {}
            PosTagger(
                const string& dictPath, 
                const string& hmmFilePath,
                const string& userDictPath = ""
            )
            {
                init(dictPath, hmmFilePath, userDictPath);
            };
            ~PosTagger(){};
        public:
            void init(
                const string& dictPath, 
                const string& hmmFilePath,
                const string& userDictPath = ""
            )
            {
                LIMONP_CHECK(_segment.init(dictPath, hmmFilePath, userDictPath));
                _dictTrie = _segment.getDictTrie();
                LIMONP_CHECK(_dictTrie);
            };
            

            bool tag(const string& src, vector<pair<string, string> >& res) const
            {
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
                    tmp = _dictTrie->find(unico.begin(), unico.end());
                    if(tmp == NULL || tmp->tag.empty())
                    {
                        res.push_back(make_pair(*itr, _specialRule(unico)));
                    }
                    else
                    {
                        res.push_back(make_pair(*itr, tmp->tag));
                    }
                }
                return !res.empty();
            }
        private:
            const char* _specialRule(const Unicode& unicode) const
            {
                size_t m = 0;
                size_t eng = 0;
                for(size_t i = 0; i < unicode.size() && eng < unicode.size() / 2; i++) 
                {
                    if(unicode[i] < 0x80)
                    {
                        eng ++;
                        if('0' <= unicode[i] && unicode[i] <= '9')
                        {
                            m++;
                        }
                    }
                }
                // ascii char is not found
                if(eng == 0)
                {
                    return POS_X;
                }
                // all the ascii is number char
                if(m == eng)
                {
                    return POS_M;
                }
                // the ascii chars contain english letter
                return POS_ENG;
            }
    };
}

#endif
