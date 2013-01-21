// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_MARKOV_H_
#define POEMY_MARKOV_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <sparsehash/dense_hash_map>

#include <poemy/defines.h>
#include <poemy/hash.h>

namespace poemy {

class Corpus;
class Dict;

class Markov {
 public:
  typedef std::pair<int, int> Key;
  typedef std::vector<int> Value;
  typedef MurmurHash3<Key> Hasher;

  explicit Markov();
  void Load(const Dict* dict, std::unique_ptr<Corpus> corp);
  const Value& Picks(Key words) const;
  void RemoveDuplicates();

 private:
  google::dense_hash_map<Key, Value, Hasher> chain_;
  std::vector<Key> keys_;
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
