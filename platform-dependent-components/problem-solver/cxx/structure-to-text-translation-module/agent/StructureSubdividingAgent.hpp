#pragma once

#include "sc-memory/kpm/sc_agent.hpp"

#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "manager/StructureSubdividingManager.hpp"

#include "StructureSubdividingAgent.generated.hpp"

namespace translationModule
{
class StructureSubdividingAgent : public ScAgent
{
  SC_CLASS(Agent, Event(scAgentsCommon::CoreKeynodes::question_initiated, ScEvent::Type::AddOutputEdge))
  SC_GENERATED_BODY()

private:
  std::unique_ptr<StructureSubdividingManager> structureSubdividingManager;

  bool checkActionClass(ScAddr const & actionAddr);

  void initFields();
};

}  // namespace translationModule
