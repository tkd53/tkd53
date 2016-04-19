#include <iostream>
#include "lattice_builder.hpp"
#include "dictionary/dictionary_interface.hpp"

namespace lime {
namespace converter {

LatticeBuilder::LatticeBuilder(shared_ptr<DictionaryInterface> dictionary)
  : dictionary_(dictionary) {
}


Lattice *LatticeBuilder::Build(
    const KkciString &str, const Token begin_token, const Token end_token) {
  ScopedDictionaryResetter resetter(dictionary_);

  const size_t size = str.size();
  vector<Node*> *nodes(new vector<Node*>());
  vector<NodeList> *begin_nodes(new vector<NodeList>(size + 2));
  vector<NodeList> *end_nodes(new vector<NodeList>(size + 2 + 1));

  nodes->push_back(new Node({begin_token, nullptr, nullptr, 0}));
  (*begin_nodes)[0].push_back((*nodes)[0]);
  (*end_nodes)[1].push_back((*nodes)[0]);

  nodes->push_back(new Node({end_token, nullptr, nullptr, 0}));
  (*begin_nodes)[size + 1].push_back((*nodes)[1]);
  (*end_nodes)[size + 2].push_back((*nodes)[1]);

  for (size_t pos = 0; pos < size; pos++) {
    vector<const Entry*> entries;
    dictionary_->PushBack(str[pos]);
    dictionary_->Lookup(&entries);
    for (auto iter = begin(entries); iter != end(entries); ++iter) {
      Node *node = new Node({(*iter)->token, *iter, nullptr, 0});
      nodes->push_back(node);
      const size_t begin_pos = pos - node->entry->kkci_string.size() + 2;
      const size_t end_pos = pos + 2;
      (*begin_nodes)[begin_pos].push_back(node);
      (*end_nodes)[end_pos].push_back(node);
    }
  }

  return new Lattice(size + 3, nodes, begin_nodes, end_nodes);
}


} // converter
} // lime
