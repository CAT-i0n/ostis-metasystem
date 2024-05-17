#include <memory>

#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/utils/AgentUtils.hpp"

#include "StructureSubdividingManager.hpp"

namespace translationModule
{
StructureSubdividingManager::StructureSubdividingManager(ScMemoryContext * context)
  : context(context)
{
}

ScAddrVector StructureSubdividingManager::manage(ScAddrVector const & processParameters) const
{
  return {};
}

}  // namespace translationModule
