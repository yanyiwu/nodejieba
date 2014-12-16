#ifndef NODEJIEBA_SRC_UTLS_H
#define NODEJIEBA_SRC_UTLS_H

#include <node.h>
#include <v8.h>
#include <nan.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace v8;

inline void WrapVector(vector<string> &ov, Local<Array> &array) {
    array = Array::New(ov.size());
    for(size_t i = 0; i < ov.size(); i++) {
        array->Set(i, String::New(ov[i].c_str()));
    }
}

inline void WrapPairVector(vector<pair<string,string> > &ov, Local<Array> &array) {
    array = Array::New(ov.size());
    for(size_t i = 0; i < ov.size(); i++) {
        array->Set(i, String::New((ov[i].first + ":" + ov[i].second).c_str()));
    }
}

inline string ValueToString(Local<Value> val) {
    String::Utf8Value su(val);
    return string(*su);
}

#endif
