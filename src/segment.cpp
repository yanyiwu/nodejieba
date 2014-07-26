#include "mix_segment.h"

void init(Handle<Object> exports) {
    exports->Set(NanNew("loadDict"),
            NanNew<FunctionTemplate>(loadDict)->GetFunction());
    exports->Set(NanNew("cutSync"),
            NanNew<FunctionTemplate>(cutSync)->GetFunction());
    exports->Set(NanNew("cut"), 
            NanNew<FunctionTemplate>(cut)->GetFunction());
}

NODE_MODULE(segment, init)
