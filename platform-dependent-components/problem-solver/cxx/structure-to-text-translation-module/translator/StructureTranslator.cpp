#include "StructureTranslator.hpp"

#include "NrelInNodeSemanticNeighbourhoodTranslator.hpp"
#include "NrelInLinkSemanticNeighbourhoodTranslator.hpp"
#include "NrelInQuasybinaryLinkSemanticNeighbourhoodTranslator.hpp"
#include "NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator.hpp"
#include "NrelFromQuasybinaryNodeSemanticNeighbourhoodTranslator.hpp"
#include "FromConceptSemanticNeighbourhoodTranslator.hpp"
#include "NrelFromNodeSemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
StructureTranslator::StructureTranslator(ScMemoryContext * context)
  : handlers({
      new FromConceptSemanticNeighbourhoodTranslator(context),
      // TOADD new InConceptSemanticNeighbourhoodTranslator(context),
      // new NrelInLinkSemanticNeighbourhoodTranslator(context),
      // new NrelInQuasybinaryLinkSemanticNeighbourhoodTranslator(context),
      // new NrelInQuasybinaryNodeSemanticNeighbourhoodTranslator(context),
      // new NrelFromQuasybinaryNodeSemanticNeighbourhoodTranslator(context),
      // new NrelFromNodeSemanticNeighbourhoodTranslator(context),
      new NrelInNodeSemanticNeighbourhoodTranslator(context),
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
  SC_LOG_DEBUG("All edges - " << notVisitedStructureEdges.size());
  SC_LOG_DEBUG("All nodes - " << notVisitedStructureNodes.size());

  ScAddrQueue structureSearchQueue;

  for (auto keyAddr : keyElements)
    structureSearchQueue.push(keyAddr);

  std::vector<std::string> answer;
  while (!notVisitedStructureEdges.empty() && !structureSearchQueue.empty())
  {
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
