#include "nodejieba.h"

NAN_MODULE_INIT(init) {
  Nan::Set(target,Nan::New<v8::String>("load").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(load)).ToLocalChecked());
  Nan::Set(target,Nan::New<v8::String>("cut").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cut)).ToLocalChecked());
  Nan::Set(target,Nan::New<v8::String>("cutAll").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cutAll)).ToLocalChecked());
  Nan::Set(target,Nan::New<v8::String>("cutHMM").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cutHMM)).ToLocalChecked());
  Nan::Set(target,Nan::New<v8::String>("cutForSearch").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cutForSearch)).ToLocalChecked());
  Nan::Set(target,Nan::New<v8::String>("cutSmall").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(cutSmall)).ToLocalChecked());
  Nan::Set(target,Nan::New<v8::String>("tag").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(tag)).ToLocalChecked());
  Nan::Set(target,Nan::New<v8::String>("extract").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(extract)).ToLocalChecked());
  Nan::Set(target,Nan::New<v8::String>("insertWord").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(insertWord)).ToLocalChecked());
}

NAN_MODULE_WORKER_ENABLED(NODE_GYP_MODULE_NAME, init)
