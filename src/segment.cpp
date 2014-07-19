#include <node.h>
#include <v8.h>
#include <string.h>
#include "CppJieba/MixSegment.hpp"


using namespace std;
using namespace v8;

struct CutTask {
    uv_work_t work;
    Persistent<Function> callback;
    bool success;
    string inputStr;
    string outputStr;
    CutTask(): success(false) {}
};
string ValueToString(Local<Value> val) {
    String::Utf8Value su(val);
    return string(*su);
}


CppJieba::MixSegment segment;

Handle<Value> cutSync(const Arguments& args) {
    HandleScope scope;

    String::Utf8Value param1(args[0]->ToString());
    
    string wordsStr;
    
    vector<string> words;

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


void DoCut(uv_work_t *req) {
    CutTask *task = static_cast<CutTask*>(req->data);
    string wordsStr;
    vector<string> words;

    string inputStr = task->inputStr;

    segment.cut(inputStr, words);
    task->outputStr = (wordsStr << words).c_str();
    task->success = true;
}

void CutCallback(uv_work_t *req, int event) {
    HandleScope scope;
    CutTask *task = static_cast<CutTask*>(req->data);
    Local<Value> args[1];
    args[0] = String::New(task->outputStr.c_str());

    task->callback->Call(Context::GetCurrent()->Global(), 1, args);
    
    task->callback.Dispose();
    delete task;
}

Handle<Value> cut(const Arguments& args) { // args: str callback
    HandleScope scope;
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
    return Undefined();
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
