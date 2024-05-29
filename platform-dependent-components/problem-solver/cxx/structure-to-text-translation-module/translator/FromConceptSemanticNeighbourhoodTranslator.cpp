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

  std::string const & nodeMainIdtf = getMainIdtf(node, {lang});
  if (nodeMainIdtf.empty())
      return {};
  while (classIterator->Next())
  {
    if (!notVisitedStructureEdges.count(classIterator->Get(1)))
      continue;
    ScAddr const & classNode = classIterator->Get(0);
    if (isInIgnoredKeynodes(classNode))
      continue;
    std::string const & classMainIdtf = getMainIdtf(classNode, {lang});
    if (classMainIdtf.empty())
      continue;
    if (lang == TranslationKeynodes::lang_en)
      translations.push_back(nodeMainIdtf + " is " + classMainIdtf);
    if (lang == TranslationKeynodes::lang_ru)
      translations.push_back(nodeMainIdtf + " это " + classMainIdtf);
    notVisitedStructureEdges.erase(classIterator->Get(1));
  }
  return translations;
}
}  // namespace translationModule
