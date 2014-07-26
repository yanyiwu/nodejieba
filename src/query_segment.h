#ifndef NODEJIEAB_SRC_QUERY_SEGMENT_H
#define NODEJIEAB_SRC_QUERY_SEGMENT_H

#include "utils.h"
#include "CppJieba/QuerySegment.hpp"

extern CppJieba::QuerySegment querySegment;

extern NAN_METHOD(queryLoadDict);
extern NAN_METHOD(queryCutSync);
extern NAN_METHOD(queryCut);

class QueryCutWorker : public NanAsyncWorker {
    public:
        QueryCutWorker(NanCallback *callback, string inputStr)
            : NanAsyncWorker(callback), inputStr(inputStr) {}

        ~QueryCutWorker() {}


        void Execute () {
            querySegment.cut(inputStr, outputWords);
        }

        void HandleOKCallback () {
            NanScope();
            Local<Value> args[1];
            Local<Array> wordList;
            WrapVector(outputWords, wordList);
            args[0] = wordList;
            callback->Call(1, args);
        }

    private:
        string inputStr;
        vector<string> outputWords;
};

#endif
