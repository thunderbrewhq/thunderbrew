#include "ui/CSimpleMessageFrame.hpp"
#include "ui/CSimpleMessageFrameScript.hpp"

int32_t CSimpleMessageFrame::s_metatable = 0;
int32_t CSimpleMessageFrame::s_objectType = 0;

void CSimpleMessageFrame::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CSimpleMessageFrame::RegisterScriptMethods);
    CSimpleMessageFrame::s_metatable = ref;
}

int32_t CSimpleMessageFrame::GetObjectType() {
    if (!CSimpleMessageFrame::s_objectType) {
        CSimpleMessageFrame::s_objectType = ++FrameScript_Object::s_objectTypes;
    }

    return CSimpleMessageFrame::s_objectType;
}

void CSimpleMessageFrame::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, SimpleMessageFrameMethods, NUM_SIMPLE_MESSAGE_FRAME_SCRIPT_METHODS);
}

CSimpleMessageFrame::CSimpleMessageFrame(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}

bool CSimpleMessageFrame::IsA(int32_t type) {
    return type == CSimpleMessageFrame::s_objectType
        || type == CSimpleFrame::s_objectType
        || type == CScriptRegion::s_objectType
        || type == CScriptObject::s_objectType;
}

int32_t CSimpleMessageFrame::GetScriptMetaTable() {
    return CSimpleMessageFrame::s_metatable;
}
