// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy.h"
#include "util.h"

#include <dirent.h>
#include <sys/types.h>

vector<string> split(string& text, char delim) {
  vector<string> res;
  std::stringstream ss(text);
  string item;
  while (std::getline(ss, item, delim)) {
    res.push_back(item);
  }
  return res;
}

void remove_duplicates_from_stringlist(string& text, char delim) {
  // Split the string, remove empty values, and store it in a set.
  dense_hash_set<string> set;
  set.set_empty_key("");
  std::stringstream ss(text);
  string item;
  while (std::getline(ss, item, delim)) {
    if (item != "") {
      set.insert(item);
    }
  }

  // Reassemble string from the set.
  text = "";
  bool first = true;
  for (auto item : set) {
    if (first) {
      first = false;
    } else {
      text += delim;
    }
    text += item;
  }
  text.shrink_to_fit();
}

vector<string> list_dir(const string& path) {
  vector<string> res;
  DIR* dir = opendir(path.c_str());
  if (dir) {
    for (;;) {
      dirent* entry = readdir(dir);
      if (entry == NULL) {
        break;
      }
      string fname(entry->d_name);
      if (fname == "." || fname == "..") {
        continue;
      }
      res.push_back(fname);
    }
    closedir(dir);
  } else {
    cerr << path << ": " << strerror(errno) << endl;
  }
  return res;
}

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
