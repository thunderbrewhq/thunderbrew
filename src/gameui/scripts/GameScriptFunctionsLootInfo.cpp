#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_SetLootPortrait(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumLootItems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLootSlotInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLootSlotLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LootSlotIsItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LootSlotIsCoin(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LootSlot(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ConfirmLootSlot(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CloseLoot(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsFishingLoot(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMasterLootCandidate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GiveMasterLoot(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLootRollItemInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLootRollItemLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLootRollTimeLeft(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RollOnLoot(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ConfirmLootRoll(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void LootInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_LOOT_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_LootInfo[i].name,
            GameScript::s_ScriptFunctions_LootInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_LootInfo[NUM_SCRIPT_FUNCTIONS_LOOT_INFO] = {
    { "SetLootPortrait", &Script_SetLootPortrait },
    { "GetNumLootItems", &Script_GetNumLootItems },
    { "GetLootSlotInfo", &Script_GetLootSlotInfo },
    { "GetLootSlotLink", &Script_GetLootSlotLink },
    { "LootSlotIsItem", &Script_LootSlotIsItem },
    { "LootSlotIsCoin", &Script_LootSlotIsCoin },
    { "LootSlot", &Script_LootSlot },
    { "ConfirmLootSlot", &Script_ConfirmLootSlot },
    { "CloseLoot", &Script_CloseLoot },
    { "IsFishingLoot", &Script_IsFishingLoot },
    { "GetMasterLootCandidate", &Script_GetMasterLootCandidate },
    { "GiveMasterLoot", &Script_GiveMasterLoot },
    { "GetLootRollItemInfo", &Script_GetLootRollItemInfo },
    { "GetLootRollItemLink", &Script_GetLootRollItemLink },
    { "GetLootRollTimeLeft", &Script_GetLootRollTimeLeft },
    { "RollOnLoot", &Script_RollOnLoot },
    { "ConfirmLootRoll", &Script_ConfirmLootRoll },
};
