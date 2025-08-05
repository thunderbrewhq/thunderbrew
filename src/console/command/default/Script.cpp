#include "console/Command.hpp"
#include "console/command/Commands.hpp"
#include "ui/FrameScript.hpp"

DECLARE_COMMAND(Script) {
    FrameScript_Execute(arguments, "CONSOLE", nullptr);
    return 1;
}
