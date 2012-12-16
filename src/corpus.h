// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_CORPUS_H
#define POEMY_CORPUS_H

class Corpus {
 public:
  explicit Corpus(const string& path) : fs_(path) {}
  bool good() { return fs_.good(); }
  void operator>>(string& out);

 private:
  std::ifstream fs_;

  DISALLOW_COPY_AND_ASSIGN(Corpus);
};

#endif // POEMY_CORPUS_H

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
