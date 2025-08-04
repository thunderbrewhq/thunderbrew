#include "gameui/CGTooltip.hpp"
#include "gameui/CGTooltipScript.hpp"
#include <bc/Memory.hpp>

int32_t CGTooltip::s_metatable;

CSimpleFrame* CGTooltip::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGTooltip@@", -2);
    return NEW(CGTooltip, parent);
}

void CGTooltip::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CGTooltip::RegisterScriptMethods);
    CGTooltip::s_metatable = ref;
}

void CGTooltip::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, CGTooltipMethods, NUM_CGTOOLTIP_SCRIPT_METHODS);
}

int32_t CGTooltip::GetScriptMetaTable() {
    return CGTooltip::s_metatable;
}

CGTooltip::CGTooltip(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}
