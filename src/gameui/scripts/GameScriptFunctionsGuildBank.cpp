#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_QueryGuildBankTab(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetCurrentGuildBankTab(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCurrentGuildBankTab(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankItemInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGuildBankTabInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankItemLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PickupGuildBankItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AutoStoreGuildBankItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SplitGuildBankItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumGuildBankTabs(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankTabInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankTabCost(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_BuyGuildBankTab(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DepositGuildBankMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_WithdrawGuildBankMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanWithdrawGuildBankMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PickupGuildBankMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankWithdrawMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CloseGuildBankFrame(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildTabardFileNames(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QueryGuildBankLog(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumGuildBankTransactions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankTransaction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumGuildBankMoneyTransactions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankMoneyTransaction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QueryGuildBankText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildBankText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGuildBankText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void GuildBankRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_GUILD_BANK; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_GuildBank[i].name,
            GameScript::s_ScriptFunctions_GuildBank[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_GuildBank[NUM_SCRIPT_FUNCTIONS_GUILD_BANK] = {
    { "QueryGuildBankTab", &Script_QueryGuildBankTab },
    { "SetCurrentGuildBankTab", &Script_SetCurrentGuildBankTab },
    { "GetCurrentGuildBankTab", &Script_GetCurrentGuildBankTab },
    { "GetGuildBankItemInfo", &Script_GetGuildBankItemInfo },
    { "SetGuildBankTabInfo", &Script_SetGuildBankTabInfo },
    { "GetGuildBankItemLink", &Script_GetGuildBankItemLink },
    { "PickupGuildBankItem", &Script_PickupGuildBankItem },
    { "AutoStoreGuildBankItem", &Script_AutoStoreGuildBankItem },
    { "SplitGuildBankItem", &Script_SplitGuildBankItem },
    { "GetNumGuildBankTabs", &Script_GetNumGuildBankTabs },
    { "GetGuildBankTabInfo", &Script_GetGuildBankTabInfo },
    { "GetGuildBankTabCost", &Script_GetGuildBankTabCost },
    { "BuyGuildBankTab", &Script_BuyGuildBankTab },
    { "DepositGuildBankMoney", &Script_DepositGuildBankMoney },
    { "WithdrawGuildBankMoney", &Script_WithdrawGuildBankMoney },
    { "CanWithdrawGuildBankMoney", &Script_CanWithdrawGuildBankMoney },
    { "PickupGuildBankMoney", &Script_PickupGuildBankMoney },
    { "GetGuildBankMoney", &Script_GetGuildBankMoney },
    { "GetGuildBankWithdrawMoney", &Script_GetGuildBankWithdrawMoney },
    { "CloseGuildBankFrame", &Script_CloseGuildBankFrame },
    { "GetGuildTabardFileNames", &Script_GetGuildTabardFileNames },
    { "QueryGuildBankLog", &Script_QueryGuildBankLog },
    { "GetNumGuildBankTransactions", &Script_GetNumGuildBankTransactions },
    { "GetGuildBankTransaction", &Script_GetGuildBankTransaction },
    { "GetNumGuildBankMoneyTransactions", &Script_GetNumGuildBankMoneyTransactions },
    { "GetGuildBankMoneyTransaction", &Script_GetGuildBankMoneyTransaction },
    { "QueryGuildBankText", &Script_QueryGuildBankText },
    { "GetGuildBankText", &Script_GetGuildBankText },
    { "SetGuildBankText", &Script_SetGuildBankText },
};
