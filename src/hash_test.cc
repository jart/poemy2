// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/hash.h"
#include <vector>
#include <gtest/gtest.h>

using poemy::MurmurHash3;
using std::vector;
using std::string;

TEST(MurmurHash3Test, IntegralIdentity) {
  MurmurHash3<int> hash;
  EXPECT_EQ(1u, hash(1));
  EXPECT_EQ(666u, hash(666));
  MurmurHash3<bool> hash2;
  EXPECT_EQ(1u, hash2(true));
  EXPECT_EQ(0u, hash2(false));
}

TEST(MurmurHash3Test, String) {
  MurmurHash3<string> hash;
  for (auto key : vector<string>{"hi", "there", "what's up?"}) {
    uint32_t correct = 0;
    MurmurHash3_x86_32(key.data(), key.size(), hash.kSeed, &correct);
    EXPECT_EQ(correct, hash(key));
  }
}

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
