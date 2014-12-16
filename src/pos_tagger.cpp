#include "pos_tagger.h"

CppJieba::PosTagger tagger;

NAN_METHOD (tagSync) {
    NanScope();

    String::Utf8Value param1(args[0]->ToString());
    vector<pair<string, string> > words;

    tagger.tag(*param1, words); 

    Local<Array> outArray;
    WrapPairVector(words, outArray);

    NanReturnValue(outArray);
}
NAN_METHOD (taggerLoadDict) {
    NanScope();
    String::Utf8Value param0(args[0]->ToString());
    String::Utf8Value param1(args[1]->ToString());
    tagger.init(*param0, *param1);
    NanReturnValue (Boolean::New(true));
}

NAN_METHOD (tag) { 
    NanScope();
    if (args.Length() == 2){
        string inputStr = ValueToString(args[0]);
        Local<Function> callback = args[1].As<Function>();

        NanCallback* nanCallback = new NanCallback(callback);
        TaggerWorker* worker = new TaggerWorker(nanCallback, inputStr);
        NanAsyncQueueWorker(worker);
    }
    else {
        NanThrowTypeError("argc must equals to 2");
    }
    NanReturnUndefined();
}
