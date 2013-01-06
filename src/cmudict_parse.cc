
#line 1 "src/cmudict_parse.rl"
// -*- C++ -*-
// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

// This parser also implements a very crappy syllabification algorithm.

#include "poemy/cmudict.h"
#include <glog/logging.h>

using std::string;

namespace poemy {


#line 18 "src/cmudict_parse.cc"
static const int cmudict_start = 1;
static const int cmudict_first_final = 16;
static const int cmudict_error = 0;

static const int cmudict_en_main = 1;


#line 17 "src/cmudict_parse.rl"


bool Cmudict::Parse(const string& line, string* word, Pronounce *res) const {
  int cs;
  const char* f = &line.front();
  const char* p = f;
  const char* pe = p + line.size();
  Syllable* syllable;
  bool found_vowel = false;
  Phoneme phoneme;

  if (p == pe) {
    return false;
  }
  word->clear();
  res->clear();
  res->emplace_back();
  syllable = &res->back();

  
#line 47 "src/cmudict_parse.cc"
	{
	cs = cmudict_start;
	}

#line 52 "src/cmudict_parse.cc"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
case 1:
	switch( (*p) ) {
		case 39: goto tr0;
		case 45: goto tr0;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto tr2;
	goto st0;
st0:
cs = 0;
	goto _out;
tr0:
#line 39 "src/cmudict_parse.rl"
	{
      *word += *p;
    }
	goto st2;
tr2:
#line 42 "src/cmudict_parse.rl"
	{
      *word += *p + ('a' - 'A');
    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 85 "src/cmudict_parse.cc"
	switch( (*p) ) {
		case 32: goto st3;
		case 39: goto tr0;
		case 40: goto st13;
		case 45: goto tr0;
	}
	if ( 65 <= (*p) && (*p) <= 90 )
		goto tr2;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 32 )
		goto st4;
	goto st0;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 65: goto st5;
		case 66: goto tr7;
		case 67: goto st6;
		case 68: goto tr9;
		case 69: goto st7;
		case 70: goto tr11;
		case 71: goto tr12;
		case 72: goto st8;
		case 73: goto st9;
		case 74: goto st10;
		case 75: goto tr16;
		case 76: goto tr17;
		case 77: goto tr18;
		case 78: goto tr19;
		case 79: goto st11;
		case 80: goto tr21;
		case 82: goto tr22;
		case 83: goto tr23;
		case 84: goto tr24;
		case 85: goto st12;
		case 86: goto tr26;
		case 87: goto tr27;
		case 89: goto tr28;
		case 90: goto tr29;
	}
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	switch( (*p) ) {
		case 65: goto tr30;
		case 69: goto tr31;
		case 72: goto tr32;
		case 79: goto tr33;
		case 87: goto tr34;
		case 89: goto tr35;
	}
	goto st0;
tr7:
#line 72 "src/cmudict_parse.rl"
	{ phoneme = kB;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr11:
#line 76 "src/cmudict_parse.rl"
	{ phoneme = kF;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr12:
#line 77 "src/cmudict_parse.rl"
	{ phoneme = kG;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr16:
#line 80 "src/cmudict_parse.rl"
	{ phoneme = kK;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr17:
#line 81 "src/cmudict_parse.rl"
	{ phoneme = kL;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr18:
#line 82 "src/cmudict_parse.rl"
	{ phoneme = kM;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr21:
#line 85 "src/cmudict_parse.rl"
	{ phoneme = kP;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr22:
#line 86 "src/cmudict_parse.rl"
	{ phoneme = kR;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr26:
#line 91 "src/cmudict_parse.rl"
	{ phoneme = kV;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr27:
#line 92 "src/cmudict_parse.rl"
	{ phoneme = kW;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr28:
#line 93 "src/cmudict_parse.rl"
	{ phoneme = kY;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr30:
#line 57 "src/cmudict_parse.rl"
	{ phoneme = kAA; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr31:
#line 58 "src/cmudict_parse.rl"
	{ phoneme = kAE; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr32:
#line 59 "src/cmudict_parse.rl"
	{ phoneme = kAH; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr33:
#line 60 "src/cmudict_parse.rl"
	{ phoneme = kAO; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr34:
#line 61 "src/cmudict_parse.rl"
	{ phoneme = kAW; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr35:
#line 62 "src/cmudict_parse.rl"
	{ phoneme = kAY; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr36:
#line 73 "src/cmudict_parse.rl"
	{ phoneme = kCH; }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr37:
#line 63 "src/cmudict_parse.rl"
	{ phoneme = kEH; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr38:
#line 64 "src/cmudict_parse.rl"
	{ phoneme = kER; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr39:
#line 65 "src/cmudict_parse.rl"
	{ phoneme = kEY; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr40:
#line 78 "src/cmudict_parse.rl"
	{ phoneme = kHH; }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr41:
#line 66 "src/cmudict_parse.rl"
	{ phoneme = kIH; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr42:
#line 67 "src/cmudict_parse.rl"
	{ phoneme = kIY; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr43:
#line 79 "src/cmudict_parse.rl"
	{ phoneme = kJH; }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr44:
#line 68 "src/cmudict_parse.rl"
	{ phoneme = kOW; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr45:
#line 69 "src/cmudict_parse.rl"
	{ phoneme = kOY; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr46:
#line 70 "src/cmudict_parse.rl"
	{ phoneme = kUH; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr47:
#line 71 "src/cmudict_parse.rl"
	{ phoneme = kUW; }
#line 48 "src/cmudict_parse.rl"
	{
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }
	goto st16;
tr53:
#line 75 "src/cmudict_parse.rl"
	{ phoneme = kDH; }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr54:
#line 84 "src/cmudict_parse.rl"
	{ phoneme = kNG; }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr55:
#line 88 "src/cmudict_parse.rl"
	{ phoneme = kSH; }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr56:
#line 90 "src/cmudict_parse.rl"
	{ phoneme = kTH; }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
tr57:
#line 95 "src/cmudict_parse.rl"
	{ phoneme = kZH; }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 497 "src/cmudict_parse.cc"
	switch( (*p) ) {
		case 32: goto st4;
		case 48: goto tr50;
		case 49: goto tr51;
		case 50: goto tr52;
	}
	goto st0;
tr50:
#line 98 "src/cmudict_parse.rl"
	{ syllable->stress = 0; }
	goto st17;
tr51:
#line 99 "src/cmudict_parse.rl"
	{ syllable->stress = 1; }
	goto st17;
tr52:
#line 100 "src/cmudict_parse.rl"
	{ syllable->stress = 2; }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 521 "src/cmudict_parse.cc"
	if ( (*p) == 32 )
		goto st4;
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( (*p) == 72 )
		goto tr36;
	goto st0;
tr9:
#line 74 "src/cmudict_parse.rl"
	{ phoneme = kD;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 544 "src/cmudict_parse.cc"
	switch( (*p) ) {
		case 32: goto st4;
		case 48: goto tr50;
		case 49: goto tr51;
		case 50: goto tr52;
		case 72: goto tr53;
	}
	goto st0;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
	switch( (*p) ) {
		case 72: goto tr37;
		case 82: goto tr38;
		case 89: goto tr39;
	}
	goto st0;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
	if ( (*p) == 72 )
		goto tr40;
	goto st0;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
	switch( (*p) ) {
		case 72: goto tr41;
		case 89: goto tr42;
	}
	goto st0;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
	if ( (*p) == 72 )
		goto tr43;
	goto st0;
tr19:
#line 83 "src/cmudict_parse.rl"
	{ phoneme = kN;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 598 "src/cmudict_parse.cc"
	switch( (*p) ) {
		case 32: goto st4;
		case 48: goto tr50;
		case 49: goto tr51;
		case 50: goto tr52;
		case 71: goto tr54;
	}
	goto st0;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
	switch( (*p) ) {
		case 87: goto tr44;
		case 89: goto tr45;
	}
	goto st0;
tr23:
#line 87 "src/cmudict_parse.rl"
	{ phoneme = kS;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 628 "src/cmudict_parse.cc"
	switch( (*p) ) {
		case 32: goto st4;
		case 48: goto tr50;
		case 49: goto tr51;
		case 50: goto tr52;
		case 72: goto tr55;
	}
	goto st0;
tr24:
#line 89 "src/cmudict_parse.rl"
	{ phoneme = kT;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 649 "src/cmudict_parse.cc"
	switch( (*p) ) {
		case 32: goto st4;
		case 48: goto tr50;
		case 49: goto tr51;
		case 50: goto tr52;
		case 72: goto tr56;
	}
	goto st0;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
	switch( (*p) ) {
		case 72: goto tr46;
		case 87: goto tr47;
	}
	goto st0;
tr29:
#line 94 "src/cmudict_parse.rl"
	{ phoneme = kZ;  }
#line 45 "src/cmudict_parse.rl"
	{
      syllable->phonemes.push_back(phoneme);
    }
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 679 "src/cmudict_parse.cc"
	switch( (*p) ) {
		case 32: goto st4;
		case 48: goto tr50;
		case 49: goto tr51;
		case 50: goto tr52;
		case 72: goto tr57;
	}
	goto st0;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
	if ( (*p) == 41 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
	if ( (*p) == 32 )
		goto st3;
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 111 "src/cmudict_parse.rl"


  return (cs != cmudict_error);
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
