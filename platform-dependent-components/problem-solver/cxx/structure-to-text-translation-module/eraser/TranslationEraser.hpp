#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_memory.hpp"

namespace translationModule
{
class TranslationEraser
{
public:
  explicit TranslationEraser(ScMemoryContext * context);


private:
  ScMemoryContext * context;
};

}  // namespace translationModule
