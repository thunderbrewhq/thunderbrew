#include "ui/CSimpleMessageScrollFrame.hpp"
#include "ui/CSimpleMessageScrollFrameScript.hpp"

int32_t CSimpleMessageScrollFrame::s_metatable = 0;
int32_t CSimpleMessageScrollFrame::s_objectType = 0;

void CSimpleMessageScrollFrame::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CSimpleMessageScrollFrame::RegisterScriptMethods);
    CSimpleMessageScrollFrame::s_metatable = ref;
}

int32_t CSimpleMessageScrollFrame::GetObjectType() {
    if (!CSimpleMessageScrollFrame::s_objectType) {
        CSimpleMessageScrollFrame::s_objectType = ++FrameScript_Object::s_objectTypes;
    }

    return CSimpleMessageScrollFrame::s_objectType;
}

void CSimpleMessageScrollFrame::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, SimpleMessageScrollFrameMethods, NUM_SIMPLE_MESSAGE_SCROLL_FRAME_SCRIPT_METHODS);
}

CSimpleMessageScrollFrame::CSimpleMessageScrollFrame(CSimpleFrame* parent)
    : CSimpleHyperlinkedFrame(parent) {
}

bool CSimpleMessageScrollFrame::IsA(int32_t type) {
    return type == CSimpleMessageScrollFrame::s_objectType
        || type == CSimpleFrame::s_objectType
        || type == CScriptRegion::s_objectType
        || type == CScriptObject::s_objectType;
}

int32_t CSimpleMessageScrollFrame::GetScriptMetaTable() {
    return CSimpleMessageScrollFrame::s_metatable;
}
