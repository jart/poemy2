// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/markov.h"

#include <memory>

#include <glog/logging.h>
#include "poemy/corpus.h"

using std::string;
using std::vector;

namespace poemy {

void Markov::Load(Corpus* corp) {
  std::unique_ptr<Corpus> free_corp(corp);
  while (corp->good()) {
    string w1 = corp->get();
    if (w1.empty()) {
      continue;
    }
    if (!corp->good()) {
      break;
    }
    string w2 = corp->get();
    if (w2.empty()) {
      continue;
    }
    while (corp->good()) {
      string w3 = corp->get();
      if (w3.empty()) {
        break;
      }
      CHECK(w3[0] != '\0');
      chain_[w1 + kDelimiter + w2].push_back(w3);
      std::swap(w1, w2);
      std::swap(w2, w3);
    }
  }
}

void Markov::LoadDone() {
  CHECK(chain_.size() > 0) << "You need to actually load some data.";
  keys_.clear();
  keys_.reserve(chain_.size());
  for (auto& pair : chain_) {
    std::unique(std::begin(pair.second), std::end(pair.second));
    keys_.push_back(pair.first);
  }
}

void Markov::PickFirst(string* o_word1, string* o_word2) {
  std::uniform_int_distribution<size_t> distrib(0, keys_.size() - 1);
  const string& key = keys_[distrib(dev_random_)];
  const int i = key.find(kDelimiter);
  *o_word1 = key.substr(0, i);
  *o_word2 = key.substr(i + 1, key.length() - (i + 1));
}

vector<string> Markov::Picks(const string& word1, const string& word2) {
  const string key = word1 + kDelimiter + word2;
  vector<string> choices = chain_[key];
  // std::random_shuffle(std::begin(choices), std::end(choices));
  return choices;
}

}  // namespace poemy

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
