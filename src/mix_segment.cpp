#include "mix_segment.h"

CppJieba::MixSegment segment;

NAN_METHOD (loadDict) {
    NanScope();
    String::Utf8Value param0(args[0]->ToString());
    String::Utf8Value param1(args[1]->ToString());
    if(args.Length() >= 3) {
      String::Utf8Value param2(args[2]->ToString());
      NanReturnValue (NanIntern::Factory<v8::Boolean>::New(segment.init(*param0, *param1, *param2)));
    } else {
      NanReturnValue (NanIntern::Factory<v8::Boolean>::New(segment.init(*param0, *param1)));
    }
}

NAN_METHOD (cutSync) {
    NanScope();

    String::Utf8Value param1(args[0]->ToString());
    vector<string> words;

    segment.cut(*param1, words); 

    Local<Array> outArray;
    WrapVector(words, outArray);

    NanReturnValue(outArray);
}

NAN_METHOD (cut) { 
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
