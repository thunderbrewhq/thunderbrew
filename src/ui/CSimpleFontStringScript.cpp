#include "ui/CSimpleFontStringScript.hpp"
#include "ui/CSimpleFont.hpp"
#include "ui/CSimpleFontString.hpp"
#include "ui/Util.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"
#include "util/StringTo.hpp"
#include "gx/Coordinate.hpp"
#include <cstdint>

int32_t CSimpleFontString_IsObjectType(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    if (!lua_isstring(L, 2)) {
        return luaL_error(L, "Usage: %s:IsObjectType(\"TYPE\")", string->GetDisplayName());
    }

    if (string->IsA(lua_tolstring(L, 2, nullptr))) {
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int32_t CSimpleFontString_GetObjectType(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));
    lua_pushstring(L, string->GetObjectTypeName());
    return 1;
}

int32_t CSimpleFontString_GetDrawLayer(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));
    auto layer = DrawLayerToString(string->m_drawlayer);
    lua_pushstring(L, layer);
    return 1;
}

int32_t CSimpleFontString_SetDrawLayer(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    const char* strlayer = lua_isstring(L, 2) ? lua_tostring(L, 2) : nullptr;

    int32_t layer = 0;
    if (!strlayer || !StringToDrawLayer(strlayer, layer)) {
        return luaL_error(L, "Usage: %s:SetDrawLayer(\"layer\")", string->GetDisplayName());
    }

    string->SetFrame(string->m_parent, layer, string->m_shown);
    return 0;
}

int32_t CSimpleFontString_SetVertexColor(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    CImVector color;
    string->GetVertexColor(color);

    CImVector newColor;
    FrameScript_GetColor(L, 2, newColor);
    if (!lua_isnumber(L, 5)) {
        newColor.a = color.a;
    }

    string->SetVertexColor(color);
    // TODO: Some flag should be set
    return 0;
}

int32_t CSimpleFontString_GetAlpha(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    CImVector color;
    string->GetVertexColor(color);
    lua_pushnumber(L, color.a / 255.0);
    return 1;
}

int32_t CSimpleFontString_SetAlpha(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    if (!lua_isnumber(L, 2)) {
        return luaL_error(L, "Usage: %s:SetAlpha(alpha)", string->GetDisplayName());
    }

    CImVector color;
    string->GetVertexColor(color);

    color.a = lua_tonumber(L, 2) * 255.0;
    string->SetVertexColor(color);
    return 0;
}

int32_t CSimpleFontString_SetAlphaGradient(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    if (!lua_isnumber(L, 2) || !lua_isnumber(L, 3)) {
        return luaL_error(L, "Usage: %s:SetAlphaGradient(start, length)", string->GetDisplayName());
    }

    auto start = lua_tonumber(L, 2);
    auto length = lua_tonumber(L, 3);
    if (string->SetAlphaGradient(start, length)) {
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int32_t CSimpleFontString_Show(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    string->Show();

    return 0;
}

int32_t CSimpleFontString_Hide(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    string->Hide();

    return 0;
}

int32_t CSimpleFontString_IsVisible(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));
    if (string->m_visible) {
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int32_t CSimpleFontString_IsShown(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));
    if (string->m_shown) {
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int32_t CSimpleFontString_GetFontObject(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));
    if (string->m_fontObject) {
        if (!string->m_fontObject->lua_registered) {
            string->m_fontObject->RegisterScriptObject(nullptr);
        }
        lua_rawgeti(L, LUA_REGISTRYINDEX, string->m_fontObject->lua_objectRef);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

int32_t CSimpleFontString_SetFontObject(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    CSimpleFont* font = nullptr;

    if (lua_type(L, 2) == LUA_TTABLE) {
        lua_rawgeti(L, 2, 0);
        font = static_cast<CSimpleFont*>(lua_touserdata(L, -1));
        lua_settop(L, -2);

        if (!font) {
            luaL_error(L, "%s:SetFontObject(): Couldn't find 'this' in font object", string->GetDisplayName());
        }

        if (!font->IsA(CSimpleFont::GetObjectType())) {
            luaL_error(L, "%s:SetFontObject(): Wrong object type, expected font", string->GetDisplayName());
        }
    } else if (lua_type(L, 2) == LUA_TSTRING) {
        auto fontName = lua_tolstring(L, 2, nullptr);
        font = CSimpleFont::GetFont(fontName, 0);

        if (!font) {
            luaL_error(L, "%s:SetFontObject(): Couldn't find font named %s", string->GetDisplayName(), fontName);
        }
    } else if (lua_type(L, 2) != LUA_TNIL) {
        luaL_error(L, "Usage: %s:SetFontObject(font or \"font\" or nil)", string->GetDisplayName());
    }

    string->SetFontObject(font);

    return 0;
}

int32_t CSimpleFontString_GetFont(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    lua_pushstring(L, string->GetFontName());

    auto height = string->GetFontHeight(false);
    height *= CoordinateGetAspectCompensation() * 1024.0f;
    height = DDCToNDCWidth(height);
    lua_pushnumber(L, height);

    auto flags = FontFlagsToString(string->GetFontFlags());
    lua_pushstring(L, flags);

    return 3;
}

int32_t CSimpleFontString_SetFont(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetFieldSize(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetText(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    if (!string->m_font) {
        luaL_error(L, "%s:SetText(): Font not set", string->GetDisplayName());
    }

    const char* text = lua_tolstring(L, 2, 0);
    string->SetText(text, 1);

    return 0;
}

int32_t CSimpleFontString_SetFormattedText(lua_State* L) {
    auto type = CSimpleFontString::GetObjectType();
    auto string = static_cast<CSimpleFontString*>(FrameScript_GetObjectThis(L, type));

    if (!string->m_font) {
        luaL_error(L, "%s:SetFormattedText(): Font not set", string->GetDisplayName());
    }

    char buffer[4096];
    auto text = FrameScript_Sprintf(L, 2, buffer, sizeof(buffer));
    string->SetText(text, 1);
    return 0;
}

int32_t CSimpleFontString_GetTextColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetTextColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetShadowColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetShadowColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetShadowOffset(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetShadowOffset(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetSpacing(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetSpacing(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetTextHeight(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetStringWidth(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetStringHeight(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetJustifyH(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetJustifyH(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetJustifyV(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetJustifyV(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_CanNonSpaceWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetNonSpaceWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_CanWordWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetWordWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_GetIndentedWordWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleFontString_SetIndentedWordWrap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

FrameScript_Method SimpleFontStringMethods[NUM_SIMPLE_FONT_STRING_SCRIPT_METHODS] = {
    { "IsObjectType",           &CSimpleFontString_IsObjectType },
    { "GetObjectType",          &CSimpleFontString_GetObjectType },
    { "GetDrawLayer",           &CSimpleFontString_GetDrawLayer },
    { "SetDrawLayer",           &CSimpleFontString_SetDrawLayer },
    { "SetVertexColor",         &CSimpleFontString_SetVertexColor },
    { "GetAlpha",               &CSimpleFontString_GetAlpha },
    { "SetAlpha",               &CSimpleFontString_SetAlpha },
    { "SetAlphaGradient",       &CSimpleFontString_SetAlphaGradient },
    { "Show",                   &CSimpleFontString_Show },
    { "Hide",                   &CSimpleFontString_Hide },
    { "IsVisible",              &CSimpleFontString_IsVisible },
    { "IsShown",                &CSimpleFontString_IsShown },
    { "GetFontObject",          &CSimpleFontString_GetFontObject },
    { "SetFontObject",          &CSimpleFontString_SetFontObject },
    { "GetFont",                &CSimpleFontString_GetFont },
    { "SetFont",                &CSimpleFontString_SetFont },
    { "GetText",                &CSimpleFontString_GetText },
    { "GetFieldSize",           &CSimpleFontString_GetFieldSize },
    { "SetText",                &CSimpleFontString_SetText },
    { "SetFormattedText",       &CSimpleFontString_SetFormattedText },
    { "GetTextColor",           &CSimpleFontString_GetTextColor },
    { "SetTextColor",           &CSimpleFontString_SetTextColor },
    { "GetShadowColor",         &CSimpleFontString_GetShadowColor },
    { "SetShadowColor",         &CSimpleFontString_SetShadowColor },
    { "GetShadowOffset",        &CSimpleFontString_GetShadowOffset },
    { "SetShadowOffset",        &CSimpleFontString_SetShadowOffset },
    { "GetSpacing",             &CSimpleFontString_GetSpacing },
    { "SetSpacing",             &CSimpleFontString_SetSpacing },
    { "SetTextHeight",          &CSimpleFontString_SetTextHeight },
    { "GetStringWidth",         &CSimpleFontString_GetStringWidth },
    { "GetStringHeight",        &CSimpleFontString_GetStringHeight },
    { "GetJustifyH",            &CSimpleFontString_GetJustifyH },
    { "SetJustifyH",            &CSimpleFontString_SetJustifyH },
    { "GetJustifyV",            &CSimpleFontString_GetJustifyV },
    { "SetJustifyV",            &CSimpleFontString_SetJustifyV },
    { "CanNonSpaceWrap",        &CSimpleFontString_CanNonSpaceWrap },
    { "SetNonSpaceWrap",        &CSimpleFontString_SetNonSpaceWrap },
    { "CanWordWrap",            &CSimpleFontString_CanWordWrap },
    { "SetWordWrap",            &CSimpleFontString_SetWordWrap },
    { "GetIndentedWordWrap",    &CSimpleFontString_GetIndentedWordWrap },
    { "SetIndentedWordWrap",    &CSimpleFontString_SetIndentedWordWrap }
};
