#include <iostream>
#include "lattice_builder.hpp"
#include "dictionary/dictionary_interface.hpp"

namespace lime {
namespace converter {

LatticeBuilder::LatticeBuilder(shared_ptr<DictionaryInterface> dictionary)
  : dictionary_(dictionary) {
}


unique_ptr<Lattice> LatticeBuilder::Build(
    const KkciString &str, const Token begin_token, const Token end_token) {
  ScopedDictionaryResetter resetter(dictionary_);

  const size_t size = str.size();
  unique_ptr<vector<shared_ptr<Node> > > nodes(
      new vector<shared_ptr<Node> >());
  unique_ptr<vector<vector<shared_ptr<Node> > > > begin_nodes(
      new vector<vector<shared_ptr<Node> > >(size + 2));
  unique_ptr<vector<vector<shared_ptr<Node> > > > end_nodes(
      new vector<vector<shared_ptr<Node> > >(size + 2 + 1));

  nodes->push_back(shared_ptr<Node>(
      new Node({begin_token, nullptr, nullptr, 0})));
  (*begin_nodes)[0].push_back((*nodes)[0]);
  (*end_nodes)[1].push_back((*nodes)[0]);

  nodes->push_back(shared_ptr<Node>(
      new Node({end_token, nullptr, nullptr, 0})));
  (*begin_nodes)[size + 1].push_back((*nodes)[1]);
  (*end_nodes)[size + 2].push_back((*nodes)[1]);

  for (size_t pos = 0; pos < size; pos++) {
    vector<const Entry*> entries;
    dictionary_->PushBack(str[pos]);
    dictionary_->Lookup(&entries);
    for (vector<const Entry*>::iterator iter = entries.begin();
         iter != entries.end(); ++iter) {
      shared_ptr<Node> node(new Node({(*iter)->token, *iter, nullptr, 0}));
      nodes->push_back(node);
      const size_t begin_pos = pos - node->entry->kkci_string.size() + 2;
      const size_t end_pos = pos + 2;
      (*begin_nodes)[begin_pos].push_back(node);
      (*end_nodes)[end_pos].push_back(node);
    }
  }

  return unique_ptr<Lattice>(new Lattice(
      size + 3, move(nodes), move(begin_nodes), move(end_nodes)));
}


} // converter
} // lime
