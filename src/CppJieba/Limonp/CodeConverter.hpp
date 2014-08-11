#ifndef LIMONP_CODE_CONVERTER_HPP
#define LIMONP_CODE_CONVERTER_HPP

#include <iconv.h> 
#include <iostream> 
#include <memory.h>

namespace Limonp
{
    using namespace std; 
    class CodeConverter
    { 
        public: 
            CodeConverter(const char *from_charset,const char *to_charset) 
            { 
                _iconv_handle = iconv_open(to_charset,from_charset); 
            } 

            ~CodeConverter() 
            { 
                iconv_close(_iconv_handle); 
            } 

            bool convert(const string& from, string& to) const
            {
                char * pfrom = (char*)from.c_str();
                size_t from_size = from.size();
                to.resize(from_size * 2); // iconv failed, may be you can raise this 2 to bigger number.
                char * pto = (char*)to.c_str();
                size_t to_size = to.size();
                if(size_t(-1) == iconv(_iconv_handle, &pfrom, &from_size, &pto, &to_size))
                {
                    to.clear();
                    return false;
                }
                to.resize(to.size() - to_size);
                return true;
            }
        private: 
            iconv_t _iconv_handle; 
    }; 
    
    inline bool code_convert(const char* from_charset, const char* to_charset, const string& from, string& to)
    {
        CodeConverter cc(from_charset, to_charset);
        return cc.convert(from, to);
    }
}

#endif
