// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_TIMEIT_H_
#define POEMY_TIMEIT_H_

#include <chrono>
#include <string>
#include <poemy/defines.h>

namespace poemy {

class Timeit {
 public:
  enum Precision {
    kSeconds = 0,
    kMilliseconds = 1,
    kMicroseconds = 2,
    kNanoseconds = 3,
  };
  explicit Timeit(const std::string& name);
  explicit Timeit(const std::string& name, Precision precision);
  ~Timeit();
 private:
  std::string name_;
  Precision precision_;
  std::chrono::time_point<std::chrono::high_resolution_clock> begin_;
  POEMY_DISALLOW_COPY_AND_ASSIGN(Timeit);
};

}  // namespace poemy

#endif  // POEMY_TIMEIT_H_

// For Emacs:
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:2
// c-file-style: nil
// End:
// For VIM:
// vim:set expandtab softtabstop=2 shiftwidth=2 tabstop=4:
