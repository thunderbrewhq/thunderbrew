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


CharacterSelectionDisplay::CharacterSelectionDisplay()
    : m_characterModel(nullptr) {
}


void CCharacterSelection::Initialize() {
    // Empty method
}

void CCharacterSelection::RenderPrep() {
    // TODO
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
    // TODO

    if (CCharacterSelection::m_modelFrame) {
        auto model = CCharacterSelection::m_modelFrame->m_model;
        if (model) {
            //model->DetachAllChildrenById(0);
            //model->DetachAllChildrenById(1);
        }
    }

    CCharacterSelection::m_charFacing = 0.0;

    auto& character = CCharacterSelection::s_characterList[index];

    if (character.m_characterModel) {
        if (!character.m_characterModel->m_attachParent && CCharacterSelection::m_modelFrame && CCharacterSelection::m_modelFrame->m_model) {
            character.m_characterModel->SetVisible(1);
            character.m_characterModel->AttachToParent(CCharacterSelection::m_modelFrame->m_model, 0, nullptr, 0);
            character.m_characterModel->SetVisible(1);
        }

        // TODO
        return;
    }

    auto rec = Player_C_GetModelName(character.m_characterInfo.raceID, character.m_characterInfo.sexID);
    STORM_ASSERT(rec);
    if (!rec->m_modelName) {
        // TODO
        return;
    }

    auto scene = CCharacterSelection::m_modelFrame->GetScene();
    character.m_characterModel = scene->CreateModel(rec->m_modelName, 0);
}

void CCharacterSelection::SetCharFacing(float facing) {
    if (!CCharacterSelection::m_characterCount || !CCharacterSelection::GetNumCharacters()) {
        return;
    }

    auto character = CCharacterSelection::s_characterList[CCharacterSelection::m_selectionIndex];
    if (character.m_characterModel) {
        character.m_characterModel->SetWorldTransform(C3Vector(), facing, 1.0);
    }
}

void CCharacterSelection::ClearCharacterList() {
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
            // TODO
        }
    }
    FrameScript_SignalEvent(7, nullptr);
}

uint32_t CCharacterSelection::GetNumCharacters() {
    return CCharacterSelection::s_characterList.Count();
}
