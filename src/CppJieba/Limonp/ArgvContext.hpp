/************************************
 * file enc : ascii
 * author   : wuyanyi09@gmail.com
 ************************************/

#ifndef LIMONP_ARGV_FUNCTS_H
#define LIMONP_ARGV_FUNCTS_H

#include <set>
#include <sstream>
#include "str_functs.hpp"
#include "map_functs.hpp"

namespace Limonp
{
    using namespace std;
    class ArgvContext
    {
        public :
            ArgvContext(int argc, const char* const * argv)
            {

                for(int i = 0; i < argc; i++)
                {
                    if(startsWith(argv[i], "-"))
                    {
                        if(i + 1 < argc && !startsWith(argv[i + 1], "-"))
                        {
                            _mpss[argv[i]] = argv[i+1];
                            i++;
                        }
                        else
                        {
                            _sset.insert(argv[i]);
                        }
                    }
                    else
                    {
                        _args.push_back(argv[i]);
                    }
                }
            }
            ~ArgvContext(){};
        public:
            friend ostream& operator << (ostream& os, const ArgvContext& args); 
            string operator [](uint i) const
            {
                if(i < _args.size())
                {
                    return _args[i];
                }
                return "";
            }
            string operator [](const string& key) const
            {
                map<string, string>::const_iterator it = _mpss.find(key);
                if(it != _mpss.end())
                {
                    return it->second;
                }
                return "";
            }
        public:
            bool hasKey(const string& key) const
            {
                if(_mpss.find(key) != _mpss.end() || _sset.find(key) != _sset.end())
                {
                    return true;
                }
                return false;
            }
        private:
            vector<string> _args;
            map<string, string> _mpss;
            set<string> _sset; 

    };

    inline ostream& operator << (ostream& os, const ArgvContext& args)
    {
        return os<<args._args<<args._mpss<<args._sset;
    }
            //string toString()
            //{
            //    stringstream ss;
            //    return ss.str();
            //}
}

#endif
