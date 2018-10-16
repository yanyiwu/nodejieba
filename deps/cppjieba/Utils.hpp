#ifndef CPPJIEBA_UTILS_H
#define CPPJIEBA_UTILS_H

#include <set>
#include "limonp/StringUtil.hpp"

namespace cppjieba {

  using namespace std;
  class Utils {
    public:
        /**
           将allowedPOS字符串，转换成set，例如：allowedPOS="vn,n,v,ns"
        */
        static set<string> GetAllowedPOS(const string& allowedPOS, const string delim=",") {
            set<string> result;
            if("" == allowedPOS) {
                return  result;
            }

            string strs = allowedPOS + delim;
            size_t pos;
            size_t size = strs.size();

            for (size_t i = 0; i < size; ++i) {
                pos = strs.find(delim, i);
                if( pos < size) {
                    string s = strs.substr(i, pos - i);
                    result.insert(s);
                    i = pos + delim.size() - 1;
                }
            }
            return result;
        }

        /**
            判断词性是否属于允许的词性中
        */
        static bool IsAllowedPOS(set<string>& allowedPOSSet, const string& wordTag) {
            bool result = true;
            if (allowedPOSSet.size() > 0 && allowedPOSSet.count(wordTag) == 0) {
                result = false;
            }
            return result;
        }

        /**
            把words字符串转成vector
            wordsStr = '词1/n 词2/v'
        */
        static vector<pair<string, string>> ConvertWordsStr2Vector(const string& wordsStr) {
            vector<pair<string, string>> result;
            vector<string> items = limonp::Split(wordsStr, " ");
            for (size_t i = 0; i < items.size(); i++) {
                vector<string> wordTag = limonp::Split(items[i], "/");
                if (wordTag.size() == 2 && wordTag[0].length() > 0 && wordTag[1].length() > 0) {
                    result.push_back(pair<string, string>(wordTag[0], wordTag[1]));
                }
            }
            return result;
        }

  };

}


#endif // CPPJIEBA_UTILS_H

