#ifndef CONSOLE_SCREEN_HPP
#define CONSOLE_SCREEN_HPP

#include "console/Types.hpp"

extern float s_consoleLines;
extern float s_consoleHeight;
extern CONSOLERESIZESTATE s_consoleResizeState;
extern CImVector s_colorArray[NUM_COLORTYPES];

void ConsoleScreenAnimate(float elapsedSec);

void ConsoleScreenInitialize(const char* title);

#endif
