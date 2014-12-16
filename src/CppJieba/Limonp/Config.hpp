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
                loadFile_(filePath);
            }
        public:
            operator bool ()
            {
                return !map_.empty();
            }
        private:
            void loadFile_(const string& filePath)
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
                    if(!map_.insert(make_pair(key, value)).second)
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
                map<string, string>::const_iterator it = map_.find(key);
                if(map_.end() != it)
                {
                    value = it->second;
                    return true;
                }
                return false;
            }
            bool get(const string& key, int & value) const
            {
                string str;
                if(!get(key, str)) {
                    return false;
                }
                value = atoi(str.c_str());
                return true;
            }
            const char* operator [] (const char* key) const
            {
                if(NULL == key)
                {
                    return NULL;
                }
                map<string, string>::const_iterator it = map_.find(key);
                if(map_.end() != it)
                {
                    return it->second.c_str();
                }
                return NULL;
            }
        public:
            string getConfigInfo() const
            {
                string res;
                res << *this;
                return res;
            }
        private:
            map<string, string> map_;
        private:
            friend ostream& operator << (ostream& os, const Config& config);
    };
    
    inline ostream& operator << (ostream& os, const Config& config)
    {
        return os << config.map_;
    }
}

#endif
