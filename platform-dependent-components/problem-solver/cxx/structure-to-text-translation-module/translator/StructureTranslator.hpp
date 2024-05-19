#pragma once

#include "translator/SemanticNeighbourhoodTranslator.hpp"

#include "searcher/TranslationSearcher.hpp"

namespace translationModule
{
class StructureTranslator
{
public:
  explicit StructureTranslator(ScMemoryContext * context);

  ~StructureTranslator();

  std::vector<std::string> TranslateStructure(
      ScAddr const & structure,
      ScAddrVector const & keyElements,
      ScAddr const & lang) const;

private:
  std::unique_ptr<TranslationSearcher> translationSearcher;
  std::vector<SemanticNeighbourhoodTranslator *> const handlers;
};

}  // namespace translationModule
