#include "nodejieba.h"

CppJieba::Application* gApp;

NAN_METHOD(load) {
  NanScope();

  if(args.Length() != 5) {
    NanReturnValue (NanIntern::Factory<v8::Boolean>::New(false));
  }

  String::Utf8Value dictPath(args[0]->ToString());
  String::Utf8Value modelPath(args[1]->ToString());
  String::Utf8Value userDictPath(args[2]->ToString());
  String::Utf8Value idfPath(args[3]->ToString());
  String::Utf8Value stopWordsPath(args[4]->ToString());

  gApp = new CppJieba::Application(*dictPath, 
                                  *modelPath, 
                                  *userDictPath,
                                  *idfPath, 
                                  *stopWordsPath);

  NanReturnValue (NanIntern::Factory<v8::Boolean>::New(true));
}

NAN_METHOD(cut) {
  NanScope();
  if (args.Length() == 0) {
    NanReturnValue (NanIntern::Factory<v8::Boolean>::New(false));
  }
  string sentence = *(String::Utf8Value(args[0]->ToString()));
  vector<string> words;

  if (args.Length() == 2) {
    string method = *(String::Utf8Value(args[1]->ToString()));
    if ("MP" == method) {
      gApp->cut(sentence, words, CppJieba::METHOD_MP); 
    } else if ("HMM" == method) {
      gApp->cut(sentence, words, CppJieba::METHOD_HMM); 
    } else if ("MIX" == method) {
      gApp->cut(sentence, words, CppJieba::METHOD_MIX); 
    } else if ("FULL" == method) {
      gApp->cut(sentence, words, CppJieba::METHOD_FULL); 
    } else if ("QUERY" == method) {
      gApp->cut(sentence, words, CppJieba::METHOD_QUERY); 
    } else {
      gApp->cut(sentence, words, CppJieba::METHOD_MIX); 
    }
  } else {
    gApp->cut(sentence, words, CppJieba::METHOD_MIX); 
  }

  Local<Array> outArray;
  WrapVector(words, outArray);

  NanReturnValue(outArray);
}

NAN_METHOD(tag) {
  NanScope();
  if (args.Length() == 0) {
    NanReturnValue (NanIntern::Factory<v8::Boolean>::New(false));
  }

  vector<pair<string, string> > words;
  string sentence = *(String::Utf8Value(args[0]->ToString()));
  gApp->tag(sentence, words); 

  Local<Array> outArray;
  WrapPairVector(words, outArray);

  NanReturnValue(outArray);
}

NAN_METHOD(extract) {
  NanScope();

  if (args.Length() != 2) {
    NanReturnValue (NanIntern::Factory<v8::Boolean>::New(false));
  }

  string sentence = *(String::Utf8Value(args[0]->ToString()));
  size_t topN = args[1]->Int32Value();
  vector<pair<string, double> > words;

  gApp->extract(sentence, words, topN); 

  Local<Array> outArray;
  WrapPairVector(words, outArray);

  NanReturnValue(outArray);
}
