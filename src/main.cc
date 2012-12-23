// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <sparsehash/dense_hash_set>

#include "poemy/error.h"
#include "poemy/isledict.h"
#include "poemy/markov.h"
#include "poemy/corpus.h"
#include "poemy/util.h"

DEFINE_int32(lines, 30, "How many lines of poetry to generate.");
DEFINE_int32(tries, 1000, "How many times to crawl node before quitting.");
DEFINE_string(corpora, "goth", "Comma-separated list of corpora to load.");
DEFINE_string(corpora_path, "./corpora", "Path of corpus folders.");
DEFINE_string(isledict, "./data/isledict/isledict0.2.txt",
              "Path of isledict database file.");
DEFINE_string(bad_end_words, "./data/bad_end_words.txt",
              "Path of new-line delimited bad end words file.");
DEFINE_string(bad_start_words, "./data/bad_start_words.txt",
              "Path of new-line delimited bad start words file.");

using poemy::Error;
using poemy::Syllable;
using std::cout;
using std::endl;
using std::string;
using std::vector;

static google::dense_hash_set<string> g_bad_end_words;
static google::dense_hash_set<string> g_bad_start_words;
static poemy::Markov g_chain;
static poemy::Isledict g_dict;

void MatchMeter(const vector<vector<Syllable> >& prons,
                const vector<int>& meter, size_t pos,
                vector<Syllable>& res) {
  CHECK(pos < meter.size());
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
      res = pron;
      return;
    }
  }
  res.clear();
  return;
}

bool IsRhyme(const vector<vector<Syllable> >& prons1,
             const vector<vector<Syllable> >& prons2) {
  for (const auto& pron1 : prons1) {
    CHECK(pron1.size() > 0);
    for (const auto& pron2 : prons2) {
      CHECK(pron2.size() > 0);
      if (pron1[pron1.size() - 1].phonemes ==
          pron2[pron2.size() - 1].phonemes) {
        return true;
      }
    }
  }
  return false;
}

void MakeWord(const string& word1,
              const string& word2,
              size_t pos,
              const vector<int>& meter,
              const string& rhyme,
              vector<std::pair<string, vector<Syllable> > >& words,
              google::dense_hash_set<string>& visited,
              Error* err) {
  if (pos == meter.size()) {
    if (g_bad_end_words.find(word2) != g_bad_end_words.end()) {
      err->set_code(Error::kExhausted);
      return;
    }
    if (!rhyme.empty()) {
      const string& last_word = words[words.size() - 1].first;
      if (last_word == rhyme) {
        err->set_code(Error::kExhausted);
        return;
      }
      if (!IsRhyme(g_dict[last_word], g_dict[rhyme])) {
        err->set_code(Error::kExhausted);
        return;
      }
    }
    return;
  }
  for (const auto& w3 : g_chain.Picks(word1, word2)) {
    string visited_key = word2 + '/' + w3;
    if (visited.find(visited_key) != visited.end()) {
      continue;
    }
    visited.insert(std::move(visited_key));
    const vector<vector<Syllable> >& prons = g_dict[w3];
    if (prons.empty()) {
      continue;
    }
    std::pair<string, vector<Syllable> > p3;
    p3.first = w3;
    MatchMeter(prons, meter, pos, p3.second);
    if (p3.second.empty()) {
      continue;
    }
    words.push_back(p3);
    pos += p3.second.size();
    MakeWord(word2, p3.first, pos, meter, rhyme, words, visited, err);
    if (err->Ok()) {
      return;
    }
    err->Reset();
    pos -= words[words.size() - 1].second.size();
    words.pop_back();
  }
  err->set_code(Error::kExhausted);
}

vector<string>
MakeLine(const vector<int>& meter, const string& rhyme, Error* err) {
  for (int tries = 0; tries < FLAGS_tries; ++tries) {
    size_t pos = 0;
    google::dense_hash_set<string> visited;
    visited.set_empty_key("");
    vector<std::pair<string, vector<Syllable> > > words;
    std::pair<string, vector<Syllable> > p1, p2;
    g_chain.PickFirst(&p1.first, &p2.first);
    if (g_bad_start_words.find(p1.first) != g_bad_start_words.end()) {
      continue;
    }
    visited.insert(p1.first + "/" + p2.first);
    MatchMeter(g_dict[p1.first], meter, pos, p1.second);
    if (p1.second.empty()) {
      continue;
    }
    words.push_back(p1);
    pos += p1.second.size();
    MatchMeter(g_dict[p2.first], meter, pos, p2.second);
    if (p2.second.empty()) {
      continue;
    }
    words.push_back(p2);
    pos += p2.second.size();
    MakeWord(p1.first, p2.first, pos, meter, rhyme, words, visited, err);
    if (err->Ok()) {
      vector<string> res;
      for (const auto& pair : words) {
        res.push_back(pair.first);
      }
      return res;
    }
    err->Reset();
  }
  err->set_code(Error::kExhausted);
  return {};
}

void LoadWords(google::dense_hash_set<string>* out, const string& path) {
  std::ifstream input(path);
  CHECK(input.good()) << "Bad file: " << path;
  out->set_empty_key("");
  string word;
  while (std::getline(input, word, '\n')) {
    if (!word.empty()) {
      out->insert(word);
    }
  }
}

int main(int argc, char** argv) {
  google::SetUsageMessage(PACKAGE_NAME " [FLAGS]");
  google::SetVersionString(VERSION);
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();

  LoadWords(&g_bad_end_words, FLAGS_bad_end_words);
  LoadWords(&g_bad_start_words, FLAGS_bad_start_words);

  g_dict.Load(new std::ifstream(FLAGS_isledict));

  for (const auto& corpus : poemy::util::Split(FLAGS_corpora, ',')) {
    string corpus_path(FLAGS_corpora_path + "/" + corpus);
    for (const auto& entry : poemy::util::ListDir(corpus_path)) {
      string path(FLAGS_corpora_path + "/" + corpus + "/" + entry);
      LOG(INFO) << "loading: " << path;
      g_chain.Load(new poemy::Corpus(new std::ifstream(path)));
    }
  }
  g_chain.LoadDone();

  poemy::util::CpuProfilerStart();
  const vector<int> meter = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
  int n = 0;
  while (n < FLAGS_lines) {
    Error err;
    vector<string> line1 = MakeLine(meter, "", &err);
    if (!err.Ok()) {
      LOG(WARNING) << "MakeLine() #1 failed: " << err;
      continue;
    }
    err.Reset();
    const string& rhyme = line1[line1.size() - 1];
    vector<string> line2 = MakeLine(meter, rhyme, &err);
    if (!err.Ok()) {
      LOG(WARNING) << "MakeLine() #2 failed: " << err;
      continue;
    }
    for (const auto& str : line1) cout << str << " "; cout << endl;
    for (const auto& str : line2) cout << str << " "; cout << endl;
    n += 2;
  }
  poemy::util::CpuProfilerStop();

  // line = MakeLine(meter, rhyme);
  // for (const auto& str : line) {
  //   cout << str << " ";
  // }
  // cout << endl;

  CHECK(system("pmap -x $(pidof poemy) | tail -n1 | awk '{print $4}'") == 0);

  return 0;
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
