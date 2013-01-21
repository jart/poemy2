// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_DICT_H_
#define POEMY_DICT_H_

#include <limits>
#include <memory>
#include <istream>
#include <string>

#include <poemy/defines.h>
#include <poemy/pronounce.h>

namespace poemy {

class Dict {
 public:
  static const int kMissing = -1;
  static const int kSentinel = -2;
  virtual void Load(std::unique_ptr<std::istream> input) = 0;
  virtual const Pronounces& Speak(int code) const = 0;
  virtual const std::string& Word(int code) const = 0;
  virtual int Code(const std::string& word) const = 0;
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
