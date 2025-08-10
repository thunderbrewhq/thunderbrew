#include "ui/CSimpleStatusBar.hpp"
#include "ui/CSimpleStatusBarScript.hpp"

int32_t CSimpleStatusBar::s_metatable = 0;
int32_t CSimpleStatusBar::s_objectType = 0;

void CSimpleStatusBar::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CSimpleStatusBar::RegisterScriptMethods);
    CSimpleStatusBar::s_metatable = ref;
}

int32_t CSimpleStatusBar::GetObjectType() {
    if (!CSimpleStatusBar::s_objectType) {
        CSimpleStatusBar::s_objectType = ++FrameScript_Object::s_objectTypes;
    }

    return CSimpleStatusBar::s_objectType;
}

void CSimpleStatusBar::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, SimpleStatusBarMethods, NUM_SIMPLE_STATUS_BAR_SCRIPT_METHODS);
}

CSimpleStatusBar::CSimpleStatusBar(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}

bool CSimpleStatusBar::IsA(int32_t type) {
    return type == CSimpleStatusBar::s_objectType
        || type == CSimpleFrame::s_objectType
        || type == CScriptRegion::s_objectType
        || type == CScriptObject::s_objectType;
}

int32_t CSimpleStatusBar::GetScriptMetaTable() {
    return CSimpleStatusBar::s_metatable;
}
