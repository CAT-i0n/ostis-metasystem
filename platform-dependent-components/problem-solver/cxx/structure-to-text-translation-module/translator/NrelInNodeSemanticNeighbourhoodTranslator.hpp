#pragma once

#include "SemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
/**
 * node _=> _nrel_relation:: _source;;
 */
class NrelInNodeSemanticNeighbourhoodTranslator : public SemanticNeighbourhoodTranslator
{
public:
  explicit NrelInNodeSemanticNeighbourhoodTranslator(ScMemoryContext * context);

  std::vector<std::string> getSemanticNeighbourhoodTranslation(
      ScAddrQueue & structureSearchQueue,
      ScAddrSet & notVisitedStructureEdges,
      ScAddr const & structure, 
      ScAddr const & lang) const override;

protected:
private:
};

}  // namespace translationModule
