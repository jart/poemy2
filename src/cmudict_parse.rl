// -*- C++ -*-
// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

// This parser also implements a very crappy syllabification algorithm.

#include "poemy/cmudict.h"
#include <glog/logging.h>

using std::string;

namespace poemy {

%%{
  machine cmudict;
  write data;
}%%

bool Cmudict::Parse(const string& line, string* word, Pronounce *res) const {
  int cs;
  const char* f = &line.front();
  const char* p = f;
  const char* pe = p + line.size();
  const char* eof = pe;
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

  %%{
    machine cmudict;

    action word_append {
      *word += *p;
    }
    action word_append_lower {
      *word += *p + ('a' - 'A');
    }
    action phoneme_add_consonant {
      syllable->phonemes.push_back(phoneme);
    }
    action phoneme_add_vowel {
      if (found_vowel) {
        res->emplace_back();
        syllable = &res->back();
      }
      syllable->phonemes.push_back(phoneme);
      found_vowel = true;
    }

    phoneme = "AA" @{ phoneme = kAA; } @phoneme_add_vowel
            | "AE" @{ phoneme = kAE; } @phoneme_add_vowel
            | "AH" @{ phoneme = kAH; } @phoneme_add_vowel
            | "AO" @{ phoneme = kAO; } @phoneme_add_vowel
            | "AW" @{ phoneme = kAW; } @phoneme_add_vowel
            | "AY" @{ phoneme = kAY; } @phoneme_add_vowel
            | "EH" @{ phoneme = kEH; } @phoneme_add_vowel
            | "ER" @{ phoneme = kER; } @phoneme_add_vowel
            | "EY" @{ phoneme = kEY; } @phoneme_add_vowel
            | "IH" @{ phoneme = kIH; } @phoneme_add_vowel
            | "IY" @{ phoneme = kIY; } @phoneme_add_vowel
            | "OW" @{ phoneme = kOW; } @phoneme_add_vowel
            | "OY" @{ phoneme = kOY; } @phoneme_add_vowel
            | "UH" @{ phoneme = kUH; } @phoneme_add_vowel
            | "UW" @{ phoneme = kUW; } @phoneme_add_vowel
            | "B"  @{ phoneme = kB;  } @phoneme_add_consonant
            | "CH" @{ phoneme = kCH; } @phoneme_add_consonant
            | "D"  @{ phoneme = kD;  } @phoneme_add_consonant
            | "DH" @{ phoneme = kDH; } @phoneme_add_consonant
            | "F"  @{ phoneme = kF;  } @phoneme_add_consonant
            | "G"  @{ phoneme = kG;  } @phoneme_add_consonant
            | "HH" @{ phoneme = kHH; } @phoneme_add_consonant
            | "JH" @{ phoneme = kJH; } @phoneme_add_consonant
            | "K"  @{ phoneme = kK;  } @phoneme_add_consonant
            | "L"  @{ phoneme = kL;  } @phoneme_add_consonant
            | "M"  @{ phoneme = kM;  } @phoneme_add_consonant
            | "N"  @{ phoneme = kN;  } @phoneme_add_consonant
            | "NG" @{ phoneme = kNG; } @phoneme_add_consonant
            | "P"  @{ phoneme = kP;  } @phoneme_add_consonant
            | "R"  @{ phoneme = kR;  } @phoneme_add_consonant
            | "S"  @{ phoneme = kS;  } @phoneme_add_consonant
            | "SH" @{ phoneme = kSH; } @phoneme_add_consonant
            | "T"  @{ phoneme = kT;  } @phoneme_add_consonant
            | "TH" @{ phoneme = kTH; } @phoneme_add_consonant
            | "V"  @{ phoneme = kV;  } @phoneme_add_consonant
            | "W"  @{ phoneme = kW;  } @phoneme_add_consonant
            | "Y"  @{ phoneme = kY;  } @phoneme_add_consonant
            | "Z"  @{ phoneme = kZ;  } @phoneme_add_consonant
            | "ZH" @{ phoneme = kZH; } @phoneme_add_consonant ;

    stress = "0" @{ syllable->stress = 0; }
           | "1" @{ syllable->stress = 1; }
           | "2" @{ syllable->stress = 2; } ;

    word_char = ( upper $word_append_lower ) | ( ( "'" | "-" ) $word_append ) ;
    word      = word_char+ ( "(" digit ")" )? ;
    sound     = " " phoneme stress? ;
    pronounce = word " " sound+ ;

    main := pronounce ;
    write init;
    write exec;
  }%%

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
