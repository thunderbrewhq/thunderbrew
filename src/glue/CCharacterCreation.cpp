#include "glue/CCharacterCreation.hpp"
#include "glue/CCharacterComponent.hpp"
#include "ui/CSimpleModelFFX.hpp"
#include "model/CM2Model.hpp"
#include "clientobject/Player_C.hpp"
#include "db/Db.hpp"

int32_t CCharacterCreation::m_existingCharacterIndex;
int32_t CCharacterCreation::m_raceIndex;
CSimpleModel* CCharacterCreation::m_charCustomizeFrame;
float CCharacterCreation::m_charFacing;
uint32_t CCharacterCreation::m_prevSkinIndex;
uint32_t CCharacterCreation::m_prevFaceIndex;
uint32_t CCharacterCreation::m_prevHairColorIndex;
uint32_t CCharacterCreation::m_prevHairStyleIndex;
uint32_t CCharacterCreation::m_prevFacialFeatureIndex;
CCharacterComponent* CCharacterCreation::m_character = nullptr;
TSGrowableArray<uint32_t> CCharacterCreation::m_races;

void CCharacterCreation::Initialize() {
    CCharacterCreation::m_charFacing = 0.0;
    CCharacterCreation::m_charCustomizeFrame = nullptr;
    CCharacterCreation::m_existingCharacterIndex = -1;
}

void CCharacterCreation::SetCharCustomizeFrame(CSimpleModel* frame) {
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

    // TODO

    CCharacterCreation::m_raceIndex = -1;

    // TODO
}

void CCharacterCreation::GetRandomRaceAndSex(ComponentData* data) {
    // TODO
    // WORKAROUND
    data->m_info.raceID = 1;
}

void CCharacterCreation::CalcClasses(uint32_t raceID) {
}

void CCharacterCreation::InitCharacterComponent(ComponentData* data, int32_t randomize) {
    auto record = Player_C_GetModelName(data->m_info.raceID, data->m_info.sexID);
    if (!record || !record->m_modelName[0]) {
        return;
    }

    if (CCharacterCreation::m_character) {
        auto model = CCharacterCreation::m_character->m_data.m_model;
        if (model->m_attachParent) {
            // TODO: model->DetachFromParent();
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
