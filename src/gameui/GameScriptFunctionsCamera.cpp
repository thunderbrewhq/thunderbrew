#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


int32_t Script_CameraZoomIn(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_CameraZoomOut(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewInStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewInStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewOutStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewOutStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewLeftStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewLeftStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewRightStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewRightStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewUpStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewUpStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewDownStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_MoveViewDownStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_SetView(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_SaveView(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_ResetView(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_NextView(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_PrevView(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_FlipCameraYaw(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_VehicleCameraZoomIn(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_VehicleCameraZoomOut(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}


void CameraRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_CAMERA; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Camera[i].name,
            GameScript::s_ScriptFunctions_Camera[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_Camera[NUM_SCRIPT_FUNCTIONS_CAMERA] = {
    { "CameraZoomIn", &Script_CameraZoomIn },
    { "CameraZoomOut", &Script_CameraZoomOut },
    { "MoveViewInStart", &Script_MoveViewInStart },
    { "MoveViewInStop", &Script_MoveViewInStop },
    { "MoveViewOutStart", &Script_MoveViewOutStart },
    { "MoveViewOutStop", &Script_MoveViewOutStop },
    { "MoveViewLeftStart", &Script_MoveViewLeftStart },
    { "MoveViewLeftStop", &Script_MoveViewLeftStop },
    { "MoveViewRightStart", &Script_MoveViewRightStart },
    { "MoveViewRightStop", &Script_MoveViewRightStop },
    { "MoveViewUpStart", &Script_MoveViewUpStart },
    { "MoveViewUpStop", &Script_MoveViewUpStop },
    { "MoveViewDownStart", &Script_MoveViewDownStart },
    { "MoveViewDownStop", &Script_MoveViewDownStop },
    { "SetView", &Script_SetView },
    { "SaveView", &Script_SaveView },
    { "ResetView", &Script_ResetView },
    { "NextView", &Script_NextView },
    { "PrevView", &Script_PrevView },
    { "FlipCameraYaw", &Script_FlipCameraYaw },
    { "VehicleCameraZoomIn", &Script_VehicleCameraZoomIn },
    { "VehicleCameraZoomOut", &Script_VehicleCameraZoomOut },
};
