#include "ui/CSimpleHyperlinkButton.hpp"
#include "ui/CSimpleHyperlinkedFrame.hpp"
#include "ui/CSimpleFontString.hpp"
#include "gx/Coordinate.hpp"
#include <bc/Memory.hpp>


CSimpleHyperlinkButton::CSimpleHyperlinkButton(CSimpleHyperlinkedFrame* parent)
    : CSimpleButton(parent) {
}

void CSimpleHyperlinkButton::SetHyperlink(CSimpleFontString* string, const GXUFONTHYPERLINKINFO* hyperlink) {
    if (!string || !hyperlink) {
        this->Hide();
        return;
    }

    this->m_hyperlink = static_cast<char*>(SMemReAlloc(this->m_hyperlink, hyperlink->linkLength + 1, __FILE__, __LINE__, 0));
    SStrCopy(this->m_hyperlink, hyperlink->link, hyperlink->linkLength + 1);

    CRect extent;
    NDCToDDC(hyperlink->extent.minX, hyperlink->extent.minY, &extent.minX, &extent.minY);
    NDCToDDC(hyperlink->extent.maxX, hyperlink->extent.maxY, &extent.maxX, &extent.maxY);

    // TODO: switch()

    this->ClearAllPoints();
    this->SetPoint(
        FRAMEPOINT_TOPLEFT,
        string,
        FRAMEPOINT_TOPLEFT,
        extent.minX / this->m_layoutScale,
        extent.minY / this->m_layoutScale,
        1);

    float width = (extent.maxX - extent.minX) / this->m_layoutScale;
    float height = (extent.maxY - extent.minY) / this->m_layoutScale;
    this->SetSize(width, height);
    this->Show();
}

void CSimpleHyperlinkButton::OnLayerCursorEnter(int32_t a2) {
}

void CSimpleHyperlinkButton::OnLayerCursorExit(int32_t a2, int32_t a3) {
}

void CSimpleHyperlinkButton::OnClick(const char* btn, int32_t a3) {
}
