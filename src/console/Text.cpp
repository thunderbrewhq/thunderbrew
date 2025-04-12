#include "console/Text.hpp"

CGxStringBatch* s_batch;
uint32_t s_baseTextFlags = 0x8;
int32_t s_caret = 0;
float s_caretpixwidth;
float s_caretpixheight;
float s_charSpacing = 0.0f;
CGxString* s_inputString = nullptr;
char s_fontName[STORM_MAX_PATH];
float s_fontHeight = 0.02f;
HTEXTFONT s_textFont;
