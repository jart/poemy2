// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_UTIL_H_
#define POEMY_UTIL_H_

#include <string>
#include <vector>

#include <poemy/defines.h>

namespace poemy {
namespace util {

void RemoveDuplicatesFromStringlist(std::string* text, char delim);
std::vector<std::string> ListDir(const std::string& vector);
std::vector<std::string> Split(const std::string& text, char delim);
void CpuProfilerStart();
void CpuProfilerStop();

}  // namespace util
}  // namespace poemy

#endif  // POEMY_UTIL_H_

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
