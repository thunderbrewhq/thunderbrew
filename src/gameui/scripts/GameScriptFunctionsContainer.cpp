#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_ContainerIDToInventoryID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerNumSlots(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerItemInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerItemID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerItemLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerItemCooldown(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PickupContainerItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SplitContainerItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UseContainerItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SocketContainerItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ShowContainerSellCursor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetBagPortraitTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetBagName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerItemDurability(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerNumFreeSlots(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerFreeSlots(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerItemPurchaseInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerItemPurchaseItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ContainerRefundItemPurchase(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMaxArenaCurrency(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerItemGems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetContainerItemQuestInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void ContainerRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_CONTAINER; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Container[i].name,
            GameScript::s_ScriptFunctions_Container[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_Container[NUM_SCRIPT_FUNCTIONS_CONTAINER] = {
    { "ContainerIDToInventoryID", &Script_ContainerIDToInventoryID },
    { "GetContainerNumSlots", &Script_GetContainerNumSlots },
    { "GetContainerItemInfo", &Script_GetContainerItemInfo },
    { "GetContainerItemID", &Script_GetContainerItemID },
    { "GetContainerItemLink", &Script_GetContainerItemLink },
    { "GetContainerItemCooldown", &Script_GetContainerItemCooldown },
    { "PickupContainerItem", &Script_PickupContainerItem },
    { "SplitContainerItem", &Script_SplitContainerItem },
    { "UseContainerItem", &Script_UseContainerItem },
    { "SocketContainerItem", &Script_SocketContainerItem },
    { "ShowContainerSellCursor", &Script_ShowContainerSellCursor },
    { "SetBagPortraitTexture", &Script_SetBagPortraitTexture },
    { "GetBagName", &Script_GetBagName },
    { "GetContainerItemDurability", &Script_GetContainerItemDurability },
    { "GetContainerNumFreeSlots", &Script_GetContainerNumFreeSlots },
    { "GetContainerFreeSlots", &Script_GetContainerFreeSlots },
    { "GetContainerItemPurchaseInfo", &Script_GetContainerItemPurchaseInfo },
    { "GetContainerItemPurchaseItem", &Script_GetContainerItemPurchaseItem },
    { "ContainerRefundItemPurchase", &Script_ContainerRefundItemPurchase },
    { "GetMaxArenaCurrency", &Script_GetMaxArenaCurrency },
    { "GetContainerItemGems", &Script_GetContainerItemGems },
    { "GetContainerItemQuestInfo", &Script_GetContainerItemQuestInfo },
};
