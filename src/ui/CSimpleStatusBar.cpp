#include "ui/CSimpleStatusBar.hpp"
#include "ui/CSimpleStatusBarScript.hpp"
#include "ui/CSimpleTexture.hpp"
#include "util/Lua.hpp"

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

void CSimpleStatusBar::SetOrientation(uint32_t orientation) {
    this->m_flags |= 1;
    this->m_orientation = orientation;
}

void CSimpleStatusBar::SetMinMaxValues(float minValue, float maxValue) {
    if ((this->m_flags & 2) != 0 && this->m_minValue == minValue && this->m_maxValue == maxValue) {
        return;
    }

    this->m_flags |= 3;
    this->m_minValue = minValue;
    this->m_maxValue = maxValue;
    this->RunOnMinMaxChanged();

    if (this->m_flags & 4) {
        this->SetValue(this->m_value);
    }
}

void CSimpleStatusBar::SetBarTexture(const char* texFile, int32_t layer) {
    if (this->m_barTexture) {
        this->m_barTexture->SetTexture(texFile, false, false, GxTex_Linear, ImageMode_UI);
        return;
    }

    // TODO: CDataAllocator__GetData(CSimpleTexture::s_allocator, 0, ".?AVCSimpleTexture@@", -2);
    auto texture = NEW(CSimpleTexture, nullptr, DRAWLAYER_ARTWORK, 0);
    if (texture->SetTexture(texFile, false, false, GxTex_Linear, ImageMode_UI)) {
        texture->SetAllPoints(this, 1);
        texture->SetBlendMode(GxBlend_Add);
        this->SetBarTexture(texture, layer);
    } else if (texture) {
        // TODO: FrameScript_Object::LookupScriptMethod(texture, 1);
    }
}

void CSimpleStatusBar::SetBarTexture(CSimpleTexture* texture, int32_t layer) {
    if (texture == this->m_barTexture) {
        return;
    }

    if (this->m_barTexture) {
        // TODO: FrameScript_Object::LookupScriptMethod(this->m_checkedTexture, 1);
    }

    if (texture) {
        texture->SetFrame(this, layer, 1);
        texture->SetPoint(FRAMEPOINT_BOTTOMLEFT, this, FRAMEPOINT_BOTTOMLEFT, 0.0f, 0.0f, 1);
        texture->SetPoint(FRAMEPOINT_BOTTOMRIGHT, this, FRAMEPOINT_BOTTOMRIGHT, 0.0f, 0.0f, 1);
        texture->SetPoint(FRAMEPOINT_TOPLEFT, this, FRAMEPOINT_TOPLEFT, 0.0f, 0.0f, 1);
        texture->SetPoint(FRAMEPOINT_TOPRIGHT, this, FRAMEPOINT_TOPRIGHT, 0.0f, 0.0f, 1);
    }

    this->m_flags |= 1;
    this->m_barTexture = texture;
}

void CSimpleStatusBar::RunOnMinMaxChanged() {
    if (this->m_onMinMaxChanged.luaRef) {
        auto L = FrameScript_GetContext();
        lua_pushnumber(L, this->m_minValue);
        lua_pushnumber(L, this->m_maxValue);
        this->RunScript(this->m_onMinMaxChanged, 2, 0);
    }
}

void CSimpleStatusBar::RunOnValueChanged() {
    if (this->m_onValueChanged.luaRef) {
        auto L = FrameScript_GetContext();
        lua_pushnumber(L, this->m_value);
        this->RunScript(this->m_onMinMaxChanged, 1, 0);
    }
}

void CSimpleStatusBar::SetValue(float value) {
    if ((this->m_flags & 2) == 0) {
        return;
    }

    value = std::min(value, this->m_maxValue);
    value = std::max(value, this->m_minValue);

    if ((this->m_flags & 4) == 0 || this->m_value != value) {
        this->m_value = value;
        this->RunOnValueChanged();
    }
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

FrameScript_Object::ScriptIx* CSimpleStatusBar::GetScriptByName(const char* name, ScriptData& data) {
    auto parentScript = CSimpleFrame::GetScriptByName(name, data);

    if (parentScript) {
        return parentScript;
    }

    if (!SStrCmpI(name, "OnValueChanged", STORM_MAX_STR)) {
        data.wrapper = "return function(self,value) %s end";
        return &this->m_onValueChanged;
    }

    if (!SStrCmpI(name, "OnMinMaxChanged", STORM_MAX_STR)) {
        data.wrapper = "return function(self,min,max) %s end";
        return &this->m_onMinMaxChanged;
    }

    return nullptr;
}
