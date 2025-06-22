#include "ui/CSimpleCheckboxScript.hpp"
#include "ui/CSimpleCheckbox.hpp"
#include "ui/CSimpleTexture.hpp"
#include "util/Lua.hpp"
#include "util/StringTo.hpp"
#include "util/Unimplemented.hpp"


int32_t CSimpleCheckbox_SetChecked(lua_State* L) {
    auto type = CSimpleCheckbox::GetObjectType();
    auto checkbox = static_cast<CSimpleCheckbox*>(FrameScript_GetObjectThis(L, type));

    int32_t state = StringToBOOL(L, 2, 1);
    checkbox->SetChecked(state, 0);
    return 0;
}

int32_t CSimpleCheckbox_GetChecked(lua_State* L) {
    auto type = CSimpleCheckbox::GetObjectType();
    auto checkbox = static_cast<CSimpleCheckbox*>(FrameScript_GetObjectThis(L, type));

    if (checkbox->GetChecked()) {
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }

    return 1;
}

int32_t CSimpleCheckbox_GetCheckedTexture(lua_State* L) {
    auto type = CSimpleCheckbox::GetObjectType();
    auto checkbox = static_cast<CSimpleCheckbox*>(FrameScript_GetObjectThis(L, type));
    auto texture = checkbox->m_checkedTexture;

    if (texture) {
        if (!texture->lua_registered) {
            texture->RegisterScriptObject(nullptr);
        }
        lua_rawgeti(L, LUA_REGISTRYINDEX, texture->lua_objectRef);
    } else {
        lua_pushnil(L);
    }

    return 1;
}

int32_t CSimpleCheckbox_SetCheckedTexture(lua_State* L) {
    auto type = CSimpleCheckbox::GetObjectType();
    auto checkbox = static_cast<CSimpleCheckbox*>(FrameScript_GetObjectThis(L, type));
    auto name = checkbox->GetDisplayName();

    if (lua_type(L, 2) == LUA_TTABLE) {
        lua_rawgeti(L, 2, 0);
        auto texture = static_cast<CSimpleTexture*>(lua_touserdata(L, -1));
        lua_settop(L, -2);

        if (!texture) {
            luaL_error(L, "%s:SetCheckedTexture(): Couldn't find 'this' in texture", name);
        } else {
            auto textureType = CSimpleTexture::GetObjectType();
            if (!texture->IsA(textureType)) {
                luaL_error(L, "%s:SetCheckedTexture(): Wrong object type, expected texture", name);
                texture = nullptr;
            }
        }

        checkbox->SetCheckedTexture(texture);
        return 0;
    }

    if (lua_isstring(L, 2)) {
        auto texFile = lua_tostring(L, 2);
        checkbox->SetCheckedTexture(texFile);
        return 0;
    }

    if (lua_type(L, 2) != LUA_TNIL) {
        luaL_error(L, "Usage: %s:SetCheckedTexture(texture or \"texture\" or nil)", name);
    }

    checkbox->SetCheckedTexture(static_cast<CSimpleTexture*>(nullptr));
    return 0;
}

int32_t CSimpleCheckbox_GetDisabledCheckedTexture(lua_State* L) {
    auto type = CSimpleCheckbox::GetObjectType();
    auto checkbox = static_cast<CSimpleCheckbox*>(FrameScript_GetObjectThis(L, type));
    auto texture = checkbox->m_disabledTexture;

    if (texture) {
        if (!texture->lua_registered) {
            texture->RegisterScriptObject(nullptr);
        }
        lua_rawgeti(L, LUA_REGISTRYINDEX, texture->lua_objectRef);
    } else {
        lua_pushnil(L);
    }

    return 1;
}

int32_t CSimpleCheckbox_SetDisabledCheckedTexture(lua_State* L) {
    auto type = CSimpleCheckbox::GetObjectType();
    auto checkbox = static_cast<CSimpleCheckbox*>(FrameScript_GetObjectThis(L, type));
    auto name = checkbox->GetDisplayName();

    if (lua_type(L, 2) == LUA_TTABLE) {
        lua_rawgeti(L, 2, 0);
        auto texture = static_cast<CSimpleTexture*>(lua_touserdata(L, -1));
        lua_settop(L, -2);

        if (!texture) {
            luaL_error(L, "%s:SetDisabledCheckedTexture(): Couldn't find 'this' in texture", name);
        } else {
            auto textureType = CSimpleTexture::GetObjectType();
            if (!texture->IsA(textureType)) {
                luaL_error(L, "%s:SetDisabledCheckedTexture(): Wrong object type, expected texture", name);
                texture = nullptr;
            }
        }

        checkbox->SetDisabledCheckedTexture(texture);
        return 0;
    }

    if (lua_isstring(L, 2)) {
        auto texFile = lua_tostring(L, 2);
        checkbox->SetDisabledCheckedTexture(texFile);
        return 0;
    }

    if (lua_type(L, 2) != LUA_TNIL) {
        luaL_error(L, "Usage: %s:SetDisabledCheckedTexture(texture or \"texture\" or nil)", name);
    }

    checkbox->SetDisabledCheckedTexture(static_cast<CSimpleTexture*>(nullptr));
    return 0;
}

FrameScript_Method SimpleCheckboxMethods[NUM_SIMPLE_CHECKBOX_SCRIPT_METHODS] = {
    { "SetChecked",                  &CSimpleCheckbox_SetChecked },
    { "GetChecked",                  &CSimpleCheckbox_GetChecked },
    { "GetCheckedTexture",           &CSimpleCheckbox_GetCheckedTexture },
    { "SetCheckedTexture",           &CSimpleCheckbox_SetCheckedTexture },
    { "GetDisabledCheckedTexture",   &CSimpleCheckbox_GetDisabledCheckedTexture },
    { "SetDisabledCheckedTexture",   &CSimpleCheckbox_SetDisabledCheckedTexture }
};
