#include "console/Command.hpp"
#include "console/Console.hpp"
#include "console/Line.hpp"
#include "console/Types.hpp"
#include "console/command/Commands.hpp"
#include <cctype>
#include <storm/Error.hpp>
#include <storm/Unicode.hpp>

int32_t s_completionMode = 0;
const char* s_completedCmd = nullptr;
char s_partial[256];

char s_repeatBuffer[64];
uint32_t s_repeatCount = 0;

TSHashTable<CONSOLECOMMAND, HASHKEY_STRI> g_consoleCommandHash;

char g_commandHistory[CONSOLE_COMMAND_HISTORY_DEPTH][CONSOLE_COMMAND_BUFFER_SIZE];
uint32_t g_commandHistoryIndex;

char g_ExecBuffer[CONSOLE_COMMAND_EXEC_BUFFER_SIZE] = { 0 };
EXECMODE g_ExecCreateMode = EM_NOTACTIVE;

int32_t ValidateFileName(const char* filename) {
    if (SStrStr(filename, "..") || SStrStr(filename, "\\")) {
        // TODO
        // ConsoleWrite("File Name cannot contain '\\' or '..'", ERROR_COLOR);
        return 0;
    }

    const char* extension = SStrChrR(filename, '.');

    if (extension && SStrCmpI(extension, ".wtf", -1)) {
        // TODO
        // ConsoleWrite("Only .wtf extensions are allowed", ERROR_COLOR);
        return 0;
    }

    return 1;
}

int32_t AddLineToExecFile(const char* currentLine) {
    char stringToWrite[STORM_MAX_PATH];

    if (g_ExecCreateMode != EM_PROMPTOVERWRITE) {
        if (!SStrCmpI(currentLine, "end", STORM_MAX_STR)) {
            if (g_ExecCreateMode != EM_APPEND) {
                g_ExecCreateMode = EM_WRITEFILE;
            }

            return 1;
        }

        SStrPrintf(stringToWrite, sizeof(stringToWrite), "%s\n", currentLine);

        if (((CONSOLE_COMMAND_EXEC_BUFFER_SIZE - 1) - SStrLen(g_ExecBuffer)) != SStrLen(stringToWrite)) {
            SStrPack(g_ExecBuffer, stringToWrite, sizeof(g_ExecBuffer));
        }

        return 0;
    }

    if (currentLine[0] == 'n') {
        ConsoleWrite("Canceled File Creation", ECHO_COLOR);
        g_ExecCreateMode = EM_NOTACTIVE;
        return 0;
    }

    if (currentLine[0] != 'y') {
        ConsoleWrite("You must type 'y' to confirm overwrite. Process aborted!", ERROR_COLOR);
        g_ExecCreateMode = EM_NOTACTIVE;
        return 0;
    }

    ConsoleWrite("Begin Typing the commands", ECHO_COLOR);
    g_ExecCreateMode = EM_RECORDING;

    return 1;
}

CONSOLECOMMAND* ParseCommand(const char* commandLine, const char** command, char* arguments, size_t argsize) {
    STORM_ASSERT(commandLine);

    auto string = commandLine;

    static char cmd[32] = { 0 };
    auto cmdptr = &cmd[0];

    int32_t i = 0;
    while (i < CONSOLE_COMMAND_MAX_LENGTH) {
        int32_t chars;

        auto code = SUniSGetUTF8(reinterpret_cast<const uint8_t*>(string), &chars);
        if (code == -1 || code == ' ' || chars > CONSOLE_COMMAND_MAX_LENGTH) {
            break;
        }

        if (chars) {
            for (size_t j = 0; j < chars; j++) {
                *cmdptr++ = *string++;
            }
        }

        i += chars;
    }

    *cmdptr = '\0';

    if (command) {
        *command = cmd;
    }

    auto argptr = arguments;
    if (argptr) {
        int32_t chars;

        auto code = SUniSGetUTF8(reinterpret_cast<const uint8_t*>(string), &chars);

        // Discard space
        while (code != -1 && code == ' ') {
            string += chars;
            code = SUniSGetUTF8(reinterpret_cast<const uint8_t*>(string), &chars);
        }

        SStrCopy(argptr, string, argsize);
        auto len = SStrLen(argptr);
        while (len > 0 && (argptr[len - 1] == ' ')) {
            len--;
            argptr[len] = '\0';
        }
    }

    return g_consoleCommandHash.Ptr(cmd);
}

void ConsoleCommandDestroy() {
    g_consoleCommandHash.Clear();
}

const char* ConsoleCommandHistory(uint32_t index) {
    return g_commandHistory[((g_commandHistoryIndex - index) - 1) & (CONSOLE_COMMAND_HISTORY_DEPTH - 1)];
}

void AddToHistory(const char* command) {
    SStrCopy(g_commandHistory[g_commandHistoryIndex], command, CONSOLE_LINE_LENGTH);
    g_commandHistoryIndex = (g_commandHistoryIndex + 1) & (CONSOLE_COMMAND_HISTORY_DEPTH - 1);
}

uint32_t ConsoleCommandHistoryDepth() {
    return CONSOLE_COMMAND_HISTORY_DEPTH;
}

int32_t ConsoleCommandRegister(const char* command, COMMANDHANDLER handler, CATEGORY category, const char* helpText) {
    STORM_ASSERT(command);
    STORM_ASSERT(handler);

    if (SStrLen(command) >= CONSOLE_COMMAND_MAX_LENGTH || g_consoleCommandHash.Ptr(command)) {
        return 0;
    }

    // Register the new command
    auto commandPtr = g_consoleCommandHash.New(command, 0, 0);
    commandPtr->m_handler = handler;
    commandPtr->m_helpText = helpText;
    commandPtr->m_category = category;

    return 1;
}

void ConsoleCommandUnregister(const char* command) {
    if (command) {
        auto commandPtr = g_consoleCommandHash.Ptr(command);
        if (commandPtr) {
            g_consoleCommandHash.Delete(commandPtr);
        }
    }
}

void ConsoleCommandExecute(const char* commandLine, int32_t addToHistory) {
    auto em = g_ExecCreateMode;
    if (em == EM_RECORDING || em == EM_PROMPTOVERWRITE || em == EM_APPEND) {
        AddLineToExecFile(commandLine);
        return;
    }
    auto history = ConsoleCommandHistory(0);
    if (addToHistory && (history == nullptr || SStrCmp(commandLine, history, STORM_MAX_STR))) {
        AddToHistory(commandLine);
    }

    const char* command = nullptr;
    auto arguments = reinterpret_cast<char*>(ALLOC(CONSOLE_COMMAND_BUFFER_SIZE));

    auto cmd = ParseCommand(commandLine, &command, arguments, CONSOLE_COMMAND_BUFFER_SIZE);
    if (cmd) {
        cmd->m_handler(command, arguments);
    } else {
        ConsoleWrite("Unknown command", DEFAULT_COLOR);
    }

    if (arguments) {
        FREE(arguments);
    }
}

void ConsoleInitializeScreenCommand() {
    ConsoleCommandRegister("fontcolor",        ConsoleCommand_FontColor,       CONSOLE, "[ColorClassName] [Red 0-255] [Green 0-255] [Blue 0-255]");
    ConsoleCommandRegister("bgcolor",          ConsoleCommand_BackGroundColor, CONSOLE, "[alpha 0-255] [Red 0-255] [Green 0-255] [Blue 0-255]");
    ConsoleCommandRegister("highlightcolor",   ConsoleCommand_HighLightColor,  CONSOLE, "[alpha 0-255] [Red 0-255] [Green 0-255] [Blue 0-255]");
    ConsoleCommandRegister("fontsize",         ConsoleCommand_FontSize,        CONSOLE, "[15-50] arbitrary font size");
    ConsoleCommandRegister("font",             ConsoleCommand_Font,            CONSOLE, "[fontname] make sure to use the .ttf file name");
    ConsoleCommandRegister("consolelines",     ConsoleCommand_BufferSize,      CONSOLE, "[number] number of lines to show in the console");
    ConsoleCommandRegister("clear",            ConsoleCommand_ClearConsole,    CONSOLE, "Clears the console buffer");
    ConsoleCommandRegister("proportionaltext", ConsoleCommand_Proportional,    CONSOLE, "Toggles fixed-width text characters");
    ConsoleCommandRegister("spacing",          ConsoleCommand_CharSpacing,     CONSOLE, "[float] specifies inter-character spacing, in pixels");
    ConsoleCommandRegister("settings",         ConsoleCommand_CurrentSettings, CONSOLE, "Shows current font and console settings");
    ConsoleCommandRegister("default",          ConsoleCommand_DefaultSettings, CONSOLE, "Resets all the font and console settings");
    ConsoleCommandRegister("closeconsole",     ConsoleCommand_CloseConsole,    CONSOLE, "Closes the Console window");
    ConsoleCommandRegister("repeat",           ConsoleCommand_RepeatHandler,   CONSOLE, "Repeats a command");
    ConsoleCommandRegister("AppendLogToFile",  ConsoleCommand_AppendLogToFile, CONSOLE, "[filename = ConsoleLogs/Log<Timestamp>.txt] [numLines = all]");
}

void ConsoleCommandInitialize() {
    ConsoleCommandRegister("help", ConsoleCommand_Help, CONSOLE, "Provides help information about a command.");
}

void ConsoleInitializeCommonCommand() {
    ConsoleCommandRegister("quit",   ConsoleCommand_Quit,   DEFAULT, nullptr);
    ConsoleCommandRegister("ver",    ConsoleCommand_Ver,    DEFAULT, nullptr);
    ConsoleCommandRegister("setmap", ConsoleCommand_SetMap, DEFAULT, nullptr);
}

void ConsoleInitializeDebugCommand() {
    ConsoleCommandRegister("script", ConsoleCommand_Script, DEFAULT, nullptr);
}

int32_t ConsoleCommandComplete(const char* partial, const char** previous, int32_t direction) {
    auto current = g_consoleCommandHash.Head();

    if (*previous) {
        auto cmd = g_consoleCommandHash.Ptr(*previous);
        if (!cmd) {
            return 0;
        }
        // TODO: double check this
        current = g_consoleCommandHash.Next(direction ? cmd : cmd->m_linktoslot.Prev());
    }

    auto len = SStrLen(partial);
    while (current) {
        // console command found
        if (SStrCmpI(partial, current->m_key.m_str, len) == 0) {
            *previous = current->m_key.m_str;
            return 1;
        }
        current = g_consoleCommandHash.Next(current);
    }

    return 0;
}
