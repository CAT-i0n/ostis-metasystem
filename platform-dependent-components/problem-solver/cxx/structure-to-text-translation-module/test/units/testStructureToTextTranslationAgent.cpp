#include <boost/filesystem.hpp>

#include "sc-memory/kpm/sc_agent.hpp"
#include "sc-memory/sc_wait.hpp"
#include "sc-memory/utils/sc_log.hpp"
#include "sc-builder/src/scs_loader.hpp"
#include "sc_test.hpp"

#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/AgentUtils.hpp"

#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include "keynodes/TranslationKeynodes.hpp"

#include "agent/StructureToTextTranslationAgent.hpp"

using namespace translationModule;

namespace testSubstructuresToTextTranslation
{
ScsLoader loader;
const std::string TEST_FILES_DIR_PATH = TEST_SRC_PATH "/testStructures/substructuresToTextTranslation/";
const int WAIT_TIME = 5000;

using SubstructureToTextTranslationTest = ScMemoryTest;

void initializeClasses()
{
  scAgentsCommon::CoreKeynodes::InitGlobal();
  translationModule::TranslationKeynodes::InitGlobal();

  ScAgentInit(true);
  SC_AGENT_REGISTER(translationModule::StructureToTextTranslationAgent)
}

void deinitializeClasses()
{
  SC_AGENT_UNREGISTER(translationModule::StructureToTextTranslationAgent)
}

void loadFilesFromDir(ScMemoryContext & context, std::string const & path)
{
  for (boost::filesystem::directory_iterator itr(path); itr != boost::filesystem::directory_iterator(); itr++)
  {
    if (is_directory(itr->status()))
      loadFilesFromDir(context, itr->path().string());
    else if (is_regular_file(itr->status()))
      loader.loadScsFile(context, itr->path().string());
  }
}

TEST_F(SubstructureToTextTranslationTest, ActionDoesntHaveParameters)
{
  ScMemoryContext & ctx = *m_ctx;

  loader.loadScsFile(ctx, TEST_FILES_DIR_PATH + "actionDoesntHaveParameters.scs");
  ScAddr const & test_action_node = ctx.HelperFindBySystemIdtf("test_question_node");
  EXPECT_TRUE(ctx.IsElement(test_action_node));

  initializeClasses();

  EXPECT_TRUE(utils::AgentUtils::applyAction(&ctx, test_action_node, WAIT_TIME));

  EXPECT_TRUE(ctx.HelperCheckEdge(
      scAgentsCommon::CoreKeynodes::question_finished_unsuccessfully,
      test_action_node,
      ScType::EdgeAccessConstPosPerm));

  deinitializeClasses();
}

TEST_F(SubstructureToTextTranslationTest, Test1)
{
  ScMemoryContext & ctx = *m_ctx;

  loader.loadScsFile(ctx, TEST_FILES_DIR_PATH + "test1.scs");
  ScAddr const & test_action_node = ctx.HelperFindBySystemIdtf("test_question_node");
  EXPECT_TRUE(ctx.IsElement(test_action_node));

  initializeClasses();

  EXPECT_TRUE(utils::AgentUtils::applyAction(&ctx, test_action_node, WAIT_TIME));

  EXPECT_TRUE(ctx.HelperCheckEdge(
      scAgentsCommon::CoreKeynodes::question_finished_unsuccessfully,
      test_action_node,
      ScType::EdgeAccessConstPosPerm));

  deinitializeClasses();
}


}  // namespace testSubstructuresToTextTranslation
