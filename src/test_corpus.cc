// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/poemy.h"
#include "poemy/corpus.h"
#include "gtest/gtest.h"

TEST(CorpusTest, HelloKitty) {
  std::istringstream input("hello kitty");
  Corpus corp(&input);
  string str;
  corp >> str;
  EXPECT_EQ("hello", str);
  corp >> str;
  EXPECT_EQ("kitty", str);
  corp >> str;
  EXPECT_EQ("", str);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
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
