// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_ERROR_H_
#define POEMY_ERROR_H_

#include <ostream>
#include <string>

#include <poemy/defines.h>

namespace poemy {

// I'm an alternative to exceptions.
class Error {
 public:
  enum Code {
    kOK = 0,
    kError = 1,
    kExhausted = 2,
  };

  Error() : code_(kOK) {}
  ~Error();
  bool Ok() const;
  void Reset();
  Code code() const;
  void set_code(Code code);
  const std::string message() const;

 private:
  Code code_;

  friend std::ostream& operator<<(std::ostream& os, const Error& err) {
    return os << err.message();
  }

  POEMY_DISALLOW_COPY_AND_ASSIGN(Error);
};

}  // namespace poemy

#endif  // POEMY_ERROR_H_

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
