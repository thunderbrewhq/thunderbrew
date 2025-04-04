#include "glue/CCharacterSelection.hpp"
#include "model/CM2Shared.hpp"
#include "ui/CSimpleModelFFX.hpp"
#include "client/ClientServices.hpp"
#include "client/Client.hpp"
#include "console/CVar.hpp"
#include "net/Connection.hpp"

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
    // TODO
}

void CCharacterSelection::SetCharFacing(float facing) {
    // TODO
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
    return s_characterList.Count();
}
