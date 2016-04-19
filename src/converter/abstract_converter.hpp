#pragma once

#include "base/kkci.hpp"
#include "base/token.hpp"
#include "lattice.hpp"


namespace lime {
namespace converter {
using namespace std;
using namespace lime::base::kkci;
using namespace lime::base::token;
using namespace lime::dictionary;


class AbstractConverter {
public:
  virtual void Convert(Lattice *lattice) = 0;

protected:
  AbstractConverter() {}
  virtual ~AbstractConverter() {}
};

} // converter
} // lime
