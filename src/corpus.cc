// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/poemy.h"
#include "poemy/corpus.h"

Corpus::Corpus(std::istream* input) : input_(input), last_empty_(true) {
  CHECK(input_->good());
}

inline bool IsEndOfSentenceChar(char ch) {
  return (ch == '.' || ch == '\n' || ch == '?' || ch == '!' || ch == '"' ||
          ch == '(' || ch == ')');
}

string Corpus::get() {
  string res;
  bool begin = true;
  char ch;
  while (input_->get(ch).good()) {
    if (ch >= 'A' && ch <= 'Z') {
      ch += 'a' - 'A';
    }
    if (begin) {
      if ((ch >= 'a' && ch <= 'z') || ch == '\'') {
        begin = false;
        res += ch;
      } else if (IsEndOfSentenceChar(ch)) {
        if (!last_empty_) {
          break;
        }
      }
    } else {
      if ((ch >= 'a' && ch <= 'z') || ch == '\'') {
        res += ch;
      } else if (ch == '-') {
        char ch2 = input_->peek();
        if (ch2 >= 'a' && ch2 <= 'z') {
          res += ch;
        } else {
          break;
        }
      } else {
        if (IsEndOfSentenceChar(ch)) {
          input_->unget();
        }
        break;
      }
    }
  }
  last_empty_ = res.empty();
  return res;
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
