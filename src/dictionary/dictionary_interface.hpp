#pragma once

#include <memory>
#include <vector>

#include "../base/kkci.hpp"
#include "../base/token.hpp"

namespace lime {
namespace dictionary {
using namespace std;
using namespace lime::base::kkci;
using namespace lime::base::token;


enum Origin {
  IN_DICT,
  EX_DICT,
  USER_DICT,
};

struct Entry {
  const KkciString kkci_string;
  const Token token;
  const Origin origin;
};

class DictionaryInterface {
public:
  virtual void Clear() = 0;

  virtual void PushBack(Kkci kkci) = 0;

  virtual void Lookup(vector<const Entry*> *entries) = 0;

protected:
  DictionaryInterface() {}
  virtual ~DictionaryInterface() {}
};


class ScopedDictionaryResetter {
public:
  ScopedDictionaryResetter(shared_ptr<DictionaryInterface> dictionary)
    : dictionary_(dictionary) {
  }

  ~ScopedDictionaryResetter() {
    dictionary_->Clear();
  }

private:
  shared_ptr<DictionaryInterface> dictionary_;
};


} // dictionary
} // lime
