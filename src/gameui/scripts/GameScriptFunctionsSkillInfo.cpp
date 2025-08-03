#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetNumSkillLines(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSkillLineInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AbandonSkill(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CollapseSkillHeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ExpandSkillHeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddSkillUp(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RemoveSkillUp(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAdjustedSkillPoints(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AcceptSkillUps(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CancelSkillUps(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_BuySkillTier(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSelectedSkill(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSelectedSkill(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void SkillInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_SKILL_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_SkillInfo[i].name,
            GameScript::s_ScriptFunctions_SkillInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_SkillInfo[NUM_SCRIPT_FUNCTIONS_SKILL_INFO] = {
    { "GetNumSkillLines", &Script_GetNumSkillLines },
    { "GetSkillLineInfo", &Script_GetSkillLineInfo },
    { "AbandonSkill", &Script_AbandonSkill },
    { "CollapseSkillHeader", &Script_CollapseSkillHeader },
    { "ExpandSkillHeader", &Script_ExpandSkillHeader },
    { "AddSkillUp", &Script_AddSkillUp },
    { "RemoveSkillUp", &Script_RemoveSkillUp },
    { "GetAdjustedSkillPoints", &Script_GetAdjustedSkillPoints },
    { "AcceptSkillUps", &Script_AcceptSkillUps },
    { "CancelSkillUps", &Script_CancelSkillUps },
    { "BuySkillTier", &Script_BuySkillTier },
    { "SetSelectedSkill", &Script_SetSelectedSkill },
    { "GetSelectedSkill", &Script_GetSelectedSkill },
};
