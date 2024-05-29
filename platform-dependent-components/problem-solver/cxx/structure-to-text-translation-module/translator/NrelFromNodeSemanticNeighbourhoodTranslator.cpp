#include "NrelFromNodeSemanticNeighbourhoodTranslator.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"

namespace translationModule
{
NrelFromNodeSemanticNeighbourhoodTranslator::NrelFromNodeSemanticNeighbourhoodTranslator(ScMemoryContext * context)
  : SemanticNeighbourhoodTranslator(context)
{
}

std::vector<std::string> NrelFromNodeSemanticNeighbourhoodTranslator::getSemanticNeighbourhoodTranslation(
      ScAddrQueue & structureSearchQueue,
      ScAddrSet & notVisitedStructureEdges,
      ScAddr const & structure, 
      ScAddr const & lang) const
{
  ScAddr const & node = structureSearchQueue.front();
  std::vector<std::string> translations;
  auto const & nrelIterator = context->Iterator5(
      ScType::NodeConst, ScType::EdgeDCommonConst, node, ScType::EdgeAccessConstPosPerm, ScType::NodeConstNoRole);
  std::string const & nodeMainIdtf = getMainIdtf(node, {lang});
  if (nodeMainIdtf.empty())
      return {};
  while (nrelIterator->Next())
  {
    if (!notVisitedStructureEdges.count(nrelIterator->Get(1)) || !notVisitedStructureEdges.count(nrelIterator->Get(3)))
      continue;

    ScAddr const & nrelSourceNode = nrelIterator->Get(0);
    if (isInIgnoredKeynodes(nrelSourceNode))
      continue;
    std::string const & nrelSourceMainIdtf = getMainIdtf(nrelSourceNode, {lang});
    if (nrelSourceMainIdtf.empty())
      continue;

    ScAddr const & nrelNode = nrelIterator->Get(4);
    if (isInIgnoredKeynodes(nrelNode))
      continue;
    std::string nrelMainIdtf = getMainIdtf(nrelNode, {lang});
    if (nrelMainIdtf.empty())
      continue;

    translations.push_back(nrelSourceMainIdtf + " " + nrelMainIdtf + " " + nodeMainIdtf);

    notVisitedStructureEdges.erase(nrelIterator->Get(1));
    notVisitedStructureEdges.erase(nrelIterator->Get(3));
    structureSearchQueue.push(nrelIterator->Get(0));
  }
  return translations;
}

}  // namespace translationModule
