#include <iostream>
#include "lattice.hpp"


namespace lime {
namespace converter {

Lattice::Lattice(size_t column_count,
                 vector<Node*> *nodes,
                 vector<NodeList> *begin_nodes,
                 vector<NodeList> *end_nodes)
  : column_count_(column_count),
    nodes_(nodes), begin_nodes_(begin_nodes), end_nodes_(end_nodes) {
}


size_t Lattice::GetColumnCount() const {
  return column_count_;
}

NodeList &Lattice::GetBeginNodes(size_t pos) {
  return (*begin_nodes_)[pos];
}

NodeList &Lattice::GetEndNodes(size_t pos) {
  return (*end_nodes_)[pos];
}


} // converter
} // lime
