#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetMinigameType(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_MakeMinigameMove(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMinigameState(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void MinigameInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_MINIGAME_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_MinigameInfo[i].name,
            GameScript::s_ScriptFunctions_MinigameInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_MinigameInfo[NUM_SCRIPT_FUNCTIONS_MINIGAME_INFO] = {
    { "GetMinigameType", &Script_GetMinigameType },
    { "MakeMinigameMove", &Script_MakeMinigameMove },
    { "GetMinigameState", &Script_GetMinigameState },
};
