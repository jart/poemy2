// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_MARKOV_H_
#define POEMY_MARKOV_H_

#include <random>
#include <string>
#include <vector>

#include <sparsehash/sparse_hash_map>

#include <poemy/defines.h>
#include <poemy/hash.h>

namespace poemy {

class Corpus;

class Markov {
 public:
  explicit Markov();
  // I take ownership of 'corp'.
  void Load(Corpus* corp);
  void LoadDone();
  void PickFirst(std::string* o_word1, std::string* o_word2);
  const std::vector<std::string>& Picks(const std::string& word1,
                                        const std::string& word2);

 private:
  typedef MurmurHash3<std::string> Hasher;
  google::sparse_hash_map<std::string, std::vector<std::string>, Hasher> chain_;
  std::vector<std::string> keys_;
  std::mt19937 random_;
  static const char kDelimiter = ',';

  POEMY_DISALLOW_COPY_AND_ASSIGN(Markov);
};

}  // namespace poemy

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
