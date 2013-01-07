// poemy - A poetry generator
// Copyright (c) 2012 Justine Alexandra Roberts Tunney

#ifndef POEMY_ISLEDICT_H_
#define POEMY_ISLEDICT_H_

#include <vector>

#include <sparsehash/dense_hash_map>

#include <poemy/dict.h>
#include <poemy/hash.h>
#include <poemy/pronounce.h>

namespace poemy {

class Isledict : public Dict {
 public:
  Isledict();
  // I take ownership of 'input'.
  virtual void Load(std::istream* input);

  virtual const Pronounces& Speak(int code) const {
    return pronounce_[code];
  }

  virtual const std::string& Word(int code) const {
    return words_[code];
  }

  virtual int Code(const std::string& word) const {
    const auto& ent = codes_.find(word);
    if (ent != codes_.end()) {
      return ent->second;
    } else {
      return -1;
    }
  }

 private:
  std::vector<Pronounces> pronounce_;
  std::vector<std::string> words_;
  google::dense_hash_map<std::string, int, MurmurHash3<std::string> > codes_;
  bool Parse(const std::string& line, std::string* word, Pronounce* res) const;

  POEMY_FRIEND_TEST(IsledictTest, Parse);
  POEMY_DISALLOW_COPY_AND_ASSIGN(Isledict);
};

}  // namespace poemy

#endif  // POEMY_ISLEDICT_H_

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
