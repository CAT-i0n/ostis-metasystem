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
  std::string const & nodeMainIdtf = getMainIdtf(node, {lang});
  if (nodeMainIdtf.empty())
      return {};
  while (nrelIterator->Next())
  {
    if (!notVisitedStructureEdges.count(nrelIterator->Get(1)) || !notVisitedStructureEdges.count(nrelIterator->Get(3)))
      continue;

    ScAddr const & nrelTargetNode = nrelIterator->Get(2);
    if (isInIgnoredKeynodes(nrelTargetNode))
      continue;
    std::string const & nrelTargetMainIdtf = getMainIdtf(nrelTargetNode, {lang});
    if (nrelTargetMainIdtf.empty())
      continue;

    ScAddr const & nrelNode = nrelIterator->Get(4);
    if (isInIgnoredKeynodes(nrelNode))
      continue;
    std::string nrelMainIdtf = getMainIdtf(nrelNode, {lang});
    if (nrelMainIdtf.empty())
      continue;

    translations.push_back(nodeMainIdtf + " " + nrelMainIdtf + " " + nrelTargetMainIdtf);

    notVisitedStructureEdges.erase(nrelIterator->Get(1));
    notVisitedStructureEdges.erase(nrelIterator->Get(3));
    structureSearchQueue.push(nrelIterator->Get(2));
  }
  return translations;
}

}  // namespace translationModule