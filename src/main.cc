// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#include "poemy/poemy.h"
#include "poemy/error.h"
#include "poemy/isledict.h"
#include "poemy/markov.h"
#include "poemy/util.h"

DEFINE_int32(lines, 10, "How many lines of poetry to generate.");
DEFINE_int32(tries, 100000, "How many times to crawl node before quitting.");
DEFINE_string(corpora, "goth", "Comma-separated list of corpora to load.");
DEFINE_string(corpora_path, "./corpora", "Path of corpus folders.");
DEFINE_string(isledict_path, "./data/isledict/isledict0.2.txt",
              "Path of isledict database file.");

Markov g_chain;
Isledict g_dict;

void match_meter(const vector<vector<Syllable> >& prons,
                 const vector<int>& meter, size_t pos,
                 vector<Syllable>& res) {
  assert(pos < meter.size());
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

bool is_rhyme(const vector<vector<Syllable> >& prons1,
              const vector<vector<Syllable> >& prons2) {
  for (const auto& pron1 : prons1) {
    assert(pron1.size() > 0);
    for (const auto& pron2 : prons2) {
      assert(pron2.size() > 0);
      if (pron1[pron1.size() - 1].phonemes ==
          pron2[pron2.size() - 1].phonemes) {
        return true;
      }
    }
  }
  return false;
}

void mkword(const string& word1,
            const string& word2,
            size_t pos,
            const vector<int>& meter,
            const vector<vector<Syllable> >& rhyme,
            vector<std::pair<string, vector<Syllable> > >& words,
            dense_hash_set<string>& visited,
            Error* err) {
  if (pos == meter.size()) {
    if (rhyme.size()) {
      if (!is_rhyme(g_dict[words[words.size() - 1].first], rhyme)) {
        err->set_code(Error::kExhausted);
        return;
      }
    }
    return;
  }
  vector<string> fun = g_chain.Picks(word1, word2);
  for (const auto& w3 : fun) {
    const string visited_key(word2 + "/" + w3);
    if (visited.find(visited_key) != visited.end()) {
      continue;
    }
    visited.insert(visited_key);
    const vector<vector<Syllable> >& prons = g_dict[w3];
    if (prons.empty()) {
      continue;
    }
    std::pair<string, vector<Syllable> > p3;
    p3.first = w3;
    match_meter(prons, meter, pos, p3.second);
    if (p3.second.empty()) {
      continue;
    }
    words.push_back(p3);
    pos += p3.second.size();
    mkword(word2, p3.first, pos, meter, rhyme, words, visited, err);
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
mkline(const vector<int>& meter, const vector<vector<Syllable> >& rhyme,
       Error* err) {
  for (int tries = 0; tries < FLAGS_tries; ++tries) {
    size_t pos = 0;
    dense_hash_set<string> visited;
    visited.set_empty_key("");
    vector<std::pair<string, vector<Syllable> > > words;
    std::pair<string, vector<Syllable> > p1, p2;
    g_chain.PickFirst(&p1.first, &p2.first);
    visited.insert(p1.first + "/" + p2.first);
    match_meter(g_dict[p1.first], meter, pos, p1.second);
    if (p1.second.empty()) {
      continue;
    }
    words.push_back(p1);
    pos += p1.second.size();
    match_meter(g_dict[p2.first], meter, pos, p2.second);
    if (p2.second.empty()) {
      continue;
    }
    words.push_back(p2);
    pos += p2.second.size();
    mkword(p1.first, p2.first, pos, meter, rhyme, words, visited, err);
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

int main(int argc, char** argv) {
  google::SetUsageMessage(PACKAGE_NAME " [FLAGS]");
  google::SetVersionString(VERSION);
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();

  g_dict.Load(new std::ifstream(FLAGS_isledict_path));

  for (const auto& corpus : Split(FLAGS_corpora, ',')) {
    string corpus_path(FLAGS_corpora_path + "/" + corpus);
    for (const auto& entry : ListDir(corpus_path)) {
      string path(FLAGS_corpora_path + "/" + corpus + "/" + entry);
      LOG(INFO) << "loading: " << path;
      g_chain.Load(new Corpus(new std::ifstream(path)));
    }
  }
  g_chain.LoadDone();

  CpuProfilerStart();
  const vector<int> meter = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
  for (int n = 0; n < FLAGS_lines; ++n) {
    Error err;
    vector<vector<Syllable> > rhyme;
    vector<string> line = mkline(meter, rhyme, &err);
    if (!err.Ok()) {
      LOG(WARNING) << "mkline() #1 failed: " << err;
      continue;
    }
    for (const auto& str : line) cout << str << " "; cout << endl;
    rhyme = g_dict[line[line.size() - 1]];
    err.Reset();
    line = mkline(meter, rhyme, &err);
    if (!err.Ok()) {
      LOG(WARNING) << "mkline() #2 failed: " << err;
      continue;
    }
    for (const auto& str : line) cout << str << " "; cout << endl;
  }
  CpuProfilerStop();

  // line = mkline(meter, rhyme);
  // for (const auto& str : line) {
  //   cout << str << " ";
  // }
  // cout << endl;

  int rc = system("pmap -x $(pidof poemy) | tail -n1 | awk '{print $4}'");
  if (rc != 0) {
    exit(1);
  }

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
