#ifndef OS_INPUT_HPP
#define OS_INPUT_HPP

#include "os/Types.hpp"
#include <cstdint>

int32_t OsInputGet(OSINPUT* id, int32_t* param0, int32_t* param1, int32_t* param2, int32_t* param3);

void OsInputSetWindowResizeLock(int32_t resizeLock);

void OsInputInitialize();

bool OsInputIsUsingCocoaEventLoop();

void OsInputPostEvent(OSINPUT id, int32_t param0, int32_t param1, int32_t param2, int32_t param3);

void OsInputSetMouseMode(OS_MOUSE_MODE mode);

void OsInputGetMousePosition(int32_t* x, int32_t* y);

int32_t OsWindowProc(void* window, uint32_t message, uintptr_t wparam, intptr_t lparam);

#endif
