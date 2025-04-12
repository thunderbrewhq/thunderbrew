#ifndef CONSOLE_LINE_HPP
#define CONSOLE_LINE_HPP

#include "console/Types.hpp"

#include <storm/List.hpp>
#include <storm/Thread.hpp>

#define CONSOLE_LINES_MAX 256
#define CONSOLE_LINE_LENGTH 1024
#define CONSOLE_LINE_EXTRA_BYTES 16

class CONSOLELINE : public TSLinkedNode<CONSOLELINE> {
    public:
        char*      buffer      = nullptr;
        uint32_t   chars       = 0;
        uint32_t   charsalloc  = 0;
        uint32_t   inputpos    = 0;
        uint32_t   inputstart  = 0;
        COLOR_T    colorType   = DEFAULT_COLOR;
        CGxString* fontPointer = nullptr;

        void Up();
        void Down();
        void Delete();
        void Backspace();
        ~CONSOLELINE();
};

extern int32_t s_historyIndex;
extern STORM_LIST(CONSOLELINE) s_linelist;
extern CONSOLELINE* s_currlineptr;
extern uint32_t s_NumLines;
extern SCritSect s_critsect;

void GenerateNodeString(CONSOLELINE* node);

void SetInputString(const char* buffer);

void ReserveInputSpace(CONSOLELINE* lineptr, uint32_t len);

void MoveLinePtr(int32_t direction, int32_t modifier);

void MakeCommandCurrent(CONSOLELINE* lineptr, const char* command);

CONSOLELINE* GetInputLine();

CONSOLELINE* GetLineAtMousePosition(float y);

void PasteInInputLine(const char* characters);

void PasteClipboardInInputLine();

// void BackspaceLine(CONSOLELINE* line);

// CONSOLELINE* GetCurrentLine();

// CONSOLELINE* GetLineAtMousePosition(float y);

// void ConsoleClear();

#endif
