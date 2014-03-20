/************************************
 * file enc : ASCII
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef CPPJIEBA_TRIE_H
#define CPPJIEBA_TRIE_H

#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include <stdint.h>
#include <cmath>
#include <limits>
#include "Limonp/str_functs.hpp"
#include "Limonp/logger.hpp"
#include "Limonp/InitOnOff.hpp"
#include "TransCode.hpp"



namespace CppJieba
{
    using namespace Limonp;
    const double MIN_DOUBLE = -3.14e+100;
    const double MAX_DOUBLE = 3.14e+100;
    const size_t DICT_COLUMN_NUM = 3;
    typedef map<uint16_t, struct TrieNode*> TrieNodeMap;
    struct TrieNode
    {
        TrieNodeMap hmap;
        bool isLeaf;
        size_t nodeInfoPos;
        TrieNode()
        {
            isLeaf = false;
            nodeInfoPos = 0;
        }
    };

    struct TrieNodeInfo
    {
        Unicode word;
        size_t freq;
        string tag;
        double logFreq; //logFreq = log(freq/sum(freq));
        TrieNodeInfo():freq(0),logFreq(0.0)
        {}
        TrieNodeInfo(const TrieNodeInfo& nodeInfo):word(nodeInfo.word), freq(nodeInfo.freq), tag(nodeInfo.tag), logFreq(nodeInfo.logFreq)
        {}
        TrieNodeInfo(const Unicode& _word):word(_word),freq(0),logFreq(MIN_DOUBLE)
        {}
    };

    inline ostream& operator << (ostream& os, const TrieNodeInfo & nodeInfo)
    {
        return os << nodeInfo.word << ":" << nodeInfo.freq << ":" << nodeInfo.tag << ":" << nodeInfo.logFreq ;
    }

    typedef map<size_t, const TrieNodeInfo*> DagType;

    class Trie: public InitOnOff
    {

        private:
            TrieNode* _root;
            vector<TrieNodeInfo> _nodeInfos;

            int64_t _freqSum;
            double _minLogFreq;

        public:
            Trie()
            {
                _root = NULL;
                _freqSum = 0;
                _minLogFreq = MAX_DOUBLE;
                _setInitFlag(false);
            }
            Trie(const string& filePath)
            {
                Trie();
                _setInitFlag(init(filePath));
            }
            ~Trie()
            {
                _deleteNode(_root);
            }
        public:
            bool init(const string& filePath)
            {
                assert(!_getInitFlag());

                _root = new TrieNode;
                assert(_root);
                if(!_trieInsert(filePath))
                {
                    LogError("_trieInsert failed.");
                    return false;
                }
                _countWeight();
                return _setInitFlag(true);
            }

        public:
            const TrieNodeInfo* find(Unicode::const_iterator begin, Unicode::const_iterator end)const
            {
                TrieNodeMap::const_iterator citer;
                TrieNode* p = _root;
                for(Unicode::const_iterator it = begin; it != end; it++)
                {
                    uint16_t chUni = *it;
                    citer = p->hmap.find(chUni);
                    if(p-> hmap.end() == citer)
                    {
                        return NULL;
                    }
                    p = citer->second;
                }
                if(p->isLeaf)
                {
                    return &(_nodeInfos[p->nodeInfoPos]);
                }
                return NULL;
            }

            bool find(Unicode::const_iterator begin, Unicode::const_iterator end, vector<pair<size_t, const TrieNodeInfo*> >& res) const
            {
                TrieNodeMap::const_iterator citer;
                TrieNode* p = _root;
                for (Unicode::const_iterator itr = begin; itr != end; itr++)
                {
                    citer = p->hmap.find(*itr);
                    if(p->hmap.end() == citer)
                    {
                        break;
                    }
                    p = citer->second;
                    if(p->isLeaf)
                    {
                        res.push_back(make_pair(itr-begin, &_nodeInfos[p->nodeInfoPos]));
                    }
                }
                return !res.empty();
            }

            bool find(Unicode::const_iterator begin, Unicode::const_iterator end, size_t offset, DagType & res) const
            {
                TrieNode* p = _root;
                TrieNodeMap::const_iterator citer;
                for (Unicode::const_iterator itr = begin; itr != end; itr++)
                {
                    citer = p->hmap.find(*itr);
                    if(p->hmap.end() == citer)
                    {
                        break;
                    }
                    p = citer->second;
                    if(p->isLeaf)
                    {
                        res[itr - begin + offset] = &_nodeInfos[p->nodeInfoPos];
                    }
                }
                return !res.empty();
            }

        public:
            double getMinLogFreq() const {return _minLogFreq;};

        private:
            void _insert(const TrieNodeInfo& nodeInfo, size_t nodeInfoPos)
            {
                const Unicode& unico = nodeInfo.word;
                TrieNode* p = _root;
                for(size_t i = 0; i < unico.size(); i++)
                {
                    uint16_t cu = unico[i];
                    assert(p);
                    if(!isIn(p->hmap, cu))
                    {
                        TrieNode * next = new TrieNode;
                        assert(next);
                        p->hmap[cu] = next;
                        p = next;
                    }
                    else
                    {
                        p = p->hmap[cu];
                    }
                }

                p->isLeaf = true;
                p->nodeInfoPos = nodeInfoPos;
            }

        private:
            bool _trieInsert(const string& filePath)
            {
                ifstream ifs(filePath.c_str());
                if(!ifs)
                {
                    LogError("open %s failed.", filePath.c_str());
                    return false;
                }
                string line;
                vector<string> buf;

                TrieNodeInfo nodeInfo;
                for(size_t lineno = 0 ; getline(ifs, line); lineno++)
                {
                    split(line, buf, " ");
                    assert(buf.size() == DICT_COLUMN_NUM);
                    if(!TransCode::decode(buf[0], nodeInfo.word))
                    {
                        LogError("line[%u:%s] illegal.", lineno, line.c_str());
                        return false;
                    }
                    nodeInfo.freq = atoi(buf[1].c_str());
                    nodeInfo.tag = buf[2];
                    
                    _nodeInfos.push_back(nodeInfo);

                }
                for(size_t i = 0; i < _nodeInfos.size(); i++)
                {
                    _insert(_nodeInfos[i], i);
                }
                return true;
            }
            void _countWeight()
            {
                //freq total freq
                _freqSum = 0;
                for(size_t i = 0; i < _nodeInfos.size(); i++)
                {
                    _freqSum += _nodeInfos[i].freq;
                }

                assert(_freqSum);

                //normalize
                for(size_t i = 0; i < _nodeInfos.size(); i++)
                {
                    TrieNodeInfo& nodeInfo = _nodeInfos[i];
                    assert(nodeInfo.freq);
                    nodeInfo.logFreq = log(double(nodeInfo.freq)/double(_freqSum));
                    if(_minLogFreq > nodeInfo.logFreq)
                    {
                        _minLogFreq = nodeInfo.logFreq;
                    }
                }

            }

            void _deleteNode(TrieNode* node)
            {
                if(!node)
                {
                    return;
                }
                for(TrieNodeMap::iterator it = node->hmap.begin(); it != node->hmap.end(); it++)
                {
                    TrieNode* next = it->second;
                    _deleteNode(next);
                }
                delete node;
            }

    };
}

#endif
