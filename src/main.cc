// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <sparsehash/dense_hash_set>

#include "poemy/cmudict.h"
#include "poemy/corpus.h"
#include "poemy/error.h"
#include "poemy/hash.h"
#include "poemy/isledict.h"
#include "poemy/markov.h"
#include "poemy/util.h"
#include "poemy/pronounce.h"

DEFINE_int32(lines, 30, "How many lines of poetry to generate.");
DEFINE_int32(tries, 5, "How many times to crawl node before quitting.");
DEFINE_string(corpora, "goth", "Comma-separated list of corpora to load.");
DEFINE_string(corpora_path, "./corpora", "Path of corpus folders.");
DEFINE_string(dict, "cmu", "Which pronunciation dictionary to use? This can "
                  "either be 'isle' or 'cmu'");
DEFINE_string(isledict_path, "./data/isledict/isledict0.2.txt",
              "Path of isledict.txt database file.");
DEFINE_string(cmudict_path, "./data/cmudict.txt",
              "Path of cmudict.txt database file.");
DEFINE_string(bad_end_words, "./data/bad_end_words.txt",
              "Path of new-line delimited bad end words file.");
DEFINE_string(bad_start_words, "./data/bad_start_words.txt",
              "Path of new-line delimited bad start words file.");

using poemy::Error;
using poemy::Meter;
using poemy::Pronounce;
using poemy::Pronounces;
using poemy::Syllable;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

typedef google::dense_hash_set<string, poemy::MurmurHash3<string> > Set;

static Set g_bad_end_words;
static Set g_bad_start_words;
static poemy::Markov g_chain;
static poemy::Dict* g_dict;
static int g_count_MakeWord = 0;
static int g_count_MakeLine = 0;

void MakeWord(const string& word1,
              const string& word2,
              size_t pos,
              const Meter& meter,
              const string& rhyme,
              vector<pair<string, Pronounce> >& words,
              Set* visited,
              Error* err) {
  ++g_count_MakeWord;
  if (pos == meter.size()) {
    if (g_bad_end_words.find(word2) != g_bad_end_words.end()) {
      err->set_code(Error::kExhausted);
      return;
    }
    if (!rhyme.empty()) {
      const string& last_word = words.back().first;
      if (last_word == rhyme) {
        err->set_code(Error::kExhausted);
        return;
      }
      if (!IsRhyme((*g_dict)[last_word], (*g_dict)[rhyme])) {
        err->set_code(Error::kExhausted);
        return;
      }
    }
    return;
  }
  vector<string> lol = g_chain.Picks(word1, word2);
  for (const auto& w3 : lol) {
    string visited_key = word2 + '/' + w3;
    if (visited->find(visited_key) != visited->end()) {
      continue;
    }
    visited->insert(std::move(visited_key));
    const Pronounces& prons = (*g_dict)[w3];
    if (prons.empty()) {
      continue;
    }
    pair<string, Pronounce> p3;
    p3.first = w3;
    p3.second = MatchMeter(prons, meter, pos);
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
    pos -= words.back().second.size();
    words.pop_back();
  }
  err->set_code(Error::kExhausted);
}

vector<string>
MakeLine(const Meter& meter, const string& rhyme, Error* err) {
  ++g_count_MakeLine;
  for (int tries = 0; tries < FLAGS_tries; ++tries) {
    size_t pos = 0;
    Set visited;
    visited.set_empty_key("");
    vector<pair<string, Pronounce> > words;
    pair<string, Pronounce> p1, p2;
    g_chain.PickFirst(&p1.first, &p2.first);
    if (g_bad_start_words.find(p1.first) != g_bad_start_words.end()) {
      continue;
    }
    visited.insert(p1.first + "/" + p2.first);
    p1.second = MatchMeter((*g_dict)[p1.first], meter, pos);
    if (p1.second.empty()) {
      continue;
    }
    words.push_back(p1);
    pos += p1.second.size();
    p2.second = MatchMeter((*g_dict)[p2.first], meter, pos);
    if (p2.second.empty()) {
      continue;
    }
    words.push_back(p2);
    pos += p2.second.size();
    MakeWord(p1.first, p2.first, pos, meter, rhyme, words, &visited, err);
    if (err->Ok()) {
      vector<string> res;
      for (const auto& wp : words) {
        res.push_back(wp.first);
      }
      return res;
    }
    err->Reset();
  }
  err->set_code(Error::kExhausted);
  return {};
}

void LoadWords(Set* out, const string& path) {
  std::ifstream input(path);
  PCHECK(input.good()) << path;
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

  if (FLAGS_dict == "isle") {
    g_dict = new poemy::Isledict();
    g_dict->Load(new std::ifstream(FLAGS_isledict_path));
  } else if (FLAGS_dict == "cmu") {
    g_dict = new poemy::Cmudict();
    g_dict->Load(new std::ifstream(FLAGS_cmudict_path));
  } else {
    LOG(FATAL) << "Invalid dictionary: " << FLAGS_dict;
  }
  std::unique_ptr<poemy::Dict> free_dict(g_dict);

  for (const auto& corpus : poemy::util::Split(FLAGS_corpora, ',')) {
    string corpus_path(FLAGS_corpora_path + "/" + corpus);
    for (const auto& entry : poemy::util::ListDir(corpus_path)) {
      string path(FLAGS_corpora_path + "/" + corpus + "/" + entry);
      LOG(INFO) << "loading: " << path;
      g_chain.Load(new poemy::Corpus(new std::ifstream(path)));
    }
  }
  g_chain.LoadDone();

  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  auto begin = high_resolution_clock::now();

  const Meter meter = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
  int n = 0;
  while (n < FLAGS_lines) {
    Error err;
    vector<string> line1 = MakeLine(meter, "", &err);
    if (!err.Ok()) {
      continue;
    }
    err.Reset();
    const string& rhyme = line1[line1.size() - 1];
    vector<string> line2 = MakeLine(meter, rhyme, &err);
    if (!err.Ok()) {
      continue;
    }
    for (const auto& str : line1) cout << str << " "; cout << endl;
    for (const auto& str : line2) cout << str << " "; cout << endl;
    n += 2;
  }

  auto end = high_resolution_clock::now();
  auto elapsed = duration_cast<std::chrono::milliseconds>(end - begin);
  auto lps = FLAGS_lines / (elapsed.count() / 1000.0);
  LOG(INFO) << "g_count_MakeLine: " << g_count_MakeLine;
  LOG(INFO) << "g_count_MakeWord: " << g_count_MakeWord;
  LOG(INFO) << "lines per second " << lps;

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
