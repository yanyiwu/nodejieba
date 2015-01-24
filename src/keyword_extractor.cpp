#include "keyword_extractor.h"

CppJieba::KeywordExtractor keyword;

NAN_METHOD (keywordLoadDict) {
    NanScope();
    string param0 = ValueToString(args[0]);
    string param1 = ValueToString(args[1]);
    string param2 = ValueToString(args[2]);
    string param3 = ValueToString(args[3]);
    string param4;
    if(args.Length() >= 5) {
        param4 = ValueToString(args[4]);
    } else {
        param4 = "";
    }
    keyword.init(param0, param1, param2, param3, param4);
    NanReturnValue (NanIntern::Factory<v8::Boolean>::New(true));
}

NAN_METHOD (extractSync) {
    NanScope();

    String::Utf8Value param1(args[0]->ToString());
    size_t topN = args[1]->Int32Value();
    vector<string> words;

    keyword.extract(*param1, words, topN); 

    Local<Array> outArray;
    WrapVector(words, outArray);

    NanReturnValue(outArray);
}

NAN_METHOD(extract) {
    NanScope();
    if(args.Length() == 3) {
        string inputStr = ValueToString(args[0]);
        size_t topN = args[1]->Int32Value();
        Local<Function> callback = args[2].As<Function>();
        
        NanCallback* nanCallback = new NanCallback(callback);
        KeywordWorker* worker = new KeywordWorker(nanCallback, inputStr, topN);
        NanAsyncQueueWorker(worker);
    } else {
        NanThrowTypeError("argc must equals to 2");
    }
    NanReturnUndefined();
}
