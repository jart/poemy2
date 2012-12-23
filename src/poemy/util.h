// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_UTIL_H_
#define POEMY_UTIL_H_

#include <string>
#include <vector>

void RemoveDuplicatesFromStringlist(string* text, char delim);
vector<string> ListDir(const string& vector);
vector<string> Split(const string& text, char delim);
void CpuProfilerStart();
void CpuProfilerStop();

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
