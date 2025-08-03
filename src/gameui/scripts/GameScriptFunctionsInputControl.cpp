#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_JumpOrAscendStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AscendStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DescendStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ToggleRun(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ToggleAutoRun(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_MoveForwardStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_MoveForwardStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_MoveBackwardStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_MoveBackwardStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TurnLeftStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TurnLeftStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TurnRightStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TurnRightStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_StrafeLeftStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_StrafeLeftStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_StrafeRightStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_StrafeRightStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PitchUpStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PitchUpStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PitchDownStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PitchDownStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TurnOrActionStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TurnOrActionStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CameraOrSelectOrMoveStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CameraOrSelectOrMoveStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_MoveAndSteerStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_MoveAndSteerStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetMouselookOverrideBinding(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_MouselookStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_MouselookStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsMouselooking(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleExit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehiclePrevSeat(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleNextSeat(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimUpStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimUpStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimDownStart(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimDownStop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimIncrement(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimDecrement(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimRequestAngle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimGetAngle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimRequestNormAngle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimGetNormAngle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimSetNormPower(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_VehicleAimGetNormPower(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsUsingVehicleControls(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanExitVehicle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanSwitchVehicleSeats(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsVehicleAimAngleAdjustable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsVehicleAimPowerAdjustable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DetectWowMouse(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void InputControlRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_INPUT_CONTROL; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_InputControl[i].name,
            GameScript::s_ScriptFunctions_InputControl[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_InputControl[NUM_SCRIPT_FUNCTIONS_INPUT_CONTROL] = {
    { "JumpOrAscendStart", &Script_JumpOrAscendStart },
    { "AscendStop", &Script_AscendStop },
    { "DescendStop", &Script_DescendStop },
    { "ToggleRun", &Script_ToggleRun },
    { "ToggleAutoRun", &Script_ToggleAutoRun },
    { "MoveForwardStart", &Script_MoveForwardStart },
    { "MoveForwardStop", &Script_MoveForwardStop },
    { "MoveBackwardStart", &Script_MoveBackwardStart },
    { "MoveBackwardStop", &Script_MoveBackwardStop },
    { "TurnLeftStart", &Script_TurnLeftStart },
    { "TurnLeftStop", &Script_TurnLeftStop },
    { "TurnRightStart", &Script_TurnRightStart },
    { "TurnRightStop", &Script_TurnRightStop },
    { "StrafeLeftStart", &Script_StrafeLeftStart },
    { "StrafeLeftStop", &Script_StrafeLeftStop },
    { "StrafeRightStart", &Script_StrafeRightStart },
    { "StrafeRightStop", &Script_StrafeRightStop },
    { "PitchUpStart", &Script_PitchUpStart },
    { "PitchUpStop", &Script_PitchUpStop },
    { "PitchDownStart", &Script_PitchDownStart },
    { "PitchDownStop", &Script_PitchDownStop },
    { "TurnOrActionStart", &Script_TurnOrActionStart },
    { "TurnOrActionStop", &Script_TurnOrActionStop },
    { "CameraOrSelectOrMoveStart", &Script_CameraOrSelectOrMoveStart },
    { "CameraOrSelectOrMoveStop", &Script_CameraOrSelectOrMoveStop },
    { "MoveAndSteerStart", &Script_MoveAndSteerStart },
    { "MoveAndSteerStop", &Script_MoveAndSteerStop },
    { "SetMouselookOverrideBinding", &Script_SetMouselookOverrideBinding },
    { "MouselookStart", &Script_MouselookStart },
    { "MouselookStop", &Script_MouselookStop },
    { "IsMouselooking", &Script_IsMouselooking },
    { "VehicleExit", &Script_VehicleExit },
    { "VehiclePrevSeat", &Script_VehiclePrevSeat },
    { "VehicleNextSeat", &Script_VehicleNextSeat },
    { "VehicleAimUpStart", &Script_VehicleAimUpStart },
    { "VehicleAimUpStop", &Script_VehicleAimUpStop },
    { "VehicleAimDownStart", &Script_VehicleAimDownStart },
    { "VehicleAimDownStop", &Script_VehicleAimDownStop },
    { "VehicleAimIncrement", &Script_VehicleAimIncrement },
    { "VehicleAimDecrement", &Script_VehicleAimDecrement },
    { "VehicleAimRequestAngle", &Script_VehicleAimRequestAngle },
    { "VehicleAimGetAngle", &Script_VehicleAimGetAngle },
    { "VehicleAimRequestNormAngle", &Script_VehicleAimRequestNormAngle },
    { "VehicleAimGetNormAngle", &Script_VehicleAimGetNormAngle },
    { "VehicleAimSetNormPower", &Script_VehicleAimSetNormPower },
    { "VehicleAimGetNormPower", &Script_VehicleAimGetNormPower },
    { "IsUsingVehicleControls", &Script_IsUsingVehicleControls },
    { "CanExitVehicle", &Script_CanExitVehicle },
    { "CanSwitchVehicleSeats", &Script_CanSwitchVehicleSeats },
    { "IsVehicleAimAngleAdjustable", &Script_IsVehicleAimAngleAdjustable },
    { "IsVehicleAimPowerAdjustable", &Script_IsVehicleAimPowerAdjustable },
    { "DetectWowMouse", &Script_DetectWowMouse },
};
