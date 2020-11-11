#include "nodejieba.h"

#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

NAN_METHOD(load) {
  if(info.Length() != 5) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }

  Nan::Utf8String dictPath(Nan::To<v8::String>((info[0])).ToLocalChecked());
  Nan::Utf8String modelPath(Nan::To<v8::String>((info[1])).ToLocalChecked());
  Nan::Utf8String userDictPath(Nan::To<v8::String>((info[2])).ToLocalChecked());
  Nan::Utf8String idfPath(Nan::To<v8::String>((info[3])).ToLocalChecked());
  Nan::Utf8String stopWordsPath(Nan::To<v8::String>((info[4])).ToLocalChecked());

  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  cppjieba::Jieba* _jieba_handle = Nan::GetIsolateData<cppjieba::Jieba>(isolate);
  delete _jieba_handle;
  _jieba_handle = new cppjieba::Jieba(*dictPath,
                                  *modelPath,
                                  *userDictPath,
                                  *idfPath,
                                  *stopWordsPath);
  Nan::SetIsolateData<cppjieba::Jieba>(isolate, _jieba_handle);

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(true));
}

NAN_METHOD(insertWord) {
  
  if(info.Length() < 1) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  
  string word = *(Nan::Utf8String(Nan::To<v8::String>((info[0])).ToLocalChecked()));
  string tag = "x";

  if(info.Length() > 1) {
      tag = *(Nan::Utf8String(Nan::To<v8::String>((info[1])).ToLocalChecked()));
  }
 
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  cppjieba::Jieba* _jieba_handle = Nan::GetIsolateData<cppjieba::Jieba>(isolate);
  assert(_jieba_handle);
  
  if(!_jieba_handle->InsertUserWord(word, tag)) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(true));
}

NAN_METHOD(cut) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(Nan::Utf8String(Nan::To<v8::String>((info[0])).ToLocalChecked()));
  vector<string> words;
  bool useHMM = false;
  if (info.Length() > 1) {
    useHMM = *Nan::To<v8::Boolean>((info[1])).ToLocalChecked();
  }
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  cppjieba::Jieba* _jieba_handle = Nan::GetIsolateData<cppjieba::Jieba>(isolate);
  _jieba_handle->Cut(sentence, words, useHMM); 
  Local<Array> outArray;
  WrapVector(words, outArray);
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(cutHMM) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(Nan::Utf8String(Nan::To<v8::String>((info[0])).ToLocalChecked()));
  vector<string> words;
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  cppjieba::Jieba* _jieba_handle = Nan::GetIsolateData<cppjieba::Jieba>(isolate);
  _jieba_handle->CutHMM(sentence, words); 
  Local<Array> outArray;
  WrapVector(words, outArray);
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(cutAll) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(Nan::Utf8String(Nan::To<v8::String>((info[0])).ToLocalChecked()));
  vector<string> words;
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  cppjieba::Jieba* _jieba_handle = Nan::GetIsolateData<cppjieba::Jieba>(isolate);
  _jieba_handle->CutAll(sentence, words); 
  Local<Array> outArray;
  WrapVector(words, outArray);
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(cutForSearch) {
  if (info.Length() == 0) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(Nan::Utf8String(Nan::To<v8::String>((info[0])).ToLocalChecked()));
  vector<string> words;
  bool useHMM = false;
  if (info.Length() > 1) {
    useHMM = *Nan::To<v8::Boolean>((info[1])).ToLocalChecked();
  }
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  cppjieba::Jieba* _jieba_handle = Nan::GetIsolateData<cppjieba::Jieba>(isolate);
  _jieba_handle->CutForSearch(sentence, words, useHMM); 
  Local<Array> outArray;
  WrapVector(words, outArray);
  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(cutSmall) {
  if (info.Length() < 2) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }
  string sentence = *(Nan::Utf8String(Nan::To<v8::String>((info[0])).ToLocalChecked()));
  vector<string> words;
  size_t word_len_limit =  Nan::To<int32_t>((info[1])).FromJust();
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  cppjieba::Jieba* _jieba_handle = Nan::GetIsolateData<cppjieba::Jieba>(isolate);
  _jieba_handle->CutSmall(sentence, words, word_len_limit); 
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
  string sentence = *(Nan::Utf8String(Nan::To<v8::String>((info[0])).ToLocalChecked()));
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  cppjieba::Jieba* _jieba_handle = Nan::GetIsolateData<cppjieba::Jieba>(isolate);
  assert(_jieba_handle);
  _jieba_handle->Tag(sentence, words); 

  Local<Array> outArray;
  WrapPairVector(words, outArray);

  info.GetReturnValue().Set(outArray);
}

NAN_METHOD(extract) {
  if (info.Length() != 2) {
    info.GetReturnValue().Set(Nan::New<v8::Boolean>(false));
    return;
  }

  string sentence = *(Nan::Utf8String(Nan::To<v8::String>((info[0])).ToLocalChecked()));
  size_t topN = Nan::To<int32_t>((info[1])).FromJust();
  vector<pair<string, double> > words;

  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  cppjieba::Jieba* _jieba_handle = Nan::GetIsolateData<cppjieba::Jieba>(isolate);
  assert(_jieba_handle);
  _jieba_handle->extractor.Extract(sentence, words, topN); 

  Local<Array> outArray;
  WrapPairVector(words, outArray);

  info.GetReturnValue().Set(outArray);
}
