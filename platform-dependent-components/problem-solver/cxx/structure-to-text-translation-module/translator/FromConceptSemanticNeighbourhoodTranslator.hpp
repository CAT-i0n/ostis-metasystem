#pragma once

#include "SemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
/**
 * _concept _-> node;;
 *
 * note: translation is generated only if following construction does not exist
 * _parameter_class
 *  _<- parameter;
 *  _-> _concept;;
 */
class FromConceptSemanticNeighbourhoodTranslator : public SemanticNeighbourhoodTranslator
{
public:
  explicit FromConceptSemanticNeighbourhoodTranslator(ScMemoryContext * context);

  std::vector<std::string> getSemanticNeighbourhoodTranslation(
      ScAddrQueue & structureSearchQueue,
      ScAddrSet & notVisitedStructureEdges,
      ScAddr const & structure, 
      ScAddr const & lang) const override;

  std::list<ScAddrVector> getSemanticNeighbourhoodTranslationElements(ScAddr const & node, ScAddr const & structure)
      const override;

};

}  // namespace translationModule
