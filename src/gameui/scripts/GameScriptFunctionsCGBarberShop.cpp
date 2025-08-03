#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetBarberShopStyleInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetNextBarberShopStyle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetBarberShopTotalCost(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ApplyBarberShopStyle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CancelBarberShop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetHairCustomization(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetFacialHairCustomization(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_BarberShopReset(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanAlterSkin(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void CGBarberShopRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_CGBARBER_SHOP; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_CGBarberShop[i].name,
            GameScript::s_ScriptFunctions_CGBarberShop[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_CGBarberShop[NUM_SCRIPT_FUNCTIONS_CGBARBER_SHOP] = {
    { "GetBarberShopStyleInfo", &Script_GetBarberShopStyleInfo },
    { "SetNextBarberShopStyle", &Script_SetNextBarberShopStyle },
    { "GetBarberShopTotalCost", &Script_GetBarberShopTotalCost },
    { "ApplyBarberShopStyle", &Script_ApplyBarberShopStyle },
    { "CancelBarberShop", &Script_CancelBarberShop },
    { "GetHairCustomization", &Script_GetHairCustomization },
    { "GetFacialHairCustomization", &Script_GetFacialHairCustomization },
    { "BarberShopReset", &Script_BarberShopReset },
    { "CanAlterSkin", &Script_CanAlterSkin },
};
