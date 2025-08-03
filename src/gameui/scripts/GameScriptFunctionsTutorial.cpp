#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_CanResetTutorials(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_FlagTutorial(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsTutorialFlagged(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TriggerTutorial(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClearTutorials(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ResetTutorials(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNextCompleatedTutorial(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPrevCompleatedTutorial(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void TutorialRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_TUTORIAL; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Tutorial[i].name,
            GameScript::s_ScriptFunctions_Tutorial[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_Tutorial[NUM_SCRIPT_FUNCTIONS_TUTORIAL] = {
    { "CanResetTutorials", &Script_CanResetTutorials },
    { "FlagTutorial", &Script_FlagTutorial },
    { "IsTutorialFlagged", &Script_IsTutorialFlagged },
    { "TriggerTutorial", &Script_TriggerTutorial },
    { "ClearTutorials", &Script_ClearTutorials },
    { "ResetTutorials", &Script_ResetTutorials },
    { "GetNextCompleatedTutorial", &Script_GetNextCompleatedTutorial },
    { "GetPrevCompleatedTutorial", &Script_GetPrevCompleatedTutorial },
};
