// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_PRONOUNCE_H_
#define POEMY_PRONOUNCE_H_

#include <ostream>
#include <string>
#include <vector>

namespace poemy {

enum Phoneme {
  kAA = 0,
  kAE = 1,
  kAH = 2,
  kAO = 3,
  kAW = 4,
  kAY = 5,
  kEH = 6,
  kER = 7,
  kEY = 8,
  kIH = 9,
  kIY = 10,
  kOW = 11,
  kOY = 12,
  kUH = 13,
  kUW = 14,
  kB  = 15,
  kCH = 16,
  kD  = 17,
  kDH = 18,
  kF  = 19,
  kG  = 20,
  kHH = 21,
  kJH = 22,
  kK  = 23,
  kL  = 24,
  kM  = 25,
  kN  = 26,
  kNG = 27,
  kP  = 28,
  kR  = 29,
  kS  = 30,
  kSH = 31,
  kT  = 32,
  kTH = 33,
  kV  = 34,
  kW  = 35,
  kY  = 36,
  kZ  = 37,
  kZH = 38,
};

struct Syllable {
  std::vector<Phoneme> phonemes;
  int stress;
  bool operator==(const Syllable& other) const {
    return (stress == other.stress && phonemes == other.phonemes);
  }
};

typedef std::vector<Syllable> Pronounce;
typedef std::vector<Pronounce> Pronounces;
typedef std::vector<int> Meter;

bool IsVowel(Phoneme phoneme);
bool IsRhyme(const Pronounces& prons1, const Pronounces& prons2);
const Pronounce* MatchMeter(const Pronounces& prons, const Meter& meter,
                            size_t pos);
std::string PhonemeString(Phoneme phoneme);
Phoneme ParsePhoneme(const std::string& str);

std::ostream& operator<<(std::ostream& os, const Phoneme& phoneme);
std::ostream& operator<<(std::ostream& os, const Syllable& syl);

}  // namespace poemy

#endif  // POEMY_PRONOUNCE_H_

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
