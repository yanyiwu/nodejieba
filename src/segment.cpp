#include <node.h>
#include <v8.h>

#include "nan.h"
#include "CppJieba/MixSegment.hpp"

using namespace v8;

CppJieba::MixSegment segment;

NAN_METHOD(cut) {
    NanScope();

    String::Utf8Value param1(args[0]->ToString());
    std::string wordsStr;
    std::vector<std::string> words;

    segment.cut(*param1, words);
    wordsStr << words;

    NanReturnValue(String::New(wordsStr.c_str()));
}

NAN_METHOD(loadDict) {
    NanScope();
    String::Utf8Value param0(args[0]->ToString());
    String::Utf8Value param1(args[1]->ToString());
    NanReturnValue(Boolean::New(segment.init(*param0, *param1)));
}

void init(Handle<Object> exports) {
    exports->Set(String::NewSymbol("loadDict"),
                FunctionTemplate::New(loadDict)->GetFunction());
    exports->Set(String::NewSymbol("cut"),
                FunctionTemplate::New(cut)->GetFunction());
}

NODE_MODULE(segment, init)
