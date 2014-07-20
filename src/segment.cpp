#include <node.h>
#include <v8.h>
#include "nan.h"
#include <string.h>
#include "CppJieba/MixSegment.hpp"
#include <iostream>


using namespace std;
using namespace v8;

struct CutTask {
    uv_work_t work;
    Persistent<Function> callback;
    bool success;
    string inputStr;
    vector<string> outputWords;
    CutTask(): success(false) {}
};
string ValueToString(Local<Value> val) {
    String::Utf8Value su(val);
    return string(*su);
}

void WrapVector(vector<string> &ov, Local<Array> &array) {
    array = Array::New(ov.size());
    for(size_t i = 0; i < ov.size(); i++) {
	    array->Set(i, String::New(ov[i].c_str()));
    }
}

CppJieba::MixSegment segment;

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


void DoCut(uv_work_t *req) {
    CutTask *task = static_cast<CutTask*>(req->data);
    string wordsStr;

    string inputStr = task->inputStr;

    segment.cut(inputStr, task->outputWords);
    /*
    for(int i = 0; i < words.size(); i++) {
	    cout<<i<<" =>>>> "<<words[i]<<endl;
    }
    */
    task->success = true;
}


void CutCallback(uv_work_t *req, int event) {
    NanScope();
    CutTask *task = static_cast<CutTask*>(req->data);
    Local<Value> args[1];
    Local<Array> wordList;
    WrapVector(task->outputWords, wordList);

    args[0] = wordList;

    task->callback->Call(Context::GetCurrent()->Global(), 1, args);
    
    task->callback.Dispose();
    delete task;
}

NAN_METHOD (cut) { 
    NanScope();
    if (args.Length() == 2){

        Local<Function> callback = Local<Function>::Cast(args[1]);
        CutTask *task = new CutTask();
        task->inputStr = string(ValueToString(args[0]));
        task->callback = Persistent<Function>::New(callback);
        task->work.data = task;

        int status = uv_queue_work(uv_default_loop(), &(task->work), DoCut, 
                CutCallback);

        if (status != 0) {
            cout << "uv_queue_work return " << status <<endl;
        }
    }
    else {
        ThrowException(Exception::TypeError(String::New("argc must equals to 2")));
    }
    NanReturnValue (Undefined());
}




void init(Handle<Object> exports) {
    exports->Set(String::NewSymbol("loadDict"),
                FunctionTemplate::New(loadDict)->GetFunction());
    exports->Set(String::NewSymbol("cutSync"),
                FunctionTemplate::New(cutSync)->GetFunction());
    exports->Set(String::NewSymbol("cut"), 
                FunctionTemplate::New(cut)->GetFunction());
}

NODE_MODULE(segment, init)
