// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/pronounce.h"
#include <gtest/gtest.h>

namespace poemy {

Pronounces empty = {};
Pronounces passion = {
  { {{kP, kAE}, 1}, {{kSH, kAH, kN}, 0} },
};
Pronounces fashion = {
  { {{kF, kAE}, 1}, {{kSH, kAH, kN}, 0} },
};
Pronounces acquainted = {
  { {{kAH, kK}, 0}, {{kW, kEY, kN}, 1}, {{kT, kIH, kD}, 0} },
  { {{kAH, kK}, 0}, {{kW, kEY}, 1}, {{kN, kIH, kD}, 0} },
};
Pronounces acquainted2 = {
  { {{kAH, kK}, 0}, {{kW, kEY, kN}, 1}, {{kT, kIH, kD}, 0} },
  { {{kAH, kK}, 1}, {{kW, kEY}, 0}, {{kN, kIH, kD}, 1} },  // Wrong.
  { {{kAH, kK}, 0}, {{kW, kEY}, 2} },  // Wrong.
};
Pronounces painted = {
  { {{kP, kEY, kN}, 1}, {{kT, kIH, kZ}, 0} },  // Intentionally wrong.
  { {{kP, kEY}, 1}, {{kN, kIH, kD}, 0} },
};
Pronounces thee = {
  { {{kDH, kIY}, 1} },
};
Pronounces philosophy = {
  { {{kF, kAH}, 0}, {{kL, kAA}, 1}, {{kS, kAH}, 0}, {{kF, kIY}, 0} },
};

TEST(PronounceTest, IsRhyme) {
  ASSERT_TRUE(IsRhyme(passion, fashion));
  ASSERT_TRUE(IsRhyme(fashion, passion));
  ASSERT_TRUE(IsRhyme(painted, acquainted));
  ASSERT_TRUE(IsRhyme(acquainted, painted));
  ASSERT_TRUE(IsRhyme(thee, philosophy));
  ASSERT_TRUE(IsRhyme(philosophy, thee));
  ASSERT_FALSE(IsRhyme(thee, fashion));
  ASSERT_FALSE(IsRhyme(fashion, thee));
  ASSERT_FALSE(IsRhyme(painted, fashion));
  ASSERT_FALSE(IsRhyme(fashion, painted));
  ASSERT_FALSE(IsRhyme(empty, thee));
  ASSERT_FALSE(IsRhyme(thee, empty));
  ASSERT_FALSE(IsRhyme(fashion, empty));
  ASSERT_FALSE(IsRhyme(painted, empty));
  ASSERT_FALSE(IsRhyme(fashion, empty));
}

TEST(PronounceTest, MatchMeter) {
  Meter meter = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
  ASSERT_EQ(nullptr, MatchMeter(passion, meter, 0));
  ASSERT_EQ(&passion[0], MatchMeter(passion, meter, 1));
  ASSERT_EQ(nullptr, MatchMeter(passion, meter, 2));
  ASSERT_EQ(&passion[0], MatchMeter(passion, meter, 3));
  ASSERT_EQ(&acquainted[0], MatchMeter(acquainted, meter, 0));
  ASSERT_EQ(nullptr, MatchMeter(acquainted, meter, 1));
  ASSERT_EQ(&acquainted2[1], MatchMeter(acquainted2, meter, 1));
  ASSERT_EQ(nullptr, MatchMeter(acquainted, meter, 8));
  ASSERT_EQ(&acquainted2[2], MatchMeter(acquainted2, meter, 8));
}

TEST(PronounceTest, ParsePhoneme) {
  EXPECT_EQ(kAA, ParsePhoneme("AA"));
  EXPECT_EQ(kAE, ParsePhoneme("AE"));
  EXPECT_EQ(kAH, ParsePhoneme("AH"));
  EXPECT_EQ(kAO, ParsePhoneme("AO"));
  EXPECT_EQ(kAW, ParsePhoneme("AW"));
  EXPECT_EQ(kAY, ParsePhoneme("AY"));
  EXPECT_EQ(kEH, ParsePhoneme("EH"));
  EXPECT_EQ(kER, ParsePhoneme("ER"));
  EXPECT_EQ(kEY, ParsePhoneme("EY"));
  EXPECT_EQ(kIH, ParsePhoneme("IH"));
  EXPECT_EQ(kIY, ParsePhoneme("IY"));
  EXPECT_EQ(kOW, ParsePhoneme("OW"));
  EXPECT_EQ(kOY, ParsePhoneme("OY"));
  EXPECT_EQ(kUH, ParsePhoneme("UH"));
  EXPECT_EQ(kUW, ParsePhoneme("UW"));
  EXPECT_EQ(kB,  ParsePhoneme("B"));
  EXPECT_EQ(kCH, ParsePhoneme("CH"));
  EXPECT_EQ(kD,  ParsePhoneme("D"));
  EXPECT_EQ(kDH, ParsePhoneme("DH"));
  EXPECT_EQ(kF,  ParsePhoneme("F"));
  EXPECT_EQ(kG,  ParsePhoneme("G"));
  EXPECT_EQ(kHH, ParsePhoneme("HH"));
  EXPECT_EQ(kJH, ParsePhoneme("JH"));
  EXPECT_EQ(kK,  ParsePhoneme("K"));
  EXPECT_EQ(kL,  ParsePhoneme("L"));
  EXPECT_EQ(kM,  ParsePhoneme("M"));
  EXPECT_EQ(kN,  ParsePhoneme("N"));
  EXPECT_EQ(kNG, ParsePhoneme("NG"));
  EXPECT_EQ(kP,  ParsePhoneme("P"));
  EXPECT_EQ(kR,  ParsePhoneme("R"));
  EXPECT_EQ(kS,  ParsePhoneme("S"));
  EXPECT_EQ(kSH, ParsePhoneme("SH"));
  EXPECT_EQ(kT,  ParsePhoneme("T"));
  EXPECT_EQ(kTH, ParsePhoneme("TH"));
  EXPECT_EQ(kV,  ParsePhoneme("V"));
  EXPECT_EQ(kW,  ParsePhoneme("W"));
  EXPECT_EQ(kY,  ParsePhoneme("Y"));
  EXPECT_EQ(kZ,  ParsePhoneme("Z"));
  EXPECT_EQ(kZH, ParsePhoneme("ZH"));

  EXPECT_EQ(kAA, ParsePhoneme("aa"));
  EXPECT_EQ(kAE, ParsePhoneme("ae"));
  EXPECT_EQ(kAH, ParsePhoneme("ah"));
  EXPECT_EQ(kAO, ParsePhoneme("ao"));
  EXPECT_EQ(kAW, ParsePhoneme("aw"));
  EXPECT_EQ(kAY, ParsePhoneme("ay"));
  EXPECT_EQ(kEH, ParsePhoneme("eh"));
  EXPECT_EQ(kER, ParsePhoneme("er"));
  EXPECT_EQ(kEY, ParsePhoneme("ey"));
  EXPECT_EQ(kIH, ParsePhoneme("ih"));
  EXPECT_EQ(kIY, ParsePhoneme("iy"));
  EXPECT_EQ(kOW, ParsePhoneme("ow"));
  EXPECT_EQ(kOY, ParsePhoneme("oy"));
  EXPECT_EQ(kUH, ParsePhoneme("uh"));
  EXPECT_EQ(kUW, ParsePhoneme("uw"));
  EXPECT_EQ(kB,  ParsePhoneme("b"));
  EXPECT_EQ(kCH, ParsePhoneme("ch"));
  EXPECT_EQ(kD,  ParsePhoneme("d"));
  EXPECT_EQ(kDH, ParsePhoneme("dh"));
  EXPECT_EQ(kF,  ParsePhoneme("f"));
  EXPECT_EQ(kG,  ParsePhoneme("g"));
  EXPECT_EQ(kHH, ParsePhoneme("hh"));
  EXPECT_EQ(kJH, ParsePhoneme("jh"));
  EXPECT_EQ(kK,  ParsePhoneme("k"));
  EXPECT_EQ(kL,  ParsePhoneme("l"));
  EXPECT_EQ(kM,  ParsePhoneme("m"));
  EXPECT_EQ(kN,  ParsePhoneme("n"));
  EXPECT_EQ(kNG, ParsePhoneme("ng"));
  EXPECT_EQ(kP,  ParsePhoneme("p"));
  EXPECT_EQ(kR,  ParsePhoneme("r"));
  EXPECT_EQ(kS,  ParsePhoneme("s"));
  EXPECT_EQ(kSH, ParsePhoneme("sh"));
  EXPECT_EQ(kT,  ParsePhoneme("t"));
  EXPECT_EQ(kTH, ParsePhoneme("th"));
  EXPECT_EQ(kV,  ParsePhoneme("v"));
  EXPECT_EQ(kW,  ParsePhoneme("w"));
  EXPECT_EQ(kY,  ParsePhoneme("y"));
  EXPECT_EQ(kZ,  ParsePhoneme("z"));
  EXPECT_EQ(kZH, ParsePhoneme("zh"));

  ASSERT_DEATH(ParsePhoneme("lol"), "Bad phoneme");
  ASSERT_DEATH(ParsePhoneme("lo"), "Bad phoneme");
  ASSERT_DEATH(ParsePhoneme("x"), "Bad phoneme");
  ASSERT_DEATH(ParsePhoneme(""), "Bad phoneme");
}

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
