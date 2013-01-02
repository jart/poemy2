// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/markov.h"

#include <chrono>
#include <memory>

#include <glog/logging.h>
#include "poemy/corpus.h"

using std::pair;
using std::string;
using std::vector;

namespace poemy {

Markov::Markov()
    : random_(std::chrono::system_clock::now().time_since_epoch().count()) {
  chain_.set_empty_key({"", ""});
}

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
      chain_[{w1, w2}].emplace_back(w3);
      std::swap(w1, w2);
      std::swap(w2, w3);
    }
  }
}

void Markov::LoadDone() {
  CHECK(chain_.size() > 0) << "You need to actually load some data.";
  keys_.clear();
  keys_.reserve(chain_.size());
  for (auto& ent : chain_) {
    std::unique(std::begin(ent.second), std::end(ent.second));
    ent.second.shrink_to_fit();
    keys_.emplace_back(ent.first);
  }
}

const pair<string, string>& Markov::PickFirst() const {
  std::uniform_int_distribution<size_t> distrib(0, keys_.size() - 1);
  return keys_[distrib(random_)];
}

const vector<string>& Markov::Picks(const pair<string, string>& words) const {
  static vector<string> empty;
  auto ent = chain_.find(words);
  if (ent != chain_.end()) {
    return ent->second;
  } else {
    return empty;
  }
  // vector<string> choices = chain_[word1 + kDelimiter + word2];
  // std::random_shuffle(std::begin(choices), std::end(choices));
  // return choices;
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
