#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_memory.hpp"


namespace translationModule
{
using ScAddrSet = std::unordered_set<ScAddr, ScAddrHashFunc<uint32_t>>;

class TranslationSearcher
{
public:
  explicit TranslationSearcher(ScMemoryContext * context);

private:
  ScMemoryContext * context;
};
}  // namespace translationModule
