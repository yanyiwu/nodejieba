#include "nodejieba.h"

#include "jieba/Jieba.hpp"
#include "jieba/KeywordExtractor.hpp"

cppjieba::Jieba* global_jieba_handle;
cppjieba::KeywordExtractor* global_extractor_handle;

NAN_METHOD(load) {
  if(info.Length() != 5) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
  }

  String::Utf8Value dictPath(info[0]->ToString());
  String::Utf8Value modelPath(info[1]->ToString());
  String::Utf8Value userDictPath(info[2]->ToString());
  String::Utf8Value idfPath(info[3]->ToString());
  String::Utf8Value stopWordsPath(info[4]->ToString());

  delete global_jieba_handle;
  global_jieba_handle = new cppjieba::Jieba(*dictPath, 
                                  *modelPath, 
                                  *userDictPath);
  delete global_extractor_handle;
  global_extractor_handle = new cppjieba::KeywordExtractor(
        global_jieba_handle->GetDictTrie(),
        global_jieba_handle->GetHMMModel(),
        *idfPath,
        *stopWordsPath);

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(true));
}

NAN_METHOD(insertWord) {
  assert(global_jieba_handle);
  for (int i = 0; i < info.Length(); i++) {
    string word = *(String::Utf8Value(info[i]->ToString()));
    if(!global_jieba_handle->InsertUserWord(word)) {
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

  assert(global_jieba_handle);
  if (info.Length() >= 2) {
    string method = *(String::Utf8Value(info[1]->ToString()));
    if ("MP" == method) {
      global_jieba_handle->Cut(sentence, words, false); 
      if (info.Length() == 3) {
        global_jieba_handle->CutSmall(sentence, words, info[2]->Int32Value()); 
      }
    } else if ("HMM" == method) {
      global_jieba_handle->CutHMM(sentence, words); 
    } else if ("MIX" == method) {
      global_jieba_handle->Cut(sentence, words, true); 
    } else if ("FULL" == method) {
      global_jieba_handle->CutAll(sentence, words); 
    } else if ("QUERY" == method) {
      global_jieba_handle->CutForSearch(sentence, words, true); 
    } else {
      global_jieba_handle->Cut(sentence, words, true); 
    }
  } else {
    global_jieba_handle->Cut(sentence, words, true); 
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
  assert(global_jieba_handle);
  global_jieba_handle->Tag(sentence, words); 

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

  assert(global_jieba_handle);
  global_extractor_handle->Extract(sentence, words, topN); 

  Local<Array> outArray;
  WrapPairVector(words, outArray);

  info.GetReturnValue().Set(outArray);
}
