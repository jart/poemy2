// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/pronounce.h"
#include <gtest/gtest.h>

using poemy::Phoneme;
using poemy::ParsePhoneme;

TEST(PronounceTest, ParsePhoneme) {
  EXPECT_EQ(Phoneme::kAA, ParsePhoneme("AA"));
  EXPECT_EQ(Phoneme::kAE, ParsePhoneme("AE"));
  EXPECT_EQ(Phoneme::kAH, ParsePhoneme("AH"));
  EXPECT_EQ(Phoneme::kAO, ParsePhoneme("AO"));
  EXPECT_EQ(Phoneme::kAW, ParsePhoneme("AW"));
  EXPECT_EQ(Phoneme::kAY, ParsePhoneme("AY"));
  EXPECT_EQ(Phoneme::kEH, ParsePhoneme("EH"));
  EXPECT_EQ(Phoneme::kER, ParsePhoneme("ER"));
  EXPECT_EQ(Phoneme::kEY, ParsePhoneme("EY"));
  EXPECT_EQ(Phoneme::kIH, ParsePhoneme("IH"));
  EXPECT_EQ(Phoneme::kIY, ParsePhoneme("IY"));
  EXPECT_EQ(Phoneme::kOW, ParsePhoneme("OW"));
  EXPECT_EQ(Phoneme::kOY, ParsePhoneme("OY"));
  EXPECT_EQ(Phoneme::kUH, ParsePhoneme("UH"));
  EXPECT_EQ(Phoneme::kUW, ParsePhoneme("UW"));
  EXPECT_EQ(Phoneme::kB,  ParsePhoneme("B"));
  EXPECT_EQ(Phoneme::kCH, ParsePhoneme("CH"));
  EXPECT_EQ(Phoneme::kD,  ParsePhoneme("D"));
  EXPECT_EQ(Phoneme::kDH, ParsePhoneme("DH"));
  EXPECT_EQ(Phoneme::kF,  ParsePhoneme("F"));
  EXPECT_EQ(Phoneme::kG,  ParsePhoneme("G"));
  EXPECT_EQ(Phoneme::kHH, ParsePhoneme("HH"));
  EXPECT_EQ(Phoneme::kJH, ParsePhoneme("JH"));
  EXPECT_EQ(Phoneme::kK,  ParsePhoneme("K"));
  EXPECT_EQ(Phoneme::kL,  ParsePhoneme("L"));
  EXPECT_EQ(Phoneme::kM,  ParsePhoneme("M"));
  EXPECT_EQ(Phoneme::kN,  ParsePhoneme("N"));
  EXPECT_EQ(Phoneme::kNG, ParsePhoneme("NG"));
  EXPECT_EQ(Phoneme::kP,  ParsePhoneme("P"));
  EXPECT_EQ(Phoneme::kR,  ParsePhoneme("R"));
  EXPECT_EQ(Phoneme::kS,  ParsePhoneme("S"));
  EXPECT_EQ(Phoneme::kSH, ParsePhoneme("SH"));
  EXPECT_EQ(Phoneme::kT,  ParsePhoneme("T"));
  EXPECT_EQ(Phoneme::kTH, ParsePhoneme("TH"));
  EXPECT_EQ(Phoneme::kV,  ParsePhoneme("V"));
  EXPECT_EQ(Phoneme::kW,  ParsePhoneme("W"));
  EXPECT_EQ(Phoneme::kY,  ParsePhoneme("Y"));
  EXPECT_EQ(Phoneme::kZ,  ParsePhoneme("Z"));
  EXPECT_EQ(Phoneme::kZH, ParsePhoneme("ZH"));

  EXPECT_EQ(Phoneme::kAA, ParsePhoneme("aa"));
  EXPECT_EQ(Phoneme::kAE, ParsePhoneme("ae"));
  EXPECT_EQ(Phoneme::kAH, ParsePhoneme("ah"));
  EXPECT_EQ(Phoneme::kAO, ParsePhoneme("ao"));
  EXPECT_EQ(Phoneme::kAW, ParsePhoneme("aw"));
  EXPECT_EQ(Phoneme::kAY, ParsePhoneme("ay"));
  EXPECT_EQ(Phoneme::kEH, ParsePhoneme("eh"));
  EXPECT_EQ(Phoneme::kER, ParsePhoneme("er"));
  EXPECT_EQ(Phoneme::kEY, ParsePhoneme("ey"));
  EXPECT_EQ(Phoneme::kIH, ParsePhoneme("ih"));
  EXPECT_EQ(Phoneme::kIY, ParsePhoneme("iy"));
  EXPECT_EQ(Phoneme::kOW, ParsePhoneme("ow"));
  EXPECT_EQ(Phoneme::kOY, ParsePhoneme("oy"));
  EXPECT_EQ(Phoneme::kUH, ParsePhoneme("uh"));
  EXPECT_EQ(Phoneme::kUW, ParsePhoneme("uw"));
  EXPECT_EQ(Phoneme::kB,  ParsePhoneme("b"));
  EXPECT_EQ(Phoneme::kCH, ParsePhoneme("ch"));
  EXPECT_EQ(Phoneme::kD,  ParsePhoneme("d"));
  EXPECT_EQ(Phoneme::kDH, ParsePhoneme("dh"));
  EXPECT_EQ(Phoneme::kF,  ParsePhoneme("f"));
  EXPECT_EQ(Phoneme::kG,  ParsePhoneme("g"));
  EXPECT_EQ(Phoneme::kHH, ParsePhoneme("hh"));
  EXPECT_EQ(Phoneme::kJH, ParsePhoneme("jh"));
  EXPECT_EQ(Phoneme::kK,  ParsePhoneme("k"));
  EXPECT_EQ(Phoneme::kL,  ParsePhoneme("l"));
  EXPECT_EQ(Phoneme::kM,  ParsePhoneme("m"));
  EXPECT_EQ(Phoneme::kN,  ParsePhoneme("n"));
  EXPECT_EQ(Phoneme::kNG, ParsePhoneme("ng"));
  EXPECT_EQ(Phoneme::kP,  ParsePhoneme("p"));
  EXPECT_EQ(Phoneme::kR,  ParsePhoneme("r"));
  EXPECT_EQ(Phoneme::kS,  ParsePhoneme("s"));
  EXPECT_EQ(Phoneme::kSH, ParsePhoneme("sh"));
  EXPECT_EQ(Phoneme::kT,  ParsePhoneme("t"));
  EXPECT_EQ(Phoneme::kTH, ParsePhoneme("th"));
  EXPECT_EQ(Phoneme::kV,  ParsePhoneme("v"));
  EXPECT_EQ(Phoneme::kW,  ParsePhoneme("w"));
  EXPECT_EQ(Phoneme::kY,  ParsePhoneme("y"));
  EXPECT_EQ(Phoneme::kZ,  ParsePhoneme("z"));
  EXPECT_EQ(Phoneme::kZH, ParsePhoneme("zh"));

  ASSERT_DEATH(ParsePhoneme("lol"), "Bad phoneme");
  ASSERT_DEATH(ParsePhoneme("lo"), "Bad phoneme");
  ASSERT_DEATH(ParsePhoneme("x"), "Bad phoneme");
  ASSERT_DEATH(ParsePhoneme(""), "Bad phoneme");
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
