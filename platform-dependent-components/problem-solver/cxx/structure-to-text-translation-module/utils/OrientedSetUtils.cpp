#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/utils/GenerationUtils.hpp"

#include "keynodes/TranslationKeynodes.hpp"

#include "OrientedSetUtils.hpp"

namespace translationModule
{

void OrientedSetUtils::pushBackToSequenceSet(
    ScMemoryContext * context,
    ScAddr const & newElement,
    ScAddr const & setAddr)
{
  ScAddr const & previousLastElement =
      utils::IteratorUtils::getAnyByOutRelation(context, setAddr, TranslationKeynodes::rrel_last);

  ScAddr const & tupleToNewElementEdge = context->CreateEdge(ScType::EdgeAccessConstPosPerm, setAddr, newElement);
  context->CreateEdge(ScType::EdgeAccessConstPosPerm, TranslationKeynodes::rrel_last, tupleToNewElementEdge);

  if (!context->IsElement(previousLastElement))
  {
    context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::rrel_1, tupleToNewElementEdge);
    return;
  }

  ScAddr tupleToPreviousElementEdge;
  ScIterator5Ptr sequenceIter = context->Iterator5(
      setAddr,
      ScType::EdgeAccessConstPosPerm,
      previousLastElement,
      ScType::EdgeAccessConstPosPerm,
      TranslationKeynodes::rrel_last);
  ScAddr elementToErase;
  if (sequenceIter->Next())
  {
    tupleToPreviousElementEdge = sequenceIter->Get(1);
    elementToErase = sequenceIter->Get(3);
  }
  context->EraseElement(elementToErase);

  ScAddr const & sequenceEdge =
      context->CreateEdge(ScType::EdgeDCommonConst, tupleToPreviousElementEdge, tupleToNewElementEdge);
  context->CreateEdge(ScType::EdgeAccessConstPosPerm, TranslationKeynodes::nrel_basic_sequence, sequenceEdge);
}

void OrientedSetUtils::wrapInOrientedSet(ScMemoryContext * context, ScAddrList const & addrList, ScAddr const & set)
{
  if (addrList.empty())
    return;
  ScAddr prevEdge = context->CreateEdge(ScType::EdgeAccessConstPosPerm, set, addrList.front());
  context->CreateEdge(ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::rrel_1, prevEdge);

  for (auto iterItems = ++addrList.begin(); iterItems != addrList.end(); iterItems++)
  {
    ScAddr edge = context->CreateEdge(ScType::EdgeAccessConstPosPerm, set, *iterItems);
    utils::GenerationUtils::generateRelationBetween(
        context, prevEdge, edge, scAgentsCommon::CoreKeynodes::nrel_basic_sequence);
    prevEdge = edge;
  }
  context->CreateEdge(ScType::EdgeAccessConstPosPerm, TranslationKeynodes::rrel_last, prevEdge);
}

ScAddrVector OrientedSetUtils::getElementsFromOrientedSet(ScMemoryContext * context, ScAddr const & set)
{
  if (!context->IsElement(set))
    return {};
  ScAddr curentElement = utils::IteratorUtils::getAnyByOutRelation(context, set, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!context->IsElement(curentElement))
    return {};

  ScAddrVector setElements;
  setElements.push_back(curentElement);

  while (true)
  {
    ScTemplate nextElementTemplate;
    nextElementTemplate.Triple(set, ScType::EdgeAccessVarPosPerm >> "PREV_EDGE", curentElement);
    nextElementTemplate.Quintuple(
        "PREV_EDGE",
        ScType::EdgeDCommonVar,
        ScType::EdgeAccessVarPosPerm >> "NEXT_EDGE",
        ScType::EdgeAccessVarPosPerm,
        TranslationKeynodes::nrel_basic_sequence);
    nextElementTemplate.Triple(set, "NEXT_EDGE", ScType::NodeVar >> "NEXT_ELEMENT");

    ScAddr nextEdge;
    context->HelperSmartSearchTemplate(
        nextElementTemplate,
        [&curentElement, &nextEdge](ScTemplateSearchResultItem const & item) -> ScTemplateSearchRequest
        {
          curentElement = item["NEXT_ELEMENT"];
          nextEdge = item["NEXT_EDGE"];
          return ScTemplateSearchRequest::STOP;
        });
    if (curentElement == *(setElements.end()-1))
      break;
    setElements.push_back(curentElement);
    if (context->HelperCheckEdge(TranslationKeynodes::rrel_last, nextEdge, ScType::EdgeAccessConstPosPerm))
      break;
  }
  return setElements;
}

}  // namespace translationModule
