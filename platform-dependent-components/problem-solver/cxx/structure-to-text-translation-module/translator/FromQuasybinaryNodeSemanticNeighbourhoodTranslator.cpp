#include "FromQuasybinaryNodeSemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
FromQuasybinaryNodeSemanticNeighbourhoodTranslator::FromQuasybinaryNodeSemanticNeighbourhoodTranslator(ScMemoryContext * context)
  : SemanticNeighbourhoodTranslator(context)
{
}

std::vector<std::string> FromQuasybinaryNodeSemanticNeighbourhoodTranslator::getSemanticNeighbourhoodTranslation(
    ScAddrQueue & structureSearchQueue,
    ScAddrSet & notVisitedStructureEdges,
    ScAddr const & structure,
    ScAddr const & lang) const
{
  ScAddr const & node = structureSearchQueue.front();
  std::vector<std::string> translations;
  auto const & fromTupleIterator = context->Iterator3(ScType::NodeConstTuple, ScType::EdgeAccessConstPosPerm, node);
  while (fromTupleIterator->Next())
  {
    if (!notVisitedStructureEdges.count(fromTupleIterator->Get(1)))
      continue;
    ScAddr nrelSourceNode;
    ScAddr nrelNode;
    auto const & nrelTtoTupleIterator = context->Iterator5(
        fromTupleIterator->Get(0),
        ScType::EdgeDCommonConst,
        ScType::NodeConst,
        ScType::EdgeAccessConstPosPerm,
        ScType::NodeNoRole);
    if (nrelTtoTupleIterator->Next())
    {
      if (!notVisitedStructureEdges.count(nrelTtoTupleIterator->Get(1)))
        continue;
      nrelSourceNode = nrelTtoTupleIterator->Get(2);
      nrelNode = nrelTtoTupleIterator->Get(4);
    }
    else
    {
      auto const & nrelTtoTupleIterator = context->Iterator5(
          ScType::NodeConst,
          ScType::EdgeDCommonConst,
          fromTupleIterator->Get(0),
          ScType::EdgeAccessConstPosPerm,
          ScType::NodeNoRole);
      if (nrelTtoTupleIterator->Next())
      {
        if (!notVisitedStructureEdges.count(nrelTtoTupleIterator->Get(1)))
          continue;
        nrelSourceNode = nrelTtoTupleIterator->Get(0);
        nrelNode = nrelTtoTupleIterator->Get(4);
      }
      else
        continue;
    }
    if (isInIgnoredKeynodes(nrelSourceNode) || isInIgnoredKeynodes(nrelNode))
      continue;
    ScTemplate quasibinaryTemplate;
    quasibinaryTemplate.Quintuple(
        nrelSourceNode,
        ScType::EdgeDCommonVar,
        ScType::NodeVarTuple >> "TUPLE_NODE_ALIAS",
        ScType::EdgeAccessVarPosPerm,
        nrelNode);
    quasibinaryTemplate.Triple(
        "TUPLE_NODE_ALIAS", ScType::EdgeAccessVarPosPerm >> "EDGE", ScType::NodeVar >> "ELEMENT");

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

    
    SC_LOG_DEBUG(context->HelperGetSystemIdtf(nrelSourceNode));
    std::string const & nrelSourceMainIdtf = getMainIdtf(nrelSourceNode, {lang});
    if (nrelSourceMainIdtf.empty())
      continue;
    std::string nrelMainIdtf = getMainIdtf(nrelNode, {lang});
    if (nrelMainIdtf.empty())
      continue;
    std::string translation = nrelSourceMainIdtf + " " + nrelMainIdtf + ":";

    for (auto element : tupleElements)
    {
      if (element == *(tupleElements.begin()))
        translation += " " + element;
      else
        translation += ", " + element;
    }

    translations.push_back(translation);

    notVisitedStructureEdges.erase(nrelTtoTupleIterator->Get(1));
    notVisitedStructureEdges.erase(nrelTtoTupleIterator->Get(3));
    structureSearchQueue.push(fromTupleIterator->Get(0));
  }
  return translations;
}
}  // namespace translationModule
