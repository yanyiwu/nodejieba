#include <node.h>
#include <v8.h>
#include "CppJieba/MixSegment.hpp"

using namespace v8;

CppJieba::MixSegment segment;

Handle<Value> cut(const Arguments& args) {
    HandleScope scope;

    String::Utf8Value param1(args[0]->ToString());
    
    std::string wordsStr;
    
    std::vector<std::string> words;

    segment.cut(*param1, words);
    wordsStr << words;

    return scope.Close(String::New(wordsStr.c_str()));
}

Handle<Value> loadDict(const Arguments& args) {
    HandleScope scope;
    String::Utf8Value param0(args[0]->ToString());
    String::Utf8Value param1(args[1]->ToString());
    return scope.Close(Boolean::New(segment.init(*param0, *param1)));
}

void init(Handle<Object> exports) {
    exports->Set(String::NewSymbol("loadDict"),
                FunctionTemplate::New(loadDict)->GetFunction());
    exports->Set(String::NewSymbol("cut"),
                FunctionTemplate::New(cut)->GetFunction());
}

NODE_MODULE(segment, init)
