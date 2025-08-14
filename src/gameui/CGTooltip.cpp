#include "gameui/CGTooltip.hpp"
#include "gameui/CGTooltipScript.hpp"
#include "gx/Coordinate.hpp"
#include "ui/CSimpleFontString.hpp"
#include "ui/CSimpleStatusBar.hpp"
#include "ui/CSimpleTexture.hpp"
#include "util/Lua.hpp"
#include <bc/Memory.hpp>
#include <common/XML.hpp>

int32_t CGTooltip::s_metatable;
int32_t CGTooltip::s_objectType;
CImVector CGTooltip::s_defaultColor{ 0, 210, 255, 255 };

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

void CGTooltip::ClearTooltip() {
    // TODO
    for (uint32_t line = 0; line < this->m_lines; ++line) {
        auto leftString = this->m_leftStrings[line];
        leftString->SetWidth(0.0f);
        leftString->SetText("", 1);
        leftString->Hide();

        auto rightString = this->m_rightStrings[line];
        rightString->SetWidth(0.0f);
        rightString->SetText("", 1);
        rightString->Hide();

        this->m_wrapLine[line] = 0;
    }

    if (!this->m_minWidthForced) {
        this->m_minWidth = 0.0f;
    }

    if (this->m_lines && this->m_onTooltipCleared.luaRef) {
        this->RunScript(this->m_onTooltipCleared, 0, nullptr);
    }
}

void CGTooltip::ResetPosition(int32_t a1) {
}

void CGTooltip::SetAnchorType(TOOLTIP_ANCHORPOINT anchorpoint, float xoffset, float yoffset) {
    this->m_offsetX = xoffset;
    this->m_offsetY = yoffset;
    if (this->m_owner) {
        this->m_anchorPoint = anchorpoint;
    }
    this->ResetPosition(1);
}

void CGTooltip::SetOwner(CSimpleFrame* owner, TOOLTIP_ANCHORPOINT anchorpoint, float xoffset, float yoffset) {
    this->ClearTooltip();
    this->SetFrameAlpha(255);
    // TODO: this->unk77 = 0;

    if (this->m_owner != owner
        || this->m_anchorPoint != anchorpoint
        || this->m_offsetX != xoffset
        || this->m_offsetY != yoffset) {
        this->m_offsetX = xoffset;
        this->m_offsetY = yoffset;
        this->m_owner = owner;
        this->m_anchorPoint = owner ? anchorpoint : ANCHOR_NONE;
        this->ResetPosition(1);
    }
}

void CGTooltip::AddFontStrings(CSimpleFontString* leftstring, CSimpleFontString* rightstring) {
    this->m_linesMax++;
    this->m_leftStrings.SetCount(this->m_linesMax);
    this->m_rightStrings.SetCount(this->m_linesMax);
    this->m_wrapLine.SetCount(this->m_linesMax);
    this->m_leftStrings[this->m_linesMax - 1] = leftstring;
    this->m_rightStrings[this->m_linesMax - 1] = rightstring;
    this->m_wrapLine[this->m_linesMax - 1] = 0;
}

void CGTooltip::AddLine(
    const char* leftText,
    const char* rightText,
    const CImVector& leftColor,
    const CImVector& rightColor,
    int32_t wrapped) {
    if ((!leftText || !*leftText) && (!rightText || !*rightText)) {
        return;
    }

    if (!this->m_linesMax) {
        return;
    }

    if (this->m_lines == this->m_linesMax - 1) {
        auto lastLeftString = this->m_leftStrings[this->m_linesMax - 1];
        auto lastRightString = this->m_rightStrings[this->m_linesMax - 1];

        char name[256];
        SStrPrintf(name, sizeof(name), "%sTextLeft%d", this->GetDisplayName(), this->m_linesMax + 1);
        // TODO: CDataAllocator
        auto leftFontString = NEW(CSimpleFontString, this, 2, 1);
        leftFontString->SetName(name);
        leftFontString->SetFontObject(lastLeftString->GetFontObject());

        float yoffset = -2.0f / (CoordinateGetAspectCompensation() * 1024.0f);
        yoffset = NDCToDDCWidth(yoffset);
        leftFontString->SetPoint(FRAMEPOINT_TOPLEFT, lastLeftString, FRAMEPOINT_BOTTOMLEFT, 0.0f, yoffset, 0);
        leftFontString->Hide();

        SStrPrintf(name, sizeof(name), "%sTextRight%d", this->GetDisplayName(), this->m_linesMax + 1);
        // TODO: CDataAllocator
        auto rightFontString = NEW(CSimpleFontString, this, 2, 1);
        rightFontString->SetName(name);
        rightFontString->SetFontObject(lastRightString->GetFontObject());

        float xoffset = 40.0f / (CoordinateGetAspectCompensation() * 1024.0f);
        xoffset = NDCToDDCWidth(xoffset);
        rightFontString->SetPoint(FRAMEPOINT_RIGHT, leftFontString, FRAMEPOINT_LEFT, xoffset, 0.0f, 0);
        rightFontString->Hide();

        this->AddFontStrings(leftFontString, rightFontString);
    }

    if (leftText && *leftText) {
        auto leftString = this->m_leftStrings[this->m_lines];
        leftString->SetVertexColor(leftColor);
        leftString->SetText(leftText, 1);
        leftString->Show();
    }

    if (rightText && *rightText) {
        auto rightString = this->m_rightStrings[this->m_lines];
        rightString->SetVertexColor(rightColor);
        rightString->SetText(rightText, 1);
        rightString->Show();
        wrapped = 0;
    }

    this->m_wrapLine[this->m_lines++] = wrapped;
}

void CGTooltip::FadeOut() {
    if (this->m_anchorPoint == ANCHOR_LEFT || this->m_anchorPoint == ANCHOR_CURSOR_RIGHT) {
        this->HideThis();
        this->m_fading = 0;
    } else {
        this->m_fading = 1;
        this->m_fadeTime = TOOLTIP_FADE_TIME;
    }
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

void CGTooltip::PostLoadXML(XMLNode* node, CStatus* status) {
    CSimpleFrame::PostLoadXML(node, status);
    for (int32_t pass = 0; pass < 2; ++pass) {
        if (pass == 1) {
            this->m_leftStrings.SetCount(this->m_linesMax);
            this->m_rightStrings.SetCount(this->m_linesMax);
            this->m_wrapLine.SetCount(this->m_linesMax);
        }

        for (this->m_linesMax = 0; true; ++this->m_linesMax) {
            char name[256];
            SStrPrintf(name, sizeof(name), "%sTextLeft%d", this->GetDisplayName(), this->m_linesMax + 1);
            auto leftObject = CScriptObject::GetScriptObjectByName(name, CGTooltip::GetObjectType());

            SStrPrintf(name, sizeof(name), "%sTextRight%d", this->GetDisplayName(), this->m_linesMax + 1);
            auto rightObject = CScriptObject::GetScriptObjectByName(name, CGTooltip::GetObjectType());

            if (!leftObject || !rightObject) {
                break;
            }

            if (pass == 1) {
                this->m_leftStrings[this->m_linesMax] = static_cast<CSimpleFontString*>(leftObject);
                this->m_rightStrings[this->m_linesMax] = static_cast<CSimpleFontString*>(rightObject);
                this->m_wrapLine[this->m_linesMax] = 0;
            }
        }
    }

    for (int32_t i = 0; i < 10; ++i) {
        char name[256];
        SStrPrintf(name, sizeof(name), "%sTexture%d", this->GetDisplayName(), i);
        auto object = CScriptObject::GetScriptObjectByName(name, CSimpleTexture::GetObjectType());
        this->m_textures[i] = static_cast<CSimpleTexture*>(object);
    }

    char name[256];
    SStrPrintf(name, sizeof(name), "%sStatusBar", this->GetDisplayName());
    auto object = CScriptObject::GetScriptObjectByName(name, CSimpleStatusBar::GetObjectType());
    this->m_statusBar = static_cast<CSimpleStatusBar*>(object);
}
