// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_DEFINES_H_
#define POEMY_DEFINES_H_

#define POEMY_FRIEND_TEST(test_case_name, test_name)  \
  friend class test_case_name##_##test_name##_Test

#define POEMY_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;            \
  void operator=(const TypeName&) = delete;

// Manual branch prediction. Use -fprofile-arcs first.
#ifdef __GNUC__
#  define POEMY_LIKELY(x) __builtin_expect(!!(x), 1)
#  define POEMY_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#  define POEMY_LIKELY(x) x
#  define POEMY_UNLIKELY(x) x
#endif

#endif  // POEMY_DEFINES_H_

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
