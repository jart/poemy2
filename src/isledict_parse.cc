
#line 1 "src/isledict_parse.rl"
// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/isledict.h"
#include <glog/logging.h>

using std::string;

namespace poemy {


#line 15 "src/isledict_parse.cc"
static const int isledict_start = 1;
static const int isledict_first_final = 23;
static const int isledict_error = 0;

static const int isledict_en_main = 1;


#line 14 "src/isledict_parse.rl"


bool Isledict::Parse(const string& line, string* word, Pronounce *res) const {
  int cs;
  const char* f = &line.front();
  const char* p = f;
  const char* pe = p + line.size();
  const char* eof = pe;
  Syllable* syllable;

  if (p == pe) {
    return false;
  }
  word->clear();
  res->clear();

  
#line 41 "src/isledict_parse.cc"
	{
	cs = isledict_start;
	}

#line 46 "src/isledict_parse.cc"
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
	if ( 97 <= (*p) && (*p) <= 122 )
		goto tr0;
	goto st0;
st0:
cs = 0;
	goto _out;
tr0:
#line 33 "src/isledict_parse.rl"
	{
      *word += *p;
    }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 73 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 39: goto tr0;
		case 40: goto st3;
		case 45: goto tr0;
	}
	if ( 97 <= (*p) && (*p) <= 122 )
		goto tr0;
	goto st0;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
	if ( (*p) == 41 )
		goto st4;
	goto st3;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
	switch( (*p) ) {
		case 9: goto st5;
		case 32: goto st5;
		case 40: goto st3;
		case 46: goto st6;
	}
	goto st0;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
	switch( (*p) ) {
		case 9: goto st5;
		case 32: goto st5;
		case 46: goto st6;
	}
	goto st0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	switch( (*p) ) {
		case 9: goto st6;
		case 32: goto st6;
		case 97: goto tr6;
		case 98: goto tr7;
		case 99: goto tr8;
		case 100: goto tr9;
		case 101: goto tr10;
		case 102: goto tr11;
		case 103: goto tr12;
		case 104: goto tr13;
		case 105: goto tr14;
		case 106: goto tr15;
		case 107: goto tr16;
		case 108: goto tr17;
		case 109: goto tr18;
		case 110: goto tr19;
		case 111: goto tr20;
		case 112: goto tr21;
		case 114: goto tr22;
		case 115: goto tr23;
		case 116: goto tr24;
		case 117: goto tr25;
		case 118: goto tr26;
		case 119: goto tr27;
		case 121: goto tr28;
		case 122: goto tr29;
	}
	goto st0;
tr6:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 154 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 97: goto tr30;
		case 101: goto tr31;
		case 104: goto tr32;
		case 111: goto tr33;
		case 119: goto tr34;
		case 121: goto tr35;
	}
	goto st0;
tr7:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 60 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kB);  }
	goto st8;
tr11:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 64 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kF);  }
	goto st8;
tr12:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 65 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kG);  }
	goto st8;
tr16:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 68 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kK);  }
	goto st8;
tr17:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 69 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kL);  }
	goto st8;
tr18:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 70 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kM);  }
	goto st8;
tr21:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 73 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kP);  }
	goto st8;
tr22:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 74 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kR);  }
	goto st8;
tr26:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 79 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kV);  }
	goto st8;
tr27:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 80 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kW);  }
	goto st8;
tr28:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 81 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kY);  }
	goto st8;
tr30:
#line 45 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kAA); }
	goto st8;
tr31:
#line 46 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kAE); }
	goto st8;
tr32:
#line 47 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kAH); }
	goto st8;
tr33:
#line 48 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kAO); }
	goto st8;
tr34:
#line 49 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kAW); }
	goto st8;
tr35:
#line 50 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kAY); }
	goto st8;
tr42:
#line 60 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kB);  }
	goto st8;
tr46:
#line 64 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kF);  }
	goto st8;
tr47:
#line 65 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kG);  }
	goto st8;
tr51:
#line 68 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kK);  }
	goto st8;
tr52:
#line 69 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kL);  }
	goto st8;
tr53:
#line 70 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kM);  }
	goto st8;
tr56:
#line 73 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kP);  }
	goto st8;
tr57:
#line 74 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kR);  }
	goto st8;
tr61:
#line 79 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kV);  }
	goto st8;
tr62:
#line 80 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kW);  }
	goto st8;
tr63:
#line 81 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kY);  }
	goto st8;
tr65:
#line 61 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kCH); }
	goto st8;
tr67:
#line 51 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kEH); }
	goto st8;
tr68:
#line 52 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kER); }
	goto st8;
tr69:
#line 53 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kEY); }
	goto st8;
tr75:
#line 66 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kHH); }
	goto st8;
tr71:
#line 54 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kIH); }
	goto st8;
tr72:
#line 55 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kIY); }
	goto st8;
tr73:
#line 67 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kJH); }
	goto st8;
tr74:
#line 72 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kNG); }
#line 65 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kG);  }
	goto st8;
tr76:
#line 56 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kOW); }
	goto st8;
tr77:
#line 57 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kOY); }
	goto st8;
tr80:
#line 58 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kUH); }
	goto st8;
tr81:
#line 59 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kUW); }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 389 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 9: goto st9;
		case 32: goto st9;
		case 46: goto st23;
		case 48: goto tr38;
		case 49: goto tr39;
		case 50: goto tr40;
		case 97: goto st7;
		case 98: goto tr42;
		case 99: goto st10;
		case 100: goto tr44;
		case 101: goto st12;
		case 102: goto tr46;
		case 103: goto tr47;
		case 104: goto st17;
		case 105: goto st14;
		case 106: goto st15;
		case 107: goto tr51;
		case 108: goto tr52;
		case 109: goto tr53;
		case 110: goto tr54;
		case 111: goto st18;
		case 112: goto tr56;
		case 114: goto tr57;
		case 115: goto tr58;
		case 116: goto tr59;
		case 117: goto st21;
		case 118: goto tr61;
		case 119: goto tr62;
		case 121: goto tr63;
		case 122: goto tr64;
	}
	goto st0;
tr38:
#line 85 "src/isledict_parse.rl"
	{ syllable->stress = 0; }
	goto st9;
tr39:
#line 86 "src/isledict_parse.rl"
	{ syllable->stress = 1; }
	goto st9;
tr40:
#line 87 "src/isledict_parse.rl"
	{ syllable->stress = 2; }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 439 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 9: goto st9;
		case 32: goto st9;
		case 46: goto st23;
		case 97: goto st7;
		case 98: goto tr42;
		case 99: goto st10;
		case 100: goto tr44;
		case 101: goto st12;
		case 102: goto tr46;
		case 103: goto tr47;
		case 104: goto st17;
		case 105: goto st14;
		case 106: goto st15;
		case 107: goto tr51;
		case 108: goto tr52;
		case 109: goto tr53;
		case 110: goto tr54;
		case 111: goto st18;
		case 112: goto tr56;
		case 114: goto tr57;
		case 115: goto tr58;
		case 116: goto tr59;
		case 117: goto st21;
		case 118: goto tr61;
		case 119: goto tr62;
		case 121: goto tr63;
		case 122: goto tr64;
	}
	goto st0;
st23:
	if ( ++p == pe )
		goto _test_eof23;
case 23:
	switch( (*p) ) {
		case 9: goto st23;
		case 32: goto st23;
		case 97: goto tr6;
		case 98: goto tr7;
		case 99: goto tr8;
		case 100: goto tr9;
		case 101: goto tr10;
		case 102: goto tr11;
		case 103: goto tr12;
		case 104: goto tr13;
		case 105: goto tr14;
		case 106: goto tr15;
		case 107: goto tr16;
		case 108: goto tr17;
		case 109: goto tr18;
		case 110: goto tr19;
		case 111: goto tr20;
		case 112: goto tr21;
		case 114: goto tr22;
		case 115: goto tr23;
		case 116: goto tr24;
		case 117: goto tr25;
		case 118: goto tr26;
		case 119: goto tr27;
		case 121: goto tr28;
		case 122: goto tr29;
	}
	goto st0;
tr8:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
	goto st10;
st10:
	if ( ++p == pe )
		goto _test_eof10;
case 10:
#line 514 "src/isledict_parse.cc"
	if ( (*p) == 104 )
		goto tr65;
	goto st0;
tr9:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 62 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kD);  }
	goto st11;
tr44:
#line 62 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kD);  }
	goto st11;
st11:
	if ( ++p == pe )
		goto _test_eof11;
case 11:
#line 535 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 9: goto st9;
		case 32: goto st9;
		case 46: goto st23;
		case 48: goto tr38;
		case 49: goto tr39;
		case 50: goto tr40;
		case 97: goto st7;
		case 98: goto tr42;
		case 99: goto st10;
		case 100: goto tr44;
		case 101: goto st12;
		case 102: goto tr46;
		case 103: goto tr47;
		case 104: goto tr66;
		case 105: goto st14;
		case 106: goto st15;
		case 107: goto tr51;
		case 108: goto tr52;
		case 109: goto tr53;
		case 110: goto tr54;
		case 111: goto st18;
		case 112: goto tr56;
		case 114: goto tr57;
		case 115: goto tr58;
		case 116: goto tr59;
		case 117: goto st21;
		case 118: goto tr61;
		case 119: goto tr62;
		case 121: goto tr63;
		case 122: goto tr64;
	}
	goto st0;
tr10:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
	goto st12;
st12:
	if ( ++p == pe )
		goto _test_eof12;
case 12:
#line 580 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 104: goto tr67;
		case 114: goto tr68;
		case 121: goto tr69;
	}
	goto st0;
tr66:
#line 63 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kDH); }
	goto st13;
tr70:
#line 66 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kHH); }
	goto st13;
tr78:
#line 76 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kSH); }
	goto st13;
tr79:
#line 78 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kTH); }
	goto st13;
tr82:
#line 83 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kZH); }
	goto st13;
st13:
	if ( ++p == pe )
		goto _test_eof13;
case 13:
#line 611 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 9: goto st9;
		case 32: goto st9;
		case 46: goto st23;
		case 48: goto tr38;
		case 49: goto tr39;
		case 50: goto tr40;
		case 97: goto st7;
		case 98: goto tr42;
		case 99: goto st10;
		case 100: goto tr44;
		case 101: goto st12;
		case 102: goto tr46;
		case 103: goto tr47;
		case 104: goto tr70;
		case 105: goto st14;
		case 106: goto st15;
		case 107: goto tr51;
		case 108: goto tr52;
		case 109: goto tr53;
		case 110: goto tr54;
		case 111: goto st18;
		case 112: goto tr56;
		case 114: goto tr57;
		case 115: goto tr58;
		case 116: goto tr59;
		case 117: goto st21;
		case 118: goto tr61;
		case 119: goto tr62;
		case 121: goto tr63;
		case 122: goto tr64;
	}
	goto st0;
tr14:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
	goto st14;
st14:
	if ( ++p == pe )
		goto _test_eof14;
case 14:
#line 656 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 104: goto tr71;
		case 121: goto tr72;
	}
	goto st0;
tr15:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
	goto st15;
st15:
	if ( ++p == pe )
		goto _test_eof15;
case 15:
#line 673 "src/isledict_parse.cc"
	if ( (*p) == 104 )
		goto tr73;
	goto st0;
tr19:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 71 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kN);  }
	goto st16;
tr54:
#line 71 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kN);  }
	goto st16;
st16:
	if ( ++p == pe )
		goto _test_eof16;
case 16:
#line 694 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 9: goto st9;
		case 32: goto st9;
		case 46: goto st23;
		case 48: goto tr38;
		case 49: goto tr39;
		case 50: goto tr40;
		case 97: goto st7;
		case 98: goto tr42;
		case 99: goto st10;
		case 100: goto tr44;
		case 101: goto st12;
		case 102: goto tr46;
		case 103: goto tr74;
		case 104: goto st17;
		case 105: goto st14;
		case 106: goto st15;
		case 107: goto tr51;
		case 108: goto tr52;
		case 109: goto tr53;
		case 110: goto tr54;
		case 111: goto st18;
		case 112: goto tr56;
		case 114: goto tr57;
		case 115: goto tr58;
		case 116: goto tr59;
		case 117: goto st21;
		case 118: goto tr61;
		case 119: goto tr62;
		case 121: goto tr63;
		case 122: goto tr64;
	}
	goto st0;
tr13:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
	goto st17;
st17:
	if ( ++p == pe )
		goto _test_eof17;
case 17:
#line 739 "src/isledict_parse.cc"
	if ( (*p) == 104 )
		goto tr75;
	goto st0;
tr20:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
	goto st18;
st18:
	if ( ++p == pe )
		goto _test_eof18;
case 18:
#line 754 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 119: goto tr76;
		case 121: goto tr77;
	}
	goto st0;
tr23:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 75 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kS);  }
	goto st19;
tr58:
#line 75 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kS);  }
	goto st19;
st19:
	if ( ++p == pe )
		goto _test_eof19;
case 19:
#line 777 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 9: goto st9;
		case 32: goto st9;
		case 46: goto st23;
		case 48: goto tr38;
		case 49: goto tr39;
		case 50: goto tr40;
		case 97: goto st7;
		case 98: goto tr42;
		case 99: goto st10;
		case 100: goto tr44;
		case 101: goto st12;
		case 102: goto tr46;
		case 103: goto tr47;
		case 104: goto tr78;
		case 105: goto st14;
		case 106: goto st15;
		case 107: goto tr51;
		case 108: goto tr52;
		case 109: goto tr53;
		case 110: goto tr54;
		case 111: goto st18;
		case 112: goto tr56;
		case 114: goto tr57;
		case 115: goto tr58;
		case 116: goto tr59;
		case 117: goto st21;
		case 118: goto tr61;
		case 119: goto tr62;
		case 121: goto tr63;
		case 122: goto tr64;
	}
	goto st0;
tr24:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 77 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kT);  }
	goto st20;
tr59:
#line 77 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kT);  }
	goto st20;
st20:
	if ( ++p == pe )
		goto _test_eof20;
case 20:
#line 828 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 9: goto st9;
		case 32: goto st9;
		case 46: goto st23;
		case 48: goto tr38;
		case 49: goto tr39;
		case 50: goto tr40;
		case 97: goto st7;
		case 98: goto tr42;
		case 99: goto st10;
		case 100: goto tr44;
		case 101: goto st12;
		case 102: goto tr46;
		case 103: goto tr47;
		case 104: goto tr79;
		case 105: goto st14;
		case 106: goto st15;
		case 107: goto tr51;
		case 108: goto tr52;
		case 109: goto tr53;
		case 110: goto tr54;
		case 111: goto st18;
		case 112: goto tr56;
		case 114: goto tr57;
		case 115: goto tr58;
		case 116: goto tr59;
		case 117: goto st21;
		case 118: goto tr61;
		case 119: goto tr62;
		case 121: goto tr63;
		case 122: goto tr64;
	}
	goto st0;
tr25:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
	goto st21;
st21:
	if ( ++p == pe )
		goto _test_eof21;
case 21:
#line 873 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 104: goto tr80;
		case 119: goto tr81;
	}
	goto st0;
tr29:
#line 36 "src/isledict_parse.rl"
	{
      res->emplace_back();
      syllable = &res->back();
    }
#line 82 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kZ);  }
	goto st22;
tr64:
#line 82 "src/isledict_parse.rl"
	{ syllable->phonemes.push_back(kZ);  }
	goto st22;
st22:
	if ( ++p == pe )
		goto _test_eof22;
case 22:
#line 896 "src/isledict_parse.cc"
	switch( (*p) ) {
		case 9: goto st9;
		case 32: goto st9;
		case 46: goto st23;
		case 48: goto tr38;
		case 49: goto tr39;
		case 50: goto tr40;
		case 97: goto st7;
		case 98: goto tr42;
		case 99: goto st10;
		case 100: goto tr44;
		case 101: goto st12;
		case 102: goto tr46;
		case 103: goto tr47;
		case 104: goto tr82;
		case 105: goto st14;
		case 106: goto st15;
		case 107: goto tr51;
		case 108: goto tr52;
		case 109: goto tr53;
		case 110: goto tr54;
		case 111: goto st18;
		case 112: goto tr56;
		case 114: goto tr57;
		case 115: goto tr58;
		case 116: goto tr59;
		case 117: goto st21;
		case 118: goto tr61;
		case 119: goto tr62;
		case 121: goto tr63;
		case 122: goto tr64;
	}
	goto st0;
	}
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof23: cs = 23; goto _test_eof; 
	_test_eof10: cs = 10; goto _test_eof; 
	_test_eof11: cs = 11; goto _test_eof; 
	_test_eof12: cs = 12; goto _test_eof; 
	_test_eof13: cs = 13; goto _test_eof; 
	_test_eof14: cs = 14; goto _test_eof; 
	_test_eof15: cs = 15; goto _test_eof; 
	_test_eof16: cs = 16; goto _test_eof; 
	_test_eof17: cs = 17; goto _test_eof; 
	_test_eof18: cs = 18; goto _test_eof; 
	_test_eof19: cs = 19; goto _test_eof; 
	_test_eof20: cs = 20; goto _test_eof; 
	_test_eof21: cs = 21; goto _test_eof; 
	_test_eof22: cs = 22; goto _test_eof; 

	_test_eof: {}
	_out: {}
	}

#line 99 "src/isledict_parse.rl"


  return (cs != isledict_error);
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
