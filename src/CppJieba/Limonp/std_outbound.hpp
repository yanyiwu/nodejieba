#ifndef LIMONP_STD_OUTBOUND_H
#define LIMONP_STD_OUTBOUND_H

#include "map_functs.hpp"
#include <map>
#include <set>

namespace std
{
    template<typename T>
        ostream& operator << (ostream& os, const vector<T>& vec)
        {
            if(vec.empty())
            {
                return os << "[]";
            }
            os<<"[\""<<vec[0];
            for(uint i = 1; i < vec.size(); i++)
            {
                os<<"\", \""<<vec[i];
            }
            os<<"\"]";
            return os;
        }
    template<class T1, class T2>
        ostream& operator << (ostream& os, const pair<T1, T2>& pr)
        {
            os << pr.first << ":" << pr.second ;
            return os;
        }


    template<class T>
        string& operator << (string& str, const T& obj)
        {
            stringstream ss;
            ss << obj; // call ostream& operator << (ostream& os,
            return str = ss.str();
        }

    template<class T1, class T2>
        ostream& operator << (ostream& os, const map<T1, T2>& mp)
        {
            if(mp.empty())
            {
                os<<"{}";
                return os;
            }
            os<<'{';
            typename map<T1, T2>::const_iterator it = mp.begin();
            os<<*it;
            it++;
            while(it != mp.end())
            {
                os<<", "<<*it;
                it++;
            }
            os<<'}';
            return os;
        }
    template<class T1, class T2>
        ostream& operator << (ostream& os, const HashMap<T1, T2>& mp)
        {
            if(mp.empty())
            {
                return os << "{}";
            }
            os<<'{';
            typename HashMap<T1, T2>::const_iterator it = mp.begin();
            os<<*it;
            it++;
            while(it != mp.end())
            {
                os<<", "<<*it++;
            }
            return os<<'}';
        }

    template<class T>
        ostream& operator << (ostream& os, const set<T>& st)
        {
            if(st.empty())
            {
                os << "{}";
                return os;
            }
            os<<'{';
            typename set<T>::const_iterator it = st.begin();
            os<<*it;
            it++;
            while(it != st.end())
            {
                os<<", "<<*it;
                it++;
            }
            os<<'}';
            return os;
        }
}

#endif
