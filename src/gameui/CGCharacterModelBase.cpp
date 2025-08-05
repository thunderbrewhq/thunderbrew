#include "gameui/CGCharacterModelBase.hpp"
#include "gameui/CGCharacterModelBaseScript.hpp"
#include <bc/Memory.hpp>

int32_t CGCharacterModelBase::s_metatable;

CSimpleFrame* CGCharacterModelBase::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGCharacterModelBase@@", -2);
    return NEW(CGCharacterModelBase, parent);
}

void CGCharacterModelBase::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CGCharacterModelBase::RegisterScriptMethods);
    CGCharacterModelBase::s_metatable = ref;
}

void CGCharacterModelBase::RegisterScriptMethods(lua_State* L) {
    CSimpleModel::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, CGCharacterModelBaseMethods, NUM_CGCHARACTER_MODEL_BASE_SCRIPT_METHODS);
}

int32_t CGCharacterModelBase::GetScriptMetaTable() {
    return CGCharacterModelBase::s_metatable;
}

CGCharacterModelBase::CGCharacterModelBase(CSimpleFrame* parent) : CSimpleModel(parent) {
}
