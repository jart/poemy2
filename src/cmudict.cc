// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/cmudict.h"
#include <chrono>
#include <memory>
#include <glog/logging.h>

using std::string;
using std::vector;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

namespace poemy {

void Cmudict::Load(std::istream* input) {
  std::unique_ptr<std::istream> free_input(input);
  PCHECK(input->good());
  string line;
  string word;
  auto begin = high_resolution_clock::now();
  while (std::getline(*input, line).good()) {
    Pronounce pron;
    if (!Parse(line, &word, &pron)) {
      continue;
    }
    pronounce_[word].push_back(std::move(pron));
  }
  auto end = high_resolution_clock::now();
  auto elapsed = duration_cast<std::chrono::milliseconds>(end - begin);
  LOG(INFO) << "loaded cmudict in " << elapsed.count() << "ms";
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
