#pragma once

#include "SemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
/**
 * node _<= _nrel_relation:: {_quasybinary_node};;
 */
class FromQuasybinaryNodeSemanticNeighbourhoodTranslator : public SemanticNeighbourhoodTranslator
{
public:
  explicit FromQuasybinaryNodeSemanticNeighbourhoodTranslator(ScMemoryContext * context);

  std::vector<std::string> getSemanticNeighbourhoodTranslation(
      ScAddrQueue & structureSearchQueue,
      ScAddrSet & notVisitedStructureEdges,
      ScAddr const & structure, 
      ScAddr const & lang) const override;

private:
};

}  // namespace translationModule
