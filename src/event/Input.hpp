#ifndef EVENT_INPUT_HPP
#define EVENT_INPUT_HPP

#include "event/Types.hpp"
#include <cstdint>

class C2iVector;
class CRect;
class EvtContext;

namespace Input {
    extern int32_t s_buttonDown[16];
    extern uint32_t s_buttonState;
    extern C2iVector s_currentMouse;
    extern uint32_t s_mouseHoldButton;
    extern MOUSEMODE s_mouseMode;
    extern int32_t s_simulatedRightButtonClick;
    extern uint32_t s_metaKeyState;
}

void CheckMouseModeState();

MOUSEBUTTON ConvertButtonNumberToMOUSEBUTTON(int32_t buttonNumber);

void ConvertPosition(int32_t clientx, int32_t clienty, float* x, float* y);

void EventSetMouseMode(MOUSEMODE mode, uint32_t holdButton);

uint32_t GenerateMouseFlags();

const char* GetButtonName(int32_t button);

void IEvtInputInitialize();

int32_t IEvtInputProcess(EvtContext* context, int32_t* shutdown);

void IEvtInputSetMouseMode(EvtContext* context, MOUSEMODE mode, uint32_t holdButton);

const char* KeyCodeToString(KEY key);

#endif
