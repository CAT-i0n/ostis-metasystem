#pragma once

#include "SemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
/**
 * node _=> _nrel_relation:: {_quasybinary_node};;
 */
class NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator : public SemanticNeighbourhoodTranslator
{
public:
  explicit NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator(ScMemoryContext * context);

  std::vector<std::string> getSemanticNeighbourhoodTranslation(
      ScAddrQueue & structureSearchQueue,
      ScAddrSet & notVisitedStructureEdges,
      ScAddr const & structure, 
      ScAddr const & lang) const override;
private:
};

}  // namespace translationModule
