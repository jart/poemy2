// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <sparsehash/dense_hash_set>

#include "poemy/cmudict.h"
#include "poemy/corpus.h"
#include "poemy/hash.h"
#include "poemy/isledict.h"
#include "poemy/markov.h"
#include "poemy/memoryfile.h"
#include "poemy/unique.h"
#include "poemy/util.h"
#include "poemy/pronounce.h"

DEFINE_int32(lines, 30, "How many lines of poetry to generate.");
DEFINE_int32(tries, 5, "How many times to crawl a node before trying next.");
DEFINE_string(foot, "iambic", "Which type of foot do you want to use for your "
              "poetry meter? Can be: iambic (01), trochaic (10), "
              "anapestic (001), dactylic (100), or amphibrachic (010).");
DEFINE_string(length, "pentameter", "How many feet per line? This can be an "
              "integer or one of the following traditional names: "
              "monometer (1), dimeter (2), trimeter (3), tetrameter (4), "
              "pentameter (5), hexameter (6), heptameter (7), or "
              "octameter (8)");
DEFINE_string(corpora, "goth", "Comma-separated list of corpora to load.");
DEFINE_string(corpora_path, "./corpora", "Path where corpus folders live.");
DEFINE_string(dict, "isle", "Which pronunciation dictionary to use? This can "
              "be 'isle' or 'cmu'");
DEFINE_string(isledict_path, "./data/isledict/isledict0.2.txt",
              "Path of isledict.txt database file.");
DEFINE_string(cmudict_path, "./data/cmudict.txt",
              "Path of cmudict.txt database file.");
DEFINE_string(bad_end_words, "./data/bad_end_words.txt",
              "Path of new-line delimited bad end words file.");
DEFINE_string(bad_start_words, "./data/bad_start_words.txt",
              "Path of new-line delimited bad start words file.");

using poemy::Dict;
using poemy::Meter;
using poemy::Pronounce;
using poemy::Pronounces;
using poemy::Syllable;
using poemy::new_unique;
using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

typedef google::dense_hash_set<int, poemy::MurmurHash3<int> > Set;
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
static std::unique_ptr<Dict> g_dict;
static int g_count_MakeWord = 0;
static int g_count_MakeLine = 0;
static std::mt19937 g_random(
    std::chrono::system_clock::now().time_since_epoch().count());

bool MakeLine(int word1,
              int word2,
              size_t syllables,
              const Meter& meter,
              const Word* rhyme,
              VisitedSet* visited,
              vector<Word>* words) {
  if (syllables == 0) {
    ++g_count_MakeLine;
  } else {
    ++g_count_MakeWord;
  }
  if (syllables == meter.size()) {
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
  const auto& picks = g_chain.Picks({word1, word2});
  std::uniform_int_distribution<size_t> distrib(0, picks.size() - 1);
  size_t tries = std::min(static_cast<size_t>(FLAGS_tries), picks.size());
  for (size_t n = 0; n < tries; ++n) {
    int word3 = picks[distrib(g_random)];
    if (word3 == Dict::kSentinel) {
      return false;
    }
    if (visited->find({word2, word3}) != visited->end()) {
      continue;
    }
    visited->insert({word2, word3});
    const Pronounces& prons = g_dict->Speak(word3);
    if (prons.empty()) {
      continue;
    }
    const Pronounce* pronounce = poemy::MatchMeter(prons, meter, syllables);
    if (!pronounce) {
      continue;
    }
    words->emplace_back(word3, pronounce);
    syllables += pronounce->size();
    if (MakeLine(word2, word3, syllables, meter, rhyme, visited, words)) {
      return true;
    }
    syllables -= words->back().pronounce->size();
    words->pop_back();
  }
  return false;
}

void LoadWords(Set* out, const string& path) {
  std::ifstream input(path);
  PCHECK(input.good()) << path;
  out->set_empty_key(Dict::kMissing);
  string word;
  while (std::getline(input, word, '\n')) {
    if (!word.empty()) {
      int code = g_dict->Code(word);
      if (code != Dict::kMissing) {
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
    g_dict = new_unique<poemy::Isledict>();
    g_dict->Load(new_unique<std::ifstream>(FLAGS_isledict_path));
  } else if (FLAGS_dict == "cmu") {
    g_dict = new_unique<poemy::Cmudict>();
    g_dict->Load(new_unique<std::ifstream>(FLAGS_cmudict_path));
  } else {
    LOG(FATAL) << "Invalid word dict: " << FLAGS_dict;
  }

  LoadWords(&g_bad_end_words, FLAGS_bad_end_words);
  LoadWords(&g_bad_start_words, FLAGS_bad_start_words);

  for (const auto& corpus : poemy::util::Split(FLAGS_corpora, ',')) {
    string corpus_path(FLAGS_corpora_path + "/" + corpus);
    for (const auto& entry : poemy::util::ListDir(corpus_path)) {
      string path(FLAGS_corpora_path + "/" + corpus + "/" + entry);
      LOG(INFO) << "loading: " << path;
      g_chain.Load(g_dict.get(),
                   new_unique<poemy::Corpus>(
                       new_unique<std::ifstream>(path)));
    }
  }

  auto begin = std::chrono::high_resolution_clock::now();

  // poemy::util::CpuProfilerStart();
  const Meter meter = poemy::MakeMeter(FLAGS_foot, FLAGS_length);
  int lines = 0;
  while (lines < FLAGS_lines) {
    vector<Word> line1;
    vector<Word> line2;
    VisitedSet visited;
    visited.set_empty_key({Dict::kMissing, Dict::kMissing});
    const auto sen = Dict::kSentinel;
    if (!MakeLine(sen, sen, 0, meter, nullptr,       &visited, &line1) ||
        !MakeLine(sen, sen, 0, meter, &line1.back(), &visited, &line2)) {
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
  // poemy::util::CpuProfilerStop();

  auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::high_resolution_clock::now() - begin);
  auto lps = lines / (elapsed_ms.count() / 1000.0);
  LOG(INFO) << "g_count_MakeLine: " << g_count_MakeLine;
  LOG(INFO) << "g_count_MakeWord: " << g_count_MakeWord;
  LOG(INFO) << "lines per second " << lps;

  // CHECK(system("pmap -x $(pidof poemy) | tail -n1 | awk '{print $4}'") == 0);

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
