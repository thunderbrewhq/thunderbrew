#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "ui/ScriptFunctions.hpp"

void LoadScriptFunctions() {
    RegisterSimpleFrameScriptMethods();
    // TODO
    CameraRegisterScriptFunctions();
}

void CameraRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_CAMERA; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Camera[i].name,
            GameScript::s_ScriptFunctions_Camera[i].method);
    }
}
