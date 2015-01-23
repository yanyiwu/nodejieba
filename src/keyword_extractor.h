#ifndef NODEJIEAB_SRC_KEYWORD_EXTRACTOR_H
#define NODEJIEAB_SRC_KEYWORD_EXTRACTOR_H

#include "utils.h"
#include "CppJieba/KeywordExtractor.hpp"

extern CppJieba::KeywordExtractor keyword;

extern NAN_METHOD(keywordLoadDict);
extern NAN_METHOD(extractSync);
extern NAN_METHOD(extract);

class KeywordWorker : public NanAsyncWorker {
    public:
        KeywordWorker(NanCallback * callback, string s, size_t n)
            : NanAsyncWorker(callback), inputStr(s), topN(n) {
            }
        ~KeywordWorker() {}
        void Execute () {
            keyword.extract(inputStr, outputWords, topN);
        }

        void HandleOKCallback() {
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
        size_t topN;
};

#endif
