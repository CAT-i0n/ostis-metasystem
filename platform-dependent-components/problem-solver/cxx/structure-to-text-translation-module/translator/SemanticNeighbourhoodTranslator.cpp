#include "sc-agents-common/utils/CommonUtils.hpp"

#include "sc-agents-common/keynodes/coreKeynodes.hpp"
#include "keynodes/TranslationKeynodes.hpp"

#include "SemanticNeighbourhoodTranslator.hpp"

namespace translationModule
{
size_t SemanticNeighbourhoodTranslator::hashCode() const
{
  return std::hash<std::string>()(typeid(*this).name());
}

bool SemanticNeighbourhoodTranslator::operator<(SemanticNeighbourhoodTranslator const & other) const
{
  return this->hashCode() < other.hashCode();
}

ScIterator5Ptr SemanticNeighbourhoodTranslator::getNrelMainIdtfIterator(ScAddr const & node) const
{
  return context->Iterator5(
      node,
      ScType::EdgeDCommonConst,
      ScType::LinkConst,
      ScType::EdgeAccessConstPosPerm,
      scAgentsCommon::CoreKeynodes::nrel_main_idtf);
}

std::string SemanticNeighbourhoodTranslator::getMainIdtf(ScAddr const & node, ScAddr const & lang) const
{
  return utils::CommonUtils::getMainIdtf(context, node, {lang});
}

bool SemanticNeighbourhoodTranslator::isInIgnoredKeynodes(ScAddr const & node) const
{
  return context->HelperCheckEdge(
      TranslationKeynodes::translation_ignored_keynodes, node, ScType::EdgeAccessConstPosPerm);
}

bool SemanticNeighbourhoodTranslator::isInStructure(ScAddr const & elementAddr, ScAddr const & structure)
{
  // return structure.empty() || (structure.find(elementAddr) != structure.end());
  return true;
}

bool SemanticNeighbourhoodTranslator::anyIsInStructure(ScAddrVector const & elements, ScAddr const & structure)
{
  // if (structure.empty())
  //   return true;
  // for (auto const & element : elements)
  // {
  //   if (structure.find(element) != structure.end())
  //     return true;
  // }
  return true;
}
}  // namespace translationModule
