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
    stringstream ss;
    ss << ov[i].first;
    ss << ":";
    ss << ov[i].second;
    array->Set(i, Nan::New<v8::String>(ss.str().c_str()).ToLocalChecked());
  }
}

inline void WrapPairVector(vector<pair<string,string> > &ov, Local<Array> &array) {
  array = Nan::New<v8::Array>(ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
    stringstream ss;
    ss << ov[i].first;
    ss << ":";
    ss << ov[i].second;
    array->Set(i, Nan::New<v8::String>(ss.str().c_str()).ToLocalChecked());
  }
}

inline string ValueToString(Local<Value> val) {
  String::Utf8Value su(val);
  return string(*su);
}

#endif
