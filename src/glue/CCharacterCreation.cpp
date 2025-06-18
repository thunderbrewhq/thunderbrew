#include "glue/CCharacterCreation.hpp"
#include "glue/CCharacterComponent.hpp"
#include "ui/CSimpleModelFFX.hpp"
#include "model/CM2Model.hpp"
#include "clientobject/Player_C.hpp"
#include "db/Db.hpp"

int32_t CCharacterCreation::m_selectedClassID;
int32_t CCharacterCreation::m_existingCharacterIndex;
int32_t CCharacterCreation::m_raceIndex;
CSimpleModelFFX* CCharacterCreation::m_charCustomizeFrame;
float CCharacterCreation::m_charFacing;
uint32_t CCharacterCreation::m_prevSkinIndex;
uint32_t CCharacterCreation::m_prevFaceIndex;
uint32_t CCharacterCreation::m_prevHairColorIndex;
uint32_t CCharacterCreation::m_prevHairStyleIndex;
uint32_t CCharacterCreation::m_prevFacialFeatureIndex;
CCharacterComponent* CCharacterCreation::m_character = nullptr;
TSGrowableArray<ChrClassesRec*> CCharacterCreation::m_classes;
TSGrowableArray<int32_t> CCharacterCreation::m_races;

void CCharacterCreation::Initialize() {
    CCharacterCreation::m_charFacing = 0.0;
    int32_t factionSwitch = 0;
    CCharacterCreation::m_charCustomizeFrame = nullptr;
    CCharacterCreation::m_existingCharacterIndex = -1;
    // TODO: memset
    int32_t factionSwitch2 = 0;

    bool weirdCondition = false;

    do {
        for (int32_t raceIndex = 0; raceIndex < g_chrRacesDB.GetNumRecords(); ++raceIndex) {
            auto raceRecord = g_chrRacesDB.GetRecordByIndex(raceIndex);
            if (!raceRecord || (raceRecord->m_flags & 1) != 0) {
                continue;
            }

            auto factionTemplateRecord = g_factionTemplateDB.GetRecord(raceRecord->m_factionID);
            if (!factionTemplateRecord) {
                continue;
            }

            for (int32_t factionGroupIndex = 0; factionGroupIndex < g_factionGroupDB.GetNumRecords(); ++factionGroupIndex) {
                auto factionGroupRecord = g_factionGroupDB.GetRecordByIndex(factionGroupIndex);
                if (!factionGroupRecord || factionGroupRecord->m_maskID == 0) {
                    continue;
                }

                if (((1 << factionGroupRecord->m_maskID) & factionTemplateRecord->m_factionGroup) == 0) {
                    continue;
                }

                if (SStrCmpI(factionGroupRecord->m_internalName, factionSwitch == 1 ? "Horde" : "Alliance", STORM_MAX_STR)) {
                    continue;
                }

                CCharacterCreation::m_races.Add(1, &raceRecord->m_ID);

                factionSwitch = factionSwitch2;
            }
        }

        weirdCondition = factionSwitch++ == -1;
        factionSwitch2 = factionSwitch;
    } while (weirdCondition || factionSwitch == 1);
}

void CCharacterCreation::SetCharCustomizeFrame(CSimpleModelFFX* frame) {
    CCharacterCreation::m_charCustomizeFrame = frame;
}

void CCharacterCreation::SetCharCustomizeModel(char const* filename) {
    if (!CCharacterCreation::m_charCustomizeFrame || !filename || !*filename) {
        return;
    }

    // TODO
    CCharacterCreation::m_charCustomizeFrame->SetModel(filename);
}

void CCharacterCreation::ResetCharCustomizeInfo() {
    if (!CCharacterCreation::m_charCustomizeFrame) {
        return;
    }

    CCharacterCreation::m_existingCharacterIndex = -1;

    // TODO: CM2Model__DetachAllChildrenById

    ComponentData data;
    CCharacterCreation::GetRandomRaceAndSex(&data);
    CCharacterCreation::CalcClasses(data.m_info.raceID);
    CCharacterCreation::InitCharacterComponent(&data, 1);

    CCharacterCreation::SetSelectedClass(CCharacterCreation::GetRandomClassID());

    data.m_info.classID = CCharacterCreation::m_selectedClassID;

    CCharacterCreation::m_raceIndex = -1;
    for (uint32_t i = 0; i < CCharacterCreation::m_races.Count(); ++i) {
        if (CCharacterCreation::m_races[i] == CCharacterCreation::m_character->m_data.m_info.raceID) {
            CCharacterCreation::m_raceIndex = i;
            break;
        }
    }

    // TODO: CNameGen::LoadNames
}

void CCharacterCreation::GetRandomRaceAndSex(ComponentData* data) {
    // TODO
    // WORKAROUND
    data->m_info.raceID = 1;
}

void CCharacterCreation::CalcClasses(uint32_t raceID) {
    uint32_t count = 0;

    for (int32_t i = 0; i < g_charBaseInfoDB.GetNumRecords(); ++i) {
        auto record = g_charBaseInfoDB.GetRecordByIndex(i);
        if (record && record->m_raceID == raceID) {
            ++count;
        }
    }

    CCharacterCreation::m_classes.SetCount(count);

    uint32_t index = 0;

    for (int32_t i = 0; i < g_charBaseInfoDB.GetNumRecords(); ++i) {
        auto record = g_charBaseInfoDB.GetRecordByIndex(i);
        if (!record || record->m_raceID != raceID) {
            continue;
        }

        CCharacterCreation::m_classes[index] = g_chrClassesDB.GetRecord(record->m_classID);
        ++index;
    }
}

void CCharacterCreation::InitCharacterComponent(ComponentData* data, int32_t randomize) {
    auto record = Player_C_GetModelName(data->m_info.raceID, data->m_info.sexID);
    if (!record || !record->m_modelName[0]) {
        return;
    }

    if (CCharacterCreation::m_character) {
        auto model = CCharacterCreation::m_character->m_data.m_model;
        if (model->m_attachParent) {
            model->DetachFromParent();
        }
        CCharacterComponent::FreeComponent(CCharacterCreation::m_character);
    }

    CCharacterCreation::m_character = CCharacterComponent::AllocComponent();

    auto scene = CCharacterCreation::m_charCustomizeFrame->GetScene();
    data->m_model = scene->CreateModel(record->m_modelName, 0);
    if (!data->m_model) {
        return;
    }

    data->m_unkFlag |= 2u;
    CCharacterCreation::m_character->Init(data, nullptr);

    if (randomize) {
        CCharacterCreation::RandomizeCharFeatures();
    }

    // TODO
}

void CCharacterCreation::RandomizeCharFeatures() {
    CCharacterCreation::m_character->SetRandomSkin();
    CCharacterCreation::m_character->SetRandomHairColor();
    CCharacterCreation::m_character->SetRandomHairStyle();
    CCharacterCreation::m_character->SetRandomFace();
    CCharacterCreation::m_character->SetRandomFacialFeature();

    const auto& info = CCharacterCreation::m_character->m_data.m_info;
    CCharacterCreation::m_prevSkinIndex = info.skinID;
    CCharacterCreation::m_prevFaceIndex = info.faceID;
    CCharacterCreation::m_prevHairColorIndex = info.hairColorID;
    CCharacterCreation::m_prevHairStyleIndex = info.hairStyleID;
    CCharacterCreation::m_prevFacialFeatureIndex = info.facialFeatureID;
}

void CCharacterCreation::SetSelectedRace(int32_t raceID) {
    // TODO
}

void CCharacterCreation::SetSelectedSex(int32_t sexID) {
    // TODO
}

void CCharacterCreation::SetSelectedClass(int32_t classID) {
    if (!CCharacterCreation::IsClassValid(classID)) {
        return;
    }

    CCharacterCreation::m_selectedClassID = classID;
    ComponentData data;
    data.m_info = CCharacterCreation::m_character->m_data.m_info;
    data.m_info.classID = classID;
    CCharacterComponent::ValidateComponentData(&data);
    CCharacterCreation::InitCharacterComponent(&data, 0);
    // TODO: sub_4E0FD0
    // TODO: sub_4E6AE0((int)CCharacterCreation::m_character, 1);
}

void CCharacterCreation::CycleCharCustomization(CHAR_CUSTOMIZATION_TYPE customization, int32_t delta) {
    // TODO
}

void CCharacterCreation::RandomizeCharCustomization() {
    CCharacterCreation::RandomizeCharFeatures();
    // TODO
}

void CCharacterCreation::SetCharFacing(float facing) {
    // TODO
}

void CCharacterCreation::CreateCharacter(const char* name) {
    // TODO
}

void CCharacterCreation::SetToExistingCharacter(uint32_t index) {
    // TODO
}

int32_t CCharacterCreation::IsRaceClassValid(int32_t raceID, int32_t classID) {
    for (int32_t i = 0; i < g_charBaseInfoDB.GetNumRecords(); ++i) {
        auto record = g_charBaseInfoDB.GetRecordByIndex(i);
        if (record && record->m_raceID == raceID && record->m_classID == classID) {
            return 1;
        }
    }

    return 0;
}

int32_t CCharacterCreation::IsClassValid(int32_t classID) {
    for (uint32_t i = 0; i < CCharacterCreation::m_classes.Count(); i) {
        auto record = CCharacterCreation::m_classes[i];
        if (record && record->m_ID == classID) {
            return 1;
        }
    }

    return 0;
}

int32_t CCharacterCreation::GetRandomClassID() {
    return 1;
}
