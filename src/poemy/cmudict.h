// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_CMUDICT_H_
#define POEMY_CMUDICT_H_

#include <sparsehash/dense_hash_map>

#include <poemy/dict.h>
#include <poemy/hash.h>

namespace poemy {

class Cmudict : public Dict {
 public:
  Cmudict();
  // I take ownership of 'input'.
  virtual void Load(std::istream* input);
  virtual const Pronounces& operator[](const std::string& word) {
    return pronounce_[word];
  }

 private:
  typedef MurmurHash3<std::string> Hasher;
  typedef google::dense_hash_map<const std::string, Pronounces, Hasher> Map;
  Map pronounce_;
  bool Parse(const std::string& line, std::string* word, Pronounce *res) const;

  POEMY_FRIEND_TEST(CmudictTest, Parse);
  POEMY_DISALLOW_COPY_AND_ASSIGN(Cmudict);
};

}  // namespace poemy

#endif  // POEMY_CMUDICT_H_

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
