#ifndef NODEJIEBA_SRC_UTLS_H
#define NODEJIEBA_SRC_UTLS_H

#include <node.h>
#include <v8.h>
#include <nan.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace v8;

inline void WrapVector(vector<string> &ov, Local<Array> &array) {
  array = Nan::New<v8::Array>(ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
      array->Set(i, Nan::New<v8::String>(ov[i].c_str()).ToLocalChecked());
  }
}

inline void WrapPairVector(vector<pair<string,double> > &ov, Local<Array> &array) {
  array = Nan::New<v8::Array>(ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
    Handle<v8::Object> obj = Nan::New<v8::Object>();
    Local<Value> k;
    Local<Value> v;
    k = Nan::New<v8::String>("word").ToLocalChecked();
    v = Nan::New<v8::String>(ov[i].first).ToLocalChecked();
    obj->Set(k, v);
    k = Nan::New<v8::String>("weight").ToLocalChecked();
    v = Nan::New<v8::Number>(ov[i].second);
    obj->Set(k, v);
    array->Set(i, obj);
  }
}

inline void WrapPairVector(vector<pair<string,string> > &ov, Local<Array> &array) {
  array = Nan::New<v8::Array>(ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
    Handle<v8::Object> obj = Nan::New<v8::Object>();
    Local<Value> k;
    Local<Value> v;
    k = Nan::New<v8::String>("word").ToLocalChecked();
    v = Nan::New<v8::String>(ov[i].first).ToLocalChecked();
    obj->Set(k, v);
    k = Nan::New<v8::String>("tag").ToLocalChecked();
    v = Nan::New<v8::String>(ov[i].second).ToLocalChecked();
    obj->Set(k, v);
    array->Set(i, obj);
  }
}

inline string ValueToString(Local<Value> val) {
  String::Utf8Value su(val);
  return string(*su);
}

#endif
