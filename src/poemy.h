// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_H
#define POEMY_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <algorithm>
#include <chrono>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <functional>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sparsehash/dense_hash_map>
#include <sparsehash/dense_hash_set>
#include <sparsehash/sparse_hash_map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using google::dense_hash_map;
using google::sparse_hash_map;
using google::dense_hash_set;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#endif // POEMY_H

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
