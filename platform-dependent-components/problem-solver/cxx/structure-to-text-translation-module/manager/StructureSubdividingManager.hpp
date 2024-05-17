#pragma once

#include <memory>
#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_addr.hpp"


namespace translationModule
{
class StructureSubdividingManager
{
public:
  StructureSubdividingManager(ScMemoryContext * context);

  ScAddrVector manage(ScAddrVector const & processParameters) const;

private:
  ScMemoryContext * context;

};

}  // namespace translationModule
