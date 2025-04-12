#ifndef GLUE_C_CHARACTER_CREATION_HPP
#define GLUE_C_CHARACTER_CREATION_HPP

#include "net/Types.hpp"
#include <storm/Array.hpp>

class CSimpleModelFFX;
class CM2Model;

struct CharacterCreationDisplay {
    CHARACTER_CREATE_INFO m_characterInfo;
    CM2Model* m_characterModel;
};

class CCharacterCreation {
    public:
    // Static variables
    static float m_charFacing;
    static CharacterCreationDisplay m_character;

    // Static functions
    static void Initialize();
};

#endif // GLUE_C_CHARACTER_CREATION_HPP
