// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/poemy.h"
#include "poemy/error.h"
#include "gtest/gtest.h"

TEST(ErrorTest, Basic) {
  Error err;
  EXPECT_TRUE(err.Ok());
  EXPECT_EQ("OK", err.message());
  err.set_code(Error::kExhausted);
  EXPECT_FALSE(err.Ok());
  EXPECT_EQ("Exhausted", err.message());
  err.Reset();
  EXPECT_TRUE(err.Ok());
  err.set_code(Error::kOK);
  EXPECT_TRUE(err.Ok());
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
