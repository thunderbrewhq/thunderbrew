#ifndef CONSOLE_CONSOLE_HPP
#define CONSOLE_CONSOLE_HPP

#include "console/Types.hpp"
#include "event/Types.hpp"
#include <cstdint>

int32_t ConsoleAccessGetEnabled();

void ConsoleAccessSetEnabled(int32_t enable);

int32_t ConsoleGetActive();

KEY ConsoleGetHotKey();

void ConsoleSetActive(int32_t active);

void ConsoleSetHotKey(KEY hotkey);

void ConsoleCommandDestroy();

int32_t ConsoleCommandRegister(const char* command, COMMANDHANDLER handler, CATEGORY category, const char* helpText);

void ConsoleCommandUnregister(const char* command);

void ConsoleCommandExecute(const char* commandLine, int32_t addToHistory);

void ConsolePostClose();

void ConsoleWrite(const char* str, COLOR_T color);

void ConsolePrintf(const char* str, ...);

void ConsoleWriteA(const char* str, COLOR_T color, ...);

void ConsoleClear();

#endif
