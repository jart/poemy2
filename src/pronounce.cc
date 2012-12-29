// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/pronounce.h"

#include <glog/logging.h>

namespace poemy {

bool IsVowel(Phoneme phoneme) {
  switch (phoneme) {
    case kAA:
    case kAE:
    case kAH:
    case kAO:
    case kAW:
    case kAY:
    case kEH:
    case kER:
    case kEY:
    case kIH:
    case kIY:
    case kOW:
    case kOY:
    case kUH:
    case kUW:
      return true;
    default:
      return false;
  }
}

bool IsRhyme(const Pronounces& prons1, const Pronounces& prons2) {
  for (const auto& pron1 : prons1) {
    for (const auto& pron2 : prons2) {
      const Syllable& syl1 = pron1.back();
      const Syllable& syl2 = pron2.back();
      int n1, len1 = syl1.phonemes.size();
      int n2, len2 = syl2.phonemes.size();
      // Skip over the initial consonant phonemes.
      for (n1 = 0; n1 < len1; n1++) {
        if (IsVowel(syl1.phonemes[n1])) {
          break;
        }
      }
      for (n2 = 0; n2 < len2; n2++) {
        if (IsVowel(syl2.phonemes[n2])) {
          break;
        }
      }
      // Now all the remaining phonemes must match.
      if (len1 - n1 == len2 - n2) {
        bool equal = true;
        for (; n1 < len1; n1++, n2++) {
          if (syl1.phonemes[n1] != syl2.phonemes[n2]) {
            equal = false;
            break;
          }
        }
        if (equal) {
          return true;
        }
      }
    }
  }
  return false;
}

const Pronounce* MatchMeter(const Pronounces& prons, const Meter& meter,
                            size_t pos) {
  const size_t remain = meter.size() - pos;
  for (const auto& pron : prons) {
    if (pron.size() > remain) {
      continue;
    }
    bool success = true;
    for (size_t n = 0; n < pron.size(); ++n) {
      if (!(meter[pos + n] == pron[n].stress ||
            (meter[pos + n] != 0 && pron[n].stress != 0))) {
        success = false;
        break;
      }
    }
    if (success) {
      return &pron;
    }
  }
  return nullptr;
}

std::string PhonemeString(Phoneme phoneme) {
  switch (phoneme) {
    case kAA: return "AA";
    case kAE: return "AE";
    case kAH: return "AH";
    case kAO: return "AO";
    case kAW: return "AW";
    case kAY: return "AY";
    case kEH: return "EH";
    case kER: return "ER";
    case kEY: return "EY";
    case kIH: return "IH";
    case kIY: return "IY";
    case kOW: return "OW";
    case kOY: return "OY";
    case kUH: return "UH";
    case kUW: return "UW";
    case kB:  return "B";
    case kCH: return "CH";
    case kD:  return "D";
    case kDH: return "DH";
    case kF:  return "F";
    case kG:  return "G";
    case kHH: return "HH";
    case kJH: return "JH";
    case kK:  return "K";
    case kL:  return "L";
    case kM:  return "M";
    case kN:  return "N";
    case kNG: return "NG";
    case kP:  return "P";
    case kR:  return "R";
    case kS:  return "S";
    case kSH: return "SH";
    case kT:  return "T";
    case kTH: return "TH";
    case kV:  return "V";
    case kW:  return "W";
    case kY:  return "Y";
    case kZ:  return "Z";
    case kZH: return "ZH";
    default:
      CHECK(false) << "Bad phoneme code: " << static_cast<int>(phoneme);
  }
}

// Pointlessly "optimized" for fun.
Phoneme ParsePhoneme(const std::string& str) {
  switch (str.size()) {
    case 1:
      switch (str[0]) {
        case 'B': case 'b': return kB;
        case 'D': case 'd': return kD;
        case 'F': case 'f': return kF;
        case 'G': case 'g': return kG;
        case 'K': case 'k': return kK;
        case 'L': case 'l': return kL;
        case 'M': case 'm': return kM;
        case 'N': case 'n': return kN;
        case 'P': case 'p': return kP;
        case 'R': case 'r': return kR;
        case 'S': case 's': return kS;
        case 'T': case 't': return kT;
        case 'V': case 'v': return kV;
        case 'W': case 'w': return kW;
        case 'Y': case 'y': return kY;
        case 'Z': case 'z': return kZ;
        default: CHECK(false) << "Bad phoneme: " << str;
      }
    case 2:
      switch (str[0]) {
        case 'A': case 'a':
          switch (str[1]) {
            case 'A': case 'a': return kAA;
            case 'E': case 'e': return kAE;
            case 'H': case 'h': return kAH;
            case 'O': case 'o': return kAO;
            case 'W': case 'w': return kAW;
            case 'Y': case 'y': return kAY;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'C': case 'c':
          switch (str[1]) {
            case 'H': case 'h': return kCH;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'D': case 'd':
          switch (str[1]) {
            case 'H': case 'h': return kDH;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'E': case 'e':
          switch (str[1]) {
            case 'H': case 'h': return kEH;
            case 'R': case 'r': return kER;
            case 'Y': case 'y': return kEY;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'H': case 'h':
          switch (str[1]) {
            case 'H': case 'h': return kHH;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'I': case 'i':
          switch (str[1]) {
            case 'H': case 'h': return kIH;
            case 'Y': case 'y': return kIY;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'J': case 'j':
          switch (str[1]) {
            case 'H': case 'h': return kJH;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'N': case 'n':
          switch (str[1]) {
            case 'G': case 'g': return kNG;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'O': case 'o':
          switch (str[1]) {
            case 'W': case 'w': return kOW;
            case 'Y': case 'y': return kOY;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'S': case 's':
          switch (str[1]) {
            case 'H': case 'h': return kSH;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'T': case 't':
          switch (str[1]) {
            case 'H': case 'h': return kTH;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'U': case 'u':
          switch (str[1]) {
            case 'H': case 'h': return kUH;
            case 'W': case 'w': return kUW;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        case 'Z': case 'z':
          switch (str[1]) {
            case 'H': case 'h': return kZH;
            default: CHECK(false) << "Bad phoneme: " << str;
          }
        default:
          CHECK(false) << "Bad phoneme: " << str;
      }
    default:
      CHECK(false) << "Bad phoneme: " << str;
  }
  CHECK(false);
  return kAA;  // Make the compiler happy.
}

std::ostream& operator<<(std::ostream& os, const Phoneme& phoneme) {
  if (phoneme >= kAA && phoneme <= kZH) {
    return os << PhonemeString(phoneme);
  } else {
    return os << "??";
  }
}

std::ostream& operator<<(std::ostream& os, const Syllable& syl) {
  bool first = true;
  os << syl.stress << " ";
  for (const auto& phoneme : syl.phonemes) {
    if (first) {
      first = false;
    } else {
      os << " ";
    }
    os << phoneme;
  }
  return os;
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
