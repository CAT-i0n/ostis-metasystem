#include "sc-memory/sc_addr.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"

#include "TranslationSearcher.hpp"

namespace translationModule
{
TranslationSearcher::TranslationSearcher(ScMemoryContext * context)
  : context(context)
{
}

ScAddrSet TranslationSearcher::getStructureEdges(ScAddr const & structure) const
{
  ScAddrSet edges;

  ScIterator3Ptr StructureEdgeAccessIterator = context->Iterator3(structure, ScType::EdgeAccessConstPosPerm, ScType::EdgeAccessConstPosPerm);
  while(StructureEdgeAccessIterator->Next())
  {
    edges.insert(StructureEdgeAccessIterator->Get(2));
  }
  ScIterator3Ptr StructureEdgeCommonIterator = context->Iterator3(structure, ScType::EdgeAccessConstPosPerm, ScType::EdgeDCommonConst);
  while(StructureEdgeCommonIterator->Next())
  {
    edges.insert(StructureEdgeCommonIterator->Get(2));
  }
  return edges;
}


ScAddrSet TranslationSearcher::getStructureNodes(ScAddr const & structure) const
{
  ScAddrSet nodes;

  ScIterator3Ptr StructureEdgeAccessIterator = context->Iterator3(structure, ScType::EdgeAccessConstPosPerm, ScType::NodeConst);
  while(StructureEdgeAccessIterator->Next())
  {
    nodes.insert(StructureEdgeAccessIterator->Get(2));
  }
  return nodes;
}

}  // namespace translationModule
