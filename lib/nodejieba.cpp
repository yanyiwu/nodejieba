#include "nodejieba.h"

#include "utils.h"

#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

NodeJieba::NodeJieba(Napi::Env env, Napi::Object exports) {
  DefineAddon(exports, {
    InstanceMethod("load", &NodeJieba::load),
    InstanceMethod("cut", &NodeJieba::cut),
    InstanceMethod("cutAll", &NodeJieba::cutAll),
    InstanceMethod("cutHMM", &NodeJieba::cutHMM),
    InstanceMethod("cutForSearch", &NodeJieba::cutForSearch),
    InstanceMethod("cutSmall", &NodeJieba::cutSmall),
    InstanceMethod("tag", &NodeJieba::tag),
    InstanceMethod("extract", &NodeJieba::extract),
    InstanceMethod("insertWord", &NodeJieba::insertWord)
  });
}

Napi::Value NodeJieba::load(const Napi::CallbackInfo& info) {
  if (info.Length() != 5) {
    return Napi::Boolean::New(info.Env(), false);
  }

  std::string dictPath = info[0].As<Napi::String>();
  std::string modelPath = info[1].As<Napi::String>();
  std::string userDictPath = info[2].As<Napi::String>();
  std::string idfPath = info[3].As<Napi::String>();
  std::string stopWordsPath = info[4].As<Napi::String>();

  delete _jieba_handle;
  _jieba_handle = new cppjieba::Jieba(dictPath,
                                  modelPath,
                                  userDictPath,
                                  idfPath,
                                  stopWordsPath);

  return Napi::Boolean::New(info.Env(), true);
}

Napi::Value NodeJieba::insertWord(const Napi::CallbackInfo& info) {
  if(info.Length() < 1) {
    return Napi::Boolean::New(info.Env(), false);
  }
  std::string word = info[0].As<Napi::String>();
  std::string tag = "x";
  if(info.Length() > 1) {
      tag = info[1].As<Napi::String>();
  }

  if( !_jieba_handle ){
    Napi::Error::New(info.Env(), "Before calling any other function you have to call load() first").ThrowAsJavaScriptException();
  }

  if(!_jieba_handle->InsertUserWord(word, tag)) {
    return Napi::Boolean::New(info.Env(), false);
  }

  return Napi::Boolean::New(info.Env(), true);
}

Napi::Value NodeJieba::cut(const Napi::CallbackInfo& info) {
  if (info.Length() == 0) {
    return Napi::Boolean::New(info.Env(), false);
  }
  std::string sentence = info[0].As<Napi::String>();
  bool useHMM = false;
  if (info.Length() > 1) {
    useHMM = info[1].As<Napi::Boolean>();
  }

  if( !_jieba_handle ){
    Napi::Error::New(info.Env(), "Before calling any other function you have to call load() first").ThrowAsJavaScriptException();
  }

  std::vector<std::string> words;
  _jieba_handle->Cut(sentence, words, useHMM);
  Napi::Array outArray;
  WrapVector(info.Env(), words, outArray);
  return outArray;
}

Napi::Value NodeJieba::cutHMM(const Napi::CallbackInfo& info) {
  if (info.Length() == 0) {
    return Napi::Boolean::New(info.Env(), false);
  }
  std::string sentence = info[0].As<Napi::String>();

  if( !_jieba_handle ){
    Napi::Error::New(info.Env(), "Before calling any other function you have to call load() first").ThrowAsJavaScriptException();
  }

  std::vector<std::string> words;
  _jieba_handle->CutHMM(sentence, words);
  Napi::Array outArray;
  WrapVector(info.Env(), words, outArray);
  return outArray;
}

Napi::Value NodeJieba::cutAll(const Napi::CallbackInfo& info) {
  if (info.Length() == 0) {
    return Napi::Boolean::New(info.Env(), false);
  }
  std::string sentence = info[0].As<Napi::String>();

  if( !_jieba_handle ){
    Napi::Error::New(info.Env(), "Before calling any other function you have to call load() first").ThrowAsJavaScriptException();
  }

  std::vector<std::string> words;
  _jieba_handle->CutAll(sentence, words);
  Napi::Array outArray;
  WrapVector(info.Env(), words, outArray);
  return outArray;
}

Napi::Value NodeJieba::cutForSearch(const Napi::CallbackInfo& info) {
  if (info.Length() == 0) {
    return Napi::Boolean::New(info.Env(), false);
  }
  std::string sentence = info[0].As<Napi::String>();
  bool useHMM = false;
  if (info.Length() > 1) {
    useHMM = info[1].As<Napi::Boolean>();
  }

  if( !_jieba_handle ){
    Napi::Error::New(info.Env(), "Before calling any other function you have to call load() first").ThrowAsJavaScriptException();
  }

  std::vector<std::string> words;
  _jieba_handle->CutForSearch(sentence, words, useHMM);
  Napi::Array outArray;
  WrapVector(info.Env(), words, outArray);
  return outArray;
}

Napi::Value NodeJieba::cutSmall(const Napi::CallbackInfo& info) {
  if (info.Length() < 2) {
    return Napi::Boolean::New(info.Env(), false);
  }
  std::string sentence = info[0].As<Napi::String>();
  size_t word_len_limit = info[1].As<Napi::Number>().Int32Value();

  if( !_jieba_handle ){
    Napi::Error::New(info.Env(), "Before calling any other function you have to call load() first").ThrowAsJavaScriptException();
  }

  std::vector<std::string> words;
  _jieba_handle->CutSmall(sentence, words, word_len_limit);
  Napi::Array outArray;
  WrapVector(info.Env(), words, outArray);
  return outArray;
}

Napi::Value NodeJieba::tag(const Napi::CallbackInfo& info) {
  if (info.Length() == 0) {
    return Napi::Boolean::New(info.Env(), false);
  }
  std::string sentence = info[0].As<Napi::String>();

  if( !_jieba_handle ){
    Napi::Error::New(info.Env(), "Before calling any other function you have to call load() first").ThrowAsJavaScriptException();
  }

  std::vector<std::pair<std::string, std::string> > words;
  _jieba_handle->Tag(sentence, words);
  Napi::Array outArray;
  WrapPairVector(info.Env(), words, outArray);
  return outArray;
}

Napi::Value NodeJieba::extract(const Napi::CallbackInfo& info) {
  if (info.Length() != 2) {
    return Napi::Boolean::New(info.Env(), false);
  }
  std::string sentence = info[0].As<Napi::String>();
  size_t topN = info[1].As<Napi::Number>().Int32Value();

  if( !_jieba_handle ){
    Napi::Error::New(info.Env(), "Before calling any other function you have to call load() first").ThrowAsJavaScriptException();
  }

  std::vector<std::pair<std::string, double> > words;
  _jieba_handle->extractor.Extract(sentence, words, topN);
  Napi::Array outArray;
  WrapPairVector(info.Env(), words, outArray);
  return outArray;
}
