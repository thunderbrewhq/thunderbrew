#include "glue/CCharacterCreation.hpp"
#include "glue/CCharacterComponent.hpp"
#include "glue/CCharacterSelection.hpp"
#include "ui/CSimpleModelFFX.hpp"
#include "model/CM2Model.hpp"
#include "model/CM2Shared.hpp"
#include "clientobject/Player_C.hpp"
#include "db/Db.hpp"

int32_t CCharacterCreation::m_selectedClassID;
int32_t CCharacterCreation::m_existingCharacterIndex;
CHARACTER_CREATE_INFO* CCharacterCreation::m_charPreferences[44];
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

    memset(CCharacterCreation::m_charPreferences, 0, sizeof(CCharacterCreation::m_charPreferences));

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

void CCharacterCreation::Shutdown() {
    if (CCharacterCreation::m_character) {
        CCharacterComponent::FreeComponent(CCharacterCreation::m_character);
        CCharacterCreation::m_character = nullptr;
    }

    // TODO

    for (size_t i = 0; i < 44; ++i) {
        DEL(CCharacterCreation::m_charPreferences[i]);
    }
}

void CCharacterCreation::SetCharCustomizeFrame(CSimpleModelFFX* frame) {
    CCharacterCreation::m_charCustomizeFrame = frame;
}

void CCharacterCreation::SetCharCustomizeModel(char const* filename) {
    if (!CCharacterCreation::m_charCustomizeFrame || !filename || !*filename) {
        return;
    }

    auto model = CCharacterCreation::m_charCustomizeFrame->m_model;
    if (model) {
        if (!SStrCmpI(filename, model->m_shared->m_filePath, STORM_MAX_STR)) {
            return;
        }
    }

    CCharacterCreation::m_charCustomizeFrame->SetModel(filename);
    // BYTE1(CCharacterCreation::m_charCustomizeFrame[1].m_onAttributeChange.unk) = 1;

    model = CCharacterCreation::m_charCustomizeFrame->m_model;
    if (!model) {
        return;
    }

    // LOBYTE(CCharacterCreation::m_charCustomizeFrame[1].m_onEnable.unk) = 1;
    // TODO: LightingCallback + Particles
    model->IsDrawable(1, 1);

    auto characterModel = CCharacterCreation::m_character->m_data.m_model;
    if (characterModel) {
        characterModel->AttachToParent(model, 0, nullptr, 0);
    }
}

void CCharacterCreation::ResetCharCustomizeInfo() {
    if (!CCharacterCreation::m_charCustomizeFrame) {
        return;
    }

    CCharacterCreation::m_existingCharacterIndex = -1;

    auto model = CCharacterCreation::m_charCustomizeFrame->m_model;
    if (model) {
        model->DetachAllChildrenById(0);
    }

    ComponentData data;
    CCharacterCreation::GetRandomRaceAndSex(&data);
    CCharacterCreation::CalcClasses(data.m_info.raceID);
    CCharacterCreation::InitCharacterComponent(&data, 1);

    auto classID = CCharacterCreation::GetRandomClassID();
    CCharacterCreation::SetSelectedClass(classID);

    data.m_info.classID = CCharacterCreation::m_selectedClassID;

    CCharacterCreation::m_raceIndex = -1;
    for (uint32_t i = 0; i < CCharacterCreation::m_races.Count(); ++i) {
        if (CCharacterCreation::m_races[i] == CCharacterCreation::m_character->m_data.m_info.raceID) {
            CCharacterCreation::m_raceIndex = i;
            break;
        }
    }

    // TODO: CNameGen::LoadNames
    CCharacterCreation::Sub4E6AE0(CCharacterCreation::m_character, 1);
}

void CCharacterCreation::GetRandomRaceAndSex(ComponentData* data) {
    // TODO
    // WORKAROUND
    data->m_info.sexID = 0;
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

void CCharacterCreation::Dress() {
    // TODO
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

    // TODO: LightingCallback + particles
    data->m_model->SetBoneSequence(0xFFFFFFFF, 0, 0, 0, 1.0f, 1, 1);

    data->m_unkFlag |= 2u;
    CCharacterCreation::m_character->Init(data, nullptr);

    if (randomize) {
        CCharacterCreation::RandomizeCharFeatures();
    }

    const auto& info = CCharacterCreation::m_character->m_data.m_info;
    CCharacterCreation::m_prevSkinIndex = info.skinID;
    CCharacterCreation::m_prevFaceIndex = info.faceID;
    CCharacterCreation::m_prevHairColorIndex = info.hairColorID;
    CCharacterCreation::m_prevHairStyleIndex = info.hairStyleID;
    CCharacterCreation::m_prevFacialFeatureIndex = info.facialFeatureID;

    CCharacterCreation::SetCharFacing(CCharacterCreation::m_charFacing);
    CCharacterCreation::Dress();

    CCharacterCreation::m_character->RenderPrep(0);

    auto frameModel = CCharacterCreation::m_charCustomizeFrame->m_model;
    if (frameModel) {
        auto model = CCharacterCreation::m_character->m_data.m_model;
        model->AttachToParent(frameModel, 0, nullptr, 0);
    }
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
    if (sexID < 0 || sexID >= 3) {
        return;
    }

    auto previousSex = CCharacterCreation::m_character->m_data.m_info.sexID;

    if (sexID == previousSex) {
        return;
    }

    auto raceID = CCharacterCreation::m_races[CCharacterCreation::m_raceIndex];

    auto preferences = CCharacterCreation::m_charPreferences[2 * raceID + previousSex];
    if (!preferences) {
        preferences = NEW(CHARACTER_CREATE_INFO);
        CCharacterCreation::m_charPreferences[2 * raceID + previousSex] = preferences;
    }

    CCharacterCreation::m_character->GetInfo(preferences);

    ComponentData data;
    data.m_info.raceID = CCharacterCreation::m_character->m_data.m_info.raceID;
    data.m_info.sexID = sexID;
    data.m_info.classID = CCharacterCreation::m_selectedClassID;

    if (CCharacterCreation::m_existingCharacterIndex >= 0) {
        auto display = CCharacterSelection::GetCharacterDisplay(CCharacterCreation::m_existingCharacterIndex);
        if (display && display->m_characterInfo.sexID == sexID &&
            (display->m_characterInfo.customizeFlags & 1)) {
            data.m_info.raceID = display->m_characterInfo.raceID;
            data.m_info.sexID = display->m_characterInfo.sexID;
            data.m_info.classID = display->m_characterInfo.classID;
            data.m_info.skinID = display->m_characterInfo.skinID;
            data.m_info.hairStyleID = display->m_characterInfo.hairStyleID;
            data.m_info.hairColorID = display->m_characterInfo.hairColorID;
            data.m_info.facialFeatureID = display->m_characterInfo.facialHairStyleID;
            data.m_info.faceID = display->m_characterInfo.faceID;

            CCharacterCreation::InitCharacterComponent(&data, 0);

            // TODO: CNameGen::LoadNames
            CCharacterCreation::Sub4E6AE0(CCharacterCreation::m_character, 1);
            return;
        }
    }

    preferences = CCharacterCreation::m_charPreferences[2 * raceID + sexID];
    if (preferences) {
        data.m_info = *preferences;
        data.m_info.classID = CCharacterCreation::m_selectedClassID;
        CCharacterComponent::ValidateComponentData(&data);
        CCharacterCreation::InitCharacterComponent(&data, 0);
    } else {
        data.m_info.raceID = CCharacterCreation::m_character->m_data.m_info.raceID;
        data.m_info.sexID = sexID;
        data.m_info.classID = CCharacterCreation::m_selectedClassID;
        CCharacterCreation::InitCharacterComponent(&data, 1);
    }

    // TODO: CNameGen::LoadNames
    CCharacterCreation::Sub4E6AE0(CCharacterCreation::m_character, 1);
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
    CCharacterCreation::Dress();

    CCharacterCreation::Sub4E6AE0(CCharacterCreation::m_character, 1);
}

void CCharacterCreation::CycleCharCustomization(CHAR_CUSTOMIZATION_TYPE customization, int32_t delta) {
    // TODO
}

void CCharacterCreation::RandomizeCharCustomization() {
    CCharacterCreation::RandomizeCharFeatures();
    CCharacterCreation::Dress();
    CCharacterCreation::Sub4E6AE0(CCharacterCreation::m_character, 1);
}

void CCharacterCreation::SetCharFacing(float facing) {
    CCharacterCreation::m_charFacing = facing;
    auto model = CCharacterCreation::m_character->m_data.m_model;
    if (model) {
        model->SetWorldTransform(C3Vector(), facing, 1.0f);
    }
}

void CCharacterCreation::CreateCharacter(const char* name) {
    // TODO
}

void CCharacterCreation::SetToExistingCharacter(uint32_t index) {
    // TODO
}

void CCharacterCreation::Sub4E6AE0(CCharacterComponent* component, int32_t a2) {
    // This method can be an analogue of CGlueLoading::StartLoad

    if (SFile::IsTrial) {
        // TODO
        return;
    }

    if (component) {
        component->RenderPrep(1);
        component->m_data.m_model->IsDrawable(1, 1);
    }
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
    for (uint32_t i = 0; i < CCharacterCreation::m_classes.Count(); ++i) {
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
