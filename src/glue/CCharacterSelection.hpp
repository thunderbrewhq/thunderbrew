#ifndef GLUE_C_CHARACTER_SELECTION_HPP
#define GLUE_C_CHARACTER_SELECTION_HPP

#include <storm/Array.hpp>

class CSimpleModelFFX;

struct CharacterSelectionDisplay {
    // TODO
};

class CCharacterSelection {
    public:
        // Static variables
        static TSGrowableArray<CharacterSelectionDisplay> s_characterList;
        static CSimpleModelFFX* s_modelFrame;
        static float s_charFacing;

        // Static functions
        static void RenderPrep();
        static void SetBackgroundModel(const char* modelPath);
        static void SetCharFacing(float facing);
};

#endif
