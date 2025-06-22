#ifndef GLUE_C_CHARACTER_CREATION_HPP
#define GLUE_C_CHARACTER_CREATION_HPP

#include "net/Types.hpp"
#include <storm/Array.hpp>

class CSimpleModel;
class CSimpleModelFFX;
class CM2Model;
class ComponentData;
class CCharacterComponent;
class ChrClassesRec;


class CCharacterCreation {
    public:
    enum CHAR_CUSTOMIZATION_TYPE {
        CHAR_CUSTOMIZATION_SKIN           = 0,
        CHAR_CUSTOMIZATION_FACE           = 1,
        CHAR_CUSTOMIZATION_HAIR_STYLE     = 2,
        CHAR_CUSTOMIZATION_HAIR_COLOR     = 3,
        CHAR_CUSTOMIZATION_FACIAL_FEATURE = 4
    };

    public:
    // Static variables
    static int32_t m_selectedClassID;
    static int32_t m_existingCharacterIndex;
    static CHARACTER_PREFERENCES* m_charPreferences[44];
    static int32_t m_raceIndex;
    static CSimpleModelFFX* m_charCustomizeFrame;
    static float m_charFacing;
    static uint32_t m_prevSkinIndex;
    static uint32_t m_prevFaceIndex;
    static uint32_t m_prevHairColorIndex;
    static uint32_t m_prevHairStyleIndex;
    static uint32_t m_prevFacialFeatureIndex;
    static CCharacterComponent* m_character;
    static TSGrowableArray<ChrClassesRec*> m_classes;
    static TSGrowableArray<int32_t> m_races;

    // Static functions
    static void Initialize();
    static void Shutdown();
    static void SetCharCustomizeFrame(CSimpleModelFFX* frame);
    static void SetCharCustomizeModel(char const* filename);
    static void ResetCharCustomizeInfo();
    static void GetRandomRaceAndSex(ComponentData* data);
    static void CalcClasses(uint32_t raceID);
    static void Dress();
    static void InitCharacterComponent(ComponentData* data, int32_t randomize);
    static void RandomizeCharFeatures();
    static void SetSelectedRace(int32_t raceIndex);
    static void SetSelectedSex(int32_t sexID);
    static void SetSelectedClass(int32_t classID);
    static void CycleCharCustomization(CHAR_CUSTOMIZATION_TYPE customization, int32_t delta);
    static void RandomizeCharCustomization();
    static void SetCharFacing(float facing);
    static void CreateCharacter(const char* name);
    static void SetToExistingCharacter(uint32_t index);
    static void Sub4E6AE0(CCharacterComponent* component, int32_t a2);
    static int32_t IsRaceClassValid(int32_t raceID, int32_t classID);
    static int32_t IsClassValid(int32_t classID);
    static int32_t GetRandomClassID();
};

#endif // GLUE_C_CHARACTER_CREATION_HPP
