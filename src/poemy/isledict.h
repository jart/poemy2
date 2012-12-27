// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_ISLEDICT_H_
#define POEMY_ISLEDICT_H_

#include <istream>
#include <string>
#include <vector>

#include <sparsehash/dense_hash_map>
#include <poemy/defines.h>
#include <poemy/pronounce.h>

namespace poemy {

class Isledict {
 public:
  Isledict();
  // I take ownership of 'input'.
  void Load(std::istream* input);
  const Pronounces& operator[](const std::string& word);

 private:
  static bool ExtractWord(const std::string& line, std::string* word);
  static Syllable ParseSyllable(const std::string& prons, size_t& pos);
  static Pronounce ParsePronounce(const std::string& prons, size_t& pos);

  google::dense_hash_map<std::string, std::string> pronounce_;
  google::dense_hash_map<std::string, Pronounces> pronounce_full_;

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
