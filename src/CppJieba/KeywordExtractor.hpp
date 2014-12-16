#ifndef CPPJIEBA_KEYWORD_EXTRACTOR_H
#define CPPJIEBA_KEYWORD_EXTRACTOR_H

#include "MixSegment.hpp"
#include <cmath>
#include <set>

namespace CppJieba
{
    using namespace Limonp;

    /*utf8*/
    class KeywordExtractor
    {
        private:
            MixSegment _segment;
        private:
            unordered_map<string, double> _idfMap;
            double _idfAverage;

            unordered_set<string> _stopWords;
        public:
            KeywordExtractor(){};
            KeywordExtractor(const string& dictPath, const string& hmmFilePath, const string& idfPath, const string& stopWordPath)
            {
                LIMONP_CHECK(init(dictPath, hmmFilePath, idfPath, stopWordPath));
            };
            ~KeywordExtractor(){};

        public:
            bool init(const string& dictPath, const string& hmmFilePath, const string& idfPath, const string& stopWordPath)
            {
                _loadIdfDict(idfPath);
                _loadStopWordDict(stopWordPath);
                LIMONP_CHECK(_segment.init(dictPath, hmmFilePath));
                return true;
            };
        public:

            bool extract(const string& str, vector<string>& keywords, size_t topN) const
            {
                vector<pair<string, double> > topWords;
                if(!extract(str, topWords, topN))
                {
                    return false;
                }
                for(size_t i = 0; i < topWords.size(); i++)
                {
                    keywords.push_back(topWords[i].first);
                }
                return true;
            }

            bool extract(const string& str, vector<pair<string, double> >& keywords, size_t topN) const
            {
                vector<string> words;
                if(!_segment.cut(str, words))
                {
                    LogError("segment cut(%s) failed.", str.c_str());
                    return false;
                }

                map<string, double> wordmap;
                for(vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
                {
                    if(_isSingleWord(*iter))
                    {
                        continue;
                    }
                    wordmap[*iter] += 1.0;
                }

                for(map<string, double>::iterator itr = wordmap.begin(); itr != wordmap.end(); )
                {
                    if(_stopWords.end() != _stopWords.find(itr->first))
                    {
                        wordmap.erase(itr++);
                        continue;
                    }

                    unordered_map<string, double>::const_iterator cit = _idfMap.find(itr->first);
                    if(cit != _idfMap.end())
                    {
                        itr->second *= cit->second;
                    }
                    else
                    {
                        itr->second *= _idfAverage;
                    }
                    itr ++;
                }

                keywords.clear();
                std::copy(wordmap.begin(), wordmap.end(), std::inserter(keywords, keywords.begin()));
                topN = min(topN, keywords.size());
                partial_sort(keywords.begin(), keywords.begin() + topN, keywords.end(), _cmp);
                keywords.resize(topN);
                return true;
            }
        private:
            void _loadIdfDict(const string& idfPath)
            {
                ifstream ifs(idfPath.c_str());
                if(!ifs)
                {
                    LogError("open %s failed.", idfPath.c_str());
                    assert(false);
                }
                string line ;
                vector<string> buf;
                double idf = 0.0;
                double idfSum = 0.0;
                size_t lineno = 0;
                for(;getline(ifs, line); lineno++)
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
                    idf = atof(buf[1].c_str());
                    _idfMap[buf[0]] = idf;
                    idfSum += idf;

                } 

                assert(lineno);
                _idfAverage = idfSum / lineno;
                assert(_idfAverage > 0.0);
            }
            void _loadStopWordDict(const string& filePath)
            {
                ifstream ifs(filePath.c_str());
                if(!ifs)
                {
                    LogError("open %s failed.", filePath.c_str());
                    assert(false);
                }
                string line ;
                while(getline(ifs, line))
                {
                    _stopWords.insert(line);
                }
                assert(_stopWords.size());
            }
        private:
            bool _isSingleWord(const string& str) const
            {
                Unicode unicode;
                TransCode::decode(str, unicode);
                if(unicode.size() == 1)
                  return true;
                return false;
            }

        private:
            static bool _cmp(const pair<string, double>& lhs, const pair<string, double>& rhs)
            {
                return lhs.second > rhs.second;
            }
            
    };
}

#endif


