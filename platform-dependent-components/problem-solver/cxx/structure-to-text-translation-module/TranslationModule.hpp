#pragma once

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

#include "TranslationModule.generated.hpp"

namespace translationModule
{
class TranslationModule : public ScModule
{
  SC_CLASS(LoadOrder(150))
  SC_GENERATED_BODY()

  sc_result InitializeImpl() override;

  sc_result ShutdownImpl() override;
};

}  // namespace translationModule
