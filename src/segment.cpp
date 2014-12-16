#include "mix_segment.h"
#include "query_segment.h"
#include "pos_tagger.h"

void init(Handle<Object> exports) {
    exports->Set(NanNew("loadDict"),
            NanNew<FunctionTemplate>(loadDict)->GetFunction());
    exports->Set(NanNew("cutSync"),
            NanNew<FunctionTemplate>(cutSync)->GetFunction());
    exports->Set(NanNew("cut"), 
            NanNew<FunctionTemplate>(cut)->GetFunction());
    
    exports->Set(NanNew("queryLoadDict"),
            NanNew<FunctionTemplate>(queryLoadDict)->GetFunction());
    exports->Set(NanNew("queryCutSync"),
            NanNew<FunctionTemplate>(queryCutSync)->GetFunction());
    exports->Set(NanNew("queryCut"), 
            NanNew<FunctionTemplate>(queryCut)->GetFunction());

    exports->Set(NanNew("taggerLoadDict"),
            NanNew<FunctionTemplate>(taggerLoadDict)->GetFunction());
    exports->Set(NanNew("tagSync"),
            NanNew<FunctionTemplate>(tagSync)->GetFunction());
    exports->Set(NanNew("tag"),
            NanNew<FunctionTemplate>(tag)->GetFunction());
}

NODE_MODULE(segment, init)
