// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include <dirent.h>
#include <sys/types.h>

#include "poemy/poemy.h"
#include "poemy/util.h"

vector<string> split(const string& text, char delim) {
  vector<string> res;
  std::stringstream ss(text);
  string item;
  while (std::getline(ss, item, delim)) {
    res.push_back(item);
  }
  return res;
}

void remove_duplicates_from_stringlist(char delim, string* o_text) {
  // Split the string, remove empty values, and store it in a set.
  dense_hash_set<string> set;
  set.set_empty_key("");
  std::stringstream ss(*o_text);
  string item;
  while (std::getline(ss, item, delim)) {
    if (item != "") {
      set.insert(item);
    }
  }

  // Reassemble string from the set.
  *o_text = "";
  bool first = true;
  for (auto item : set) {
    if (first) {
      first = false;
    } else {
      *o_text += delim;
    }
    *o_text += item;
  }
  o_text->shrink_to_fit();
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

#ifdef HAVE_PROFILER

void cpu_profiler_start() {
  ProfilerStart("/tmp/cpu");
}

void cpu_profiler_stop() {
  ProfilerStop();
  if (!fork()) {
    setsid();
    close(0);
    close(1);
    close(2);
    int rc = !(system("pprof --gif poemy /tmp/cpu >/tmp/cpu.gif") != 0 ||
               system("eog /tmp/cpu.gif") != 0);
    unlink("/tmp/cpu");
    unlink("/tmp/cpu.gif");
    exit(rc);
  }
}

#else

void cpu_profiler_start() {}
void cpu_profiler_stop() {}

#endif  // HAVE_PROFILER

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
