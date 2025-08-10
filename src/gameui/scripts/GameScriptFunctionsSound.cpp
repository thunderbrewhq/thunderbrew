#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_PlaySound(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PlayMusic(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PlaySoundFile(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_StopMusic(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_Sound_GameSystem_GetNumInputDrivers(lua_State* L) {
    // TODO
    lua_pushnumber(L, 0.0);
    return 1;
}

static int32_t Script_Sound_GameSystem_GetInputDriverNameByIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_Sound_GameSystem_GetNumOutputDrivers(lua_State* L) {
    // TODO
    lua_pushnumber(L, 0.0);
    return 1;
}

static int32_t Script_Sound_GameSystem_GetOutputDriverNameByIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_Sound_GameSystem_RestartSoundSystem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_Sound_ChatSystem_GetNumInputDrivers(lua_State* L) {
    // TODO
    lua_pushnumber(L, 0.0);
    return 1;
}

static int32_t Script_Sound_ChatSystem_GetInputDriverNameByIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_Sound_ChatSystem_GetNumOutputDrivers(lua_State* L) {
    // TODO
    lua_pushnumber(L, 0.0);
    return 1;
}

static int32_t Script_Sound_ChatSystem_GetOutputDriverNameByIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_StartCapture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_StopCapture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_RecordLoopbackSound(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_StopRecordingLoopbackSound(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_PlayLoopbackSound(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_StopPlayingLoopbackSound(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_IsRecordingLoopbackSound(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_IsPlayingLoopbackSound(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_GetCurrentMicrophoneSignalLevel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceChat_ActivatePrimaryCaptureCallback(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void SoundRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_SOUND; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Sound[i].name,
            GameScript::s_ScriptFunctions_Sound[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_Sound[NUM_SCRIPT_FUNCTIONS_SOUND] = {
    { "PlaySound", &Script_PlaySound },
    { "PlayMusic", &Script_PlayMusic },
    { "PlaySoundFile", &Script_PlaySoundFile },
    { "StopMusic", &Script_StopMusic },
    { "Sound_GameSystem_GetNumInputDrivers", &Script_Sound_GameSystem_GetNumInputDrivers },
    { "Sound_GameSystem_GetInputDriverNameByIndex", &Script_Sound_GameSystem_GetInputDriverNameByIndex },
    { "Sound_GameSystem_GetNumOutputDrivers", &Script_Sound_GameSystem_GetNumOutputDrivers },
    { "Sound_GameSystem_GetOutputDriverNameByIndex", &Script_Sound_GameSystem_GetOutputDriverNameByIndex },
    { "Sound_GameSystem_RestartSoundSystem", &Script_Sound_GameSystem_RestartSoundSystem },
    { "Sound_ChatSystem_GetNumInputDrivers", &Script_Sound_ChatSystem_GetNumInputDrivers },
    { "Sound_ChatSystem_GetInputDriverNameByIndex", &Script_Sound_ChatSystem_GetInputDriverNameByIndex },
    { "Sound_ChatSystem_GetNumOutputDrivers", &Script_Sound_ChatSystem_GetNumOutputDrivers },
    { "Sound_ChatSystem_GetOutputDriverNameByIndex", &Script_Sound_ChatSystem_GetOutputDriverNameByIndex },
    { "VoiceChat_StartCapture", &Script_VoiceChat_StartCapture },
    { "VoiceChat_StopCapture", &Script_VoiceChat_StopCapture },
    { "VoiceChat_RecordLoopbackSound", &Script_VoiceChat_RecordLoopbackSound },
    { "VoiceChat_StopRecordingLoopbackSound", &Script_VoiceChat_StopRecordingLoopbackSound },
    { "VoiceChat_PlayLoopbackSound", &Script_VoiceChat_PlayLoopbackSound },
    { "VoiceChat_StopPlayingLoopbackSound", &Script_VoiceChat_StopPlayingLoopbackSound },
    { "VoiceChat_IsRecordingLoopbackSound", &Script_VoiceChat_IsRecordingLoopbackSound },
    { "VoiceChat_IsPlayingLoopbackSound", &Script_VoiceChat_IsPlayingLoopbackSound },
    { "VoiceChat_GetCurrentMicrophoneSignalLevel", &Script_VoiceChat_GetCurrentMicrophoneSignalLevel },
    { "VoiceChat_ActivatePrimaryCaptureCallback", &Script_VoiceChat_ActivatePrimaryCaptureCallback },
};
