#include "gameui/GameScriptFunctions.hpp"
#include "gameui/CGUIBindings.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetNumBindings(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetBinding(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetBinding(lua_State* L) {
    if (!lua_isstring(L, 1)) {
        return luaL_error(L, "Usage: SetBinding(\"KEY\"[, \"COMMAND\"][, mode])");
    }

    int32_t mode = BINDING_MODE_0;
    if (lua_isnumber(L, 3)) {
        mode = static_cast<int32_t>(lua_tonumber(L, 3)) - 1;
        if (mode < BINDING_MODE_0 || mode > BINDING_MODE_3) {
            mode = BINDING_MODE_0;
        }
    }
    auto key = lua_tolstring(L, 1, 0);
    auto command = lua_tolstring(L, 2, 0);
    if (CGUIBindings::s_bindings->Bind(BINDING_SCRIPT, static_cast<BINDING_MODE>(mode), key, command)) {
        FrameScript_SignalEvent(0x177u, 0);
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int32_t Script_SetBindingSpell(lua_State* L) {
    if (!lua_isstring(L, 1) || !lua_isstring(L, 2)) {
        return luaL_error(L, "Usage: SetBindingSpell(\"KEY\", \"spellname\"[, mode])");
    }

    int32_t mode = BINDING_MODE_0;
    if (lua_isnumber(L, 3)) {
        mode = static_cast<int32_t>(lua_tonumber(L, 3)) - 1;
        if (mode < BINDING_MODE_0 || mode > BINDING_MODE_3) {
            mode = BINDING_MODE_0;
        }
    }
    auto key = lua_tolstring(L, 1, 0);

    auto spellName = lua_tolstring(L, 2, 0);
    auto length = SStrLen(spellName) + 7;
    auto command = static_cast<char*>(alloca(length));
    SStrPrintf(command, length, "SPELL %s", spellName);

    if (CGUIBindings::s_bindings->Bind(BINDING_SCRIPT, static_cast<BINDING_MODE>(mode), key, command)) {
        FrameScript_SignalEvent(0x177u, 0);
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int32_t Script_SetBindingItem(lua_State* L) {
    if (!lua_isstring(L, 1) || !lua_isstring(L, 2)) {
        return luaL_error(L, "Usage: SetBindingItem(\"KEY\", \"itemname\"[, mode])");
    }

    int32_t mode = BINDING_MODE_0;
    if (lua_isnumber(L, 3)) {
        mode = static_cast<int32_t>(lua_tonumber(L, 3)) - 1;
        if (mode < BINDING_MODE_0 || mode > BINDING_MODE_3) {
            mode = BINDING_MODE_0;
        }
    }
    auto key = lua_tolstring(L, 1, 0);

    auto itemName = lua_tolstring(L, 2, 0);
    auto length = SStrLen(itemName) + 7;
    auto command = static_cast<char*>(alloca(length));
    SStrPrintf(command, length, "ITEM %s", itemName);

    if (CGUIBindings::s_bindings->Bind(BINDING_SCRIPT, static_cast<BINDING_MODE>(mode), key, command)) {
        FrameScript_SignalEvent(0x177u, 0);
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int32_t Script_SetBindingMacro(lua_State* L) {
    if (!lua_isstring(L, 1) || !lua_isstring(L, 2)) {
        return luaL_error(L, "Usage: SetBindingMacro(\"KEY\", \"macroname\"|macroid[, mode])");
    }

    int32_t mode = BINDING_MODE_0;
    if (lua_isnumber(L, 3)) {
        mode = static_cast<int32_t>(lua_tonumber(L, 3)) - 1;
        if (mode < BINDING_MODE_0 || mode > BINDING_MODE_3) {
            mode = BINDING_MODE_0;
        }
    }
    auto key = lua_tolstring(L, 1, 0);

    auto macroName = lua_tolstring(L, 2, 0);
    auto length = SStrLen(macroName) + 7;
    auto command = static_cast<char*>(alloca(length));
    SStrPrintf(command, length, "MACRO %s", macroName);

    if (CGUIBindings::s_bindings->Bind(BINDING_SCRIPT, static_cast<BINDING_MODE>(mode), key, command)) {
        FrameScript_SignalEvent(0x177u, 0);
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int32_t Script_SetBindingClick(lua_State* L) {
    if (!lua_isstring(L, 1) || !lua_isstring(L, 2)) {
        return luaL_error(L, "Usage: SetBindingClick(\"KEY\", \"buttonName\"[, \"mouseButton\"][, mode])");
    }

    int32_t mode = BINDING_MODE_0;
    if (lua_isnumber(L, 4)) {
        mode = static_cast<int32_t>(lua_tonumber(L, 4)) - 1;
        if (mode < BINDING_MODE_0 || mode > BINDING_MODE_3) {
            mode = BINDING_MODE_0;
        }
    }
    auto key = lua_tolstring(L, 1, 0);

    auto buttonName = lua_tolstring(L, 2, 0);

    auto mouseButton = lua_tolstring(L, 3, 0);
    if (!mouseButton) {
        mouseButton = "LeftButton";
    }

    auto length = SStrLen(buttonName) + SStrLen(mouseButton) + 8;
    auto command = static_cast<char*>(alloca(length));
    SStrPrintf(command, length, "CLICK %s:%s", buttonName, mouseButton);

    if (CGUIBindings::s_bindings->Bind(BINDING_SCRIPT, static_cast<BINDING_MODE>(mode), key, command)) {
        FrameScript_SignalEvent(0x177u, 0);
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int32_t Script_SetOverrideBinding(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetOverrideBindingSpell(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetOverrideBindingItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetOverrideBindingMacro(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetOverrideBindingClick(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClearOverrideBindings(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetBindingKey(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetBindingAction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetBindingByKey(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RunBinding(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCurrentBindingSet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LoadBindings(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SaveBindings(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumModifiedClickActions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetModifiedClickAction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetModifiedClick(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetModifiedClick(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsModifiedClick(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetClickFrame(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void UIBindingsRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_UIBINDINGS; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_UIBindings[i].name,
            GameScript::s_ScriptFunctions_UIBindings[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_UIBindings[NUM_SCRIPT_FUNCTIONS_UIBINDINGS] = {
    { "GetNumBindings", &Script_GetNumBindings },
    { "GetBinding", &Script_GetBinding },
    { "SetBinding", &Script_SetBinding },
    { "SetBindingSpell", &Script_SetBindingSpell },
    { "SetBindingItem", &Script_SetBindingItem },
    { "SetBindingMacro", &Script_SetBindingMacro },
    { "SetBindingClick", &Script_SetBindingClick },
    { "SetOverrideBinding", &Script_SetOverrideBinding },
    { "SetOverrideBindingSpell", &Script_SetOverrideBindingSpell },
    { "SetOverrideBindingItem", &Script_SetOverrideBindingItem },
    { "SetOverrideBindingMacro", &Script_SetOverrideBindingMacro },
    { "SetOverrideBindingClick", &Script_SetOverrideBindingClick },
    { "ClearOverrideBindings", &Script_ClearOverrideBindings },
    { "GetBindingKey", &Script_GetBindingKey },
    { "GetBindingAction", &Script_GetBindingAction },
    { "GetBindingByKey", &Script_GetBindingByKey },
    { "RunBinding", &Script_RunBinding },
    { "GetCurrentBindingSet", &Script_GetCurrentBindingSet },
    { "LoadBindings", &Script_LoadBindings },
    { "SaveBindings", &Script_SaveBindings },
    { "GetNumModifiedClickActions", &Script_GetNumModifiedClickActions },
    { "GetModifiedClickAction", &Script_GetModifiedClickAction },
    { "SetModifiedClick", &Script_SetModifiedClick },
    { "GetModifiedClick", &Script_GetModifiedClick },
    { "IsModifiedClick", &Script_IsModifiedClick },
    { "GetClickFrame", &Script_GetClickFrame },
};
