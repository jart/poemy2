// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_UTIL_H
#define POEMY_UTIL_H

void remove_duplicates_from_stringlist(string& text, char delim);
vector<string> list_dir(const string& vector);
vector<string> split(string& text, char delim);

#endif // POEMY_UTIL_H

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
