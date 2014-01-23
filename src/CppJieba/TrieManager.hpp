#ifndef CPPJIEBA_TRIEMANAGER_H
#define CPPJIEBA_TRIEMANAGER_H

#include "Trie.hpp"
#include "Limonp/md5.hpp"
#include "Limonp/logger.hpp"

namespace CppJieba
{
    using namespace Limonp;
    class TrieManager
    {
        private:
            unordered_map<std::string, Trie*> _tries;
            TrieManager(){};
            TrieManager(TrieManager& tm){};
        public:
            Trie* getTrie(const char* dictpath) 
            {
                string md5;
                if (!md5File(dictpath, md5))
                {
                    LogError("error when getting md5 for file '%s'", dictpath);
                    return NULL;
                }

                if (_tries.find(md5) != _tries.end())
                {
                    return _tries[md5.c_str()];
                }

                //LogDebug("create a new trie for md5: '%s'", md5.c_str());
                Trie* trie = NULL;
                    trie = new Trie();
                if (NULL == trie)
                {
                    LogError("get NULL from new trie for file '%s'", dictpath);
                    return NULL;
                }

                if (!trie->init())
                { 
                    LogError("trie init error for file '%s'", dictpath);
                    return NULL;
                }

                if (!trie->loadDict(dictpath))
                {
                    LogError("trie->loadDict(%s) failed...", dictpath);
                    return NULL;
                }

                _tries[md5.c_str()] = trie;
                LogDebug("trie->loadDict(%s)", dictpath);
                return trie;
            }

            static TrieManager& getInstance()
            {
                static TrieManager _this;
                return _this;
            }
    };
}
#endif
