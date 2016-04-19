#pragma once

#include <memory>

#include "dictionary/dictionary_interface.hpp"
#include "abstract_converter.hpp"
#include "bigram.hpp"
#include "lattice_builder.hpp"

namespace lime {
namespace converter {
using namespace std;
using namespace lime::base::kkci;
using namespace lime::base::token;
using namespace lime::dictionary;


class BigramConverter : public AbstractConverter {
public:
  BigramConverter(shared_ptr<Bigram> bigram);

  virtual void Convert(Lattice *lattice) override;

private:
  void SetBestLeftNode(NodeList &lnodes, Node* rnode);

  shared_ptr<Bigram> bigram_;
};

} // converter
} // lime
