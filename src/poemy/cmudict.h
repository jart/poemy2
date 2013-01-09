// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_CMUDICT_H_
#define POEMY_CMUDICT_H_

#include <poemy/dict.h>
#include <vector>
#include <glog/logging.h>
#include <sparsehash/dense_hash_map>
#include <poemy/hash.h>

namespace poemy {

class Cmudict : public Dict {
 public:
  Cmudict();
  // I take ownership of 'input'.
  virtual void Load(std::istream* input);

  virtual const Pronounces& Speak(int code) const override {
    static const Pronounces empty;
    if (code == kMissing) {
      return empty;
    } else {
      CHECK(0 <= code && code < pronounce_.size());
      return pronounce_[code];
    }
  }

  virtual const std::string& Word(int code) const override {
    CHECK(0 <= code && code < words_.size());
    return words_[code];
  }

  virtual int Code(const std::string& word) const override {
    const auto& ent = codes_.find(word);
    if (ent != codes_.end()) {
      return ent->second;
    } else {
      return kMissing;
    }
  }

 private:
  std::vector<Pronounces> pronounce_;
  std::vector<std::string> words_;
  google::dense_hash_map<std::string, int, MurmurHash3<std::string> > codes_;
  bool Parse(const std::string& line, std::string* word, Pronounce* res) const;

  POEMY_FRIEND_TEST(CmudictTest, Parse);
  POEMY_DISALLOW_COPY_AND_ASSIGN(Cmudict);
};

}  // namespace poemy

#endif  // POEMY_CMUDICT_H_

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
