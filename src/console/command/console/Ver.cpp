#include "console/Console.hpp"
#include "console/command/Commands.hpp"

#if defined(NDEBUG)
#define WHOA_BUILD_TYPE "Release"
#else
#define WHOA_BUILD_TYPE "Debug"
#endif

#define WHOA_BRAND_STRING "Whoa"

#define WHOA_PROJECT_URL "https://github.com/thunderbrewhq/thunderbrew"

#define WHOA_VERSION_STRING WHOA_BRAND_STRING " [" WHOA_BUILD_TYPE "] Build " WHOA_VERSION_BUILD " (" __DATE__ ") <" WHOA_PROJECT_URL ">"

DECLARE_COMMAND(Ver) {
    // ConsoleWrite("Thunderbrew <https://github.com/thunderbrewhq/thunderbrew>", ADMIN_COLOR);
    ConsoleWrite(WHOA_VERSION_STRING, DEFAULT_COLOR);

    return 1;
}
