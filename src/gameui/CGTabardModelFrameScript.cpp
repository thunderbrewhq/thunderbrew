#include "gameui/CGTabardModelFrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"

static int32_t Script_InitializeTabardColors(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_Save(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CycleVariation(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetUpperBackgroundFileName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLowerBackgroundFileName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetUpperEmblemFileName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLowerEmblemFileName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetUpperEmblemTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLowerEmblemTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanSaveTabardNow(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}


FrameScript_Method CGTabardModelFrameMethods[NUM_CGTABARD_MODEL_FRAME_SCRIPT_METHODS] = {
    { "InitializeTabardColors", &Script_InitializeTabardColors },
    { "Save", &Script_Save },
    { "CycleVariation", &Script_CycleVariation },
    { "GetUpperBackgroundFileName", &Script_GetUpperBackgroundFileName },
    { "GetLowerBackgroundFileName", &Script_GetLowerBackgroundFileName },
    { "GetUpperEmblemFileName", &Script_GetUpperEmblemFileName },
    { "GetLowerEmblemFileName", &Script_GetLowerEmblemFileName },
    { "GetUpperEmblemTexture", &Script_GetUpperEmblemTexture },
    { "GetLowerEmblemTexture", &Script_GetLowerEmblemTexture },
    { "CanSaveTabardNow", &Script_CanSaveTabardNow }
};
