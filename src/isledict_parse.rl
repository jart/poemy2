// -*- C++ -*-
// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/isledict.h"
#include <glog/logging.h>

using std::string;

namespace poemy {

%%{
  machine isledict;
  write data;
}%%

bool Isledict::Parse(const string& line, string* word, Pronounce *res) const {
  int cs;
  const char* f = &line.front();
  const char* p = f;
  const char* pe = p + line.size();
  Syllable* syllable;

  if (p == pe) {
    return false;
  }
  word->clear();
  res->clear();

  %%{
    machine isledict;

    action word_append {
      *word += *p;
    }
    action syllable_new {
      res->emplace_back();
      syllable = &res->back();
    }

    word_char = lower | "'" | "-" ;
    info_char = any -- ")" ;
    ts        = " " | "\t";

    phoneme = "aa" @{ syllable->phonemes.push_back(kAA); }
            | "ae" @{ syllable->phonemes.push_back(kAE); }
            | "ah" @{ syllable->phonemes.push_back(kAH); }
            | "ao" @{ syllable->phonemes.push_back(kAO); }
            | "aw" @{ syllable->phonemes.push_back(kAW); }
            | "ay" @{ syllable->phonemes.push_back(kAY); }
            | "eh" @{ syllable->phonemes.push_back(kEH); }
            | "er" @{ syllable->phonemes.push_back(kER); }
            | "ey" @{ syllable->phonemes.push_back(kEY); }
            | "ih" @{ syllable->phonemes.push_back(kIH); }
            | "iy" @{ syllable->phonemes.push_back(kIY); }
            | "ow" @{ syllable->phonemes.push_back(kOW); }
            | "oy" @{ syllable->phonemes.push_back(kOY); }
            | "uh" @{ syllable->phonemes.push_back(kUH); }
            | "uw" @{ syllable->phonemes.push_back(kUW); }
            | "b"  @{ syllable->phonemes.push_back(kB);  }
            | "ch" @{ syllable->phonemes.push_back(kCH); }
            | "d"  @{ syllable->phonemes.push_back(kD);  }
            | "dh" @{ syllable->phonemes.push_back(kDH); }
            | "f"  @{ syllable->phonemes.push_back(kF);  }
            | "g"  @{ syllable->phonemes.push_back(kG);  }
            | "hh" @{ syllable->phonemes.push_back(kHH); }
            | "jh" @{ syllable->phonemes.push_back(kJH); }
            | "k"  @{ syllable->phonemes.push_back(kK);  }
            | "l"  @{ syllable->phonemes.push_back(kL);  }
            | "m"  @{ syllable->phonemes.push_back(kM);  }
            | "n"  @{ syllable->phonemes.push_back(kN);  }
            | "ng" @{ syllable->phonemes.push_back(kNG); }
            | "p"  @{ syllable->phonemes.push_back(kP);  }
            | "r"  @{ syllable->phonemes.push_back(kR);  }
            | "s"  @{ syllable->phonemes.push_back(kS);  }
            | "sh" @{ syllable->phonemes.push_back(kSH); }
            | "t"  @{ syllable->phonemes.push_back(kT);  }
            | "th" @{ syllable->phonemes.push_back(kTH); }
            | "v"  @{ syllable->phonemes.push_back(kV);  }
            | "w"  @{ syllable->phonemes.push_back(kW);  }
            | "y"  @{ syllable->phonemes.push_back(kY);  }
            | "z"  @{ syllable->phonemes.push_back(kZ);  }
            | "zh" @{ syllable->phonemes.push_back(kZH); } ;

    stress = "0" @{ syllable->stress = 0; }
           | "1" @{ syllable->stress = 1; }
           | "2" @{ syllable->stress = 2; } ;

    word      = ( word_char+ ) $word_append;
    info      = "(" info_char* ")" ;
    boundary  = ts* "." ts* ;
    silly     = phoneme stress? ts* ;
    syllable  = ( silly+ boundary ) >syllable_new ;
    pronounce = word info+ boundary syllable+ ;

    main := pronounce ;
    write init;
    write exec;
  }%%

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
