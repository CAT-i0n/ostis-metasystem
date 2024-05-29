#pragma once

#include "SemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
/**
 * _source _=> _nrel_relation:: node;;
 */
class NrelFromNodeSemanticNeighbourhoodTranslator : public SemanticNeighbourhoodTranslator
{
public:
  explicit NrelFromNodeSemanticNeighbourhoodTranslator(ScMemoryContext * context);

  std::vector<std::string> getSemanticNeighbourhoodTranslation(
      ScAddrQueue & structureSearchQueue,
      ScAddrSet & notVisitedStructureEdges,
      ScAddr const & structure, 
      ScAddr const & lang) const override;


private:
};

}  // namespace translationModule
