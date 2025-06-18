#include "glue/CCharacterSelection.hpp"
#include "model/CM2Model.hpp"
#include "model/CM2Shared.hpp"
#include "ui/CSimpleModelFFX.hpp"
#include "client/ClientServices.hpp"
#include "client/Client.hpp"
#include "console/CVar.hpp"
#include "net/Connection.hpp"
#include "clientobject/Player_C.hpp"
#include "db/Db.hpp"
#include "glue/CGlueMgr.hpp"
#include "glue/CCharacterComponent.hpp"

CSimpleModelFFX* CCharacterSelection::m_modelFrame = nullptr;
uint32_t CCharacterSelection::m_characterCount = 0;
float CCharacterSelection::m_charFacing = 0.0f;
uint32_t CCharacterSelection::m_restrictHuman = 0;
uint32_t CCharacterSelection::m_restrictDwarf = 0;
uint32_t CCharacterSelection::m_restrictGnome = 0;
uint32_t CCharacterSelection::m_restrictNightElf = 0;
uint32_t CCharacterSelection::m_restrictDraenei = 0;
uint32_t CCharacterSelection::m_restrictOrc = 0;
uint32_t CCharacterSelection::m_restrictTroll = 0;
uint32_t CCharacterSelection::m_restrictTauren = 0;
uint32_t CCharacterSelection::m_restrictUndead = 0;
uint32_t CCharacterSelection::m_restrictBloodElf = 0;
TSGrowableArray<CharacterSelectionDisplay> CCharacterSelection::s_characterList;
int32_t CCharacterSelection::m_selectionIndex = 0;


void CCharacterSelection::Initialize() {
    // Empty method
}

void CCharacterSelection::RenderPrep() {
    auto index = CCharacterSelection::m_selectionIndex;
    if (index < 0 || index >= CCharacterSelection::GetNumCharacters()) {
        return;
    }

    auto component = CCharacterSelection::s_characterList[index].m_component;
    if (component) {
        component->RenderPrep(0);
    }
}

void CCharacterSelection::SetBackgroundModel(const char* modelPath) {
    if (!CCharacterSelection::m_modelFrame || !modelPath || !*modelPath) {
        return;
    }

    auto model = CCharacterSelection::m_modelFrame->m_model;

    // Check if already set
    if (model && !SStrCmpI(modelPath, model->m_shared->m_filePath, STORM_MAX_STR)) {
        return;
    }

    CCharacterSelection::m_modelFrame->SetModel(modelPath);

    // TODO BYTE1(CCharacterSelection::m_modelFrame->simplemodelffx_dword510[3]) = 1;

    model = CCharacterSelection::m_modelFrame->m_model;

    if (model) {
        // TODO lighting callback + arg

        model->IsDrawable(1, 1);
    }
}

void CCharacterSelection::EnumerateCharactersCallback(CHARACTER_INFO& info, void* param) {
    auto character = CCharacterSelection::s_characterList.New();
    character->m_characterInfo = info;
    // TODO: LoadAddOnEnableState(a1 + 8);
}

void CCharacterSelection::ShowCharacter() {
    auto index = CCharacterSelection::m_selectionIndex;
    if (index < 0 || index >= CCharacterSelection::GetNumCharacters()) {
        return;
    }

    if (CCharacterSelection::m_modelFrame) {
        auto model = CCharacterSelection::m_modelFrame->m_model;
        if (model) {
            model->DetachAllChildrenById(0);
            model->DetachAllChildrenById(1);
        }
    }

    CCharacterSelection::m_charFacing = 0.0;

    auto& character = CCharacterSelection::s_characterList[index];
    if (character.m_component) {
        // TODO: info = DayNightGetInfo();
        float v42;
        if (character.m_characterInfo.flags & 0x2000) {
            // FFX::SetEffect(CGlueMgr__m_deathEffect);
            v42 = 0.15f;
        } else {
            // FFX::SetEffect(CGlueMgr__m_glowEffect);
            v42 = 0.4f;
        }
        // *((float *)info + 75) = v42;

        if (CCharacterSelection::m_modelFrame->m_model) {
            character.m_component->m_data.m_model->AttachToParent(
                CCharacterSelection::m_modelFrame->m_model,
                0,
                nullptr,
                0);

            if (character.m_petModel) {
                character.m_petModel->AttachToParent(
                    CCharacterSelection::m_modelFrame->m_model, 1, nullptr,0);
            }
        }

        // TODO: sub_4E6AE0((int)s_charList.m_data[selectionIndex2].m_component, v5);
        return;
    }

    auto rec = Player_C_GetModelName(character.m_characterInfo.raceID, character.m_characterInfo.sexID);
    if (!rec || !rec->m_modelName) {
        return;
    }

    auto scene = CCharacterSelection::m_modelFrame->GetScene();
    auto model = scene->CreateModel(rec->m_modelName, 0);

    ComponentData componentData(character.m_characterInfo);
    componentData.m_model = model;
    componentData.m_unkFlag |= 2;

    character.m_component = CCharacterComponent::AllocComponent();
    character.m_component->Init(&componentData, 0);

    // TODO: set model ribbon emitters & particles
    model->SetBoneSequence(0xFFFFFFFF, 0, 0xFFFFFFFF, 0, 1.0f, 1, 1);


    // Handle pet model
    // Handle hand items

    ++CCharacterSelection::m_characterCount;

    // DUPLICATE (goto in the OG)
    if (character.m_component) {
        // TODO: info = DayNightGetInfo();
        float v42;
        if (character.m_characterInfo.flags & 0x2000) {
            // FFX::SetEffect(CGlueMgr__m_deathEffect);
            v42 = 0.15f;
        } else {
            // FFX::SetEffect(CGlueMgr__m_glowEffect);
            v42 = 0.4f;
        }
        // *((float *)info + 75) = v42;

        if (CCharacterSelection::m_modelFrame->m_model) {
            character.m_component->m_data.m_model->AttachToParent(
                CCharacterSelection::m_modelFrame->m_model,
                0,
                nullptr,
                0);

            if (character.m_petModel) {
                character.m_petModel->AttachToParent(
                    CCharacterSelection::m_modelFrame->m_model, 1, nullptr, 0);
            }
        }

        // TODO: sub_4E6AE0((int)s_charList.m_data[selectionIndex2].m_component, v5);
        return;
    }
}

void CCharacterSelection::SetCharFacing(float facing) {
    if (!CCharacterSelection::m_characterCount) {
        return;
    }

    CCharacterSelection::m_charFacing = facing;

    if (!CCharacterSelection::GetNumCharacters()) {
        return;
    }

    auto index = CCharacterSelection::m_selectionIndex;
    auto component = CCharacterSelection::s_characterList[index].m_component;
    if (component && component->m_data.m_model) {
        component->m_data.m_model->SetWorldTransform(C3Vector(), facing, 1.0);
    }
}

void CCharacterSelection::ClearCharacterList() {
    CCharacterSelection::s_characterList.Clear();
    if (CCharacterSelection::m_modelFrame) {
        auto model = CCharacterSelection::m_modelFrame->m_model;
        if (model) {
            model->DetachAllChildrenById(0);
            model->DetachAllChildrenById(1);
        }
    }

    CCharacterSelection::m_selectionIndex = 0;
    CCharacterSelection::ShowCharacter();

    FrameScript_SignalEvent(8, "%d", CCharacterSelection::m_selectionIndex + 1);

    if (CCharacterSelection::m_modelFrame) {
        CCharacterSelection::m_modelFrame->SetCameraByIndex(0);
    }

    FrameScript_SignalEvent(7, nullptr);
}

void CCharacterSelection::UpdateCharacterList() {
    // TODO: ClearAddOnEnableState(0);

    CCharacterSelection::s_characterList.SetCount(0);

    CCharacterSelection::m_restrictHuman = 0;
    CCharacterSelection::m_restrictDwarf = 0;
    CCharacterSelection::m_restrictGnome = 0;
    CCharacterSelection::m_restrictNightElf = 0;
    CCharacterSelection::m_restrictDraenei = 0;
    CCharacterSelection::m_restrictOrc = 0;
    CCharacterSelection::m_restrictTroll = 0;
    CCharacterSelection::m_restrictTauren = 0;
    CCharacterSelection::m_restrictUndead = 0;
    CCharacterSelection::m_restrictBloodElf = 0;

    ClientServices::EnumerateCharacters(&CCharacterSelection::EnumerateCharactersCallback, nullptr);

    if (CCharacterSelection::s_characterList.Count()) {
        // TODO: Apply restrictions (m_restrictHuman, etc)
        // TODO: CRealmList::m_preferredCategory = 0;

        int32_t selectionIndex = Client::g_lastCharacterIndex->GetInt();
        if (selectionIndex < 0 || selectionIndex >= CCharacterSelection::s_characterList.Count()) {
            selectionIndex = 0;
        }

        CCharacterSelection::m_selectionIndex = selectionIndex;
        CCharacterSelection::ShowCharacter();

        FrameScript_SignalEvent(8, "%d", CCharacterSelection::m_selectionIndex + 1);
    } else {
        CCharacterSelection::m_selectionIndex = 0;
        CCharacterSelection::ShowCharacter();

        FrameScript_SignalEvent(8, "%d", CCharacterSelection::m_selectionIndex + 1);

        if (CCharacterSelection::m_modelFrame) {
            auto model = CCharacterSelection::m_modelFrame->m_model;
            if (model) {
                model->DetachAllChildrenById(0);
                model->DetachAllChildrenById(1);
            }
        }
    }
    FrameScript_SignalEvent(7, nullptr);
}

void CCharacterSelection::OnGetCharacterList() {
    CCharacterSelection::s_characterList.Clear();
    if (CCharacterSelection::m_modelFrame) {
        auto model = CCharacterSelection::m_modelFrame->m_model;
        if (model) {
            model->DetachAllChildrenById(0);
            model->DetachAllChildrenById(1);
        }
    }
    CGlueMgr::GetCharacterList();
}

uint32_t CCharacterSelection::GetNumCharacters() {
    return CCharacterSelection::s_characterList.Count();
}
