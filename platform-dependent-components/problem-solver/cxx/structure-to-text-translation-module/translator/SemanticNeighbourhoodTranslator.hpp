#pragma once

#include <queue>
#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_addr.hpp"

namespace translationModule
{
using ScAddrSet = std::unordered_set<ScAddr, ScAddrHashFunc<uint32_t>>;
using ScAddrQueue = std::queue<ScAddr>;

class SemanticNeighbourhoodTranslator
{
public:
  explicit SemanticNeighbourhoodTranslator(ScMemoryContext * context)
    : context(context)
  {
  }

  virtual ~SemanticNeighbourhoodTranslator() = default;

  virtual std::vector<std::string> getSemanticNeighbourhoodTranslation(
      ScAddrQueue & structureSearchQueue,
      ScAddrSet & notVisitedStructureEdges,
      ScAddr const & structure, 
      ScAddr const & lang) const = 0;


  size_t hashCode() const;

  bool operator<(SemanticNeighbourhoodTranslator const & other) const;

protected:
  ScMemoryContext * context;

  bool isInIgnoredKeynodes(ScAddr const & node) const;

  static bool isInStructure(ScAddr const & elementAddr, ScAddr const & structure);

  static bool anyIsInStructure(ScAddrVector const & elements, ScAddr const & structure);

  std::string getMainIdtf(ScAddr const & node, ScAddr const & lang) const;

private:
  ScIterator5Ptr getNrelMainIdtfIterator(ScAddr const & node) const;
};

struct SemanticNeighbourhoodTranslatorCmp
{
  bool operator()(SemanticNeighbourhoodTranslator * first, SemanticNeighbourhoodTranslator * second) const
  {
    return *first < *second;
  }
};

}  // namespace translationModule
