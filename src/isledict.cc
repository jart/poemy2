// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/isledict.h"

#include <memory>

#include <glog/logging.h>

using std::string;

namespace poemy {

Isledict::Isledict() {
  pronounce_.set_empty_key("");
  pronounce_full_.set_empty_key("");
}

const Pronounces& Isledict::operator[](const string& word) {
  Pronounces& res = pronounce_full_[word];
  if (res.empty() && pronounce_.find(word) != pronounce_.end()) {
    const string& prons = pronounce_[word];
    size_t pos = 0;
    while (pos < prons.length()) {
      res.push_back(ParsePronounce(prons, pos));
    }
  }
  return res;
}

void Isledict::Load(std::istream* input) {
  std::unique_ptr<std::istream> free_input(input);
  PCHECK(input->good());
  string line, word;
  while (std::getline(*input, line).good()) {
    if (line.substr(0, 2) == "##") {
      continue;
    }
    if (!ExtractWord(line, &word)) {
      continue;
    }

    // Extract the pronunciation without the " . " on each side.
    CHECK(line.substr(line.length() - 3, 3) == " . ");
    int start = line.find(" . ") + 3;
    CHECK(line.length() - start - 3 > 0);
    string pron = line.substr(start, line.length() - start - 3);

    // Add pron to stringlist of possible pronunciations while also trimming
    // spaces off syllable boundaries.
    string& prons = pronounce_[word];
    size_t i = 0;
    while (i < pron.length() - 1) {
      if (pron[i + 1] == '.') {
        prons += '.';
        i += 3;
      } else {
        prons += pron[i++];
      }
    }
    prons += pron[pron.length() - 1];
    prons += '|';
    prons.shrink_to_fit();
  }
}

bool Isledict::ExtractWord(const string& line, string* word) {
  auto pos = line.find("(");
  if (pos == string::npos) {
    return false;
  }
  *word = line.substr(0, pos);
  if (word->find("[") != string::npos) {
    return false;
  }
  return true;
}

Syllable Isledict::ParseSyllable(const string& prons, size_t& pos) {
  Syllable res;
  size_t begin = pos;
  while (pos < prons.length()) {
    switch (prons[pos]) {
      case '|':
      case  '.':
        if (pos > begin) {
          res.phonemes.push_back(
            ParsePhoneme(prons.substr(begin, pos - begin)));
        }
        ++pos;
        return res;
      case ' ':
        if (pos > begin) {
          res.phonemes.push_back(
            ParsePhoneme(prons.substr(begin, pos - begin)));
        }
        ++pos;
        begin = pos;
        break;
      case '0':
      case '1':
      case '2':
        res.stress = static_cast<int>(prons[pos] - '0');
        res.phonemes.push_back(
          ParsePhoneme(prons.substr(begin, pos - begin)));
        ++pos;
        begin = pos + 1;
        break;
      default:
        ++pos;
    }
  }
  CHECK(false);
}

Pronounce Isledict::ParsePronounce(const string& prons, size_t& pos) {
  Pronounce res;
  while (pos < prons.length()) {
    res.push_back(ParseSyllable(prons, pos));
    if (prons[pos - 1] == '|') {
      return res;
    }
  }
  CHECK(false);
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
