#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "TranslationKeynodes.generated.hpp"

namespace translationModule
{
class TranslationKeynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
  SC_PROPERTY(Keynode("action_subdivide_structure"), ForceCreate)
  static ScAddr action_subdivide_structure;

  SC_PROPERTY(Keynode("action_translate_structures"), ForceCreate)
  static ScAddr action_translate_structures;
};

}  // namespace translationModule
