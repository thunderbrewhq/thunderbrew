#ifndef CONSOLE_COMMAND_HPP
#define CONSOLE_COMMAND_HPP

#include "console/Types.hpp"
#include <cstdint>
#include <storm/Hash.hpp>

#define CONSOLE_COMMAND_EXEC_BUFFER_SIZE 8192
#define CONSOLE_COMMAND_BUFFER_SIZE 1024
#define CONSOLE_COMMAND_MAX_LENGTH 64
#define CONSOLE_COMMAND_HISTORY_DEPTH 32

class CONSOLECOMMAND : public TSHashObject<CONSOLECOMMAND, HASHKEY_STRI> {
    public:
        COMMANDHANDLER m_handler;
        const char* m_helpText;
        CATEGORY m_category;
};

extern int32_t s_completionMode;
extern const char* s_completedCmd;
extern char s_partial[256];
extern char s_repeatBuffer[64];
extern uint32_t s_repeatCount;

extern TSHashTable<CONSOLECOMMAND, HASHKEY_STRI> g_consoleCommandHash;

void ConsoleCommandInitialize();

const char* ConsoleCommandHistory(uint32_t index);

uint32_t ConsoleCommandHistoryDepth();

int32_t ConsoleCommandRegister(const char* command, COMMANDHANDLER handler, CATEGORY category, const char* helpText);

void ConsoleInitializeCommonCommand();

void ConsoleInitializeDebugCommand();

void ConsoleInitializeScreenCommand();

int32_t ConsoleCommandComplete(const char* partial, const char** previous, int32_t direction);

#endif
