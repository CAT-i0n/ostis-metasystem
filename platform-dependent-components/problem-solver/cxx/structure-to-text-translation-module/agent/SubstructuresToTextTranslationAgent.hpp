#pragma once

#include "sc-memory/kpm/sc_agent.hpp"

#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "manager/SubstructuresToTextTranslationManager.hpp"

#include "SubstructuresToTextTranslationAgent.generated.hpp"

namespace translationModule
{
class SubstructuresToTextTranslationAgent : public ScAgent
{
  SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

private:
  std::unique_ptr<SubstructuresToTextTranslationManager> substructuresToTextTranslationManager;

  bool checkActionClass(ScAddr const & actionAddr);

  void initFields();
};

}  // namespace translationModule
