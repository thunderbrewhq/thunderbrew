#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_PetHasActionBar(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetActionInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetActionCooldown(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetActionsUsable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetActionSlotUsable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsPetAttackActive(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PickupPetAction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TogglePetAutocast(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CastPetAction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetPassiveMode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetDefensiveMode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetAggressiveMode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetWait(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetFollow(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetAttack(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetStopAttack(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetAbandon(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetDismiss(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetRename(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetCanBeAbandoned(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetCanBeDismissed(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PetCanBeRenamed(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetTimeRemaining(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_HasPetUI(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetExperience(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetHappiness(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetFoodTypes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetIcon(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPetTalentTree(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPossessInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsPetAttackAction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void PetInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_PET_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_PetInfo[i].name,
            GameScript::s_ScriptFunctions_PetInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_PetInfo[NUM_SCRIPT_FUNCTIONS_PET_INFO] = {
    { "PetHasActionBar", &Script_PetHasActionBar },
    { "GetPetActionInfo", &Script_GetPetActionInfo },
    { "GetPetActionCooldown", &Script_GetPetActionCooldown },
    { "GetPetActionsUsable", &Script_GetPetActionsUsable },
    { "GetPetActionSlotUsable", &Script_GetPetActionSlotUsable },
    { "IsPetAttackActive", &Script_IsPetAttackActive },
    { "PickupPetAction", &Script_PickupPetAction },
    { "TogglePetAutocast", &Script_TogglePetAutocast },
    { "CastPetAction", &Script_CastPetAction },
    { "PetPassiveMode", &Script_PetPassiveMode },
    { "PetDefensiveMode", &Script_PetDefensiveMode },
    { "PetAggressiveMode", &Script_PetAggressiveMode },
    { "PetWait", &Script_PetWait },
    { "PetFollow", &Script_PetFollow },
    { "PetAttack", &Script_PetAttack },
    { "PetStopAttack", &Script_PetStopAttack },
    { "PetAbandon", &Script_PetAbandon },
    { "PetDismiss", &Script_PetDismiss },
    { "PetRename", &Script_PetRename },
    { "PetCanBeAbandoned", &Script_PetCanBeAbandoned },
    { "PetCanBeDismissed", &Script_PetCanBeDismissed },
    { "PetCanBeRenamed", &Script_PetCanBeRenamed },
    { "GetPetTimeRemaining", &Script_GetPetTimeRemaining },
    { "HasPetUI", &Script_HasPetUI },
    { "GetPetExperience", &Script_GetPetExperience },
    { "GetPetHappiness", &Script_GetPetHappiness },
    { "GetPetFoodTypes", &Script_GetPetFoodTypes },
    { "GetPetIcon", &Script_GetPetIcon },
    { "GetPetTalentTree", &Script_GetPetTalentTree },
    { "GetPossessInfo", &Script_GetPossessInfo },
    { "IsPetAttackAction", &Script_IsPetAttackAction },
};
