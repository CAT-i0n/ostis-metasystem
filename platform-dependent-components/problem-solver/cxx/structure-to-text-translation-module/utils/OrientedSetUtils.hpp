#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_memory.hpp"

namespace translationModule
{
class OrientedSetUtils
{
public:
  static void pushBackToSequenceSet(ScMemoryContext * context, ScAddr const & newElement, ScAddr const & setAddr);

  static void wrapInOrientedSet(ScMemoryContext * context, ScAddrList const & addrVector, ScAddr const & set);

  static ScAddrVector getElementsFromOrientedSet(ScMemoryContext * context, ScAddr const & set);
};

}  // namespace translationModule
