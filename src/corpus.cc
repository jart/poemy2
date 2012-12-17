// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/poemy.h"
#include "poemy/corpus.h"

// Emits one word from the corpus or empty string if at the end of sentence or
// file. This routine trims out weird characters and lower-cases everything.
void Corpus::operator>>(string& out) {
  out = "";
  bool begin = true;
  char ch;
  while (fs_->get(ch).good()) {
    if (ch >= 'A' && ch <= 'Z') {
      ch += 'a' - 'A';
    }
    if (begin) {
      if ((ch >= 'a' && ch <= 'z') || ch == '\'') {
        begin = false;
        out += ch;
      } else if (ch == '.' || ch == '\n') {
        return;
      }
    } else {
      if ((ch >= 'a' && ch <= 'z') || ch == '\'' || ch == '-') {
        out += ch;
      } else {
        if (ch == '.' || ch == '\n') {
          fs_->unget();
        }
        return;
      }
    }
  }
  out = "";
}

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
