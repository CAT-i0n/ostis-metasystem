#include "NrelInNodeSemanticNeighbourhoodTranslator.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"

namespace translationModule
{
NrelInNodeSemanticNeighbourhoodTranslator::NrelInNodeSemanticNeighbourhoodTranslator(ScMemoryContext * context)
  : SemanticNeighbourhoodTranslator(context)
{
}

std::vector<std::string> NrelInNodeSemanticNeighbourhoodTranslator::getSemanticNeighbourhoodTranslation(
      ScAddrQueue & structureSearchQueue,
      ScAddrSet & notVisitedStructureEdges,
      ScAddr const & structure, 
      ScAddr const & lang) const
{
  ScAddr const & node = structureSearchQueue.front();
  std::vector<std::string> translations;
  auto const & nrelIterator = context->Iterator5(
      node, ScType::EdgeDCommonConst, ScType::NodeConst, ScType::EdgeAccessConstPosPerm, ScType::NodeConstNoRole);
  std::string const & nodeMainIdtf = utils::CommonUtils::getMainIdtf(context, node, {lang});
  while (nrelIterator->Next())
  {
    if (!isInStructure(nrelIterator->Get(1), structure)
        || !isInStructure(nrelIterator->Get(3), structure))
      continue;
    ScAddr const & nrelTargetNode = nrelIterator->Get(2);
    if (isInIgnoredKeynodes(nrelTargetNode))
      continue;
    std::string const & nrelTargetMainIdtf = utils::CommonUtils::getMainIdtf(context, nrelTargetNode, {lang});
    if (nrelTargetMainIdtf.empty())
      continue;

    ScAddr const & nrelNode = nrelIterator->Get(4);
    if (isInIgnoredKeynodes(nrelNode))
      continue;
    std::string nrelMainIdtf = utils::CommonUtils::getMainIdtf(context, nrelNode, {lang});
    if (nrelMainIdtf.empty())
      continue;

    translations.push_back(nodeMainIdtf + " " + nrelMainIdtf + " " + nrelTargetMainIdtf);

    notVisitedStructureEdges.erase(nrelIterator->Get(1));
    notVisitedStructureEdges.erase(nrelIterator->Get(3));
    structureSearchQueue.push(nrelIterator->Get(2));
  }
  return translations;
}

std::list<ScAddrVector> NrelInNodeSemanticNeighbourhoodTranslator::getSemanticNeighbourhoodTranslationElements(
    ScAddr const & node,
    ScAddr const & structure) const
{
  std::list<ScAddrVector> answer;
  auto const & nrelIterator = context->Iterator5(
      node, ScType::EdgeDCommonConst, ScType::NodeConst, ScType::EdgeAccessConstPosPerm, ScType::NodeConstNoRole);
  while (nrelIterator->Next())
  {
    if (isInStructure(nrelIterator->Get(1), structure) == SC_FALSE
        || isInStructure(nrelIterator->Get(3), structure) == SC_FALSE)
      continue;
    ScAddr const & nrelTargetNode = nrelIterator->Get(2);
    if (isInIgnoredKeynodes(nrelTargetNode))
      continue;

    ScAddr const & nrelNode = nrelIterator->Get(4);
    if (isInIgnoredKeynodes(nrelNode))
      continue;

    answer.push_back({nrelIterator->Get(1), nrelIterator->Get(2), nrelIterator->Get(3), nrelIterator->Get(4)});
  }
  return answer;
}
}  // namespace translationModule
