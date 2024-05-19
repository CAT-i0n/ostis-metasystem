#include "keynodes/TranslationKeynodes.hpp"

#include "agent/StructureToTextTranslationAgent.hpp"
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
    SC_AGENT_REGISTER(StructureToTextTranslationAgent)
  }

  return SC_RESULT_OK;
}


sc_result TranslationModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(StructureToTextTranslationAgent)
  return SC_RESULT_OK;
}

}  // namespace translationModule
