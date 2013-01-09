// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/cmudict.h"
#include <gtest/gtest.h>
#include "poemy/unique.h"

using std::string;
using std::vector;

namespace poemy {

// TODO: If I add 'int code' to this, compiler crashes!
struct TestVector {
  string line;
  string word;
  Pronounce pronounce;
};

static vector<TestVector> vectors = {
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

TEST(CmudictTest, Parse) {
  Cmudict dict;
  for (const auto& vec : vectors) {
    string word;
    Pronounce pronounce;
    ASSERT_TRUE(dict.Parse(vec.line, &word, &pronounce)) << vec.line;
    ASSERT_EQ(vec.word, word);
    ASSERT_EQ(vec.pronounce, pronounce);
  }

  vector<string> bad_lines = {
    "",
    "\n",
    ";;; # CMUdict  --  Major Version: 0.07a [102007]",
    "JUSTINE  X AH0 S T IY1 N", "justine",
    "JUSTINE  JH AH7 S T IY1 N", "justine",
    "JUSTINE(  JH AH0 S T IY1 N", "justine",
    "JUSTINE)  JH AH0 S T IY1 N", "justine",
    "JUSTINE(666)  JH AH0 S T IY1 N", "justine",
  };
  for (const auto& line : bad_lines) {
    string word;
    Pronounce pronounce;
    ASSERT_FALSE(dict.Parse(line, &word, &pronounce)) << line;
  }
}

TEST(CmudictTest, API) {
  Cmudict dict;
  string data;
  for (const auto& vec : vectors) {
    data += vec.line + "\n";
  }
  dict.Load(new_unique<std::istringstream>(data));
  int code = 0;
  for (const auto& vec : vectors) {
    ASSERT_EQ(code, dict.Code(vec.word));
    ASSERT_EQ(vec.word, dict.Word(code));
    ASSERT_EQ(vec.pronounce, dict.Speak(code)[0]);
    ++code;
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
