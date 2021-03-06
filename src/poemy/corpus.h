// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_CORPUS_H_
#define POEMY_CORPUS_H_

#include <istream>
#include <memory>
#include <string>

#include <poemy/defines.h>

namespace poemy {

// I'm responsible for turning raw corpus text into sentences and words.
class Corpus {
 public:
  explicit Corpus(std::unique_ptr<std::istream> input);
  bool good() const { return input_->good(); }
  std::string get();

 private:
  static bool IsEndOfSentenceChar(char ch);
  std::unique_ptr<std::istream> input_;
  bool last_empty_;

  POEMY_DISALLOW_COPY_AND_ASSIGN(Corpus);
};

}  // namespace poemy

#endif  // POEMY_CORPUS_H_

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
