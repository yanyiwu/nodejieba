#ifndef CPPJIEBA_TRIE_HPP
#define CPPJIEBA_TRIE_HPP

#include "Limonp/StdExtension.hpp"
#include <vector>
#include <queue>

namespace CppJieba {
using namespace std;

struct DictUnit {
  Unicode word;
  double weight;
  string tag;
};

// for debugging
inline ostream & operator << (ostream& os, const DictUnit& unit) {
  string s;
  s << unit.word;
  return os << string_format("%s %s %.3lf", s.c_str(), unit.tag.c_str(), unit.weight);
}

typedef LocalVector<std::pair<size_t, const DictUnit*> > DagType;

struct SegmentChar {
  uint16_t uniCh;
  DagType dag;
  const DictUnit * pInfo;
  double weight;
  size_t nextPos;
  SegmentChar():uniCh(0), pInfo(NULL), weight(0.0), nextPos(0) {
  }
  ~SegmentChar() {
  }
};

typedef Unicode::value_type TrieKey;

class TrieNode {
 public:
  TrieNode(): fail(NULL), next(NULL), ptValue(NULL) {
  }
  const TrieNode * findNext(TrieKey key) const {
    if(next == NULL) {
      return NULL;
    }
    NextMap::const_iterator iter = next->find(key);
    if(iter == next->end()) {
      return NULL;
    }
    return iter->second;
  }
 public:
  typedef unordered_map<TrieKey,  TrieNode*> NextMap;
  TrieNode * fail;
  NextMap * next;
  const DictUnit * ptValue;
};

class Trie {
 public:
  Trie(const vector<Unicode>& keys, const vector<const DictUnit*> & valuePointers) {
    root_ = new TrieNode;
    createTrie_(keys, valuePointers);
    build_();// build automation
  }
  ~Trie() {
    if(root_) {
      deleteNode_(root_);
    }
  }
 public:
  const DictUnit* find(Unicode::const_iterator begin, Unicode::const_iterator end) const {
    TrieNode::NextMap::const_iterator citer;
    const TrieNode* ptNode = root_;
    for(Unicode::const_iterator it = begin; it != end; it++) {
      // build automation
      assert(ptNode);
      if(NULL == ptNode->next || ptNode->next->end() == (citer = ptNode->next->find(*it))) {
        return NULL;
      }
      ptNode = citer->second;
    }
    return ptNode->ptValue;
  }
  // aho-corasick-automation
  void find(
    Unicode::const_iterator begin,
    Unicode::const_iterator end,
    vector<struct SegmentChar>& res
  ) const {
    res.resize(end - begin);
    const TrieNode * now = root_;
    const TrieNode* node;
    // compiler will complain warnings if only "i < end - begin" .
    for (size_t i = 0; i < size_t(end - begin); i++) {
      Unicode::value_type ch = *(begin + i);
      res[i].uniCh = ch;
      assert(res[i].dag.empty());
      res[i].dag.push_back(pair<vector<Unicode >::size_type, const DictUnit* >(i, (const DictUnit*)NULL));
      bool flag = false;

      // rollback
      while( now != root_ ) {
        node = now->findNext(ch);
        if (node != NULL) {
          flag = true;
          break;
        } else {
          now = now->fail;
        }
      }

      if(!flag) {
        node = now->findNext(ch);
      }
      if(node == NULL) {
        now = root_;
      } else {
        now = node;
        const TrieNode * temp = now;
        while(temp != root_) {
          if (temp->ptValue) {
            size_t pos = i - temp->ptValue->word.size() + 1;
            res[pos].dag.push_back(pair<vector<Unicode >::size_type, const DictUnit* >(i, temp->ptValue));
            if(pos == i) {
              res[pos].dag[0].second = temp->ptValue;
            }
          }
          temp = temp->fail;
          assert(temp);
        }
      }
    }
  }
  bool find(
    Unicode::const_iterator begin,
    Unicode::const_iterator end,
    DagType & res,
    size_t offset = 0) const {
    const TrieNode * ptNode = root_;
    TrieNode::NextMap::const_iterator citer;
    for(Unicode::const_iterator itr = begin; itr != end ; itr++) {
      assert(ptNode);
      if(NULL == ptNode->next || ptNode->next->end() == (citer = ptNode->next->find(*itr))) {
        break;
      }
      ptNode = citer->second;
      if(ptNode->ptValue) {
        if(itr == begin && res.size() == 1) { // first singleword
          res[0].second = ptNode->ptValue;
        } else {
          res.push_back(pair<vector<Unicode >::size_type, const DictUnit* >(itr - begin + offset, ptNode->ptValue));
        }
      }
    }
    return !res.empty();
  }
 private:
  void build_() {
    queue<TrieNode*> que;
    assert(root_->ptValue == NULL);
    assert(root_->next);
    root_->fail = NULL;
    for(TrieNode::NextMap::iterator iter = root_->next->begin(); iter != root_->next->end(); iter++) {
      iter->second->fail = root_;
      que.push(iter->second);
    }
    TrieNode* back = NULL;
    TrieNode::NextMap::iterator backiter;
    while(!que.empty()) {
      TrieNode * now = que.front();
      que.pop();
      if(now->next == NULL) {
        continue;
      }
      for(TrieNode::NextMap::iterator iter = now->next->begin(); iter != now->next->end(); iter++) {
        back = now->fail;
        while(back != NULL) {
          if(back->next && (backiter = back->next->find(iter->first)) != back->next->end()) {
            iter->second->fail = backiter->second;
            break;
          }
          back = back->fail;
        }
        if(back == NULL) {
          iter->second->fail = root_;
        }
        que.push(iter->second);
      }
    }
  }
  void createTrie_(const vector<Unicode>& keys, const vector<const DictUnit*> & valuePointers) {
    if(valuePointers.empty() || keys.empty()) {
      return;
    }
    assert(keys.size() == valuePointers.size());

    for(size_t i = 0; i < keys.size(); i++) {
      insertNode_(keys[i], valuePointers[i]);
    }
  }
  void insertNode_(const Unicode& key, const DictUnit* ptValue) {
    TrieNode* ptNode  = root_;

    TrieNode::NextMap::const_iterator kmIter;

    for(Unicode::const_iterator citer = key.begin(); citer != key.end(); citer++) {
      if(NULL == ptNode->next) {
        ptNode->next = new TrieNode::NextMap;
      }
      kmIter = ptNode->next->find(*citer);
      if(ptNode->next->end() == kmIter) {
        TrieNode * nextNode = new TrieNode;
        nextNode->next = NULL;
        nextNode->ptValue = NULL;

        (*ptNode->next)[*citer] = nextNode;
        ptNode = nextNode;
      } else {
        ptNode = kmIter->second;
      }
    }
    ptNode->ptValue = ptValue;
  }
  void deleteNode_(TrieNode* node) {
    if(!node) {
      return;
    }
    if(node->next) {
      TrieNode::NextMap::iterator it;
      for(it = node->next->begin(); it != node->next->end(); it++) {
        deleteNode_(it->second);
      }
      delete node->next;
    }
    delete node;
  }
 private:
  TrieNode* root_;
};
}

#endif
