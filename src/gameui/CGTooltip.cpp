#include "gameui/CGTooltip.hpp"
#include "gameui/CGTooltipScript.hpp"
#include "util/Lua.hpp"
#include <bc/Memory.hpp>

int32_t CGTooltip::s_metatable;
int32_t CGTooltip::s_objectType;

CSimpleFrame* CGTooltip::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGTooltip@@", -2);
    return NEW(CGTooltip, parent);
}

void CGTooltip::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CGTooltip::RegisterScriptMethods);
    CGTooltip::s_metatable = ref;
}

int32_t CGTooltip::GetObjectType() {
    if (!CGTooltip::s_objectType) {
        CGTooltip::s_objectType = ++FrameScript_Object::s_objectTypes;
    }

    return CGTooltip::s_objectType;
}

void CGTooltip::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, CGTooltipMethods, NUM_CGTOOLTIP_SCRIPT_METHODS);
}

CGTooltip::CGTooltip(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}

bool CGTooltip::IsA(int32_t type) {
    return type == CGTooltip::s_objectType
        || type == CSimpleFrame::s_objectType
        || type == CScriptRegion::s_objectType
        || type == CScriptObject::s_objectType;
}

int32_t CGTooltip::GetScriptMetaTable() {
    return CGTooltip::s_metatable;
}

FrameScript_Object::ScriptIx* CGTooltip::GetScriptByName(const char* name, ScriptData& data) {
    auto result = this->CSimpleFrame::GetScriptByName(name, data);
    if (result)
        return result;

    if (!SStrCmpI(name, "OnTooltipSetDefaultAnchor", STORM_MAX_STR)) {
        return &this->m_onTooltipSetDefaultAnchor;
    }

    if (!SStrCmpI(name, "OnTooltipCleared", STORM_MAX_STR)) {
        return &this->m_onTooltipCleared;
    }

    if (!SStrCmpI(name, "OnTooltipAddMoney", STORM_MAX_STR)) {
        data.wrapper = "return function(self,cost,maxcost) %s end";
        return &this->m_onTooltipAddMoney;
    }

    if (!SStrCmpI(name, "OnTooltipSetUnit", STORM_MAX_STR)) {
        return &this->m_onTooltipSetUnit;
    }

    if (!SStrCmpI(name, "OnTooltipSetItem", STORM_MAX_STR)) {
        return &this->m_onTooltipSetItem;
    }

    if (!SStrCmpI(name, "OnTooltipSetSpell", STORM_MAX_STR)) {
        return &this->m_onTooltipSetSpell;
    }

    if (!SStrCmpI(name, "OnTooltipSetQuest", STORM_MAX_STR)) {
        return &this->m_onTooltipSetQuest;
    }

    if (!SStrCmpI(name, "OnTooltipSetAchievement", STORM_MAX_STR)) {
        return &this->m_onTooltipSetAchievement;
    }

    if (!SStrCmpI(name, "OnTooltipSetEquipmentSet", STORM_MAX_STR)) {
        return &this->m_onTooltipSetEquipmentSet;
    }

    if (!SStrCmpI(name, "OnTooltipSetFrameStack", STORM_MAX_STR)) {
        return &this->m_onTooltipSetFrameStack;
    }

    return nullptr;
}
