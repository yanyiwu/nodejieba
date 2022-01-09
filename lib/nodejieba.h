#ifndef NODEJIBEA_SRC_NODEJIEBA_H
#define NODEJIBEA_SRC_NODEJIEBA_H

#include <napi.h>

namespace cppjieba{ class Jieba; class TextRankExtractor; }

class NodeJieba : public Napi::Addon<NodeJieba> {
public:
  NodeJieba(Napi::Env env, Napi::Object exports);

private:
  Napi::Value load(const Napi::CallbackInfo& info);
  Napi::Value cut(const Napi::CallbackInfo& info);
  Napi::Value cutAll(const Napi::CallbackInfo& info);
  Napi::Value cutHMM(const Napi::CallbackInfo& info);
  Napi::Value cutForSearch(const Napi::CallbackInfo& info);
  Napi::Value cutSmall(const Napi::CallbackInfo& info);
  Napi::Value tag(const Napi::CallbackInfo& info);
  Napi::Value extract(const Napi::CallbackInfo& info);
  Napi::Value textRankExtract(const Napi::CallbackInfo& info);
  Napi::Value insertWord(const Napi::CallbackInfo& info);

  cppjieba::Jieba* _jieba_handle{nullptr};
  cppjieba::TextRankExtractor* _text_rank_extractor_handle{nullptr};
};

#endif // NODEJIBEA_SRC_NODEJIEBA_H
