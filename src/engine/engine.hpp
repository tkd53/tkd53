#pragma once

#include <memory>

#include "dictionary/dictionary_interface.hpp"
#include "converter/abstract_converter.hpp"

namespace lime {
namespace engine {
using namespace std;
using namespace lime::base::kkci;
using namespace lime::base::token;
using namespace lime::converter;
using namespace lime::dictionary;


class Engine {
public:
  Engine(shared_ptr<AbstractConverter> converter,
         shared_ptr<DictionaryInterface> dictionary);

  void Convert(const KkciString &input, Segments *output);

  void ListCandidates(const KkciString &input, vector<const Entry*> *output);

private:
  shared_ptr<AbstractConverter> converter_;

  shared_ptr<DictionaryInterface> dictionary_;
};


} // engine
} // lime
