#pragma once

#include "sc-memory/kpm/sc_agent.hpp"

#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "manager/StructureToTextTranslationManager.hpp"

#include "StructureToTextTranslationAgent.generated.hpp"

namespace translationModule
{
class StructureToTextTranslationAgent : public ScAgent
{
  SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

private:
  std::unique_ptr<StructureToTextTranslationManager> structureToTextTranslationManager;

  bool checkActionClass(ScAddr const & actionAddr);

  void initFields();
};

}  // namespace translationModule
