// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/poemy.h"
#include "poemy/isledict.h"

static Syllable parse_syllable(const string& prons, size_t& pos) {
  Syllable res;
  size_t begin = pos;
  while (pos < prons.length()) {
    switch (prons[pos]) {
      case '|':
      case  '.':
        if (pos > begin) {
          res.phonemes.push_back(prons.substr(begin, pos - begin));
        }
        ++pos;
        return res;
      case ' ':
        if (pos > begin) {
          res.phonemes.push_back(prons.substr(begin, pos - begin));
        }
        ++pos;
        begin = pos;
        break;
      case '0':
      case '1':
      case '2':
        res.stress = static_cast<int>(prons[pos] - '0');
        res.phonemes.push_back(prons.substr(begin, pos - begin));
        ++pos;
        begin = pos + 1;
        break;
      default:
        ++pos;
    }
  }
  assert(false);
}

static vector<Syllable> parse_pronounce(const string& prons, size_t& pos) {
  vector<Syllable> res;
  while (pos < prons.length()) {
    res.push_back(parse_syllable(prons, pos));
    if (prons[pos - 1] == '|') {
      return res;
    }
  }
  assert(false);
}

Isledict::Isledict() {
  pronounce_.set_empty_key("");
  pronounce_full_.set_empty_key("");
}

const vector<vector<Syllable> >&
Isledict::operator[](const string& word) {
  vector<vector<Syllable> >& res = pronounce_full_[word];
  if (res.size() == 0 && pronounce_.find(word) != pronounce_.end()) {
    const string& prons = pronounce_[word];
    size_t pos = 0;
    while (pos < prons.length()) {
      res.push_back(parse_pronounce(prons, pos));
    }
  }
  return res;
}

void Isledict::Print(const vector<Syllable>& pron) {
  for (const auto& syl : pron) {
    cout << syl.stress << ": ";
    for (const auto& lol : syl.phonemes) {
      cout << lol << " ";
    }
    cout << endl;
  }
}

void Isledict::Print(const vector<vector<Syllable> >& prons) {
  for (const auto& pron : prons) {
    cout << "----" << endl;
    for (const auto& syl : pron) {
      cout << syl.stress << ": ";
      for (auto lol : syl.phonemes) {
        cout << lol << " ";
      }
      cout << endl;
    }
  }
}

static bool extract_word(const string& line, string& word) {
  auto pos = line.find("(");
  if (pos == string::npos) {
    return false;
  }
  word = line.substr(0, pos);
  if (word.find("[") != string::npos) {
    return false;
  }
  return true;
}

void Isledict::Load(const string& path) {
  std::ifstream isledict(path);
  string line, word;
  while (std::getline(isledict, line).good()) {
    if (line.substr(0, 2) == "##") {
      continue;
    }
    if (!extract_word(line, word)) {
      continue;
    }

    // Extract the pronunciation without the " . " on each side.
    assert(line.substr(line.length() - 3, 3) == " . ");
    int start = line.find(" . ") + 3;
    assert(line.length() - start - 3 > 0);
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
