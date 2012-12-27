// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_HASH_H_
#define POEMY_HASH_H_

#include <cstdint>
#include <string>

#include <poemy/defines.h>

void MurmurHash3_x86_32(const void* key, int len, uint32_t seed, void* out);
void MurmurHash3_x86_128(const void* key, int len, uint32_t seed, void* out);
void MurmurHash3_x64_128(const void* key, int len, uint32_t seed, void* out);

namespace poemy {

template<typename Result, typename Type>
struct MurmurHash3Base {
  typedef Type argument_type;
  typedef Result result_type;
  static const size_t kSeed = 1;
};

template<typename Type>
struct MurmurHash3 : public MurmurHash3Base<size_t, Type> {
  size_t operator()(Type val) const;
};

#define _MURMURHASH3_INTEGRAL_IMPL(Type)                            \
  template<>                                                        \
  inline size_t MurmurHash3<Type>::operator()(Type val) const {     \
    return static_cast<size_t>(val);                                \
  }                                                                 \

_MURMURHASH3_INTEGRAL_IMPL(bool);
_MURMURHASH3_INTEGRAL_IMPL(char);
_MURMURHASH3_INTEGRAL_IMPL(signed char);
_MURMURHASH3_INTEGRAL_IMPL(unsigned char);
_MURMURHASH3_INTEGRAL_IMPL(wchar_t);
_MURMURHASH3_INTEGRAL_IMPL(char16_t);
_MURMURHASH3_INTEGRAL_IMPL(char32_t);
_MURMURHASH3_INTEGRAL_IMPL(short);
_MURMURHASH3_INTEGRAL_IMPL(int);
_MURMURHASH3_INTEGRAL_IMPL(long);
_MURMURHASH3_INTEGRAL_IMPL(long long);
_MURMURHASH3_INTEGRAL_IMPL(unsigned short);
_MURMURHASH3_INTEGRAL_IMPL(unsigned int);
_MURMURHASH3_INTEGRAL_IMPL(unsigned long);
_MURMURHASH3_INTEGRAL_IMPL(unsigned long long);

template<>
struct MurmurHash3<std::string> : public MurmurHash3Base<size_t, std::string> {
  inline size_t operator()(const std::string& val) const {
    uint32_t out;
    MurmurHash3_x86_32(val.data(), val.size(), kSeed, &out);
    return out;
  }
};

}  // namespace poemy

#endif  // POEMY_HASH_H_

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
