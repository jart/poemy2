// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_CORPUS_H_
#define POEMY_CORPUS_H_

#include <string>

class Corpus {
 public:
  explicit Corpus(std::istream* input) : input_(input) {}
  bool good() { return input_->good(); }
  void operator>>(string& out);

 private:
  std::istream* input_;

  DISALLOW_COPY_AND_ASSIGN(Corpus);
};

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
