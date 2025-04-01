#include "sound/SI2.hpp"
#include "ui/FrameScript.hpp"
#include "console/CVar.hpp"
#include <bc/Memory.hpp>

#if defined(WHOA_BUILD_FMOD)

FMOD::System* SI2::sm_pGameSystem = nullptr;
FMOD::System* SI2::sm_pChatSystem = nullptr;

void* F_CALL FMOD_Alloc(unsigned int size, FMOD_MEMORY_TYPE type, const char* sourcestr) {
    return SMemAlloc(size, sourcestr, 0, 0);
}

void* F_CALL FMOD_ReAlloc(void* ptr, unsigned int size, FMOD_MEMORY_TYPE type, const char* sourcestr) {
    return SMemReAlloc(ptr, size, sourcestr, 0, 0);
}

void F_CALL FMOD_Free(void* ptr, FMOD_MEMORY_TYPE type, const char* sourcestr) {
    SMemFree(ptr, sourcestr, 0, 0);
}

#endif

void SI2::RegisterScriptFunctions() {
    for (int32_t i = 0; i < s_NumScriptFunctions; i++) {
        auto item = &s_ScriptFunctions[i];
        FrameScript_RegisterFunction(item->name, item->method);
    }
}

int32_t SI2::Init(int32_t flag) {
    Log_Init();
    SI2_LOG("=> Version %s (%s) %s", "1.0.0", "00000", "Feb 25 2024");
    SI2_LOG(" ");
    SI2_LOG("=> Setting up Game Sound:");
    SI2_LOG(" - SESound Engine Init");

#if defined(WHOA_BUILD_FMOD)
    SI2_LOG(" - FMOD Memory Init");
    FMOD::Memory_Initialize(nullptr, 0, &FMOD_Alloc, &FMOD_ReAlloc, &FMOD_Free);
    // sub_877440(&off_B1D5E4);

    SI2_LOG(" - FMOD System Create");
    auto errcode = FMOD::System_Create(&sm_pGameSystem);
    if (errcode) {
        if (errcode != FMOD_ERR_DSP_SILENCE && errcode != FMOD_ERR_INVALID_VECTOR && errcode != FMOD_ERR_RECORD) {
            SI2_ERR(errcode, "");
        }
        SI2_LOG(" -###########################################################################################");
        SI2_ERR(errcode, " -######## ERROR INITIALIZING. ALL GAME SOUND DISABLED.");
        SI2_LOG(" -###########################################################################################");
        sm_pGameSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
        goto LABEL_9;
    }

    errcode = FMOD::System_Create(&sm_pChatSystem);
    if (errcode != FMOD_ERR_DSP_SILENCE && errcode != FMOD_ERR_INVALID_VECTOR && errcode != FMOD_ERR_RECORD) {
        SI2_ERR(errcode, "");
    }

    if (sm_pChatSystem && sm_pChatSystem->init(4, FMOD_INIT_NORMAL, nullptr)) {
        sm_pChatSystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
    }

    sm_pGameSystem->setOutput(FMOD_OUTPUTTYPE_AUTODETECT);
#endif
LABEL_9:

    return 0;
}

void SI2::StartGlueMusic(const char* filename) {

}
