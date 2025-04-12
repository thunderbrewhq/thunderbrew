
#include "console/Console.hpp"
#include "console/Highlight.hpp"
#include "console/Line.hpp"
#include "console/Command.hpp"
#include "console/Text.hpp"
#include "console/Screen.hpp"
#include "gx/Device.hpp"
#include "os/Clipboard.hpp"
#include <bc/Memory.hpp>
#include <storm/Thread.hpp>
#include <cstdarg>
#include <cstdio>

int32_t s_historyIndex = 0;
// in this list
//  head = the input line
//  tail = the oldest line
STORM_LIST(CONSOLELINE) s_linelist;
CONSOLELINE* s_currlineptr;
uint32_t s_NumLines = 0;
SCritSect s_critsect;

void CONSOLELINE::Up() {
    if ((ConsoleCommandHistoryDepth() - 1) == s_historyIndex) {
        return;
    }

    auto previous = ConsoleCommandHistory(s_historyIndex + 1);

    if (previous) {
        MakeCommandCurrent(this, previous);
        s_historyIndex++;
        SetInputString(this->buffer);
    }
}

void CONSOLELINE::Down() {
    if (s_historyIndex == -1) {
        return;
    }

    const char* next;

    if (s_historyIndex == 0) {
        next = "";
    } else {
        if (!(next = ConsoleCommandHistory(s_historyIndex - 1))) {
            return;
        }
    }

    MakeCommandCurrent(this, next);
    s_historyIndex--;
    SetInputString(this->buffer);
}

void CONSOLELINE::Delete() {
    if (this->inputpos > this->chars) {
        return;
    }

    auto pos = this->inputpos;
    memmove(this->buffer + pos, this->buffer + pos + 1, this->chars - pos);
    this->chars--;
    SetInputString(this->buffer);
}

void CONSOLELINE::Backspace() {
    auto pos = this->inputpos;

    if (this->inputstart >= pos) {
        return;
    }

    if (pos < this->chars) {
        memmove(this->buffer + pos - 1, this->buffer + pos, (this->chars - pos) + 1);
    } else {
        this->buffer[pos - 1] = '\0';
    }

    this->inputpos--;
    this->chars--;
    SetInputString(this->buffer);
}

CONSOLELINE::~CONSOLELINE() {
    if (this->buffer) {
        FREE(this->buffer);
    }

    if (this->fontPointer) {
        GxuFontDestroyString(this->fontPointer);
    }
}

void GenerateNodeString(CONSOLELINE* node) {
    auto font = TextBlockGetFontPtr(s_textFont);

    if (font && node && node->buffer && node->buffer[0] != '\0') {
        if (node->fontPointer) {
            GxuFontDestroyString(node->fontPointer);
        }

        C3Vector pos = {
            0.0f, 0.0f, 1.0f
        };

        GxuFontCreateString(
            font,
            node->buffer,
            s_fontHeight,
            pos,
            1.0f,
            s_fontHeight,
            0.0f,
            node->fontPointer,
            GxVJ_Middle, GxHJ_Left,
            s_baseTextFlags,
            s_colorArray[node->colorType],
            s_charSpacing,
            1.0f);

        STORM_ASSERT(node->fontPointer);
    }
}

void SetInputString(const char* buffer) {
    if (s_inputString) {
        GxuFontDestroyString(s_inputString);
    }
    s_inputString = nullptr;

    if (buffer && buffer[0] != '\0') {
        C3Vector pos = { 0.0f, 0.0f, 1.0f };

        auto font = TextBlockGetFontPtr(s_textFont);

        GxuFontCreateString(
            font,
            buffer,
            s_fontHeight,
            pos,
            1.0f,
            s_fontHeight,
            0.0f,
            s_inputString,
            GxVJ_Middle, GxHJ_Left,
            s_baseTextFlags,
            s_colorArray[INPUT_COLOR],
            s_charSpacing,
            1.0f);
    }
}

void ReserveInputSpace(CONSOLELINE* line, uint32_t chars) {
    size_t newsize = line->chars + chars;
    if (newsize >= line->charsalloc) {
        while (line->charsalloc <= newsize) {
            line->charsalloc += CONSOLE_LINE_EXTRA_BYTES;
        }

        auto buffer = reinterpret_cast<char*>(ALLOC(line->charsalloc));
        SStrCopy(buffer, line->buffer, line->charsalloc);
        FREE(line->buffer);
        line->buffer = buffer;
    }
}

void MoveLinePtr(int32_t direction, int32_t modifier) {
    auto lineptr = s_currlineptr;

    if (modifier == 1) {
        for (int32_t i = 0; i < 10 && lineptr != nullptr; i++) {
            lineptr = direction == 1 ? lineptr->m_link.Next() : lineptr->m_link.Prev();
        }
    } else {
        lineptr = direction == 1 ? lineptr->m_link.Next() : lineptr->m_link.Prev();
    }

    if (lineptr) {
        s_currlineptr = lineptr;
    }
}

void MakeCommandCurrent(CONSOLELINE* lineptr, const char* command) {
    auto len = lineptr->inputstart;
    lineptr->inputpos = len;
    lineptr->chars = len;
    lineptr->buffer[len] = '\0';

    len = SStrLen(command);
    ReserveInputSpace(lineptr, len);

    SStrCopy(lineptr->buffer + lineptr->inputpos, command, STORM_MAX_STR);

    len = lineptr->inputpos + len;
    lineptr->inputpos = len;
    lineptr->chars = len;
}

void EnforceMaxLines() {
    if (s_NumLines <= CONSOLE_LINES_MAX) {
        return;
    }

    // Pop oldest line off the list
    auto lineptr = s_linelist.Tail();
    if (lineptr == s_currlineptr) {
        s_currlineptr = lineptr->Prev();
    }

    // Clean up oldest line
    s_linelist.DeleteNode(lineptr);

    s_NumLines--;
}

CONSOLELINE* GetInputLine() {
    auto head = s_linelist.Head();

    // If the list is empty, or the list's head is an entered input-line,
    // Create a fresh input line, with "> " prefixed before the caret
    if (head && head->inputpos != 0) {
        return head;
    }

    auto line = NEW(CONSOLELINE);
    line->buffer = reinterpret_cast<char*>(ALLOC(CONSOLE_LINE_EXTRA_BYTES));
    line->charsalloc = CONSOLE_LINE_EXTRA_BYTES;

    s_linelist.LinkToHead(line);
    s_NumLines++;

    SStrCopy(line->buffer, "> ", line->charsalloc);
    SetInputString(line->buffer);
    auto chars = SStrLen(line->buffer);
    line->inputstart = chars;
    line->inputpos = chars;
    line->chars = chars;
    line->colorType = INPUT_COLOR;

    s_currlineptr = line;

    EnforceMaxLines();

    return line;
}

CONSOLELINE* GetLineAtMousePosition(float y) {
    // Loop through linelist to find line at mouse position
    auto linePos = static_cast<int32_t>((s_consoleHeight - (1.0 - y)) / s_fontHeight);

    if (linePos == 1) {
        return s_linelist.Head();
    }

    if (s_currlineptr != s_linelist.Head()) {
        linePos--;
    }

    auto line = s_currlineptr;

    while (linePos > 1) {
        linePos--;

        if (!line) {
            line = s_linelist.Head();
        }

        if (line == nullptr) {
            return nullptr;
        }

        line = line->Next();
    }

    return line;
}

void PasteInInputLine(const char* characters) {
    auto len = SStrLen(characters);

    if (!len) {
        return;
    }

    auto line = GetInputLine();

    ReserveInputSpace(line, len);

    if (line->inputpos < line->chars) {
        if (len <= 1) {
            memmove(&line->buffer[line->inputpos + 1], &line->buffer[line->inputpos], line->chars - (line->inputpos + 1));

            line->buffer[line->inputpos] = *characters;

            line->inputpos++;
            line->chars++;
        } else {
            auto input = reinterpret_cast<char*>(ALLOC(line->charsalloc));
            SStrCopy(input, &line->buffer[line->inputpos], STORM_MAX_STR);

            auto buffer = reinterpret_cast<char*>(ALLOC(line->charsalloc));
            SStrCopy(buffer, line->buffer, STORM_MAX_STR);
            buffer[line->inputpos] = '\0';

            SStrPack(buffer, characters, line->charsalloc);

            auto len = SStrLen(buffer);

            line->inputpos = len;

            SStrPack(buffer, input, line->charsalloc);
            SStrCopy(line->buffer, buffer, STORM_MAX_STR);

            line->chars = SStrLen(line->buffer);

            if (input) {
                FREE(input);
            }

            if (buffer) {
                FREE(buffer);
            }
        }
    } else {
        for (int32_t i = 0; i < len; i++) {
            line->buffer[line->inputpos++] = characters[i];
        }

        line->buffer[line->inputpos] = '\0';
        line->chars = line->inputpos;
    }

    SetInputString(line->buffer);
}

void ConsoleWrite(const char* str, COLOR_T color) {
    if (!str || !*str || !GxDevExists() || !s_textFont) {
        return;
    }

    s_critsect.Enter();

    auto lineptr = NEW(CONSOLELINE);
    auto head = s_linelist.Head();
    if (head == nullptr || head->inputpos == 0) {
        // Attach console line to head
        s_linelist.LinkToHead(lineptr);
    } else {
        // Attach console line between head and head-1
        s_linelist.LinkNode(lineptr, 1, head->Prev());
    }

    size_t len = SStrLen(str) + 1;
    lineptr->chars = len;
    lineptr->charsalloc = len;
    lineptr->buffer = reinterpret_cast<char*>(ALLOC(len));
    lineptr->colorType = color;
    SStrCopy(lineptr->buffer, str, STORM_MAX_STR);

    GenerateNodeString(lineptr);

    s_NumLines++;
    EnforceMaxLines();

    s_critsect.Leave();
}

void ConsolePrintf(const char* str, ...) {
    char buffer[1024] = {0};

    if (str != nullptr && str[0] != '\0') {
        va_list list;
        va_start(list, str);
        vsnprintf(buffer, sizeof(buffer), str, list);
        va_end(list);

        ConsoleWrite(buffer, DEFAULT_COLOR);
    }
}

void ConsoleWriteA(const char* str, COLOR_T color, ...) {
    char buffer[1024] = {0};

    if (str != nullptr && str[0] != '\0') {
        va_list list;
        va_start(list, color);
        vsnprintf(buffer, sizeof(buffer), str, list);
        va_end(list);

        ConsoleWrite(buffer, color);
    }
}

void PasteClipboardInInputLine() {
    auto str = OsClipboardGetString();
    if (str) {
        PasteInInputLine(str);
        FREE(str);
        ResetHighlight();
    }
}

void ConsoleClear() {
    s_NumLines = 0;
    s_linelist.Clear();
}
