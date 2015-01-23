#include "query_segment.h"

CppJieba::QuerySegment querySegment;

NAN_METHOD (queryLoadDict) {
    NanScope();
    String::Utf8Value param0(args[0]->ToString());
    String::Utf8Value param1(args[1]->ToString());
    String::Utf8Value param2(args[2]->ToString());
    int param3 = args.Length() >= 4 ? args[3]->Int32Value() : 4;
    NanReturnValue (NanIntern::Factory<v8::Boolean>::New(querySegment.init(*param0, *param1, param3, *param2)));
}

NAN_METHOD (queryCutSync) {
    NanScope();

    String::Utf8Value param1(args[0]->ToString());
    vector<string> words;

    querySegment.cut(*param1, words); 

    Local<Array> outArray;
    WrapVector(words, outArray);

    NanReturnValue(outArray);
}

NAN_METHOD (queryCut) { 
    NanScope();
    if (args.Length() == 2){
        string inputStr = ValueToString(args[0]);
        Local<Function> callback = args[1].As<Function>();

        NanCallback* nanCallback = new NanCallback(callback);
        QueryCutWorker* worker = new QueryCutWorker(nanCallback, inputStr);
        NanAsyncQueueWorker(worker);
    }
    else {
        NanThrowTypeError("argc must equals to 2");
    }
    NanReturnUndefined();
}
