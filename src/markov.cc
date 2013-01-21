// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/markov.h"

#include <algorithm>
#include <chrono>
#include <memory>

#include <glog/logging.h>
#include "poemy/corpus.h"
#include "poemy/dict.h"

namespace poemy {

Markov::Markov() {
  chain_.set_empty_key({Dict::kMissing, Dict::kMissing});
}

void Markov::Load(const Dict* dict, std::unique_ptr<Corpus> corp) {
  int w1 = Dict::kSentinel;
  int w2 = Dict::kSentinel;
  int w3 = Dict::kSentinel;
  while (corp->good()) {
    w3 = dict->Code(corp->get());
    if (w3 == Dict::kMissing) {
      w3 = Dict::kSentinel;
      chain_[{w1, w2}].push_back(w3);
      w1 = Dict::kSentinel;
      w2 = Dict::kSentinel;
      continue;
    }
    chain_[{w1, w2}].push_back(w3);
    w1 = w2;
    w2 = w3;
  }
}

const Markov::Value& Markov::Picks(Markov::Key words) const {
  static const Markov::Value empty;
  auto ent = chain_.find(words);
  if (ent != chain_.end()) {
    return ent->second;
  } else {
    return empty;
  }
}

void Markov::RemoveDuplicates(Markov::Value* list) {
  std::sort(list->begin(), list->end());
  auto new_end = std::unique(list->begin(), list->end());
  list->resize(new_end - list->begin());
  list->shrink_to_fit();
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
