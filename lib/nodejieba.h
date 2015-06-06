#ifndef NODEJIBEA_SRC_NODEJIEBA_H
#define NODEJIBEA_SRC_NODEJIEBA_H

#include "utils.h"
#include "CppJieba/Application.hpp"

extern NAN_METHOD(load);
extern NAN_METHOD(cut);
extern NAN_METHOD(tag);
extern NAN_METHOD(extract);

#endif // NODEJIBEA_SRC_NODEJIEBA_H
