#include "console/Highlight.hpp"
#include "console/Text.hpp"
#include "os/Clipboard.hpp"

HIGHLIGHTSTATE s_highlightState = HS_NONE;
RECTF s_hRect = { 0.0f, 0.0f, 0.0f, 0.0f };
float s_highlightHStart = 0.0f;
float s_highlightHEnd = 0.0f;
uint32_t s_highlightLeftCharIndex = 0;
uint32_t s_highlightRightCharIndex = 0;
int32_t s_highlightInput = 0;
char s_copyText[CONSOLE_HIGHLIGHT_CLIPBOARD_SIZE] = { 0 };

void ResetHighlight() {
    s_highlightState = HS_NONE;
    s_hRect = { 0.0f, 0.0f, 0.0f, 0.0f };
}

void UpdateHighlight() {
    auto font = TextBlockGetFontPtr(s_textFont);
    STORM_ASSERT(font);

    auto len = SStrLen(s_copyText);

    float left = std::min(s_highlightHStart, s_highlightHEnd);
    float right = std::max(s_highlightHStart, s_highlightHEnd);

    auto chars = GxuFontGetMaxCharsWithinWidth(font, s_copyText, s_fontHeight, left, len, &s_hRect.left, 0.0f, 1.0f, s_charSpacing, s_baseTextFlags);

    s_highlightLeftCharIndex = chars;

    if (chars) {
        s_highlightRightCharIndex = chars - 1;
    }

    if (s_hRect.left < 0.015f) {
        s_hRect.left = 0.0f;
    }

    s_highlightRightCharIndex = GxuFontGetMaxCharsWithinWidth(font, s_copyText, s_fontHeight, right, len, &s_hRect.right, 0.0f, 1.0f, s_charSpacing, s_baseTextFlags);
}

void CopyHighlightToClipboard() {
    char buffer[CONSOLE_HIGHLIGHT_CLIPBOARD_SIZE];

    if (s_copyText[0] != '\0') {
        auto highlightWidth = s_highlightRightCharIndex - s_highlightLeftCharIndex;
        if (highlightWidth >= (CONSOLE_HIGHLIGHT_CLIPBOARD_SIZE-1)) {
            highlightWidth = CONSOLE_HIGHLIGHT_CLIPBOARD_SIZE-1;
        }

        SStrCopy(buffer, &s_copyText[s_highlightLeftCharIndex], highlightWidth);
        buffer[highlightWidth] = '\0';

        OsClipboardPutString(buffer);
    }

    ResetHighlight();
}
