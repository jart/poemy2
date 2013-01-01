// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_MEMORYFILE_H_
#define POEMY_MEMORYFILE_H_

#include <string>

#include <poemy/defines.h>

namespace poemy {

// Uses mmap() to load file to memory in read-only mode.
class MemoryFile {
 public:
  explicit MemoryFile(const std::string& path);
  ~MemoryFile();
  inline const void* addr() const { return addr_; }
  inline size_t size() const { return size_; }
 private:
  int fd_;
  void* addr_;
  size_t size_;
  std::string path_;
  POEMY_DISALLOW_COPY_AND_ASSIGN(MemoryFile);
};

}  // namespace poemy

#endif  // POEMY_MEMORYFILE_H_

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
