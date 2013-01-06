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
#include "poemy/memoryfile.h"
#include "poemy/util.h"
#include "poemy/pronounce.h"

DEFINE_int32(lines, 30, "How many lines of poetry to generate.");
DEFINE_int32(tries, 5, "How many times to crawl node before quitting.");
DEFINE_string(corpora, "goth", "Comma-separated list of corpora to load.");
DEFINE_string(corpora_path, "./corpora", "Path of corpus folders.");
DEFINE_string(dict, "isle", "Which pronunciation dictionary to use? This can "
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

typedef google::dense_hash_set<int> Set;
typedef google::dense_hash_set<
  pair<int, int>, poemy::MurmurHash3<pair<int, int> > > VisitedSet;

struct Word {
  Word(int word, const Pronounce* pronounce)
      : word(word), pronounce(pronounce) {}
  int word;
  const Pronounce* pronounce;
};

static Set g_bad_end_words;
static Set g_bad_start_words;
static poemy::Markov g_chain;
static poemy::Dict* g_dict;
static int g_count_MakeWord = 0;
static int g_count_MakeLine = 0;

bool MakeWord(int word1,
              int word2,
              size_t pos,
              const Meter& meter,
              const Word* rhyme,
              VisitedSet* visited,
              vector<Word>* words) {
  ++g_count_MakeWord;
  if (pos == meter.size()) {
    if (g_bad_end_words.find(word2) != g_bad_end_words.end()) {
      return false;
    }
    if (rhyme != nullptr) {
      const Word* last_word = &words->back();
      if (rhyme->word == last_word->word) {
        return false;
      }
      if (!poemy::IsRhyme(*rhyme->pronounce, *last_word->pronounce)) {
        return false;
      }
    }
    return true;
  }
  for (int word3 : g_chain.Picks({word1, word2})) {
    if (visited->find({word2, word3}) != visited->end()) {
      continue;
    }
    visited->insert({word2, word3});
    const Pronounces& prons = (*g_dict)[word3];
    if (prons.empty()) {
      continue;
    }
    const Pronounce* pronounce = poemy::MatchMeter(prons, meter, pos);
    if (!pronounce) {
      continue;
    }
    words->emplace_back(word3, pronounce);
    pos += pronounce->size();
    if (MakeWord(word2, word3, pos, meter, rhyme, visited, words)) {
      return true;
    }
    pos -= words->back().pronounce->size();
    words->pop_back();
  }
  return false;
}

bool MakeLine(const Meter& meter, const Word* rhyme, vector<Word>* words) {
  ++g_count_MakeLine;
  VisitedSet visited;
  visited.set_empty_key({-1, -1});
  for (int tries = 0; tries < FLAGS_tries; ++tries) {
    words->clear();
    visited.clear();
    size_t pos = 0;
    const Pronounce* pronounce1;
    const Pronounce* pronounce2;
    pair<int, int> first_words = g_chain.PickFirst();
    int word1 = first_words.first;
    int word2 = first_words.second;
    if (g_bad_start_words.find(word1) != g_bad_start_words.end()) {
      continue;
    }
    visited.insert({word1, word2});
    pronounce1 = poemy::MatchMeter((*g_dict)[word1], meter, pos);
    if (!pronounce1) {
      continue;
    }
    pos += pronounce1->size();
    pronounce2 = poemy::MatchMeter((*g_dict)[word2], meter, pos);
    if (!pronounce2) {
      continue;
    }
    pos += pronounce2->size();
    words->emplace_back(word1, pronounce1);
    words->emplace_back(word2, pronounce2);
    if (MakeWord(word1, word2, pos, meter, rhyme, &visited, words)) {
      return true;
    }
  }
  return false;
}

void LoadWords(Set* out, const string& path) {
  std::ifstream input(path);
  PCHECK(input.good()) << path;
  out->set_empty_key(-1);
  string word;
  while (std::getline(input, word, '\n')) {
    if (!word.empty()) {
      int code = g_dict->Code(word);
      if (code != -1) {
        out->insert(code);
      }
    }
  }
}

int main(int argc, char** argv) {
  google::SetUsageMessage(PACKAGE_NAME " [FLAGS]");
  google::SetVersionString(VERSION);
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();

  if (FLAGS_dict == "isle") {
    g_dict = new poemy::Isledict();
    g_dict->Load(new std::ifstream(FLAGS_isledict_path));
  } else if (FLAGS_dict == "cmu") {
    g_dict = new poemy::Cmudict();
    g_dict->Load(new std::ifstream(FLAGS_cmudict_path));
  } else {
    LOG(FATAL) << "Invalid word dict: " << FLAGS_dict;
  }
  std::unique_ptr<poemy::Dict> free_dict(g_dict);

  LoadWords(&g_bad_end_words, FLAGS_bad_end_words);
  LoadWords(&g_bad_start_words, FLAGS_bad_start_words);

  for (const auto& corpus : poemy::util::Split(FLAGS_corpora, ',')) {
    string corpus_path(FLAGS_corpora_path + "/" + corpus);
    for (const auto& entry : poemy::util::ListDir(corpus_path)) {
      string path(FLAGS_corpora_path + "/" + corpus + "/" + entry);
      LOG(INFO) << "loading: " << path;
      g_chain.Load(g_dict, new poemy::Corpus(new std::ifstream(path)));
    }
  }
  g_chain.LoadDone();

  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  auto begin = high_resolution_clock::now();

  poemy::util::CpuProfilerStart();
  const Meter meter = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
  int lines = 0;
  while (lines < FLAGS_lines) {
    vector<Word> line1;
    vector<Word> line2;
    if (!MakeLine(meter, nullptr, &line1) ||
        !MakeLine(meter, &line1.back(), &line2)) {
      continue;
    }
    for (const Word& word : line1) {
      cout << g_dict->Word(word.word) << " ";
    }
    cout << endl;
    for (const Word& word : line2) {
      cout << g_dict->Word(word.word) << " ";
    }
    cout << endl;
    lines += 2;
  }
  poemy::util::CpuProfilerStop();

  auto end = high_resolution_clock::now();
  auto elapsed = duration_cast<std::chrono::milliseconds>(end - begin);
  auto lps = lines / (elapsed.count() / 1000.0);
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
