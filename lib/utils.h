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
  array = NanIntern::Factory<v8::Array>::New(ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
      array->Set(i, NanIntern::Factory<v8::String>::New(ov[i].c_str()));
  }
}

inline void WrapPairVector(vector<pair<string,double> > &ov, Local<Array> &array) {
  array = NanIntern::Factory<v8::Array>::New(ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
    stringstream ss;
    ss << ov[i].first;
    ss << ":";
    ss << ov[i].second;
    array->Set(i, NanIntern::Factory<v8::String>::New(ss.str().c_str()));
  }
}

inline void WrapPairVector(vector<pair<string,string> > &ov, Local<Array> &array) {
  array = NanIntern::Factory<v8::Array>::New(ov.size());
  for(size_t i = 0; i < ov.size(); i++) {
    stringstream ss;
    ss << ov[i].first;
    ss << ":";
    ss << ov[i].second;
    array->Set(i, NanIntern::Factory<v8::String>::New(ss.str().c_str()));
  }
}

inline string ValueToString(Local<Value> val) {
  String::Utf8Value su(val);
  return string(*su);
}

#endif
