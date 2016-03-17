#include <sstream>

#include "engine.hpp"

namespace lime {
namespace engine {

Engine::Engine(shared_ptr<AbstractConverter> converter,
               shared_ptr<DictionaryInterface> dictionary)
  : converter_(converter), dictionary_(dictionary) {
}

void Engine::Convert(const KkciString &input, Segments *output) {
  converter_->Convert(input, kBOS, kBOS, output);
}

void Engine::ListCandidates(const KkciString &input,
                            vector<const Entry*> *output) {
  ScopedDictionaryResetter resetter(dictionary_);
  for (KkciString::const_iterator it = input.begin();
       it != input.end(); ++it) {
    dictionary_->PushBack(*it);
  }
  dictionary_->Lookup(output);
}

} // converter
} // lime
