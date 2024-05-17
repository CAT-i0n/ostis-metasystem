#include "sc-memory/sc_addr.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "TranslationSearcher.hpp"

namespace translationModule
{
TranslationSearcher::TranslationSearcher(ScMemoryContext * context)
  : context(context)
{
}

}  // namespace translationModule
