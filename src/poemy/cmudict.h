// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_CMUDICT_H_
#define POEMY_CMUDICT_H_

#include <poemy/dict.h>

namespace poemy {

class Cmudict : public Dict {
 public:
  // I take ownership of 'input'.
  virtual void Load(std::istream* input);
 private:
  POEMY_FRIEND_TEST(CmudictTest, Parse);
  bool Parse(const std::string& line, std::string* word, Pronounce *res) const;
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
