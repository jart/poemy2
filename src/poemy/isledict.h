// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_ISLEDICT_H_
#define POEMY_ISLEDICT_H_

#include <istream>
#include <string>
#include <vector>

#include <sparsehash/dense_hash_map>
#include <poemy/defines.h>

namespace poemy {

struct Syllable {
  std::vector<std::string> phonemes;
  int stress;
};

class Isledict {
 public:
  Isledict();
  // I take ownership of 'input'.
  void Load(std::istream* input);
  const std::vector<std::vector<Syllable> >& operator[](
    const std::string& word);
  // static void Print(const std::vector<Syllable>& pron);
  // static void Print(const std::vector<std::vector<Syllable> >& prons);

 private:
  google::dense_hash_map<std::string, std::string> pronounce_;
  google::dense_hash_map<std::string,
                         std::vector<std::vector<Syllable> > > pronounce_full_;

  POEMY_DISALLOW_COPY_AND_ASSIGN(Isledict);
};

}  // namespace poemy

#endif  // POEMY_ISLEDICT_H_

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
