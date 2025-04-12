#include "console/Console.hpp"
#include "console/command/Commands.hpp"

DECLARE_COMMAND(Quit) {
    ConsolePostClose();
    return 1;
}
