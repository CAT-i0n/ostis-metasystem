#include "keynodes/TranslationKeynodes.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"

#include "FromConceptSemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
FromConceptSemanticNeighbourhoodTranslator::FromConceptSemanticNeighbourhoodTranslator(ScMemoryContext * context)
  : SemanticNeighbourhoodTranslator(context)
{
}

std::vector<std::string> FromConceptSemanticNeighbourhoodTranslator::getSemanticNeighbourhoodTranslation(
    ScAddrQueue & structureSearchQueue,
    ScAddrSet & notVisitedStructureEdges,
    ScAddr const & structure,
    ScAddr const & lang) const
{
  ScAddr const & node = structureSearchQueue.front();
  std::vector<std::string> translations;
  auto const & classIterator = context->Iterator3(ScType::NodeConstClass, ScType::EdgeAccessConstPosPerm, node);

  std::string const & nodeMainIdtf = utils::CommonUtils::getMainIdtf(context, node, {lang});
  while (classIterator->Next())
  {
    if (!isInStructure(classIterator->Get(1), structure))
      continue;
    ScAddr const & classNode = classIterator->Get(0);
    if (isInIgnoredKeynodes(classNode))
      continue;
    std::string const & classMainIdtf = utils::CommonUtils::getMainIdtf(context, classNode, {lang});
    if (classMainIdtf.empty())
      continue;
    translations.push_back(nodeMainIdtf + " is " + classMainIdtf);
    notVisitedStructureEdges.erase(classIterator->Get(1));
  }
  return translations;
}

std::list<ScAddrVector> FromConceptSemanticNeighbourhoodTranslator::getSemanticNeighbourhoodTranslationElements(
    ScAddr const & node,
    ScAddr const & structure) const
{
  std::list<ScAddrVector> answer;

  auto const & classIterator = context->Iterator3(ScType::NodeConstClass, ScType::EdgeAccessConstPosPerm, node);
  while (classIterator->Next())
  {
    if (isInStructure(classIterator->Get(1), structure) == SC_FALSE)
      continue;
    ScAddr const & classNode = classIterator->Get(0);
    if (isInIgnoredKeynodes(classNode))
      continue;
    answer.push_back({classIterator->Get(0), classIterator->Get(1)});
  }

  return answer;
}
}  // namespace translationModule
