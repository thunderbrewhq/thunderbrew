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

void CSimpleHyperlinkedFrame::OnHyperlinkClick(const char* link, const char* text, const char* button) {
    if (this->m_onHyperlinkClick.luaRef) {
        auto L = FrameScript_GetContext();
        lua_pushstring(L, link);
        lua_pushstring(L, text);
        lua_pushstring(L, button);

        this->RunScript(this->m_onHyperlinkClick, 3, 0);
    }
}

void CSimpleHyperlinkedFrame::OnHyperlinkLeave(const char* link, const char* text) {
    if (this->m_onHyperlinkLeave.luaRef) {
        auto L = FrameScript_GetContext();
        lua_pushstring(L, link);
        lua_pushstring(L, text);

        this->RunScript(this->m_onHyperlinkLeave, 2, 0);
    }
}

void CSimpleHyperlinkedFrame::OnHyperlinkEnter(const char* link, const char* text) {
    if (this->m_onHyperlinkEnter.luaRef) {
        auto L = FrameScript_GetContext();
        lua_pushstring(L, link);
        lua_pushstring(L, text);

        this->RunScript(this->m_onHyperlinkEnter, 2, 0);
    }
}
