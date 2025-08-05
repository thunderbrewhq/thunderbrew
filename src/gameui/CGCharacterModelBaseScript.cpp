#include "gameui/CGCharacterModelBaseScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"

static int32_t Script_SetUnit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetCreature(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RefreshUnit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetRotation(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}


FrameScript_Method CGCharacterModelBaseMethods[NUM_CGCHARACTER_MODEL_BASE_SCRIPT_METHODS] = {
    { "SetUnit", &Script_SetUnit },
    { "SetCreature", &Script_SetCreature },
    { "RefreshUnit", &Script_RefreshUnit },
    { "SetRotation", &Script_SetRotation }
};
