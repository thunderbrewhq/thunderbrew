#include "console/Console.hpp"
#include "console/command/Commands.hpp"

DECLARE_COMMAND(ClearConsole) {
    ConsoleClear();
    return 1;
}
