#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_BankButtonIDToInvSlotID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumBankSlots(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetBankSlotCost(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PurchaseSlot(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CloseBankFrame(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void BankRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_BANK; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Bank[i].name,
            GameScript::s_ScriptFunctions_Bank[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_Bank[NUM_SCRIPT_FUNCTIONS_BANK] = {
    { "BankButtonIDToInvSlotID", &Script_BankButtonIDToInvSlotID },
    { "GetNumBankSlots", &Script_GetNumBankSlots },
    { "GetBankSlotCost", &Script_GetBankSlotCost },
    { "PurchaseSlot", &Script_PurchaseSlot },
    { "CloseBankFrame", &Script_CloseBankFrame },
};
