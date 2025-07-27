#ifndef GAMEUI_GAME_SCRIPT_FUNCTIONS_HPP
#define GAMEUI_GAME_SCRIPT_FUNCTIONS_HPP

#include "ui/Types.hpp"
#include <cstdint>

struct lua_State;

#define NUM_SCRIPT_FUNCTIONS_CAMERA 22

namespace GameScript {
    extern FrameScript_Method s_ScriptFunctions_Camera[NUM_SCRIPT_FUNCTIONS_CAMERA];
}

// Utility

void LoadScriptFunctions();
void CameraRegisterScriptFunctions();

#endif
