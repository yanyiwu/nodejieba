#ifndef CPPJIEBA_SEGMENTINTERFACE_H
#define CPPJIEBA_SEGMENTINTERFACE_H


namespace CppJieba
{
    class ISegment
    {
        public:
            virtual ~ISegment(){};
        public:
            virtual bool cut(Unicode::const_iterator begin , Unicode::const_iterator end, vector<string>& res) const = 0;
            virtual bool cut(const string& str, vector<string>& res) const = 0;
    };
}

#endif
