#ifndef NODEJIEAB_SRC_POSTAGGER_H
#define NODEJIEAB_SRC_POSTAGGER_H
#include "utils.h"
#include "CppJieba/PosTagger.hpp"

extern CppJieba::PosTagger tagger;

extern NAN_METHOD(taggerLoadDict);
extern NAN_METHOD(tagSync);
extern NAN_METHOD(tag);

class TaggerWorker : public NanAsyncWorker {
    public:
        TaggerWorker(NanCallback *callback, string inputStr)
            : NanAsyncWorker(callback), inputStr(inputStr) {}

        ~TaggerWorker() {}


        void Execute () {
            tagger.tag(inputStr, outputWords);
        }

        void HandleOKCallback () {
            NanScope();
            Local<Value> args[1];
            Local<Array> wordList;
            WrapPairVector(outputWords, wordList);
            args[0] = wordList;
            callback->Call(1, args);
        }

    private:
        string inputStr;
        vector<pair<string, string> > outputWords;
};

#endif
