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
    // Static variables
    static int32_t m_selectedClassID;
    static int32_t m_existingCharacterIndex;
    static int32_t m_raceIndex;
    static CSimpleModel* m_charCustomizeFrame;
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
    static void SetCharCustomizeFrame(CSimpleModel* frame);
    static void SetCharCustomizeModel(char const* filename);
    static void ResetCharCustomizeInfo();
    static void GetRandomRaceAndSex(ComponentData* data);
    static void CalcClasses(uint32_t raceID);
    static void InitCharacterComponent(ComponentData* data, int32_t randomize);
    static void RandomizeCharFeatures();
    static void SetSelectedRace(int32_t raceID);
    static void SetSelectedSex(int32_t sexID);
    static void SetSelectedClass(int32_t classID);
};

#endif // GLUE_C_CHARACTER_CREATION_HPP
