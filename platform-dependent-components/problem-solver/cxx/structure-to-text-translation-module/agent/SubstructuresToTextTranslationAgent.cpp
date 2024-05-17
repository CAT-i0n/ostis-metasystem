#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "keynodes/TranslationKeynodes.hpp"
#include "manager/SubstructuresToTextTranslationManager.hpp"

#include "SubstructuresToTextTranslationAgent.hpp"

namespace translationModule
{
SC_AGENT_IMPLEMENTATION(SubstructuresToTextTranslationAgent)
{
  ScAddr actionAddr = otherAddr;

  if (!checkActionClass(actionAddr))
    return SC_RESULT_OK;

  SC_LOG_DEBUG("SubstructuresToTextTranslationAgent started");

  ScAddrVector answerVector;
  initFields();

  ScAddr const & translationLinkAddr =
      utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionAddr, scAgentsCommon::CoreKeynodes::rrel_1);
  if (!m_memoryCtx.IsElement(translationLinkAddr))
  {
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    SC_LOG_DEBUG(
        "SubstructuresToTextTranslationAgent: translation node is not found "
        "\nSubstructuresToTextTranslationAgent finished with errors");
    return SC_RESULT_ERROR;
  }

  try
  {
    answerVector = substructuresToTextTranslationManager->manage({translationLinkAddr});
  }
  catch (utils::ScException & ex)
  {
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    SC_LOG_DEBUG(ex.Message() << "\nSubstructuresToTextTranslationAgent finished with errors");
    return SC_RESULT_ERROR;
  }

  if (answerVector.empty())
  {
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    SC_LOG_DEBUG("SubstructuresToTextTranslationAgent finished unsuccessfully");
    return SC_RESULT_ERROR;
  }

  utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerVector, true);
  SC_LOG_DEBUG("SubstructuresToTextTranslationAgent finished");
  return SC_RESULT_OK;
}

void SubstructuresToTextTranslationAgent::initFields()
{
  this->substructuresToTextTranslationManager = std::make_unique<SubstructuresToTextTranslationManager>(&m_memoryCtx);
}

bool SubstructuresToTextTranslationAgent::checkActionClass(ScAddr const & actionAddr)
{
  return m_memoryCtx.HelperCheckEdge(
      TranslationKeynodes::action_subdivide_structure, actionAddr, ScType::EdgeAccessConstPosPerm);
}

}  // namespace translationModule
