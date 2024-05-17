#include "keynodes/TranslationKeynodes.hpp"

#include "agent/SubstructuresToTextTranslationAgent.hpp"
#include "agent/StructureSubdividingAgent.hpp"

#include "TranslationModule.hpp"

namespace translationModule
{
SC_IMPLEMENT_MODULE(TranslationModule)

sc_result TranslationModule::InitializeImpl()
{
  if (!TranslationModule::InitGlobal())
  {
    SC_LOG_ERROR("TranslationModule is deactivated");
    return SC_RESULT_ERROR;
  }

  if (!TranslationKeynodes::InitGlobal())
  {
    SC_LOG_ERROR("TranslationKeynodes is deactivated");
    return SC_RESULT_ERROR;
  }
  else
  {
    SC_AGENT_REGISTER(SubstructuresToTextTranslationAgent)
    SC_AGENT_REGISTER(StructureSubdividingAgent)
  }

  return SC_RESULT_OK;
}


sc_result TranslationModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(SubstructuresToTextTranslationAgent)
  SC_AGENT_UNREGISTER(StructureSubdividingAgent)
  return SC_RESULT_OK;
}

}  // namespace translationModule
