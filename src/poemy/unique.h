// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_UNIQUE_H_
#define POEMY_UNIQUE_H_

#include <memory>
#include <utility>

// This is the proper way to express that you intend to pass ownershp of a
// brand new pointer to another function.
template<typename T, typename... Args>
static inline std::unique_ptr<T> new_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif  // POEMY_UNIQUE_H_

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
