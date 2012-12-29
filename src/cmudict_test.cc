// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/cmudict.h"
#include <gtest/gtest.h>

using std::string;
using std::vector;

namespace poemy {

TEST(CmudictTest, Parse) {
  Cmudict dict;

  struct TestVector {
    string line;
    string word;
    Pronounce pronounce;
  };
  vector<TestVector> vectors = {
    { "JUSTINE  JH AH0 S T IY1 N", "justine",
      { {{kJH, kAH, kS, kT}, 0}, {{kIY, kN}, 1} } },
    { "KALE(1)  K EY1 L", "kale",
      { {{kK, kEY, kL}, 1} } },
    { "REGAL  R IY1 G AH0 L", "regal",
      { {{kR, kIY, kG}, 1}, {{kAH, kL}, 0} } },
    { "REGENERATED  R IY0 JH EH1 N ER0 EY2 T IH0 D", "regenerated",
      { {{kR, kIY, kJH}, 0}, {{kEH, kN}, 1}, {{kER}, 0}, {{kEY, kT}, 2},
        {{kIH, kD}, 0} } },
    { "REG  R EH1 G", "reg",
      { {{kR, kEH, kG}, 1} } },
    { "'-REG-'(6)  R EH1 G", "'-reg-'",
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
    ";;; # CMUdict  --  Major Version: 0.07a [102007]",
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
