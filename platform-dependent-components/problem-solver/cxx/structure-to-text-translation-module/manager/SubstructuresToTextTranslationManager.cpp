#include <memory>

#include "sc-agents-common/utils/CommonUtils.hpp"


#include "SubstructuresToTextTranslationManager.hpp"

namespace translationModule
{
SubstructuresToTextTranslationManager::SubstructuresToTextTranslationManager(ScMemoryContext * context)
  : context(context)
{
}

ScAddrVector SubstructuresToTextTranslationManager::manage(ScAddrVector const & processParameters) const
{
  return {};
}

}  // namespace translationModule
