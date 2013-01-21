// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/markov.h"
#include <sstream>
#include <gtest/gtest.h>
#include <sparsehash/sparse_hash_set>
#include "poemy/dict.h"
#include "poemy/cmudict.h"
#include "poemy/corpus.h"
#include "poemy/unique.h"

#define C(word_string) dict.Code(word_string)

using std::pair;
using std::vector;
using std::vector;

namespace poemy {

TEST(MarkovTest, TheRaven) {
  Cmudict dict;
  dict.Load(new_unique<std::istringstream>(
      "ONCE  W AH1 N S\n"
      "UPON  AH0 P AA1 N\n"
      "A  AH0\n"
      "MIDNIGHT  M IH1 D N AY2 T\n"
      "DREARY  D R IH1 R IY0\n"
      "WHILE  W AY1 L\n"
      "WHILE(1)  HH W AY1 L\n"
      "I  AY1\n"
      "PONDERED  P AA1 N D ER0 D\n"
      "WEAK  W IY1 K\n"
      "AND  AH0 N D\n"
      "AND(1)  AE1 N D\n"
      "WEARY  W IH1 R IY0\n"));
  Markov markov;
  markov.Load(&dict, new_unique<Corpus>(new_unique<std::istringstream>(
      "Once upon a midnight dreary, while I pondered, weak and weary,")));

  EXPECT_EQ(1, markov.Picks({C("once"), C("upon")}).size());
  EXPECT_EQ(1, markov.Picks({C("upon"), C("a")}).size());
  EXPECT_EQ(1, markov.Picks({C("a"), C("midnight")}).size());
  EXPECT_EQ(1, markov.Picks({C("midnight"), C("dreary")}).size());
  EXPECT_EQ(1, markov.Picks({C("dreary"), C("while")}).size());
  EXPECT_EQ(1, markov.Picks({C("while"), C("i")}).size());
  EXPECT_EQ(1, markov.Picks({C("i"), C("pondered")}).size());
  EXPECT_EQ(1, markov.Picks({C("pondered"), C("weak")}).size());
  EXPECT_EQ(1, markov.Picks({C("weak"), C("and")}).size());
  EXPECT_EQ(1, markov.Picks({C("and"), C("weary")}).size());
  EXPECT_EQ(0, markov.Picks({C("once"), C("weary")}).size());
  // TODO: Resolve -1 -2 kludge nonsense
  // EXPECT_EQ(0, markov.Picks({C("LOL"), C("CAT")}).size());

  EXPECT_EQ(C("a"), markov.Picks({C("once"), C("upon")})[0]);
  EXPECT_EQ(C("midnight"), markov.Picks({C("upon"), C("a")})[0]);
  EXPECT_EQ(C("dreary"), markov.Picks({C("a"), C("midnight")})[0]);
  EXPECT_EQ(C("while"), markov.Picks({C("midnight"), C("dreary")})[0]);
  EXPECT_EQ(C("i"), markov.Picks({C("dreary"), C("while")})[0]);
  EXPECT_EQ(C("pondered"), markov.Picks({C("while"), C("i")})[0]);
  EXPECT_EQ(C("weak"), markov.Picks({C("i"), C("pondered")})[0]);
  EXPECT_EQ(C("and"), markov.Picks({C("pondered"), C("weak")})[0]);
  EXPECT_EQ(C("weary"), markov.Picks({C("weak"), C("and")})[0]);
  auto sen = Dict::kSentinel;
  EXPECT_EQ(sen, markov.Picks({C("and"), C("weary")})[0]);
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
