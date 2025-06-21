#include "ui/CSimpleCheckboxScript.hpp"
#include "ui/CSimpleCheckbox.hpp"
#include "util/Lua.hpp"
#include "util/StringTo.hpp"
#include "util/Unimplemented.hpp"


int32_t CSimpleCheckbox_SetChecked(lua_State* L) {
    auto type = CSimpleCheckbox::GetObjectType();
    auto checkbox = static_cast<CSimpleCheckbox*>(FrameScript_GetObjectThis(L, type));

    int32_t state = StringToBOOL(L, 2, 0);
    checkbox->SetChecked(state, 0);
    return 0;
}

int32_t CSimpleCheckbox_GetChecked(lua_State* L) {
    auto type = CSimpleCheckbox::GetObjectType();
    auto checkbox = static_cast<CSimpleCheckbox*>(FrameScript_GetObjectThis(L, type));

    lua_Number state = checkbox->GetChecked() ? 1.0 : 0.0;
    lua_pushnumber(L, state);
    return 1;
}

int32_t CSimpleCheckbox_GetCheckedTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleCheckbox_SetCheckedTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleCheckbox_GetDisabledCheckedTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t CSimpleCheckbox_SetDisabledCheckedTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

FrameScript_Method SimpleCheckboxMethods[NUM_SIMPLE_CHECKBOX_SCRIPT_METHODS] = {
    { "SetChecked",                  &CSimpleCheckbox_SetChecked },
    { "GetChecked",                  &CSimpleCheckbox_GetChecked },
    { "GetCheckedTexture",           &CSimpleCheckbox_GetCheckedTexture },
    { "SetCheckedTexture",           &CSimpleCheckbox_SetCheckedTexture },
    { "GetDisabledCheckedTexture",   &CSimpleCheckbox_GetDisabledCheckedTexture },
    { "SetDisabledCheckedTexture",   &CSimpleCheckbox_SetDisabledCheckedTexture }
};
