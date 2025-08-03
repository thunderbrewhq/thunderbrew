#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_CloseAuctionHouse(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAuctionHouseDepositRate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalculateAuctionDeposit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClickAuctionSellItemButton(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAuctionSellItemInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_StartAuction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QueryAuctionItems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetOwnerAuctionItems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetBidderAuctionItems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumAuctionItems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAuctionItemInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAuctionItemLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAuctionItemTimeLeft(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PlaceAuctionBid(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAuctionItemClasses(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAuctionItemSubClasses(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAuctionInvTypes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanSendAuctionQuery(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SortAuctionItems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSelectedAuctionItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSelectedAuctionItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsAuctionSortReversed(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CancelAuction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanCancelAuction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAuctionSort(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SortAuctionClearSort(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SortAuctionSetSort(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SortAuctionApplySort(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CancelSell(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetAuctionsTabShowing(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void AuctionHouseRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_AUCTION_HOUSE; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_AuctionHouse[i].name,
            GameScript::s_ScriptFunctions_AuctionHouse[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_AuctionHouse[NUM_SCRIPT_FUNCTIONS_AUCTION_HOUSE] = {
    { "CloseAuctionHouse", &Script_CloseAuctionHouse },
    { "GetAuctionHouseDepositRate", &Script_GetAuctionHouseDepositRate },
    { "CalculateAuctionDeposit", &Script_CalculateAuctionDeposit },
    { "ClickAuctionSellItemButton", &Script_ClickAuctionSellItemButton },
    { "GetAuctionSellItemInfo", &Script_GetAuctionSellItemInfo },
    { "StartAuction", &Script_StartAuction },
    { "QueryAuctionItems", &Script_QueryAuctionItems },
    { "GetOwnerAuctionItems", &Script_GetOwnerAuctionItems },
    { "GetBidderAuctionItems", &Script_GetBidderAuctionItems },
    { "GetNumAuctionItems", &Script_GetNumAuctionItems },
    { "GetAuctionItemInfo", &Script_GetAuctionItemInfo },
    { "GetAuctionItemLink", &Script_GetAuctionItemLink },
    { "GetAuctionItemTimeLeft", &Script_GetAuctionItemTimeLeft },
    { "PlaceAuctionBid", &Script_PlaceAuctionBid },
    { "GetAuctionItemClasses", &Script_GetAuctionItemClasses },
    { "GetAuctionItemSubClasses", &Script_GetAuctionItemSubClasses },
    { "GetAuctionInvTypes", &Script_GetAuctionInvTypes },
    { "CanSendAuctionQuery", &Script_CanSendAuctionQuery },
    { "SortAuctionItems", &Script_SortAuctionItems },
    { "SetSelectedAuctionItem", &Script_SetSelectedAuctionItem },
    { "GetSelectedAuctionItem", &Script_GetSelectedAuctionItem },
    { "IsAuctionSortReversed", &Script_IsAuctionSortReversed },
    { "CancelAuction", &Script_CancelAuction },
    { "CanCancelAuction", &Script_CanCancelAuction },
    { "GetAuctionSort", &Script_GetAuctionSort },
    { "SortAuctionClearSort", &Script_SortAuctionClearSort },
    { "SortAuctionSetSort", &Script_SortAuctionSetSort },
    { "SortAuctionApplySort", &Script_SortAuctionApplySort },
    { "CancelSell", &Script_CancelSell },
    { "SetAuctionsTabShowing", &Script_SetAuctionsTabShowing },
};
