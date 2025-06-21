#include "ui/CSimpleCheckbox.hpp"
#include "ui/CSimpleCheckboxScript.hpp"
#include "ui/CSimpleTexture.hpp"

int32_t CSimpleCheckbox::s_metatable;
int32_t CSimpleCheckbox::s_objectType;

void CSimpleCheckbox::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CSimpleCheckbox::RegisterScriptMethods);
    CSimpleCheckbox::s_metatable = ref;
}

int32_t CSimpleCheckbox::GetObjectType() {
    if (!CSimpleCheckbox::s_objectType) {
        CSimpleCheckbox::s_objectType = ++FrameScript_Object::s_objectTypes;
    }

    return CSimpleCheckbox::s_objectType;
}

void CSimpleCheckbox::RegisterScriptMethods(lua_State* L) {
    CSimpleButton::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, SimpleCheckboxMethods, NUM_SIMPLE_CHECKBOX_SCRIPT_METHODS);
}

CSimpleCheckbox::CSimpleCheckbox(CSimpleFrame* parent)
    : CSimpleButton(parent) {
}

int32_t CSimpleCheckbox::GetScriptMetaTable() {
    return CSimpleCheckbox::s_metatable;
}

void CSimpleCheckbox::Enable(int32_t enabled) {
    this->CSimpleButton::Enable(enabled);
    this->SetChecked(this->m_checked, 1);
}

void CSimpleCheckbox::SetChecked(int32_t state, int32_t force) {
    if (state == this->m_checked && !force) {
        return;
    }

    this->m_checked = state;
    if (this->m_checkedTexture) {
        this->m_checkedTexture->Hide();
    }

    if (this->m_disabledTexture) {
        this->m_disabledTexture->Hide();
    }

    if (this->m_checked) {
        if (!this->m_disabledTexture || this->m_state) {
            if (this->m_checkedTexture) {
                this->m_checkedTexture->Show();
            }
        } else {
            this->m_disabledTexture->Show();
        }
    }
}

int32_t CSimpleCheckbox::GetChecked() {
    return this->m_checked;
}

void CSimpleCheckbox::OnClick(const char* btn, int32_t a3) {
    this->SetChecked(this->m_checked == 0, 0);
    this->CSimpleButton::OnClick(btn, a3);
}

bool CSimpleCheckbox::IsA(int32_t type) {
    return type == CSimpleCheckbox::s_objectType
        || type == CSimpleButton::s_objectType
        || type == CSimpleFrame::s_objectType
        || type == CScriptRegion::s_objectType
        || type == CScriptObject::s_objectType;
}
