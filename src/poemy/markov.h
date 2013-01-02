// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_MARKOV_H_
#define POEMY_MARKOV_H_

#include <random>
#include <string>
#include <utility>
#include <vector>

#include <sparsehash/dense_hash_map>

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
  const std::pair<std::string, std::string>& PickFirst() const;
  const std::vector<std::string>& Picks(
      const std::pair<std::string, std::string>& words) const;

 private:
  typedef MurmurHash3<std::pair<std::string, std::string> > Hasher;
  typedef google::dense_hash_map<std::pair<std::string, std::string>,
                                 std::vector<std::string>, Hasher> Map;
  Map chain_;
  std::vector<std::pair<std::string, std::string> > keys_;
  mutable std::mt19937 random_;
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
