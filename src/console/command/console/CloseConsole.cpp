#include "console/Console.hpp"
#include "console/command/Commands.hpp"

DECLARE_COMMAND(CloseConsole) {
    ConsoleSetActive(false);
    return 1;
}
