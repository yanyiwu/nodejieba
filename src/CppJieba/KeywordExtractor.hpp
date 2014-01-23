#ifndef CPPJIEBA_KEYWORD_EXTRACTOR_H
#define CPPJIEBA_KEYWORD_EXTRACTOR_H

#include "MPSegment.hpp"
#include <cmath>
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

namespace CppJieba
{
    using namespace Limonp;

    //struct KeyWordInfo
    //{
    //    string word;
    //    double tfidf;
    //};

    //inline ostream& operator << (ostream& os, const KeyWordInfo & keyword)
    //{
    //    return os << keyword.word << "," << keyword.idf;
    //}

    class KeywordExtractor
    {
        private:
            MPSegment _segment;
        private:
            unordered_map<string, double> _idfMap;
        protected:
            bool _isInited;
            bool _getInitFlag()const{return _isInited;};
            bool _setInitFlag(bool flag){return _isInited = flag;};
        public:
            operator bool(){return _getInitFlag();};
        public:
            KeywordExtractor(){_setInitFlag(false);};
            explicit KeywordExtractor(const string& dictPath, const string& idfPath){_setInitFlag(init(dictPath, idfPath));};
            ~KeywordExtractor(){};
        public:
            bool init(const string& dictPath, const string& idfPath)
            {
                ifstream ifs(idfPath.c_str());
                if(!ifs)
                {
                    LogError("open %s failed.", idfPath.c_str());
                    return false;
                }
                string line ;
                vector<string> buf;
                for(uint lineno = 0; getline(ifs, line); lineno++)
                {
                    buf.clear();
                    if(line.empty())
                    {
                        LogError("line[%d] empty. skipped.", lineno);
                        continue;
                    }
                    if(!split(line, buf, " ") || buf.size() != 2)
                    {
                        LogError("line %d [%s] illegal. skipped.", lineno, line.c_str());
                        continue;
                    }
                    _idfMap[buf[0]] = atof(buf[1].c_str());
                }
                return _setInitFlag(_segment.init(dictPath));
            };
        public:

            bool extract(const string& str, vector<string>& keywords, uint topN) const
            {
                assert(_getInitFlag());
                vector<pair<string, double> > topWords;
                if(!extract(str, topWords, topN))
                {
                    return false;
                }
                for(uint i = 0; i < topWords.size(); i++)
                {
                    keywords.push_back(topWords[i].first);
                }
                return true;
            }

            bool extract(const string& str, vector<pair<string, double> >& keywords, uint topN) const
            {
                vector<string> words;
                if(!_segment.cut(str, words))
                {
                    LogError("segment cut(%s) failed.", str.c_str());
                    return false;
                }

                unordered_map<string, double> wordmap;
                for(uint i = 0; i < words.size(); i ++)
                {
                    wordmap[ words[i] ] += 1.0;
                }

                for(unordered_map<string, double>::iterator itr = wordmap.begin(); itr != wordmap.end();)
                {
                    unordered_map<string, double>::const_iterator cit = _idfMap.find(itr->first);
                    if(cit != _idfMap.end())
                    {
                        itr->second *= cit->second;
                        itr ++;
                    }
                    else
                    {
                        itr = wordmap.erase(itr);
                    }
                }

                keywords.resize(MIN(topN, wordmap.size()));
                partial_sort_copy(wordmap.begin(), wordmap.end(), keywords.begin(), keywords.end(), _cmp);
                return true;
            }

        private:
            static bool _cmp(const pair<string, uint>& lhs, const pair<string, uint>& rhs)
            {
                return lhs.second > rhs.second;
            }
            
    };
}

#endif


