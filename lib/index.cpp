#include "nodejieba.h"

void init(Handle<Object> exports) {
  exports->Set(NanNew("load"),
        NanNew<FunctionTemplate>(load)->GetFunction());
  exports->Set(NanNew("cut"),
        NanNew<FunctionTemplate>(cut)->GetFunction());
  exports->Set(NanNew("tag"),
        NanNew<FunctionTemplate>(tag)->GetFunction());
  exports->Set(NanNew("extract"),
        NanNew<FunctionTemplate>(extract)->GetFunction());
}

NODE_MODULE(nodejieba, init)
