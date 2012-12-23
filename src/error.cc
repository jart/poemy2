// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/error.h"

#include <glog/logging.h>

namespace poemy {

Error::~Error() {
}

bool Error::Ok() const {
  return code_ == Error::kOK;
}

void Error::Reset() {
  code_ = kOK;
}

Error::Code Error::code() const {
  return code_;
}

void Error::set_code(Error::Code code) {
  CHECK(code != Error::kOK) << "Please use Reset() instead of set_code(kOK).";
  code_ = code;
}

const std::string Error::message() const {
  switch (code_) {
    case Error::kOK:
      return "OK";
    case Error::kExhausted:
      return "Exhausted";
    default:
      CHECK(false) << "Unknown error state: " << code_;
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
