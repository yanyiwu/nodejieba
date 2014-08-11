/************************************
 * file enc : utf8
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef LIMONP_CONFIG_H
#define LIMONP_CONFIG_H


#include <map>
#include <fstream>
#include <iostream>
#include <assert.h>
#include "StringUtil.hpp"

namespace Limonp
{
    using namespace std;
    class Config
    {
        public:
            explicit Config(const string& filePath)
            {
                _loadFile(filePath);
            }
        public:
            operator bool ()
            {
                return !_map.empty();
            }
        private:
            void _loadFile(const string& filePath)
            {
                ifstream ifs(filePath.c_str());
                assert(ifs);
                string line;
                vector<string> vecBuf;
                size_t lineno = 0;
                while(getline(ifs, line))
                {
                    lineno ++;
                    trim(line);
                    if(line.empty() || startsWith(line, "#"))
                    {
                        continue;
                    }
                    vecBuf.clear();
                    if(!split(line, vecBuf, "=") || 2 != vecBuf.size())
                    {
                        fprintf(stderr, "line[%s] illegal.\n", line.c_str());
                        assert(false);
                        continue;
                    }
                    string& key = vecBuf[0];
                    string& value = vecBuf[1];
                    trim(key);
                    trim(value);
                    if(!_map.insert(make_pair(key, value)).second)
                    {
                        fprintf(stderr, "key[%s] already exits.\n", key.c_str());
                        assert(false);
                        continue;
                    }
                }
                ifs.close();
            }
        public:
            bool get(const string& key, string& value) const
            {
                map<string, string>::const_iterator it = _map.find(key);
                if(_map.end() != it)
                {
                    value = it->second;
                    return true;
                }
                return false;
            }
            const char* operator [] (const char* key) const
            {
                if(NULL == key)
                {
                    return NULL;
                }
                map<string, string>::const_iterator it = _map.find(key);
                if(_map.end() != it)
                {
                    return it->second.c_str();
                }
                return NULL;
            }
        private:
            map<string, string> _map;
        private:
            friend ostream& operator << (ostream& os, const Config& config);
    };
    
    inline ostream& operator << (ostream& os, const Config& config)
    {
        return os << config._map;
    }
}

#endif
