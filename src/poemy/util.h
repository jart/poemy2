// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_UTIL_H_
#define POEMY_UTIL_H_

#include <string>
#include <vector>

void remove_duplicates_from_stringlist(char delim, string* o_text);
vector<string> list_dir(const string& vector);
vector<string> split(const string& text, char delim);
void cpu_profiler_start();
void cpu_profiler_stop();

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
