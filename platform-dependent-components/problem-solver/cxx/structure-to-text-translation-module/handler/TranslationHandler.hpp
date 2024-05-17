#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_memory.hpp"



namespace translationModule
{
class TranslationHandler
{
public:
  explicit TranslationHandler(ScMemoryContext * context);

private:
  ScMemoryContext * context;

};
}  // namespace translationModule
