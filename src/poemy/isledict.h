// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_ISLEDICT_H_
#define POEMY_ISLEDICT_H_

#include <string>
#include <vector>

namespace poemy {

struct Syllable {
  vector<string> phonemes;
  int stress;
};

class Isledict {
 public:
  Isledict();
  // I take ownership of 'input'.
  void Load(std::istream* input);
  const vector<vector<Syllable> >& operator[](const string& word);
  static void Print(const vector<Syllable>& pron);
  static void Print(const vector<vector<Syllable> >& prons);

 private:
  dense_hash_map<string, string> pronounce_;
  dense_hash_map<string, vector<vector<Syllable> > > pronounce_full_;

  DISALLOW_COPY_AND_ASSIGN(Isledict);
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
