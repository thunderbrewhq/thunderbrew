#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_PlayDance(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void CGDanceStudioRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_CGDANCE_STUDIO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_CGDanceStudio[i].name,
            GameScript::s_ScriptFunctions_CGDanceStudio[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_CGDanceStudio[NUM_SCRIPT_FUNCTIONS_CGDANCE_STUDIO] = {
    { "PlayDance", &Script_PlayDance },
};
