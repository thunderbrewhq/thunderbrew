#ifndef CONSOLE_COMMAND_COMMANDS_HPP
#define CONSOLE_COMMAND_COMMANDS_HPP

#include <cstdint>

#include "console/Types.hpp"

#define DECLARE_COMMAND(x) int32_t ConsoleCommand_##x(const char* command, const char* arguments)

int32_t CCGxRestart(const char* command, const char* argument);

DECLARE_COMMAND(Quit);
DECLARE_COMMAND(Ver);
DECLARE_COMMAND(SetMap);
DECLARE_COMMAND(Script);

DECLARE_COMMAND(Help);
DECLARE_COMMAND(FontColor);
DECLARE_COMMAND(BackGroundColor);
DECLARE_COMMAND(HighLightColor);
DECLARE_COMMAND(FontSize);
DECLARE_COMMAND(Font);
DECLARE_COMMAND(BufferSize);
DECLARE_COMMAND(ClearConsole);
DECLARE_COMMAND(Proportional);
DECLARE_COMMAND(CharSpacing);
DECLARE_COMMAND(CurrentSettings);
DECLARE_COMMAND(DefaultSettings);
DECLARE_COMMAND(CloseConsole);
DECLARE_COMMAND(RepeatHandler);
DECLARE_COMMAND(AppendLogToFile);

#endif
