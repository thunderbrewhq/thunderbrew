#ifndef CONSOLE_HIGHLIGHT_HPP
#define CONSOLE_HIGHLIGHT_HPP

#include <cstdint>
#include <storm/Region.hpp>

#define CONSOLE_HIGHLIGHT_CLIPBOARD_SIZE 128

enum HIGHLIGHTSTATE {
    HS_NONE = 0,
    HS_HIGHLIGHTING = 1,
    HS_ENDHIGHLIGHT = 2,
    NUM_HIGHLIGHTSTATES
};

extern HIGHLIGHTSTATE s_highlightState;
extern RECTF s_hRect;
extern float s_highlightHStart;
extern float s_highlightHEnd;
extern uint32_t s_highlightLeftCharIndex;
extern uint32_t s_highlightRightCharIndex;
extern int32_t s_highlightInput;
extern char s_copyText[CONSOLE_HIGHLIGHT_CLIPBOARD_SIZE];

void ResetHighlight();

void UpdateHighlight();

void CopyHighlightToClipboard();

#endif
