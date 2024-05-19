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
  inline static ScAddr action_subdivide_structure;

  SC_PROPERTY(Keynode("action_translate_structures"), ForceCreate)
  inline static ScAddr action_translate_structures;

  SC_PROPERTY(Keynode("rrel_last"), ForceCreate)
  inline static ScAddr rrel_last;

  SC_PROPERTY(Keynode("nrel_basic_sequence"), ForceCreate)
  inline static ScAddr nrel_basic_sequence;

  SC_PROPERTY(Keynode("translation_ignored_keynodes"), ForceCreate)
  inline static ScAddr translation_ignored_keynodes;

  SC_PROPERTY(Keynode("lang_en"), ForceCreate)
  inline static ScAddr lang_en;

  SC_PROPERTY(Keynode("lang_ru"), ForceCreate)
  inline static ScAddr lang_ru;
};

}  // namespace translationModule
