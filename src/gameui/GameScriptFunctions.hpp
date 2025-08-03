#ifndef GAMEUI_GAME_SCRIPT_FUNCTIONS_HPP
#define GAMEUI_GAME_SCRIPT_FUNCTIONS_HPP

#include "ui/Types.hpp"
#include <cstdint>

struct lua_State;

#define NUM_SCRIPT_FUNCTIONS_GAME 310
#define NUM_SCRIPT_FUNCTIONS_CAMERA 22
#define NUM_SCRIPT_FUNCTIONS_SCRIPT_EVENTS 169
#define NUM_SCRIPT_FUNCTIONS_CHAT 89

namespace GameScript {
    extern FrameScript_Method s_ScriptFunctions_Game[NUM_SCRIPT_FUNCTIONS_GAME];
    extern FrameScript_Method s_ScriptFunctions_Camera[NUM_SCRIPT_FUNCTIONS_CAMERA];
    extern FrameScript_Method s_ScriptFunctions_ScriptEvents[NUM_SCRIPT_FUNCTIONS_SCRIPT_EVENTS];
    extern FrameScript_Method s_ScriptFunctions_Chat[NUM_SCRIPT_FUNCTIONS_CHAT];
    }

// Utility

void LoadScriptFunctions();
void CameraRegisterScriptFunctions();
void ScriptEventsRegisterFunctions();
void ChatRegisterScriptFunctions();

#endif
