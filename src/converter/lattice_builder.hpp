#pragma once

#include <memory>
#include <vector>

#include "base/kkci.hpp"
#include "base/token.hpp"
#include "dictionary/dictionary_interface.hpp"
#include "lattice.hpp"

namespace lime {
namespace converter {
using namespace std;
using namespace lime::base::kkci;
using namespace lime::base::token;
using namespace lime::dictionary;

class LatticeBuilder {
public:
  LatticeBuilder(shared_ptr<DictionaryInterface> dictionary);

  Lattice *Build(const KkciString &str, Token begin_token, Token end_token);

private:
  shared_ptr<DictionaryInterface> dictionary_;
};

} // converter
} // lime
