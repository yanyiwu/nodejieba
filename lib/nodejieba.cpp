#include "nodejieba.h"

CppJieba::Application* gNodeJieba;

NAN_METHOD(load) {
  if(info.Length() != 5) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
  }

  String::Utf8Value dictPath(info[0]->ToString());
  String::Utf8Value modelPath(info[1]->ToString());
  String::Utf8Value userDictPath(info[2]->ToString());
  String::Utf8Value idfPath(info[3]->ToString());
  String::Utf8Value stopWordsPath(info[4]->ToString());

  delete gNodeJieba;
  gNodeJieba = new CppJieba::Application(*dictPath, 
                                  *modelPath, 
                                  *userDictPath,
                                  *idfPath, 
                                  *stopWordsPath);

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(true));
}

NAN_METHOD(insertWord) {
  assert(gNodeJieba);
  for (int i = 0; i < info.Length(); i++) {
    string word = *(String::Utf8Value(info[i]->ToString()));
    if(!gNodeJieba->insertUserWord(word)) {
      info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    }
  }
  info.GetReturnValue().Set(Nan::New<v8::Boolean>(true));
  
}

NAN_METHOD(cut) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
  }
  string sentence = *(String::Utf8Value(info[0]->ToString()));
  vector<string> words;

  assert(gNodeJieba);
  if (info.Length() >= 2) {
    string method = *(String::Utf8Value(info[1]->ToString()));
    if ("MP" == method) {
      gNodeJieba->cut(sentence, words, CppJieba::METHOD_MP); 
      if (info.Length() == 3) {
        gNodeJieba->cut(sentence, words, info[2]->Int32Value()); 
      }
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

  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(tag) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
  }

  vector<pair<string, string> > words;
  string sentence = *(String::Utf8Value(info[0]->ToString()));
  assert(gNodeJieba);
  gNodeJieba->tag(sentence, words); 

  Local<Array> outArray;
  WrapPairVector(words, outArray);

  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(extract) {
  if (info.Length() != 2) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
  }

  string sentence = *(String::Utf8Value(info[0]->ToString()));
  size_t topN = info[1]->Int32Value();
  vector<pair<string, double> > words;

  assert(gNodeJieba);
  gNodeJieba->extract(sentence, words, topN); 

  Local<Array> outArray;
  WrapPairVector(words, outArray);

  info.GetReturnValue().Set(outArray);
}
