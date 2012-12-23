// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/util.h"

#include <dirent.h>
#include <sys/types.h>
#include <sstream>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <sparsehash/dense_hash_set>

using std::string;
using std::vector;

namespace poemy {
namespace util {

vector<string> Split(const string& text, char delim) {
  vector<string> res;
  std::stringstream ss(text);
  string item;
  while (std::getline(ss, item, delim)) {
    res.push_back(std::move(item));
  }
  return res;
}

void RemoveDuplicatesFromStringlist(string* text, char delim) {
  // Split the string, remove empty values, and store it in a set.
  google::dense_hash_set<string> set;
  set.set_empty_key("");
  std::stringstream ss(*text);
  string item;
  while (std::getline(ss, item, delim)) {
    if (!item.empty()) {
      set.insert(std::move(item));
    }
  }
  // Reassemble string from the set.
  *text = "";
  bool first = true;
  for (const auto& item : set) {
    if (first) {
      first = false;
    } else {
      *text += delim;
    }
    *text += item;
  }
  text->shrink_to_fit();
}

vector<string> ListDir(const string& path) {
  vector<string> res;
  DIR* dir = opendir(path.c_str());
  PCHECK(dir != NULL);
  for (;;) {
    dirent* entry = readdir(dir);
    if (entry == nullptr) {
      break;
    }
    string fname(entry->d_name);
    if (fname == "." || fname == "..") {
      continue;
    }
    res.push_back(fname);
  }
  PCHECK(closedir(dir) == 0);
  return res;
}

#ifdef HAVE_PROFILER
#include <gperftools/profiler.h>

DEFINE_string(viewer, "xdg-open", "Command for viewing media content.");

void CpuProfilerStart() {
  ProfilerStart("/tmp/cpu");
}

void CpuProfilerStop() {
  ProfilerStop();
  if (!fork()) {
    setsid();
    close(0);
    close(1);
    close(2);
    if (system("pprof --gif poemy /tmp/cpu >/tmp/cpu.gif") != 0) {
      LOG(ERROR) << "Failed to run pprof.";
    } else {
      string cmd(FLAGS_viewer + " /tmp/cpu.gif");
      if (system(cmd.c_str()) != 0) {
        LOG(ERROR) << "I failed to show you the cpu profiler image :(";
      }
    }
    unlink("/tmp/cpu");
    exit(0);
  }
}

#else
void CpuProfilerStart() {}
void CpuProfilerStop() {}
#endif  // HAVE_PROFILER

}  // namespace util
}  // namespace poemy

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
