#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "keynodes/TranslationKeynodes.hpp"

#include "StructureToTextTranslationAgent.hpp"

namespace translationModule
{
SC_AGENT_IMPLEMENTATION(StructureToTextTranslationAgent)
{
  ScAddr actionAddr = otherAddr;

  if (!checkActionClass(actionAddr))
    return SC_RESULT_OK;

  SC_LOG_DEBUG("StructureToTextTranslationAgent started");

  ScAddrVector answerVector;
  initFields();

  ScAddr const & structureAddr =
      utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionAddr, scAgentsCommon::CoreKeynodes::rrel_1);

  ScAddr const & keyElementsSetAddr =
      utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionAddr, scAgentsCommon::CoreKeynodes::rrel_2);
  if (!m_memoryCtx.IsElement(structureAddr))
  {
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    SC_LOG_DEBUG(
        "StructureToTextTranslationAgent: structureAddr node is not found "
        "\nStructureToTextTranslationAgent finished with errors");
    return SC_RESULT_ERROR;
  }
  try
  {
    answerVector = structureToTextTranslationManager->manage({structureAddr, keyElementsSetAddr});
  }
  catch (utils::ScException & ex)
  {
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    SC_LOG_DEBUG(ex.Message() << "\nStructureToTextTranslationAgent finished with errors");
    return SC_RESULT_ERROR;
  }

  if (answerVector.empty())
  {
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    SC_LOG_DEBUG("StructureToTextTranslationAgent: empty structure was generated");
    return SC_RESULT_ERROR;
  }
    
  utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerVector, true);
  SC_LOG_DEBUG("StructureToTextTranslationAgent finished");
  return SC_RESULT_OK;
}

void StructureToTextTranslationAgent::initFields()
{
  this->structureToTextTranslationManager = std::make_unique<StructureToTextTranslationManager>(&m_memoryCtx);
}

bool StructureToTextTranslationAgent::checkActionClass(ScAddr const & actionAddr)
{
  return m_memoryCtx.HelperCheckEdge(
      TranslationKeynodes::action_translate_structures, actionAddr, ScType::EdgeAccessConstPosPerm);
}

}  // namespace translationModule
