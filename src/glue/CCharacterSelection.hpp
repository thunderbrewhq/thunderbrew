#ifndef GLUE_C_CHARACTER_SELECTION_HPP
#define GLUE_C_CHARACTER_SELECTION_HPP

#include <storm/Array.hpp>
#include "net/Types.hpp"

class CSimpleModelFFX;
class CM2Model;
class CCharacterComponent;

struct CharacterSelectionDisplay {
    CharacterSelectionDisplay() = default;

    CHARACTER_INFO m_characterInfo = {};
    CCharacterComponent* m_component = nullptr;
    CM2Model* m_petModel = nullptr;
};

class CCharacterSelection {
    public:
        // Static variables
        static CSimpleModelFFX* m_modelFrame;
        static uint32_t m_characterCount;
        static float m_charFacing;
        static uint32_t m_restrictHuman;
        static uint32_t m_restrictDwarf;
        static uint32_t m_restrictGnome;
        static uint32_t m_restrictNightElf;
        static uint32_t m_restrictDraenei;
        static uint32_t m_restrictOrc;
        static uint32_t m_restrictTroll;
        static uint32_t m_restrictTauren;
        static uint32_t m_restrictUndead;
        static uint32_t m_restrictBloodElf;
        static TSGrowableArray<CharacterSelectionDisplay> s_characterList;
        static int32_t m_selectionIndex;

        // Static functions
        static void Initialize();
        static void RenderPrep();
        static void SetBackgroundModel(const char* modelPath);
        static void EnumerateCharactersCallback(CHARACTER_INFO& info, void* param);
        static void ShowCharacter();
        static void SetCharFacing(float facing);
        static void ClearCharacterList();
        static void UpdateCharacterList();
        static uint32_t GetNumCharacters();
};

#endif
