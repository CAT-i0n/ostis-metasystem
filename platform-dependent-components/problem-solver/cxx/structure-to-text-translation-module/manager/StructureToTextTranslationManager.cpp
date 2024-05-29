#include <memory>
#include <queue>
#include <iterator>
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/utils/AgentUtils.hpp"

#include "utils/OrientedSetUtils.hpp"

#include "StructureToTextTranslationManager.hpp"

#include "keynodes/TranslationKeynodes.hpp"

namespace translationModule
{
using ScAddrSet = std::unordered_set<ScAddr, ScAddrHashFunc<uint32_t>>;
using ScAddrQueue = std::queue<ScAddr>;

StructureToTextTranslationManager::StructureToTextTranslationManager(ScMemoryContext * context)
  : context(context)
{
  this->structureTranslator = std::make_unique<StructureTranslator>(context);
}

ScAddrVector StructureToTextTranslationManager::manage(ScAddrVector const & processParameters) const
{
  ScAddr const & structure = processParameters[0];
  ScAddrVector keyElements = OrientedSetUtils::getElementsFromOrientedSet(context, processParameters[1]);
  for (auto const key : keyElements)
    SC_LOG_DEBUG("key " << context->HelperGetSystemIdtf(key));
  if (keyElements.empty())
    // findKeyElemet(keyElements);
    return {};
  ScAddr const & lang = TranslationKeynodes::lang_ru;
  std::vector<std::string> translations = structureTranslator->TranslateStructure(structure, keyElements, lang);

  std::string const & translation = join(translations.cbegin(), translations.cend());
  SC_LOG_DEBUG(translation);
  ScAddr const & result =
      createLink(translation, {lang});
  return {result};
}

ScAddr StructureToTextTranslationManager::createLink(std::string const & text, ScAddrVector const & linkClasses) const
{
  ScAddr addr = context->CreateLink();
  context->SetLinkContent(addr, text);
  for (auto const & linkClass : linkClasses)
  {
    if (context->IsElement(linkClass))
      context->CreateEdge(ScType::EdgeAccessConstPosPerm, linkClass, addr);
  }

  return addr;
}

std::string StructureToTextTranslationManager::join(    std::vector<std::string>::const_iterator const & cbegin,
    std::vector<std::string>::const_iterator const & cend) const
{
  std::ostringstream os;
  std::copy(cbegin, cend, std::ostream_iterator<std::string>(os, ". "));
  std::string joined = os.str();
  return joined;
}

}  // namespace translationModule
