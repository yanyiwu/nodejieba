/************************************
 * file enc : utf8
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef LIMONP_CONFIG_H
#define LIMONP_CONFIG_H


#include <map>
#include <fstream>
#include <iostream>
#include "logger.hpp"
#include "str_functs.hpp"

namespace Limonp
{
    using namespace std;
    class Config
    {
        public:
            Config(const char * const filePath)
            {
                _loadFile(filePath);
            }
        public:
            operator bool ()
            {
                return !_map.empty();
            }
        private:
            bool _loadFile(const char * const filePath)
            {
                ifstream ifs(filePath);
                if(!ifs)
                {
                    LogFatal("open file[%s] failed.", filePath);
                    return false;
                }
                string line;
                vector<string> vecBuf;
                uint lineno = 0;
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
                        LogFatal("line[%d:%s] is illegal.", lineno, line.c_str());
                        return false;
                    }
                    string& key = vecBuf[0];
                    string& value = vecBuf[1];
                    trim(key);
                    trim(value);
                    if(_map.end() != _map.find(key))
                    {
                        LogFatal("key[%s] already exists.", key.c_str());
                        return false;
                    }
                    _map[key] = value;
                }
                ifs.close();
                return true;
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
