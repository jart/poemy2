// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/isledict.h"
#include <memory>
#include <glog/logging.h>
#include "poemy/timeit.h"

namespace poemy {

void Isledict::Load(std::istream* input) {
  Timeit timeit("Isledict::Load()");
  std::unique_ptr<std::istream> free_input(input);
  PCHECK(input->good());
  std::string line, word;
  while (std::getline(*input, line).good()) {
    Pronounce pron;
    if (!Parse(line, &word, &pron)) {
      continue;
    }
    pronounce_[word].push_back(std::move(pron));
  }
}

}  // namespace poemy

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
