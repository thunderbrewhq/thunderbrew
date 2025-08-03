#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetNumTalentTabs(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTalentTabInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumTalents(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTalentInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTalentLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTalentPrereqs(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LearnTalent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetUnspentTalentPoints(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumTalentGroups(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetActiveTalentGroup(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetActiveTalentGroup(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPreviewTalentPointsSpent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGroupPreviewTalentPointsSpent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddPreviewTalentPoints(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ResetPreviewTalentPoints(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ResetGroupPreviewTalentPoints(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LearnPreviewTalents(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void TalentInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_TALENT_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_TalentInfo[i].name,
            GameScript::s_ScriptFunctions_TalentInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_TalentInfo[NUM_SCRIPT_FUNCTIONS_TALENT_INFO] = {
    { "GetNumTalentTabs", &Script_GetNumTalentTabs },
    { "GetTalentTabInfo", &Script_GetTalentTabInfo },
    { "GetNumTalents", &Script_GetNumTalents },
    { "GetTalentInfo", &Script_GetTalentInfo },
    { "GetTalentLink", &Script_GetTalentLink },
    { "GetTalentPrereqs", &Script_GetTalentPrereqs },
    { "LearnTalent", &Script_LearnTalent },
    { "GetUnspentTalentPoints", &Script_GetUnspentTalentPoints },
    { "GetNumTalentGroups", &Script_GetNumTalentGroups },
    { "GetActiveTalentGroup", &Script_GetActiveTalentGroup },
    { "SetActiveTalentGroup", &Script_SetActiveTalentGroup },
    { "GetPreviewTalentPointsSpent", &Script_GetPreviewTalentPointsSpent },
    { "GetGroupPreviewTalentPointsSpent", &Script_GetGroupPreviewTalentPointsSpent },
    { "AddPreviewTalentPoints", &Script_AddPreviewTalentPoints },
    { "ResetPreviewTalentPoints", &Script_ResetPreviewTalentPoints },
    { "ResetGroupPreviewTalentPoints", &Script_ResetGroupPreviewTalentPoints },
    { "LearnPreviewTalents", &Script_LearnPreviewTalents },
};
