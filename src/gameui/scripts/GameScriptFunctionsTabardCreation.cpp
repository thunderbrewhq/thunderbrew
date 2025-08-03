#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_CloseTabardCreation(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTabardCreationCost(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void TabardCreationRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_TABARD_CREATION; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_TabardCreation[i].name,
            GameScript::s_ScriptFunctions_TabardCreation[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_TabardCreation[NUM_SCRIPT_FUNCTIONS_TABARD_CREATION] = {
    { "CloseTabardCreation", &Script_CloseTabardCreation },
    { "GetTabardCreationCost", &Script_GetTabardCreationCost },
};
