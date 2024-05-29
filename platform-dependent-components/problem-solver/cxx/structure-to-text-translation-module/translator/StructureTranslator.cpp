#include "StructureTranslator.hpp"

#include "NrelInNodeSemanticNeighbourhoodTranslator.hpp"
#include "NrelInLinkSemanticNeighbourhoodTranslator.hpp"
#include "NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator.hpp"
#include "FromQuasybinaryNodeSemanticNeighbourhoodTranslator.hpp"
#include "FromConceptSemanticNeighbourhoodTranslator.hpp"
#include "NrelFromNodeSemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
StructureTranslator::StructureTranslator(ScMemoryContext * context)
  : handlers({
      new FromConceptSemanticNeighbourhoodTranslator(context),
      // new FromSctructureSemanticNeighbourhoodTranslator(context),
      new FromQuasybinaryNodeSemanticNeighbourhoodTranslator(context),
      // new CommonAccessSemanticNeighbourhoodTranslator(context),
      // new ReverseCommonAccessSemanticNeighbourhoodTranslator(context),
      new NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator(context),
      new NrelInLinkSemanticNeighbourhoodTranslator(context),
      new NrelInNodeSemanticNeighbourhoodTranslator(context),
      new NrelFromNodeSemanticNeighbourhoodTranslator(context)
  })
{
  this->translationSearcher = std::make_unique<TranslationSearcher>(context);
}

StructureTranslator::~StructureTranslator()
{
  for (auto const & handler : handlers)
    delete handler;
}

std::vector<std::string> StructureTranslator::TranslateStructure(
    ScAddr const & structure,
    ScAddrVector const & keyElements,
    ScAddr const & lang) const
{
  ScAddrSet notVisitedStructureEdges = translationSearcher->getStructureEdges(structure);
  ScAddrSet notVisitedStructureNodes = translationSearcher->getStructureNodes(structure);
  ScAddrQueue structureSearchQueue;
  for (auto keyAddr : keyElements)
    structureSearchQueue.push(keyAddr);

  std::vector<std::string> answer;
  while (!notVisitedStructureEdges.empty())
  {
    if (structureSearchQueue.empty())
    {
      if (!notVisitedStructureNodes.empty())
        structureSearchQueue.push(*notVisitedStructureNodes.begin());
      else
        break;
    }
    if (!notVisitedStructureNodes.count(structureSearchQueue.front()))
    {
      structureSearchQueue.pop();
      continue;
    }
    for (auto const & handler : handlers)
    {
      auto translations =
          handler->getSemanticNeighbourhoodTranslation(structureSearchQueue, notVisitedStructureEdges, structure, lang);
      answer.insert(answer.cend(), translations.cbegin(), translations.cend());
    }
    notVisitedStructureNodes.erase(structureSearchQueue.front());
    structureSearchQueue.pop();
  }
  return answer;
}
}  // namespace translationModule
