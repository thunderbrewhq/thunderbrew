#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_StartDuel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AcceptDuel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CancelDuel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void DuelInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_DUEL_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_DuelInfo[i].name,
            GameScript::s_ScriptFunctions_DuelInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_DuelInfo[NUM_SCRIPT_FUNCTIONS_DUEL_INFO] = {
    { "StartDuel", &Script_StartDuel },
    { "AcceptDuel", &Script_AcceptDuel },
    { "CancelDuel", &Script_CancelDuel },
};
