#include <common/Time.hpp>

#include "os/Input.hpp"
#include "os/Queue.hpp"

#include "os/internal/Queue.hpp"

#if defined(WHOA_BUILD_GLSDL)
#include "os/sdl/Input.hpp"
#endif

int32_t OsInputGet(OSINPUT* id, int32_t* param0, int32_t* param1, int32_t* param2, int32_t* param3) {
#if defined(WHOA_BUILD_GLSDL)
    if (OsSDLInputActive()) {
        return OsSDLInputGet(id, param0, param1, param2, param3);
    }
#endif
    if (s_queueTail == s_queueHead) {
        return 0;
    }

    OsQueueSetParam(3, OsGetAsyncTimeMs());

    return OsQueueGet(id, param0, param1, param2, param3);
}

void OsInputSetWindowResizeLock(int32_t resizeLock) {
#if defined(WHOA_BUILD_GLSDL)
    OsSDLInputSetWindowResizeLock(resizeLock);
#endif
}

void OsInputInitialize() {
}

bool OsInputIsUsingCocoaEventLoop() {
    return false;
}

void OsInputPostEvent(OSINPUT id, int32_t param0, int32_t param1, int32_t param2, int32_t param3) {
    // TODO
}

void OsInputSetMouseMode(OS_MOUSE_MODE mode) {
    // TODO
}

void OsInputGetMousePosition(int32_t* x, int32_t* y) {
#if defined(WHOA_BUILD_GLSDL)
    if (OsSDLInputActive()) {
        OsSDLInputGetMousePosition(x, y);
        return;
    }
#endif

    if (x) {
        *x = 0;
    }
    if (y) {
        *y = 0;
    }
}

int32_t OsWindowProc(void* window, uint32_t message, uintptr_t wparam, intptr_t lparam) {
    return 0;
}
