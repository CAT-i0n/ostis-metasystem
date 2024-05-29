#pragma once

#include "SemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
/**
 * node _=> _nrel_relation:: _[];;
 */
class NrelInLinkSemanticNeighbourhoodTranslator : public SemanticNeighbourhoodTranslator
{
public:
  explicit NrelInLinkSemanticNeighbourhoodTranslator(ScMemoryContext * context);

  std::vector<std::string> getSemanticNeighbourhoodTranslation(
      ScAddrQueue & structureSearchQueue,
      ScAddrSet & notVisitedStructureEdges,
      ScAddr const & structure, 
      ScAddr const & lang) const override;
private:
};

}  // namespace translationModule
