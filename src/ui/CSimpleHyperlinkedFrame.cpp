#include "ui/CSimpleHyperlinkedFrame.hpp"
#include "util/Lua.hpp"

CSimpleHyperlinkedFrame::CSimpleHyperlinkedFrame(CSimpleFrame* parent) : CSimpleFrame(parent) {
    // TODO
}

FrameScript_Object::ScriptIx* CSimpleHyperlinkedFrame::GetScriptByName(const char* name, ScriptData& data) {
    auto result = this->CSimpleFrame::GetScriptByName(name, data);
    if (result)
        return result;

    if (!SStrCmpI(name, "OnHyperlinkEnter", STORM_MAX_STR)) {
        data.wrapper = "return function(self,link,text) %s end";
        return &this->m_onHyperlinkEnter;
    }

    if (!SStrCmpI(name, "OnHyperlinkLeave", STORM_MAX_STR)) {
        data.wrapper = "return function(self,link,text) %s end";
        return &this->m_onHyperlinkLeave;
    }

    if (!SStrCmpI(name, "OnHyperlinkClick", STORM_MAX_STR)) {
        data.wrapper = "return function(self,link,text,button) %s end";
        return &this->m_onHyperlinkClick;
    }

    return nullptr;
}

void CSimpleHyperlinkedFrame::OnHyperlinkClick(const char* a2, const char* a3, const char* a4) {
    if (this->m_onHyperlinkClick.luaRef) {
        auto L = FrameScript_GetContext();
        lua_pushstring(L, a2);
        lua_pushstring(L, a3);

        this->RunScript(this->m_onHyperlinkClick, 2, 0);
    }
}

void CSimpleHyperlinkedFrame::OnHyperlinkLeave(const char* a2, const char* a3) {
    if (this->m_onHyperlinkLeave.luaRef) {
        auto L = FrameScript_GetContext();
        lua_pushstring(L, a2);
        lua_pushstring(L, a3);

        this->RunScript(this->m_onHyperlinkLeave, 2, 0);
    }
}

void CSimpleHyperlinkedFrame::OnHyperlinkEnter(const char* a2, const char* a3) {
    if (this->m_onHyperlinkEnter.luaRef) {
        auto L = FrameScript_GetContext();
        lua_pushstring(L, a2);
        lua_pushstring(L, a3);

        this->RunScript(this->m_onHyperlinkEnter, 2, 0);
    }
}
