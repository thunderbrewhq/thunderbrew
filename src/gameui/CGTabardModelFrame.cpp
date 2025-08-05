#include "gameui/CGTabardModelFrame.hpp"
#include "gameui/CGTabardModelFrameScript.hpp"
#include <bc/Memory.hpp>

int32_t CGTabardModelFrame::s_metatable;

CSimpleFrame* CGTabardModelFrame::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGTabardModelFrame@@", -2);
    return NEW(CGTabardModelFrame, parent);
}

void CGTabardModelFrame::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CGTabardModelFrame::RegisterScriptMethods);
    CGTabardModelFrame::s_metatable = ref;
}

void CGTabardModelFrame::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, CGTabardModelFrameMethods, NUM_CGTABARD_MODEL_FRAME_SCRIPT_METHODS);
}

int32_t CGTabardModelFrame::GetScriptMetaTable() {
    return CGTabardModelFrame::s_metatable;
}

CGTabardModelFrame::CGTabardModelFrame(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}
