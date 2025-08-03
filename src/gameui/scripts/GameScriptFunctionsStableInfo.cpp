#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_ClosePetStables(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_StablePet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UnstablePet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_BuyStableSlot(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumStablePets(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumStableSlots(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetStablePetInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNextStableSlotCost(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClickStablePet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PickupStablePet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSelectedStablePet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetPetStablePaperdoll(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetStablePetFoodTypes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsAtStableMaster(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void StableInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_STABLE_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_StableInfo[i].name,
            GameScript::s_ScriptFunctions_StableInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_StableInfo[NUM_SCRIPT_FUNCTIONS_STABLE_INFO] = {
    { "ClosePetStables", &Script_ClosePetStables },
    { "StablePet", &Script_StablePet },
    { "UnstablePet", &Script_UnstablePet },
    { "BuyStableSlot", &Script_BuyStableSlot },
    { "GetNumStablePets", &Script_GetNumStablePets },
    { "GetNumStableSlots", &Script_GetNumStableSlots },
    { "GetStablePetInfo", &Script_GetStablePetInfo },
    { "GetNextStableSlotCost", &Script_GetNextStableSlotCost },
    { "ClickStablePet", &Script_ClickStablePet },
    { "PickupStablePet", &Script_PickupStablePet },
    { "GetSelectedStablePet", &Script_GetSelectedStablePet },
    { "SetPetStablePaperdoll", &Script_SetPetStablePaperdoll },
    { "GetStablePetFoodTypes", &Script_GetStablePetFoodTypes },
    { "IsAtStableMaster", &Script_IsAtStableMaster },
};
