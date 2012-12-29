// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/isledict.h"
#include <gtest/gtest.h>

using std::string;
using std::vector;

namespace poemy {

TEST(IsledictTest, Parse) {
  Isledict dict;

  struct TestVector {
    string line;
    string word;
    Pronounce pronounce;
  };
  vector<TestVector> vectors = {
    { "justine(n)(nnp girlname 0.017)  . jh ah0 s . t iy1 n . ",
      "justine",
      { {{kJH, kAH, kS}, 0}, {{kT, kIY, kN}, 1} } },
    { "kale(n)(nnp boyname 0.000)(nn root:kale)  . k ey1 l . ",
      "kale",
      { {{kK, kEY, kL}, 1} } },
    { "regal(j,n)(jj root:regal)(nnp -11.403)  . r iy1 . g ah0 l . ",
      "regal",
      { {{kR, kIY}, 1}, {{kG, kAH, kL}, 0} } },
    { "regenerated(v)(vbd root:generate)(morphology:re+generate+ed)"
      "(vbn root:generate)  . r iy0 . jh eh1 . n er0 . ey2 . t ih0 d . ",
      "regenerated",
      { {{kR, kIY}, 0}, {{kJH, kEH}, 1}, {{kN, kER}, 0}, {{kEY}, 2},
        {{kT, kIH, kD}, 0} } },
    { "reg()\t  . r eh1 g . ",
      "reg",
      { {{kR, kEH, kG}, 1} } },
    { "reg'-()\t  . r eh1 g . ",
      "reg'-",
      { {{kR, kEH, kG}, 1} } },
  };
  for (const auto& vec : vectors) {
    string word;
    Pronounce pronounce;
    ASSERT_TRUE(dict.Parse(vec.line, &word, &pronounce)) << vec.line;
    ASSERT_EQ(vec.word, word);
    ASSERT_EQ(vec.pronounce, pronounce);
  }

  vector<string> fail_lines = {
    "",
    "\n",
    "## ISLEdict is designed to have the following features:",
    ",(s)(punc -0.884)  . k aa1 . m ah0 . ",
    "-[40]1k(n)(nnp product)  . w ah2 n . k ey2 . ",
    "regal(j,n)(jj root:regal)(nnp -11.403)  . r iy1 . g AH0 l . "
    "regal(j,n)(jj root:regal)(nnp -11.403)  . r iy1 . g xx0 l . "
  };
  for (const auto& line : fail_lines) {
    string word;
    Pronounce pronounce;
    ASSERT_FALSE(dict.Parse(line, &word, &pronounce)) << line;
  }
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
