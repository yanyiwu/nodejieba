#include "nodejieba.h"

void init(Handle<Object> exports) {
  exports->Set(Nan::New<v8::String>("load").ToLocalChecked(),
        Nan::New<FunctionTemplate>(load)->GetFunction());
  exports->Set(Nan::New<v8::String>("cut").ToLocalChecked(),
        Nan::New<FunctionTemplate>(cut)->GetFunction());
  exports->Set(Nan::New<v8::String>("cutAll").ToLocalChecked(),
        Nan::New<FunctionTemplate>(cutAll)->GetFunction());
  exports->Set(Nan::New<v8::String>("cutHMM").ToLocalChecked(),
        Nan::New<FunctionTemplate>(cutHMM)->GetFunction());
  exports->Set(Nan::New<v8::String>("cutForSearch").ToLocalChecked(),
        Nan::New<FunctionTemplate>(cutForSearch)->GetFunction());
  exports->Set(Nan::New<v8::String>("cutSmall").ToLocalChecked(),
        Nan::New<FunctionTemplate>(cutSmall)->GetFunction());
  exports->Set(Nan::New<v8::String>("tag").ToLocalChecked(),
        Nan::New<FunctionTemplate>(tag)->GetFunction());
  exports->Set(Nan::New<v8::String>("extract").ToLocalChecked(),
        Nan::New<FunctionTemplate>(extract)->GetFunction());
  exports->Set(Nan::New<v8::String>("insertWord").ToLocalChecked(),
        Nan::New<FunctionTemplate>(insertWord)->GetFunction());
}

NODE_MODULE(nodejieba, init)
