#include "NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator::NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator(
    ScMemoryContext * context)
  : SemanticNeighbourhoodTranslator(context)
{
}

std::vector<std::string> NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator::getSemanticNeighbourhoodTranslation(
    ScAddrQueue & structureSearchQueue,
    ScAddrSet & notVisitedStructureEdges,
    ScAddr const & structure,
    ScAddr const & lang) const
{
  ScAddr const & node = structureSearchQueue.front();
  std::vector<std::string> translations;
  auto const & nrelInTupleIterator = context->Iterator5(
      node, ScType::EdgeDCommonConst, ScType::NodeConstTuple, ScType::EdgeAccessConstPosPerm, ScType::NodeConstNoRole);
  std::string const & nodeMainIdtf = getMainIdtf(node, {lang});
  if (nodeMainIdtf.empty())
    return {};
  while (nrelInTupleIterator->Next())
  {
    if (!notVisitedStructureEdges.count(nrelInTupleIterator->Get(1))
        || !notVisitedStructureEdges.count(nrelInTupleIterator->Get(3)))
      continue;
    ScAddr const & tupleNode = nrelInTupleIterator->Get(2);
    if (isInIgnoredKeynodes(tupleNode))
      continue;

    ScAddr const & nrelNode = nrelInTupleIterator->Get(4);
    if (isInIgnoredKeynodes(nrelNode))
      continue;
    std::string nrelMainIdtf = getMainIdtf(nrelNode, {lang});
    if (nrelMainIdtf.empty())
      continue;

    ScTemplate quasibinaryTemplate;
    quasibinaryTemplate.Quintuple(node, ScType::EdgeDCommonVar, tupleNode, ScType::EdgeAccessVarPosPerm, nrelNode);
    quasibinaryTemplate.Triple(tupleNode, ScType::EdgeAccessVarPosPerm >> "EDGE", ScType::NodeVar >> "ELEMENT");
    std::vector<std::string> tupleElements;

    context->HelperSmartSearchTemplate(
        quasibinaryTemplate,
        [this, &lang, &tupleElements, &notVisitedStructureEdges, &structureSearchQueue](
            ScTemplateSearchResultItem const & item)
        {
          if (!notVisitedStructureEdges.count(item["EDGE"]))
            return ScTemplateSearchRequest::CONTINUE;
          notVisitedStructureEdges.erase(item["EDGE"]);
          std::string const & nodeIdtf = getMainIdtf(item["ELEMENT"], {lang});
          if (!nodeIdtf.empty())
            tupleElements.push_back(nodeIdtf);
          structureSearchQueue.push(item["ELEMENT"]);
          return ScTemplateSearchRequest::CONTINUE;
        });

    std::string translation = nodeMainIdtf + " " + nrelMainIdtf + ":";

    for (auto element : tupleElements)
    {
      if (element == *(tupleElements.begin()))
        translation += " " + element;
      else
        translation += ", " + element;
    }

    translations.push_back(translation);

    notVisitedStructureEdges.erase(nrelInTupleIterator->Get(1));
    notVisitedStructureEdges.erase(nrelInTupleIterator->Get(3));
  }
  return translations;
}

}  // namespace translationModule
