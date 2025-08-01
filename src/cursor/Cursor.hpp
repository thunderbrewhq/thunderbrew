#ifndef CURSOR_CURSOR_HPP
#define CURSOR_CURSOR_HPP

#define CURSOR_IMAGE_SIZE (32 * 32)
#define CURSOR_IMAGE_BYTES (CURSOR_IMAGE_SIZE * 4)

#include "cursor/Types.hpp"

void CursorInitialize();
void CursorSetMode(CURSORMODE mode);
void CursorResetCursor();

#endif
