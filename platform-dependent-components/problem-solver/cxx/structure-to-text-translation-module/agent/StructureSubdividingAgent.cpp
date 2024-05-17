#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "keynodes/TranslationKeynodes.hpp"

#include "StructureSubdividingAgent.hpp"

namespace translationModule
{
SC_AGENT_IMPLEMENTATION(StructureSubdividingAgent)
{
  ScAddr actionAddr = otherAddr;

  if (!checkActionClass(actionAddr))
    return SC_RESULT_OK;

  SC_LOG_DEBUG("StructureSubdividingAgent started");

  ScAddrVector answerVector;
  initFields();

  ScAddr const & structureAddr =
      utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionAddr, scAgentsCommon::CoreKeynodes::rrel_1);

  ScAddr const & keyElementsSetAddr =
      utils::IteratorUtils::getAnyByOutRelation(&m_memoryCtx, actionAddr, scAgentsCommon::CoreKeynodes::rrel_2);
  // if (!m_memoryCtx.IsElement(structureAddr))
  // {
  //   utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
  //   SC_LOG_DEBUG(
  //       "StructureSubdividingAgent: structureAddr node is not found "
  //       "\nStructureSubdividingAgent finished with errors");
  //   return SC_RESULT_ERROR;
  // }
  try
  {
    answerVector = structureSubdividingManager->manage({structureAddr, keyElementsSetAddr});
  }
  catch (utils::ScException & ex)
  {
    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, false);
    SC_LOG_DEBUG(ex.Message() << "\nStructureSubdividingAgent finished with errors");
    return SC_RESULT_ERROR;
  }

  if (answerVector.empty())
    SC_LOG_DEBUG("StructureSubdividingAgent didn't find any translations");
  utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerVector, true);
  SC_LOG_DEBUG("StructureSubdividingAgent finished");
  return SC_RESULT_OK;
}

void StructureSubdividingAgent::initFields()
{
  this->structureSubdividingManager = std::make_unique<StructureSubdividingManager>(&m_memoryCtx);
}

bool StructureSubdividingAgent::checkActionClass(ScAddr const & actionAddr)
{
  return m_memoryCtx.HelperCheckEdge(
      TranslationKeynodes::action_translate_structures, actionAddr, ScType::EdgeAccessConstPosPerm);
}

}  // namespace translationModule
