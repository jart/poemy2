// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/markov.h"
#include <string>
#include <vector>
#include <sstream>
#include <gtest/gtest.h>
#include "poemy/corpus.h"

using std::string;
using std::vector;

namespace poemy {

TEST(MarkovTest, TheRaven) {
  Markov markov;
  markov.Load(new Corpus(new std::istringstream(
      "Once upon a midnight dreary, while I pondered, weak and weary,")));
  markov.LoadDone();
  EXPECT_EQ("a", string(markov.Picks({"once", "upon"})[0]));
  EXPECT_EQ("midnight", string(markov.Picks({"upon", "a"})[0]));
  EXPECT_EQ("dreary", string(markov.Picks({"a", "midnight"})[0]));
  EXPECT_EQ("while", string(markov.Picks({"midnight", "dreary"})[0]));
  EXPECT_EQ("i", string(markov.Picks({"dreary", "while"})[0]));
  EXPECT_EQ("pondered", string(markov.Picks({"while", "i"})[0]));
  EXPECT_EQ("weak", string(markov.Picks({"i", "pondered"})[0]));
  EXPECT_EQ("and", string(markov.Picks({"pondered", "weak"})[0]));
  EXPECT_EQ("weary", string(markov.Picks({"weak", "and"})[0]));
}

TEST(MarkovTest, RemoveDuplicates) {
  vector<string> list = {"hi", "abc", "hi", "there", "lol", "abc"};
  Markov::RemoveDuplicates(&list);
  vector<string> list2 = {"abc", "hi", "lol", "there"};
  EXPECT_EQ(list, list2);
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
