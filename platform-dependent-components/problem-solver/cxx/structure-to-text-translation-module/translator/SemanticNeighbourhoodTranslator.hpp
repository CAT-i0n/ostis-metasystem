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

  virtual std::list<ScAddrVector> getSemanticNeighbourhoodTranslationElements(ScAddr const & node, ScAddr const & structure)
      const = 0;

  size_t hashCode() const;

  bool operator<(SemanticNeighbourhoodTranslator const & other) const;

protected:
  ScMemoryContext * context;

  std::string getEnglishContent(ScAddr const & linkNode) const;

  std::string getEnglishMainIdtf(ScAddr const & node) const;

  bool isInIgnoredKeynodes(ScAddr const & node) const;

  static bool isInStructure(ScAddr const & elementAddr, ScAddr const & structure);

  static bool anyIsInStructure(ScAddrVector const & elements, ScAddr const & structure);

private:
  ScIterator5Ptr getNrelMainIdtfIterator(ScAddr const & node) const;

  bool isEnglish(ScAddr const & node) const;
};

struct SemanticNeighbourhoodTranslatorCmp
{
  bool operator()(SemanticNeighbourhoodTranslator * first, SemanticNeighbourhoodTranslator * second) const
  {
    return *first < *second;
  }
};

}  // namespace translationModule
