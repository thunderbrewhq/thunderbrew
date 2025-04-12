#include "console/Console.hpp"
#include "console/command/Commands.hpp"

DECLARE_COMMAND(Ver) {
    ConsoleWrite("Whoa <https://github.com/whoahq/whoa>", DEFAULT_COLOR);
    return 1;
}
