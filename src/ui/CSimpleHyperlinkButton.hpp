#ifndef UI_C_SIMPLE_HYPERLINK_BUTTON_HPP
#define UI_C_SIMPLE_HYPERLINK_BUTTON_HPP

#include "ui/CSimpleButton.hpp"

class CSimpleHyperlinkedFrame;

class CSimpleHyperlinkButton : public CSimpleButton {
    public:
    // Member functions
    CSimpleHyperlinkButton(CSimpleHyperlinkedFrame* parent);
    void SetHyperlink(CSimpleFontString* string, const GXUFONTHYPERLINKINFO* hyperlink);

    virtual void OnLayerCursorEnter(int32_t a2);
    virtual void OnLayerCursorExit(int32_t a2, int32_t a3);
    virtual void OnClick(const char* btn, int32_t a3);


    // Member variables
    char* m_hyperlink = nullptr;
    TSLink<CSimpleHyperlinkButton> m_link;
};

#endif
