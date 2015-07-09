#include "nodejieba.h"

CppJieba::Application* gNodeJieba;

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

  if (gNodeJieba != NULL) {
    delete gNodeJieba;
  }
  gNodeJieba = new CppJieba::Application(*dictPath, 
                                  *modelPath, 
                                  *userDictPath,
                                  *idfPath, 
                                  *stopWordsPath);

  NanReturnValue (NanIntern::Factory<v8::Boolean>::New(true));
}

NAN_METHOD(insertWord) {
  NanScope();
  assert(gNodeJieba);
  for (int i = 0; i < args.Length(); i++) {
    string word = *(String::Utf8Value(args[i]->ToString()));
    if(!gNodeJieba->insertUserWord(word)) {
      NanReturnValue (NanIntern::Factory<v8::Boolean>::New(false));
    }
  }
  NanReturnValue (NanIntern::Factory<v8::Boolean>::New(true));
  
}

NAN_METHOD(cut) {
  NanScope();
  if (args.Length() == 0) {
    NanReturnValue (NanIntern::Factory<v8::Boolean>::New(false));
  }
  string sentence = *(String::Utf8Value(args[0]->ToString()));
  vector<string> words;

  assert(gNodeJieba);
  if (args.Length() == 2) {
    string method = *(String::Utf8Value(args[1]->ToString()));
    if ("MP" == method) {
      gNodeJieba->cut(sentence, words, CppJieba::METHOD_MP); 
    } else if ("HMM" == method) {
      gNodeJieba->cut(sentence, words, CppJieba::METHOD_HMM); 
    } else if ("MIX" == method) {
      gNodeJieba->cut(sentence, words, CppJieba::METHOD_MIX); 
    } else if ("FULL" == method) {
      gNodeJieba->cut(sentence, words, CppJieba::METHOD_FULL); 
    } else if ("QUERY" == method) {
      gNodeJieba->cut(sentence, words, CppJieba::METHOD_QUERY); 
    } else {
      gNodeJieba->cut(sentence, words, CppJieba::METHOD_MIX); 
    }
  } else {
    gNodeJieba->cut(sentence, words, CppJieba::METHOD_MIX); 
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
  assert(gNodeJieba);
  gNodeJieba->tag(sentence, words); 

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

  assert(gNodeJieba);
  gNodeJieba->extract(sentence, words, topN); 

  Local<Array> outArray;
  WrapPairVector(words, outArray);

  NanReturnValue(outArray);
}
