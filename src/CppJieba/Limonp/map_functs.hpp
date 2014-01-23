/************************************
 * file enc : ascii
 * author   : wuyanyi09@gmail.com
 ************************************/


#ifndef LIMONP_MAP_FUNCTS_H
#define LIMONP_MAP_FUNCTS_H

#include <map>
#include <set>
#include <iostream>
#include <sstream>

#include <unordered_map>
#define HashMap std::unordered_map

namespace Limonp
{
    using namespace std;

    template<class kT, class vT>
        vT getMap(const map<kT, vT>& mp, const kT & key, const vT & defaultVal)
        {
            typename map<kT, vT>::const_iterator it;
            it = mp.find(key);
            if(mp.end() == it)
            {
                return defaultVal;
            }
            return it->second;
        }

    template<class kT, class vT>
        void map2Vec(const map<kT, vT>& mp, vector<pair<kT, vT> > & res)
        {
            typename map<kT, vT>::const_iterator it = mp.begin();
            for(; it != mp.end(); it++)
            {
                res.push_back(*it);
            }
        }
}

#endif
