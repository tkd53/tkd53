#pragma once

#include <vector>
#include <memory>

#include "base/kkci.hpp"
#include "base/token.hpp"
#include "dictionary/dictionary_interface.hpp"

namespace lime {
namespace converter {
using namespace std;
using namespace lime::base::kkci;
using namespace lime::base::token;
using namespace lime::dictionary;

typedef double Cost;


struct Node {
  const Token token;
  const Entry* const entry;
  Node *prev;
  Cost cost_so_far;
};

typedef vector<Node*> NodeList;

class Lattice {
public:
  size_t GetColumnCount() const;

  NodeList &GetBeginNodes(size_t pos);

  NodeList &GetEndNodes(size_t pos);

  Lattice(size_t column_count,
          vector<Node*> *nodes,
          vector<NodeList> *begin_nodes,
          vector<NodeList> *end_nodes);
private:
  const size_t column_count_;
  const unique_ptr<vector<Node*> > nodes_;
  unique_ptr<vector<NodeList> > begin_nodes_;
  unique_ptr<vector<NodeList> > end_nodes_;
};


} // converter
} // lime
