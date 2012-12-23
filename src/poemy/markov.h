// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_MARKOV_H_
#define POEMY_MARKOV_H_

#include <chrono>
#include <string>
#include <vector>
#include <sparsehash/sparse_hash_map>
#include "corpus.h"

class Markov {
 public:
  Markov();
  // I take ownership of 'corp'.
  void Load(Corpus* corp);
  void LoadDone();
  void PickFirst(string* o_word1, string* o_word2);
  const vector<string>& Picks(const string& word1, const string& word2);

 private:
  sparse_hash_map<string, vector<string> > chain_;
  vector<string> keys_;
  std::mt19937 rand_;
  static const char kDelimiter = ',';

  DISALLOW_COPY_AND_ASSIGN(Markov);
};

#endif  // POEMY_MARKOV_H_

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
