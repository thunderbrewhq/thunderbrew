#include <cstdint>
#include <storm/String.hpp>
#include "console/Handlers.hpp"
#include "console/Line.hpp"
#include "console/Console.hpp"
#include "console/Command.hpp"
#include "console/Screen.hpp"
#include "console/Text.hpp"
#include "console/Highlight.hpp"
#include "event/Event.hpp"
#include "event/Types.hpp"

#define SHIFT_MODIFIER(data) ((data->metaKeyState & ((1 << KEY_LSHIFT) | (1 << KEY_RSHIFT))) != 0)
#define CTRL_MODIFIER(data) ((data->metaKeyState & ((1 << KEY_LCONTROL) | (1 << KEY_RCONTROL))) != 0)

namespace {

int32_t OnChar(const EVENT_DATA_CHAR* data, void* param) {
    char character[2];

    if (ConsoleAccessGetEnabled() && EventIsKeyDown(ConsoleGetHotKey())) {
        return 0;
    }

    if (ConsoleGetActive()) {
        character[0] = char(data->ch);
        character[1] = 0;

        // TODO: add custom behavior to support non-ASCII commands?
        // SUniSPutUTF8(data->ch, character);

        PasteInInputLine(character);
        ResetHighlight();
        return 0;
    }

    return 1;
}

int32_t OnIdle(const EVENT_DATA_IDLE* data, void* param) {
    if (s_repeatCount && (*s_repeatBuffer)) {
        ConsoleCommandExecute(s_repeatBuffer, 0);
        s_repeatCount--;
    }

    ConsoleScreenAnimate(data->elapsedSec);

    return 1;
}

int32_t OnKeyDown(const EVENT_DATA_KEY* data, void* param) {
    if (data->key == ConsoleGetHotKey() && ConsoleAccessGetEnabled()) {
        // Toggle the console on/off if the console hotkey is pressed down
        // and the console access is enabled for the client
        ConsoleSetActive(!ConsoleGetActive());

        // Reset the highlight when toggled off
        if (!ConsoleGetActive()) {
            ResetHighlight();
        }

        return 0;
    }

    if (EventIsKeyDown(ConsoleGetHotKey()) || !ConsoleGetActive()) {
        return 1;
    }

    auto lineptr = GetInputLine();

    switch (data->key) {
    case KEY_ESCAPE:
        if (lineptr->inputstart < lineptr->inputpos) {
            ConsoleSetActive(0);
        } else {
            lineptr->inputpos = lineptr->inputstart;
            lineptr->chars = lineptr->inputstart;
            lineptr->buffer[lineptr->inputstart] = '\0';
            SetInputString(lineptr->buffer);
        }
        break;
    case KEY_C:
        if (CTRL_MODIFIER(data)) {
            CopyHighlightToClipboard();
        }
        break;
    case KEY_V:
        if (CTRL_MODIFIER(data)) {
            PasteClipboardInInputLine();
        }
        break;
    case KEY_ENTER:
        if (lineptr->inputstart < lineptr->inputpos) {
            lineptr->inputpos = 0;
            GenerateNodeString(lineptr);
            ConsoleCommandExecute(lineptr->buffer + lineptr->inputstart, 1);
            s_historyIndex = -1;
        }
        break;
    case KEY_BACKSPACE:
        lineptr->Backspace();
        break;
    case KEY_TAB:
        if (s_completionMode == 0) {
            s_completedCmd = nullptr;
            s_completionMode = 1;
            SStrCopy(s_partial, lineptr->buffer + lineptr->inputstart, STORM_MAX_STR);
        }
        if (ConsoleCommandComplete(s_partial, &s_completedCmd, SHIFT_MODIFIER(data))) {
            MakeCommandCurrent(lineptr, s_completedCmd);
        }
        SetInputString(lineptr->buffer);
        break;
    case KEY_LEFT:
        if (lineptr->inputstart < lineptr->inputpos) {
            lineptr->inputpos--;
        }
        break;
    case KEY_UP:
        lineptr->Up();
        break;
    case KEY_RIGHT:
        if (lineptr->inputpos < lineptr->chars) {
            lineptr->inputpos++;
        }
        break;
    case KEY_DOWN:
        lineptr->Down();
        break;
    case KEY_DELETE:
        lineptr->Delete();
        break;
    case KEY_HOME:
        if (CTRL_MODIFIER(data)) {
            s_currlineptr = s_linelist.Tail();
        } else {
            if (lineptr->inputpos > lineptr->inputstart) {
                lineptr->inputpos = lineptr->inputstart;
            }
        }
        break;
    case KEY_END:
        if (CTRL_MODIFIER(data)) {
            s_currlineptr = s_linelist.Head();
        } else {
            if (lineptr->inputpos < lineptr->chars) {
                lineptr->inputpos = lineptr->chars;
            }
        }
        break;
    case KEY_PAGEUP:
        MoveLinePtr(1, SHIFT_MODIFIER(data));
        break;
    case KEY_PAGEDOWN:
        MoveLinePtr(0, SHIFT_MODIFIER(data));
        break;
    default:
        break;
    }

    if (data->key != KEY_TAB
     && data->key != KEY_LSHIFT
     && data->key != KEY_RSHIFT
     && data->key != KEY_LALT
     && data->key != KEY_RALT
     && !(CTRL_MODIFIER(data))) {
        s_completionMode = 0;
        ResetHighlight();
    }

    return 0;
}

int32_t OnKeyDownRepeat(const EVENT_DATA_KEY* data, void* param) {
    if (data->key == ConsoleGetHotKey() && ConsoleAccessGetEnabled()) {
        ConsoleSetActive(!ConsoleGetActive());
        return 0;
    }

    if (EventIsKeyDown(ConsoleGetHotKey()) || !ConsoleGetActive()) {
        return 1;
    }

    auto lineptr = GetInputLine();

    switch (data->key) {
    case KEY_BACKSPACE:
        lineptr->Backspace();
        break;
    case KEY_LEFT:
        if (lineptr->inputstart < lineptr->inputpos) {
            lineptr->inputpos--;
        }
        break;
    case KEY_UP:
        lineptr->Up();
        break;
    case KEY_RIGHT:
        if (lineptr->inputstart < lineptr->inputpos) {
            lineptr->inputpos++;
        }
        break;
    case KEY_DOWN:
        lineptr->Down();
        break;
    case KEY_DELETE:
        lineptr->Delete();
        break;
    case KEY_PAGEUP:
        MoveLinePtr(1, SHIFT_MODIFIER(data));
        break;
    case KEY_PAGEDOWN:
        MoveLinePtr(0, SHIFT_MODIFIER(data));
        break;
    default:
        break;
    }

    if (data->key != KEY_TAB
     && data->key != KEY_LSHIFT
     && data->key != KEY_RSHIFT
     && data->key != KEY_LALT
     && data->key != KEY_RALT
     && !(CTRL_MODIFIER(data))) {
        s_completionMode = 0;
        ResetHighlight();
    }

    return 1;
}

int32_t OnKeyUp(const EVENT_DATA_KEY* data, void* param) {
    if (data->key == ConsoleGetHotKey()) {
        if (ConsoleAccessGetEnabled()) {
            return 0;
        }
    }

    return !ConsoleGetActive();
}

int32_t OnMouseDown(const EVENT_DATA_MOUSE* data, void* param) {
    if (EventIsKeyDown(ConsoleGetHotKey()) || !ConsoleGetActive() || (1.0f - s_consoleHeight) > data->y) {
        return 1;
    }

    float clickPos = 1.0f - data->y;

    if (clickPos < (std::min(s_consoleHeight, 1.0f) - (s_fontHeight * 0.75f)) || clickPos > s_consoleHeight) {
        ResetHighlight();

        auto lineptr = GetLineAtMousePosition(data->y);

        if (lineptr) {
            SStrCopy(s_copyText, lineptr->buffer, CONSOLE_HIGHLIGHT_CLIPBOARD_SIZE);
            s_highlightState = HS_HIGHLIGHTING;

            float v7 = 1.0f - (s_consoleHeight - (s_fontHeight * 0.75f) - (s_fontHeight) - ((s_consoleHeight - clickPos) / s_fontHeight - 1.0) * s_fontHeight);

            s_hRect.bottom = v7;
            s_hRect.top = v7 - s_fontHeight;

            s_highlightHStart = v7;
            s_highlightHEnd = v7;

            UpdateHighlight();

            return 0;
        }

        s_copyText[0] = '\0';
        return 0;
    }

    ResetHighlight();
    s_consoleResizeState = CS_STRETCH;

    return 1;
}

int32_t OnMouseMove(const EVENT_DATA_MOUSE* data, void* param) {
    if (EventIsKeyDown(ConsoleGetHotKey()) || !ConsoleGetActive()) {
        return 1;
    }

    if (s_consoleResizeState == CS_STRETCH) {
        auto newHeight = std::max(1.0f - data->y, s_fontHeight);
        s_consoleHeight = newHeight;
    } else if ((1.0f - s_consoleHeight) > data->y) {
        return 1;
    }

    s_highlightHEnd = data->x;

    if (s_highlightState == HS_HIGHLIGHTING) {
        UpdateHighlight();
    }

    return 1;
}

int32_t OnMouseUp(const EVENT_DATA_MOUSE* data, void* param) {
    if (EventIsKeyDown(ConsoleGetHotKey()) || !ConsoleGetActive()) {
        return 1;
    }

    s_highlightState = HS_ENDHIGHLIGHT;
    s_consoleResizeState = CS_NONE;

    return 1;
}

}

void RegisterHandlers() {
    EventRegisterEx(EVENT_ID_CHAR, reinterpret_cast<EVENTHANDLERFUNC>(OnChar), nullptr, 7.0f);
    EventRegisterEx(EVENT_ID_IDLE, reinterpret_cast<EVENTHANDLERFUNC>(OnIdle), nullptr, 7.0f);
    EventRegisterEx(EVENT_ID_KEYDOWN, reinterpret_cast<EVENTHANDLERFUNC>(OnKeyDown), nullptr, 7.0f);
    EventRegisterEx(EVENT_ID_KEYUP, reinterpret_cast<EVENTHANDLERFUNC>(OnKeyUp), nullptr, 7.0f);
    EventRegisterEx(EVENT_ID_KEYDOWN_REPEATING, reinterpret_cast<EVENTHANDLERFUNC>(OnKeyDownRepeat), nullptr, 7.0f);
    EventRegisterEx(EVENT_ID_MOUSEDOWN, reinterpret_cast<EVENTHANDLERFUNC>(OnMouseDown), nullptr, 7.0f);
    EventRegisterEx(EVENT_ID_MOUSEUP, reinterpret_cast<EVENTHANDLERFUNC>(OnMouseUp), nullptr, 7.0f);
    EventRegisterEx(EVENT_ID_MOUSEMOVE, reinterpret_cast<EVENTHANDLERFUNC>(OnMouseMove), nullptr, 7.0f);
}
