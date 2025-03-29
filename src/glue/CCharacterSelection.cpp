#include "glue/CCharacterSelection.hpp"
#include "model/CM2Shared.hpp"
#include "ui/CSimpleModelFFX.hpp"
#include "client/ClientServices.hpp"
#include "net/Connection.hpp"

TSGrowableArray<CharacterSelectionDisplay> CCharacterSelection::s_characterList;
CSimpleModelFFX* CCharacterSelection::s_modelFrame;
float CCharacterSelection::s_charFacing = 0.0f;

void CCharacterSelection::RenderPrep() {
    // TODO
}

void CCharacterSelection::SetBackgroundModel(const char* modelPath) {
    if (!CCharacterSelection::s_modelFrame || !modelPath || !*modelPath) {
        return;
    }

    auto model = CCharacterSelection::s_modelFrame->m_model;

    // Check if already set
    if (model && !SStrCmpI(modelPath, model->m_shared->m_filePath, STORM_MAX_STR)) {
        return;
    }

    CCharacterSelection::s_modelFrame->SetModel(modelPath);

    // TODO BYTE1(CCharacterSelection::m_modelFrame->simplemodelffx_dword510[3]) = 1;

    model = CCharacterSelection::s_modelFrame->m_model;

    if (model) {
        // TODO lighting callback + arg

        model->IsDrawable(1, 1);
    }
}

void CCharacterSelection::SetCharFacing(float facing) {
    // TODO:
}

void CCharacterSelection::ClearCharacterList() {
}

void CCharacterSelection::UpdateCharacterList() {
    // TODO: ClearAddOnEnableState(0);
    // TODO: Proper implementation

    auto& received = ClientServices::Connection()->m_characterList;
    CCharacterSelection::s_characterList.SetCount(received.Count());
    for (uint32_t i = 0; i < received.Count(); ++i) {
        CCharacterSelection::s_characterList[i].m_characterInfo = received[i];
    }

    if (CCharacterSelection::GetNumCharacters()) {
        int32_t currentIndex = 0;
        FrameScript_SignalEvent(8, "%d", currentIndex + 1);
    } else {
        int32_t currentIndex = 0;
        FrameScript_SignalEvent(8, "%d", currentIndex + 1);
    }
    FrameScript_SignalEvent(7, nullptr);
}

uint32_t CCharacterSelection::GetNumCharacters() {
    return s_characterList.Count();
}
