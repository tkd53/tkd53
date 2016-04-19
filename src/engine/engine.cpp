#include <sstream>

#include "engine.hpp"

namespace lime {
namespace engine {

namespace {

Node *FindMinCostNode(const NodeList &nodes) {
  Cost min_cost;
  Node *node = nullptr;
  for (auto it = begin(nodes); it != end(nodes); ++it) {
    if (!node || (*it)->cost_so_far < min_cost) {
      min_cost = (*it)->cost_so_far;
      node = *it;
    }
  }
  return node;
}

} // namespace


Engine::Engine(shared_ptr<AbstractConverter> converter,
               shared_ptr<DictionaryInterface> dictionary)
  : converter_(converter),
    dictionary_(dictionary),
    lattice_builder_(LatticeBuilder(dictionary)) {
}

void Engine::Convert(const KkciString &input, deque<Node> *output) {
  unique_ptr<Lattice> closer(lattice_builder_.Build(input, kBOS, kBOS));
  Lattice *lattice = closer.get();

  converter_->Convert(lattice);

  Node *last_node = FindMinCostNode(
      lattice->GetEndNodes(lattice->GetColumnCount() - 1));
  if (last_node == nullptr) {
    throw runtime_error("failed to run viterbi.");
  }

  // begin_tokenとend_tokenはkBOSなので入れなくてよい
  for (Node *node = last_node->prev; node->prev != nullptr;
       node = node->prev) {
    output->push_front(Node({
        node->token, node->entry, node->prev, node->cost_so_far}));
  }
}


void Engine::ListCandidates(const KkciString &input,
                            vector<const Entry*> *output) {
  ScopedDictionaryResetter resetter(dictionary_);
  for (KkciString::const_iterator it = input.begin();
       it != input.end(); ++it) {
    dictionary_->PushBack(*it);
  }
  vector<const Entry*> tmp;
  dictionary_->Lookup(&tmp);
  for (size_t i = 0; i < tmp.size(); i++) {
    if (tmp[i]->kkci_string == input) {
      output->push_back(tmp[i]);
    }
  }
}

} // converter
} // lime
