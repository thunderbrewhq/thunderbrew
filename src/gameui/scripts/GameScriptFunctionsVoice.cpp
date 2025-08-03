#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_VoiceEnumerateOutputDevices(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceEnumerateCaptureDevices(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceSelectOutputDevice(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceSelectCaptureDevice(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceGetCurrentOutputDevice(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceGetCurrentCaptureDevice(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetVoiceStatus(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumVoiceSessions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetVoiceSessionInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetVoiceCurrentSessionID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetActiveVoiceChannelBySessionID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumVoiceSessionMembersBySessionID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetVoiceSessionMemberInfoBySessionID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VoiceIsDisabledByClient(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UnitIsTalking(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void VoiceRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_VOICE; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Voice[i].name,
            GameScript::s_ScriptFunctions_Voice[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_Voice[NUM_SCRIPT_FUNCTIONS_VOICE] = {
    { "VoiceEnumerateOutputDevices", &Script_VoiceEnumerateOutputDevices },
    { "VoiceEnumerateCaptureDevices", &Script_VoiceEnumerateCaptureDevices },
    { "VoiceSelectOutputDevice", &Script_VoiceSelectOutputDevice },
    { "VoiceSelectCaptureDevice", &Script_VoiceSelectCaptureDevice },
    { "VoiceGetCurrentOutputDevice", &Script_VoiceGetCurrentOutputDevice },
    { "VoiceGetCurrentCaptureDevice", &Script_VoiceGetCurrentCaptureDevice },
    { "GetVoiceStatus", &Script_GetVoiceStatus },
    { "GetNumVoiceSessions", &Script_GetNumVoiceSessions },
    { "GetVoiceSessionInfo", &Script_GetVoiceSessionInfo },
    { "GetVoiceCurrentSessionID", &Script_GetVoiceCurrentSessionID },
    { "SetActiveVoiceChannelBySessionID", &Script_SetActiveVoiceChannelBySessionID },
    { "GetNumVoiceSessionMembersBySessionID", &Script_GetNumVoiceSessionMembersBySessionID },
    { "GetVoiceSessionMemberInfoBySessionID", &Script_GetVoiceSessionMemberInfoBySessionID },
    { "VoiceIsDisabledByClient", &Script_VoiceIsDisabledByClient },
    { "UnitIsTalking", &Script_UnitIsTalking },
};
