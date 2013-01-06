// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/memoryfile.h"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <glog/logging.h>

namespace poemy {

MemoryFile::MemoryFile(const std::string& path) : path_(path) {
  struct stat sb;
  PCHECK(fd_ = open(path_.c_str(), O_RDONLY)) << path_;
  PCHECK(fstat(fd_, &sb) == 0) << path_;
  size_ = sb.st_size;
  addr_ = mmap(nullptr, size_, PROT_READ, MAP_PRIVATE, fd_, 0);
  PCHECK(addr_ != MAP_FAILED) << path_;
}

MemoryFile::~MemoryFile() {
  PCHECK(munmap(addr_, size_) == 0) << path_;
  PCHECK(close(fd_) == 0) << path_;
}

}  // namespace poemy

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
