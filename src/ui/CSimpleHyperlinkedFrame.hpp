#ifndef UI_C_SIMPLE_HYPERLINKED_FRAME_HPP
#define UI_C_SIMPLE_HYPERLINKED_FRAME_HPP

#include "ui/CSimpleFrame.hpp"

class CSimpleHyperlinkedFrame : public CSimpleFrame {
    public:
        // Member functions
        CSimpleHyperlinkedFrame(CSimpleFrame* parent);
        virtual ScriptIx* GetScriptByName(const char* name, ScriptData& data);

        void OnHyperlinkClick(const char* a2, const char* a3, const char* a4);
        void OnHyperlinkLeave(const char* a2, const char* a3);
        void OnHyperlinkEnter(const char* a2, const char* a3);

        // Member variables
        ScriptIx m_onHyperlinkEnter;
        ScriptIx m_onHyperlinkLeave;
        ScriptIx m_onHyperlinkClick;
};

#endif
