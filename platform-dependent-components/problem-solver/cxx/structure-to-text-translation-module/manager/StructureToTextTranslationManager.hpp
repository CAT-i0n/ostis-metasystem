#pragma once

#include <memory>
#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_addr.hpp"

#include "translator/StructureTranslator.hpp"


namespace translationModule
{
class StructureToTextTranslationManager
{
public:
  StructureToTextTranslationManager(ScMemoryContext * context);

  ScAddrVector manage(ScAddrVector const & processParameters) const;

  ScAddr createLink(std::string const & text, ScAddrVector const & linkClasses) const;

  std::string join(
      std::vector<std::string>::const_iterator const & cbegin,
      std::vector<std::string>::const_iterator const & cend) const;

private:
  ScMemoryContext * context;

  std::unique_ptr<StructureTranslator> structureTranslator;
};

}  // namespace translationModule
