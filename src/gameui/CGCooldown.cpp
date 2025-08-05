#include "gameui/CGCooldown.hpp"
#include "gameui/CGCooldownScript.hpp"
#include <bc/Memory.hpp>

int32_t CGCooldown::s_metatable;

CSimpleFrame* CGCooldown::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGCooldown@@", -2);
    return NEW(CGCooldown, parent);
}

void CGCooldown::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CGCooldown::RegisterScriptMethods);
    CGCooldown::s_metatable = ref;
}

void CGCooldown::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, CGCooldownMethods, NUM_CGCOOLDOWN_SCRIPT_METHODS);
}

int32_t CGCooldown::GetScriptMetaTable() {
    return CGCooldown::s_metatable;
}

CGCooldown::CGCooldown(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}
