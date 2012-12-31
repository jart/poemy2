// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/timeit.h"
#include <glog/logging.h>

namespace poemy {

Timeit::Timeit(const std::string& name)
    : name_(name),
      precision_(kMilliseconds),
      begin_(std::chrono::high_resolution_clock::now()) {
}

Timeit::Timeit(const std::string& name, Precision precision)
    : name_(name),
      precision_(precision),
      begin_(std::chrono::high_resolution_clock::now()) {
}

Timeit::~Timeit() {
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = end - begin_;
  switch (precision_) {
    case kSeconds: {
      auto dur = std::chrono::duration_cast<std::chrono::seconds>(elapsed);
      LOG(INFO) << name_ << " took " << dur.count() << "sec";
      break;
    }
    case kMilliseconds: {
      auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
      LOG(INFO) << name_ << " took " << dur.count() << "ms";
      break;
    }
    case kMicroseconds: {
      auto dur = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
      LOG(INFO) << name_ << " took " << dur.count() << "µs";
      break;
    }
    case kNanoseconds: {
      auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed);
      LOG(INFO) << name_ << " took " << dur.count() << "ns";
      break;
    }
    default:
      LOG(ERROR) << "Bad precision: " << precision_;
  }
}

}  // namespace poemy

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
