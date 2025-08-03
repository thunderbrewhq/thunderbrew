#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_CombatLogResetFilter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatLogAddFilter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatLogSetRetentionTime(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatLogGetRetentionTime(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatLogGetNumEntries(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatLogSetCurrentEntry(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatLogGetCurrentEntry(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatLogAdvanceEntry(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatLogClearEntries(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatLog_Object_IsA(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CombatTextSetActiveUnit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void UnitCombatLogRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_UNIT_COMBAT_LOG; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_UnitCombatLog[i].name,
            GameScript::s_ScriptFunctions_UnitCombatLog[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_UnitCombatLog[NUM_SCRIPT_FUNCTIONS_UNIT_COMBAT_LOG] = {
    { "CombatLogResetFilter", &Script_CombatLogResetFilter },
    { "CombatLogAddFilter", &Script_CombatLogAddFilter },
    { "CombatLogSetRetentionTime", &Script_CombatLogSetRetentionTime },
    { "CombatLogGetRetentionTime", &Script_CombatLogGetRetentionTime },
    { "CombatLogGetNumEntries", &Script_CombatLogGetNumEntries },
    { "CombatLogSetCurrentEntry", &Script_CombatLogSetCurrentEntry },
    { "CombatLogGetCurrentEntry", &Script_CombatLogGetCurrentEntry },
    { "CombatLogAdvanceEntry", &Script_CombatLogAdvanceEntry },
    { "CombatLogClearEntries", &Script_CombatLogClearEntries },
    { "CombatLog_Object_IsA", &Script_CombatLog_Object_IsA },
    { "CombatTextSetActiveUnit", &Script_CombatTextSetActiveUnit },
};
