#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_CloseGuildRegistrar(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetGuildCharterCost(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_BuyGuildCharter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TurnInGuildCharter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTabardInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void GuildRegistrarRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_GUILD_REGISTRAR; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_GuildRegistrar[i].name,
            GameScript::s_ScriptFunctions_GuildRegistrar[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_GuildRegistrar[NUM_SCRIPT_FUNCTIONS_GUILD_REGISTRAR] = {
    { "CloseGuildRegistrar", &Script_CloseGuildRegistrar },
    { "GetGuildCharterCost", &Script_GetGuildCharterCost },
    { "BuyGuildCharter", &Script_BuyGuildCharter },
    { "TurnInGuildCharter", &Script_TurnInGuildCharter },
    { "GetTabardInfo", &Script_GetTabardInfo },
};
