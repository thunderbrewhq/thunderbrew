#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_CloseTrade(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClickTradeButton(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClickTargetTradeButton(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTradeTargetItemInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTradeTargetItemLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTradePlayerItemInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTradePlayerItemLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AcceptTrade(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CancelTradeAccept(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPlayerTradeMoney(lua_State* L) {
    // TODO
    lua_pushnumber(L, 0.0);
    return 1;
}

static int32_t Script_GetTargetTradeMoney(lua_State* L) {
    // TODO
    lua_pushnumber(L, 0.0);
    return 1;
}

static int32_t Script_PickupTradeMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddTradeMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetTradeMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void TradeInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_TRADE_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_TradeInfo[i].name,
            GameScript::s_ScriptFunctions_TradeInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_TradeInfo[NUM_SCRIPT_FUNCTIONS_TRADE_INFO] = {
    { "CloseTrade", &Script_CloseTrade },
    { "ClickTradeButton", &Script_ClickTradeButton },
    { "ClickTargetTradeButton", &Script_ClickTargetTradeButton },
    { "GetTradeTargetItemInfo", &Script_GetTradeTargetItemInfo },
    { "GetTradeTargetItemLink", &Script_GetTradeTargetItemLink },
    { "GetTradePlayerItemInfo", &Script_GetTradePlayerItemInfo },
    { "GetTradePlayerItemLink", &Script_GetTradePlayerItemLink },
    { "AcceptTrade", &Script_AcceptTrade },
    { "CancelTradeAccept", &Script_CancelTradeAccept },
    { "GetPlayerTradeMoney", &Script_GetPlayerTradeMoney },
    { "GetTargetTradeMoney", &Script_GetTargetTradeMoney },
    { "PickupTradeMoney", &Script_PickupTradeMoney },
    { "AddTradeMoney", &Script_AddTradeMoney },
    { "SetTradeMoney", &Script_SetTradeMoney },
};
