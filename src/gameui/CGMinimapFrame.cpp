#include "gameui/CGMinimapFrame.hpp"
#include "gameui/CGMinimapFrameScript.hpp"
#include <bc/Memory.hpp>

int32_t CGMinimapFrame::s_metatable;

CSimpleFrame* CGMinimapFrame::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGMinimapFrame@@", -2);
    return NEW(CGMinimapFrame, parent);
}

void CGMinimapFrame::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CGMinimapFrame::RegisterScriptMethods);
    CGMinimapFrame::s_metatable = ref;
}

void CGMinimapFrame::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, CGMinimapFrameMethods, NUM_CGMINIMAP_FRAME_SCRIPT_METHODS);
}

int32_t CGMinimapFrame::GetScriptMetaTable() {
    return CGMinimapFrame::s_metatable;
}

CGMinimapFrame::CGMinimapFrame(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}
