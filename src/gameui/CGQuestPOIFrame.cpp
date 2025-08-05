#include "gameui/CGQuestPOIFrame.hpp"
#include "gameui/CGQuestPOIFrameScript.hpp"
#include <bc/Memory.hpp>

int32_t CGQuestPOIFrame::s_metatable;

CSimpleFrame* CGQuestPOIFrame::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGQuestPOIFrame@@", -2);
    return NEW(CGQuestPOIFrame, parent);
}

void CGQuestPOIFrame::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CGQuestPOIFrame::RegisterScriptMethods);
    CGQuestPOIFrame::s_metatable = ref;
}

void CGQuestPOIFrame::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, CGQuestPOIFrameMethods, NUM_CGQUEST_POI_FRAME_SCRIPT_METHODS);
}

int32_t CGQuestPOIFrame::GetScriptMetaTable() {
    return CGQuestPOIFrame::s_metatable;
}

CGQuestPOIFrame::CGQuestPOIFrame(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}
