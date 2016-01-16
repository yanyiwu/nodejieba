#ifndef CPPJIEAB_JIEBA_H
#define CPPJIEAB_JIEBA_H

#include "QuerySegment.hpp"
#include "PosTagger.hpp"
#include "LevelSegment.hpp"

namespace cppjieba {

class Jieba {
 public:
  Jieba(const string& dict_path, const string& model_path, const string& user_dict_path) 
    : dict_trie_(dict_path, user_dict_path),
      model_(model_path),
      mp_seg_(&dict_trie_),
      hmm_seg_(&model_),
      mix_seg_(&dict_trie_, &model_),
      full_seg_(&dict_trie_),
      query_seg_(&dict_trie_, &model_),
      level_seg_(&dict_trie_),
      pos_tagger_(&dict_trie_, &model_) {
  }
  ~Jieba() {
  }

  struct LocWord {
    string word;
    size_t begin;
    size_t end;
  }; // struct LocWord

  void Cut(const string& sentence, vector<string>& words, bool hmm = true) const {
    mix_seg_.Cut(sentence, words, hmm);
  }
  void CutAll(const string& sentence, vector<string>& words) const {
    full_seg_.Cut(sentence, words);
  }
  void CutForSearch(const string& sentence, vector<string>& words, bool hmm = true) const {
    query_seg_.Cut(sentence, words, hmm);
  }
  void CutHMM(const string& sentence, vector<string>& words) const {
    hmm_seg_.Cut(sentence, words);
  }
  void CutLevel(const string& sentence, vector<string>& words) const {
    level_seg_.Cut(sentence, words);
  }
  void CutLevel(const string& sentence, vector<pair<string, size_t> >& words) const {
    level_seg_.Cut(sentence, words);
  }
  void CutSmall(const string& sentence, vector<string>& words, size_t max_word_len) const {
    mp_seg_.Cut(sentence, words, max_word_len);
  }
  void Locate(const vector<string>& words, vector<LocWord>& loc_words) const {
    loc_words.resize(words.size());
    size_t begin = 0;
    for (size_t i = 0; i < words.size(); i++) {
      size_t len = TransCode::Decode(words[i]).size();
      loc_words[i].word = words[i];
      loc_words[i].begin = begin;
      loc_words[i].end = loc_words[i].begin + len;
      begin = loc_words[i].end;
    }
  }
  
  void Tag(const string& sentence, vector<pair<string, string> >& words) const {
    pos_tagger_.Tag(sentence, words);
  }
  bool InsertUserWord(const string& word, const string& tag = UNKNOWN_TAG) {
    return dict_trie_.InsertUserWord(word, tag);
  }

  const DictTrie* GetDictTrie() const {
    return &dict_trie_;
  } 
  const HMMModel* GetHMMModel() const {
    return &model_;
  }
 
  void SetQuerySegmentThreshold(size_t len) {
    query_seg_.SetMaxWordLen(len);
  }
 private:
  DictTrie dict_trie_;
  HMMModel model_;
  
  // They share the same dict trie and model
  MPSegment mp_seg_;
  HMMSegment hmm_seg_;
  MixSegment mix_seg_;
  FullSegment full_seg_;
  QuerySegment query_seg_;
  LevelSegment level_seg_;
  
  PosTagger pos_tagger_;
  
}; // class Jieba

} // namespace cppjieba

#endif // CPPJIEAB_JIEBA_H
