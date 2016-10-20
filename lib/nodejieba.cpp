#include "nodejieba.h"

#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

cppjieba::Jieba* global_jieba_handle;
cppjieba::KeywordExtractor* global_extractor_handle;

NAN_METHOD(load) {
  if(info.Length() != 5) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
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
  
  if(info.Length() < 1) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  
  string word = *(String::Utf8Value(info[0]->ToString()));
  string tag = "x";

  if(info.Length() > 1) {
      tag = *(String::Utf8Value(info[1]->ToString()));
  }
 
  assert(global_jieba_handle);
  
  if(!global_jieba_handle->InsertUserWord(word, tag)) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(true));
}

//NAN_METHOD(cut) {
//  if (info.Length() == 0) {
//    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
//    return;
//  }
//  string sentence = *(String::Utf8Value(info[0]->ToString()));
//  vector<string> words;
//
//  assert(global_jieba_handle);
//  if (info.Length() >= 2) {
//    string method = *(String::Utf8Value(info[1]->ToString()));
//    if ("MP" == method) {
//      global_jieba_handle->Cut(sentence, words, false); 
//      if (info.Length() == 3) {
//        global_jieba_handle->CutSmall(sentence, words, info[2]->Int32Value()); 
//      }
//    } else if ("HMM" == method) {
//      global_jieba_handle->CutHMM(sentence, words); 
//    } else if ("MIX" == method) {
//      global_jieba_handle->Cut(sentence, words, true); 
//    } else {
//      global_jieba_handle->Cut(sentence, words, true); 
//    }
//  } else {
//    global_jieba_handle->Cut(sentence, words, true); 
//  }
//
//  Local<Array> outArray;
//  WrapVector(words, outArray);
//
//  info.GetReturnValue().Set(outArray);
//}

NAN_METHOD(cut) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(String::Utf8Value(info[0]->ToString()));
  vector<string> words;
  bool useHMM = false;
  if (info.Length() > 1) {
    useHMM = *info[1]->ToBoolean();
  }
  global_jieba_handle->Cut(sentence, words, useHMM); 
  Local<Array> outArray;
  WrapVector(words, outArray);
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(cutHMM) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(String::Utf8Value(info[0]->ToString()));
  vector<string> words;
  global_jieba_handle->CutHMM(sentence, words); 
  Local<Array> outArray;
  WrapVector(words, outArray);
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(cutAll) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(String::Utf8Value(info[0]->ToString()));
  vector<string> words;
  global_jieba_handle->CutAll(sentence, words); 
  Local<Array> outArray;
  WrapVector(words, outArray);
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(cutForSearch) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(String::Utf8Value(info[0]->ToString()));
  vector<string> words;
  bool useHMM = false;
  if (info.Length() > 1) {
    useHMM = *info[1]->ToBoolean();
  }
  global_jieba_handle->CutForSearch(sentence, words, useHMM); 
  Local<Array> outArray;
  WrapVector(words, outArray);
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(cutSmall) {
  if (info.Length() < 2) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(String::Utf8Value(info[0]->ToString()));
  vector<string> words;
  size_t word_len_limit = info[1]->IntegerValue();
  global_jieba_handle->CutSmall(sentence, words, word_len_limit); 
  Local<Array> outArray;
  WrapVector(words, outArray);
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(tag) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
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
    return;
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
