/************************************
 * file enc : ascii
 * author   : wuyanyi09@gmail.com
 ************************************/

#ifndef LIMONP_ARGV_FUNCTS_H
#define LIMONP_ARGV_FUNCTS_H

#include <set>
#include <sstream>
#include "StringUtil.hpp"

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
                            mpss_[argv[i]] = argv[i+1];
                            i++;
                        }
                        else
                        {
                            sset_.insert(argv[i]);
                        }
                    }
                    else
                    {
                        args_.push_back(argv[i]);
                    }
                }
            }
            ~ArgvContext(){};
        public:
            friend ostream& operator << (ostream& os, const ArgvContext& args); 
            string operator [](size_t i) const
            {
                if(i < args_.size())
                {
                    return args_[i];
                }
                return "";
            }
            string operator [](const string& key) const
            {
                map<string, string>::const_iterator it = mpss_.find(key);
                if(it != mpss_.end())
                {
                    return it->second;
                }
                return "";
            }
        public:
            bool hasKey(const string& key) const
            {
                if(mpss_.find(key) != mpss_.end() || sset_.find(key) != sset_.end())
                {
                    return true;
                }
                return false;
            }
        private:
            vector<string> args_;
            map<string, string> mpss_;
            set<string> sset_; 

    };

    inline ostream& operator << (ostream& os, const ArgvContext& args)
    {
        return os<<args.args_<<args.mpss_<<args.sset_;
    }
}

#endif
