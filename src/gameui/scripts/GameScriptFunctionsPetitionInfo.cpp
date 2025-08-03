#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_ClosePetition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetitionInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumPetitionNames(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetitionNameInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanSignPetition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SignPetition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_OfferPetition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RenamePetition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void PetitionInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_PETITION_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_PetitionInfo[i].name,
            GameScript::s_ScriptFunctions_PetitionInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_PetitionInfo[NUM_SCRIPT_FUNCTIONS_PETITION_INFO] = {
    { "ClosePetition", &Script_ClosePetition },
    { "GetPetitionInfo", &Script_GetPetitionInfo },
    { "GetNumPetitionNames", &Script_GetNumPetitionNames },
    { "GetPetitionNameInfo", &Script_GetPetitionNameInfo },
    { "CanSignPetition", &Script_CanSignPetition },
    { "SignPetition", &Script_SignPetition },
    { "OfferPetition", &Script_OfferPetition },
    { "RenamePetition", &Script_RenamePetition },
};
