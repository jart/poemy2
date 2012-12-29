// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_DICT_H_
#define POEMY_DICT_H_

#include <string>
#include <istream>

#include <sparsehash/dense_hash_map>
#include <poemy/defines.h>
#include <poemy/hash.h>
#include <poemy/pronounce.h>

namespace poemy {

class Dict {
 public:
  Dict();
  virtual void Load(std::istream* input) = 0;
  const Pronounces& operator[](const std::string& word) {
    return pronounce_[word];
  }

 protected:
  typedef MurmurHash3<std::string> Hasher;
  google::dense_hash_map<const std::string, Pronounces, Hasher> pronounce_;

 private:
  POEMY_DISALLOW_COPY_AND_ASSIGN(Dict);
};

}  // namespace poemy

#endif  // POEMY_DICT_H_

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
