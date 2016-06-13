#ifndef NODEJIBEA_SRC_NODEJIEBA_H
#define NODEJIBEA_SRC_NODEJIEBA_H

#include "utils.h"

extern NAN_METHOD(load);
extern NAN_METHOD(cut);
extern NAN_METHOD(cutAll);
extern NAN_METHOD(cutHMM);
extern NAN_METHOD(cutForSearch);
extern NAN_METHOD(cutSmall);
extern NAN_METHOD(tag);
extern NAN_METHOD(extract);
extern NAN_METHOD(insertWord);

#endif // NODEJIBEA_SRC_NODEJIEBA_H
