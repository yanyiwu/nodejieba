#include "nodejieba.h"

void init(Local<Object> exports) {
  Nan::Set(exports,Nan::New<v8::String>("load").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(load)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("cut").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cut)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("cutAll").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cutAll)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("cutHMM").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cutHMM)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("cutForSearch").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cutForSearch)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("cutSmall").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cutSmall)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("tag").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(tag)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("extract").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(extract)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("extractWithWords").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(extractWithWords)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("insertWord").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(insertWord)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("textRankExtract").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(textRankExtract)).ToLocalChecked());
  Nan::Set(exports,Nan::New<v8::String>("textRankExtractWithWords").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(textRankExtractWithWords)).ToLocalChecked());
}

NODE_MODULE(nodejieba, init)
