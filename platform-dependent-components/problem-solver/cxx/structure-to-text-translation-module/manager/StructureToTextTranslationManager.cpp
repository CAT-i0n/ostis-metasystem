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
  ScAddrVector const & keyElements = OrientedSetUtils::getElementsFromOrientedSet(context, processParameters[1]);
  for (auto const key : keyElements)
    SC_LOG_DEBUG("key " << context->HelperGetSystemIdtf(key));

  if (keyElements.empty())
    // find main element and add to key
    return {};

  ScAddr const & lang = TranslationKeynodes::lang_en;

  std::vector<std::string> translations = structureTranslator->TranslateStructure(structure, keyElements, lang);

  std::string const & translation = join(translations.cbegin(), translations.cend());

  SC_LOG_DEBUG(translation);
  // result = translator->translateStructe(structure, keyElements, notVisitedStructureEdges, notVisitedStructureNodes)

  return {};
}

std::string StructureToTextTranslationManager::join(
    std::vector<std::string>::const_iterator const & cbegin,
    std::vector<std::string>::const_iterator const & cend) const
{
  std::ostringstream os;
  std::copy(cbegin, cend, std::ostream_iterator<std::string>(os, ". "));
  std::string joined = os.str();
  return joined;
}

}  // namespace translationModule
