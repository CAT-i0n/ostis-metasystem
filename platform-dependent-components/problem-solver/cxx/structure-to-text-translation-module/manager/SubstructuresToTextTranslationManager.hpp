#pragma once

#include <memory>

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_addr.hpp"

namespace translationModule
{
class SubstructuresToTextTranslationManager
{
public:
  explicit SubstructuresToTextTranslationManager(ScMemoryContext * context);

  ScAddrVector manage(ScAddrVector const & processParameters) const;

private:
  ScMemoryContext * context;

};

}  // namespace translationModule
