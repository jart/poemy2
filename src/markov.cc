// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/poemy.h"
#include "poemy/util.h"
#include "poemy/corpus.h"
#include "poemy/markov.h"

static const char kDelimiter = ',';

Markov::Markov(const string& corpora_path)
    : corpora_path_(corpora_path),
      rand_(std::chrono::system_clock::now().time_since_epoch().count()) {
}

void Markov::Load(const string& corpus) {
  string corpus_path(corpora_path_ + "/" + corpus);
  for (const auto& entry : list_dir(corpus_path)) {
    LoadCorpus(corpus_path + "/" + entry);
  }
}

void Markov::Init() {
  keys_.clear();
  keys_.reserve(chain_.size());
  for (auto& pair : chain_) {
    // remove_duplicates_from_stringlist(kDelimiter, &pair.second);
    std::unique(std::begin(pair.second), std::end(pair.second));
    keys_.push_back(pair.first);
  }
}

void Markov::LoadCorpus(const string& path) {
  std::ifstream fs(path);
  Corpus corp(&fs);
  string w1, w2;
  while (corp.good()) {
    corp >> w1;
    if (w1.empty()) {
      continue;
    }
    if (!corp.good()) {
      break;
    }
    corp >> w2;
    if (w2.empty()) {
      continue;
    }
    while (corp.good()) {
      string w3;
      corp >> w3;
      if (w3.empty()) {
        break;
      }
      chain_[w1 + kDelimiter + w2].push_back(w3);
      std::swap(w1, w2);
      std::swap(w2, w3);
    }
  }
}

void Markov::PickFirst(string* o_word1, string* o_word2) {
  const string& key = keys_[rand_() % keys_.size()];
  const int i = key.find(kDelimiter);
  *o_word1 = key.substr(0, i);
  *o_word2 = key.substr(i + 1, key.length() - (i + 1));
}

const vector<string>&
Markov::Picks(const string& word1, const string& word2) {
  const string key = word1 + kDelimiter + word2;
  vector<string>& choices = chain_[key];
  // std::random_shuffle(std::begin(choices), std::end(choices));
  return choices;
}

// For Emacs:
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:2
// c-basic-offset:2
// c-file-style:nil
// End:
// For VIM:
// vim:set expandtab softtabstop=2 shiftwidth=2 tabstop=2:
