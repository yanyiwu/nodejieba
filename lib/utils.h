#ifndef NODEJIEBA_SRC_UTLS_H
#define NODEJIEBA_SRC_UTLS_H

#include <string>
#include <utility>
#include <vector>

inline void WrapVector(Napi::Env env, std::vector<std::string> &ov, Napi::Array &array) {
  array = Napi::Array::New(env, ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
      array.Set(i, Napi::String::New(env, ov[i]));
  }
}

inline void WrapPairVector(Napi::Env env, std::vector<std::pair<std::string,double> > &ov, Napi::Array &array) {
  array = Napi::Array::New(env, ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
    Napi::Object obj = Napi::Object::New(env);
    Napi::Value k;
    Napi::Value v;
    k = Napi::String::New(env, "word");
    v = Napi::String::New(env, ov[i].first);
    obj.Set(k, v);
    k = Napi::String::New(env, "weight");
    v = Napi::Number::New(env, ov[i].second);
    obj.Set(k, v);
    array.Set(i, obj);
  }
}

inline void WrapPairVector(Napi::Env env, std::vector<std::pair<std::string,std::string> > &ov, Napi::Array &array) {
  array = Napi::Array::New(env, ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
    Napi::Object obj = Napi::Object::New(env);
    Napi::Value k;
    Napi::Value v;
    k = Napi::String::New(env, "word");
    v = Napi::String::New(env, ov[i].first);
    obj.Set(k, v);
    k = Napi::String::New(env, "tag");
    v = Napi::String::New(env, ov[i].second);
    obj.Set(k, v);
    array.Set(i, obj);
  }
}

#endif
