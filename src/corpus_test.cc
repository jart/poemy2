// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/poemy.h"
#include "poemy/corpus.h"
#include "gtest/gtest.h"

TEST(CorpusTest, HelloKitty) {
  Corpus corp(new std::istringstream("hello kitty"));
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("hello", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("kitty", corp.get());
  EXPECT_FALSE(corp.good());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, MultiSentence) {
  Corpus corp(new std::istringstream("hello kitty. i love you"));
  EXPECT_EQ("hello", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("kitty", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("i", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("love", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("you", corp.get());
  EXPECT_FALSE(corp.good());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, MultiLine) {
  Corpus corp(new std::istringstream("hello kitty...\n i love you"));
  EXPECT_EQ("hello", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("kitty", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("i", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("love", corp.get());
  EXPECT_TRUE(corp.good());
  EXPECT_EQ("you", corp.get());
  EXPECT_FALSE(corp.good());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, ConvertToLowerCase) {
  Corpus corp(new std::istringstream("HELLO KITTY"));
  EXPECT_EQ("hello", corp.get());
  EXPECT_EQ("kitty", corp.get());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, IncludeApostrophe) {
  Corpus corp(new std::istringstream("eat at joe's"));
  EXPECT_EQ("eat", corp.get());
  EXPECT_EQ("at", corp.get());
  EXPECT_EQ("joe's", corp.get());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, IncludeApostrophePrefix) {
  Corpus corp(new std::istringstream("'Tis the wind"));
  EXPECT_EQ("'tis", corp.get());
  EXPECT_EQ("the", corp.get());
  EXPECT_EQ("wind", corp.get());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, HyphenMiddle) {
  Corpus corp(new std::istringstream("lol-cat"));
  EXPECT_EQ("lol-cat", corp.get());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, NoEndHyphen) {
  Corpus corp(new std::istringstream("lol- -cat -lol-cat-"));
  EXPECT_EQ("lol", corp.get());
  EXPECT_EQ("cat", corp.get());
  EXPECT_EQ("lol-cat", corp.get());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, BreakDash) {
  for (const auto& str : vector<string> {"Thrilled me--filled me",
                                         "Thrilled me---filled me",
                                         "Thrilled me----filled me"}) {
    Corpus corp(new std::istringstream(str));
    EXPECT_EQ("thrilled", corp.get()) << "Original: " << str;
    EXPECT_EQ("me", corp.get()) << "Original: " << str;
    EXPECT_EQ("filled", corp.get()) << "Original: " << str;
    EXPECT_EQ("me", corp.get()) << "Original: " << str;
    EXPECT_EQ("", corp.get()) << "Original: " << str;
  }
}

TEST(CorpusTest, DealWithQuotes) {
  string str = "\"Lenore!\" Merely this, and nothing more.";
  Corpus corp(new std::istringstream(str));
  EXPECT_EQ("lenore", corp.get());
  EXPECT_EQ("", corp.get());
  EXPECT_EQ("merely", corp.get());
  EXPECT_EQ("this", corp.get());
  EXPECT_EQ("and", corp.get());
  EXPECT_EQ("nothing", corp.get());
  EXPECT_EQ("more", corp.get());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, DealWithQuotes2) {
  string str = "by a touch, \"you promised me!\" it said.";
  Corpus corp(new std::istringstream(str));
  EXPECT_EQ("by", corp.get());
  EXPECT_EQ("a", corp.get());
  EXPECT_EQ("touch", corp.get());
  EXPECT_EQ("", corp.get());
  EXPECT_EQ("you", corp.get());
  EXPECT_EQ("promised", corp.get());
  EXPECT_EQ("me", corp.get());
  EXPECT_EQ("", corp.get());
  EXPECT_EQ("it", corp.get());
  EXPECT_EQ("said", corp.get());
  EXPECT_EQ("", corp.get());
}

TEST(CorpusTest, DoubleLine) {
  Corpus corp(new std::istringstream("Hi.\n\n\nThere."));
  EXPECT_EQ("hi", corp.get());
  EXPECT_EQ("", corp.get());
  EXPECT_EQ("there", corp.get());
  EXPECT_EQ("", corp.get());
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
