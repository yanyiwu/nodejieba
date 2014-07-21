#include <node.h>
#include <v8.h>
#include <nan.h>
#include <string.h>
#include "CppJieba/MixSegment.hpp"
#include <iostream>

using namespace std;
using namespace v8;

CppJieba::MixSegment segment;

void WrapVector(vector<string> &ov, Local<Array> &array) {
    array = Array::New(ov.size());
    for(size_t i = 0; i < ov.size(); i++) {
        array->Set(i, String::New(ov[i].c_str()));
    }
}

string ValueToString(Local<Value> val) {
    String::Utf8Value su(val);
    return string(*su);
}

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

NAN_METHOD (cutSync) {
    NanScope();

    String::Utf8Value param1(args[0]->ToString());
    vector<string> words;

    segment.cut(*param1, words); 

    Local<Array> outArray;
    WrapVector(words, outArray);

    NanReturnValue(outArray);
}

NAN_METHOD (loadDict) {
    NanScope();
    String::Utf8Value param0(args[0]->ToString());
    String::Utf8Value param1(args[1]->ToString());
    NanReturnValue (Boolean::New(segment.init(*param0, *param1)));
}

NAN_METHOD (Cut) { 
    NanScope();
    if (args.Length() == 2){
        string inputStr = ValueToString(args[0]);
        Local<Function> callback = args[1].As<Function>();

        NanCallback* nanCallback = new NanCallback(callback);
        CutWorker* worker = new CutWorker(nanCallback, inputStr);
        NanAsyncQueueWorker(worker);
    }
    else {
        NanThrowTypeError("argc must equals to 2");
    }
    NanReturnUndefined();
}

void init(Handle<Object> exports) {
    exports->Set(NanNew("loadDict"),
            NanNew<FunctionTemplate>(loadDict)->GetFunction());
    exports->Set(NanNew("cutSync"),
            NanNew<FunctionTemplate>(cutSync)->GetFunction());
    exports->Set(NanNew("cut"), 
            NanNew<FunctionTemplate>(Cut)->GetFunction());
}

NODE_MODULE(segment, init)
