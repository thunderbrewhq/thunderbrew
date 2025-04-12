#ifndef CONSOLE_TEXT_HPP
#define CONSOLE_TEXT_HPP

#include "gx/Font.hpp"
#include "storm/String.hpp"

extern CGxStringBatch* s_batch;
extern uint32_t s_baseTextFlags;
extern int32_t s_caret;
extern float s_caretpixwidth;
extern float s_caretpixheight;
extern float s_charSpacing;
extern CGxString* s_inputString;
extern char s_fontName[STORM_MAX_PATH];
extern float s_fontHeight;
extern HTEXTFONT s_textFont;

#endif
