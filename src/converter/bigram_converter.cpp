#include <map>
#include <stdexcept>

#include "bigram_converter.hpp"


namespace lime {
namespace converter {

BigramConverter::BigramConverter(shared_ptr<Bigram> bigram)
  : bigram_(bigram) {
}


void BigramConverter::Convert(Lattice *lattice) {
  // viterbi
  for (size_t pos = 1; pos < lattice->GetColumnCount() - 1; pos++) {
    NodeList &lnodes = lattice->GetEndNodes(pos);
    NodeList &rnodes = lattice->GetBeginNodes(pos);
    for (auto rnode_iter = begin(rnodes); rnode_iter != end(rnodes);
         ++rnode_iter) {
      SetBestLeftNode(lnodes, *rnode_iter);
    }
  }
}


void BigramConverter::SetBestLeftNode(NodeList &lnodes, Node *rnode) {
  Cost cost = 0;
  Node *lnode = nullptr;
  for (auto lnode_iter = begin(lnodes);
       lnode_iter != end(lnodes); ++lnode_iter) {
    // MEMO:
    // - latticeにコストを持たせることもできそう
    const Cost new_cost = (*lnode_iter)->cost_so_far
      + bigram_->GetCost((*lnode_iter)->token, rnode->token);
    if (!lnode || new_cost < cost) {
      cost = new_cost;
      lnode = *lnode_iter;
    }
  }
  rnode->prev = lnode;
  rnode->cost_so_far = cost;
}

} // converter
} // lime
