#include "os/Input.hpp"
#include <common/Time.hpp>
#include <tempest/Vector.hpp>

double Input::s_savedMouseSpeed;

static C2iVector s_mousePos;

int32_t OsInputGet(OSINPUT* id, int32_t* param0, int32_t* param1, int32_t* param2, int32_t* param3) {
    // TODO
    // Unknown logic

    if (!OsInputIsUsingCocoaEventLoop()) {
        // Legacy Carbon input handling
        return 0;
    }

    // TODO
    // Steelseries WoW Mouse logic

    if (Input::s_queueTail == Input::s_queueHead) {
        return 0;
    }

    OsQueueSetParam(3, OsGetAsyncTimeMs());

    auto queue_result = OsQueueGet(id, param0, param1, param2, param3);
    if (queue_result) {
        if (*id == OS_INPUT_MOUSE_MOVE) {
            s_mousePos.x = *param1;
            s_mousePos.y = *param2;
        }
    }

    return queue_result;
}

void OsInputSetWindowResizeLock(int32_t resizeLock) {
    s_WindowResizeLock = resizeLock;
}

void OsInputInitialize() {
    // Legacy Carbon input handling
    // if (!byte_143EFE0) {
    //     Carbon_OsInputRegisterHICommandHandler(0x71756974, sub_A4F230);
    // }

    MacClient::SetMouseCoalescingEnabled(true);
    Input::s_savedMouseSpeed = MacClient::GetMouseSpeed();
}

bool OsInputIsUsingCocoaEventLoop() {
    // TODO

    return true;
}

void OsInputSetMouseMode(OS_MOUSE_MODE mode) {
    // TODO
}

void OsInputGetMousePosition(int32_t* x, int32_t* y) {
    if (x) {
        *x = s_mousePos.x;
    }

    if (y) {
        *y = s_mousePos.y;
    }
}

int32_t OsWindowProc(void* window, uint32_t message, uintptr_t wparam, intptr_t lparam) {
    return 0;
}
