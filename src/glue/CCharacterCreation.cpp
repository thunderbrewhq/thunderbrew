#include "glue/CCharacterCreation.hpp"

float CCharacterCreation::m_charFacing = 0.0;
CharacterCreationDisplay CCharacterCreation::m_character = {};

void CCharacterCreation::Initialize() {
    CCharacterCreation::m_charFacing = 0.0;
}
