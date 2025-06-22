#include "ui/CSimpleCheckbox.hpp"
#include "ui/CSimpleCheckboxScript.hpp"
#include "ui/CSimpleTexture.hpp"
#include "ui/LoadXML.hpp"
#include "util/StringTo.hpp"
#include <common/XML.hpp>


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

void CSimpleCheckbox::LoadXML(XMLNode* node, CStatus* status) {
    CSimpleButton::LoadXML(node, status);

    const char* checked = node->GetAttributeByName("checked");

    if (checked && *checked) {
        this->SetChecked(StringToBOOL(checked), 0);
    }

    for (XMLNode* child = node->m_child; child; child = child->m_next) {
        if (!SStrCmpI(child->GetName(), "CheckedTexture", STORM_MAX_STR)) {
            CSimpleTexture* texture = LoadXML_Texture(child, this, status);
            this->SetCheckedTexture(texture);

        } else if (!SStrCmpI(child->GetName(), "DisabledCheckedTexture", STORM_MAX_STR)) {
            CSimpleTexture* texture = LoadXML_Texture(child, this, status);
            this->SetDisabledCheckedTexture(texture);
        }
    }
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

void CSimpleCheckbox::SetCheckedTexture(const char* texFile) {
    if (this->m_checkedTexture) {
        this->m_checkedTexture->SetTexture(texFile, false, false, GxTex_Linear, ImageMode_UI);
        return;
    }

    // TODO: CDataAllocator__GetData(CSimpleTexture::s_allocator, 0, ".?AVCSimpleTexture@@", -2);
    auto texture = NEW(CSimpleTexture, nullptr, DRAWLAYER_ARTWORK, 0);
    if (texture->SetTexture(texFile, false, false, GxTex_Linear, ImageMode_UI)) {
        texture->SetAllPoints(this, 1);
        texture->SetBlendMode(GxBlend_Add);
        this->SetCheckedTexture(texture);
    } else if (texture) {
        // TODO: FrameScript_Object::LookupScriptMethod(texture, 1);
    }
}

void CSimpleCheckbox::SetCheckedTexture(CSimpleTexture* texture) {
    if (texture == this->m_checkedTexture) {
        return;
    }

    if (this->m_checkedTexture) {
        // TODO: FrameScript_Object::LookupScriptMethod(this->m_checkedTexture, 1);
    }

    if (texture) {
        texture->SetFrame(this, 3, 0);
    }

    this->m_checkedTexture = texture;
    this->SetChecked(this->m_checked, 1);
}

void CSimpleCheckbox::SetDisabledCheckedTexture(const char* texFile) {
    if (this->m_disabledTexture) {
        this->m_disabledTexture->SetTexture(texFile, false, false, GxTex_Linear, ImageMode_UI);
        return;
    }

    // TODO: CDataAllocator__GetData(CSimpleTexture::s_allocator, 0, ".?AVCSimpleTexture@@", -2);
    auto texture = NEW(CSimpleTexture, nullptr, DRAWLAYER_ARTWORK, 0);
    if (texture->SetTexture(texFile, false, false, GxTex_Linear, ImageMode_UI)) {
        texture->SetAllPoints(this, 1);
        texture->SetBlendMode(GxBlend_Add);
        this->SetDisabledCheckedTexture(texture);
    } else if (texture) {
        // TODO: FrameScript_Object::LookupScriptMethod(texture, 1);
    }
}

void CSimpleCheckbox::SetDisabledCheckedTexture(CSimpleTexture* texture) {
    if (texture == this->m_disabledTexture) {
        return;
    }

    if (this->m_disabledTexture) {
        // TODO: FrameScript_Object::LookupScriptMethod(this->m_disabledTexture, 1);
    }

    if (texture) {
        texture->SetFrame(this, 3, 0);
    }

    this->m_disabledTexture = texture;
    this->SetChecked(this->m_checked, 1);
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
