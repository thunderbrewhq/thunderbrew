#include "gameui/CGDressUpModelFrame.hpp"
#include "gameui/CGDressUpModelFrameScript.hpp"
#include <bc/Memory.hpp>

int32_t CGDressUpModelFrame::s_metatable;

CSimpleFrame* CGDressUpModelFrame::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGDressUpModelFrame@@", -2);
    return NEW(CGDressUpModelFrame, parent);
}

void CGDressUpModelFrame::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CGDressUpModelFrame::RegisterScriptMethods);
    CGDressUpModelFrame::s_metatable = ref;
}

void CGDressUpModelFrame::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, CGDressUpModelFrameMethods, NUM_CGDRESS_UP_MODEL_FRAME_SCRIPT_METHODS);
}

int32_t CGDressUpModelFrame::GetScriptMetaTable() {
    return CGDressUpModelFrame::s_metatable;
}

CGDressUpModelFrame::CGDressUpModelFrame(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}
