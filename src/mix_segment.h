#ifndef NODEJIEAB_SRC_MIX_SEGMENT_H
#define NODEJIEAB_SRC_MIX_SEGMENT_H
#include "utils.h"
#include "CppJieba/MixSegment.hpp"

extern CppJieba::MixSegment segment;

extern NAN_METHOD(loadDict);
extern NAN_METHOD(cutSync);
extern NAN_METHOD(cut);

class CutWorker : public NanAsyncWorker {
    public:
        CutWorker(NanCallback *callback, string inputStr)
            : NanAsyncWorker(callback), inputStr(inputStr) {}

        ~CutWorker() {}


        void Execute () {
            segment.cut(inputStr, outputWords);
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
