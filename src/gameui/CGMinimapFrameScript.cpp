#include "gameui/CGMinimapFrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"

static int32_t Script_SetMaskTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetIconTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetBlipTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetClassBlipTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetPOIArrowTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetStaticPOIArrowTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetCorpsePOIArrowTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetPlayerTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetPlayerTextureHeight(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetPlayerTextureWidth(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetZoomLevels(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetZoom(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetZoom(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PingLocation(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPingPosition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}


FrameScript_Method CGMinimapFrameMethods[NUM_CGMINIMAP_FRAME_SCRIPT_METHODS] = {
    { "SetMaskTexture", &Script_SetMaskTexture },
    { "SetIconTexture", &Script_SetIconTexture },
    { "SetBlipTexture", &Script_SetBlipTexture },
    { "SetClassBlipTexture", &Script_SetClassBlipTexture },
    { "SetPOIArrowTexture", &Script_SetPOIArrowTexture },
    { "SetStaticPOIArrowTexture", &Script_SetStaticPOIArrowTexture },
    { "SetCorpsePOIArrowTexture", &Script_SetCorpsePOIArrowTexture },
    { "SetPlayerTexture", &Script_SetPlayerTexture },
    { "SetPlayerTextureHeight", &Script_SetPlayerTextureHeight },
    { "SetPlayerTextureWidth", &Script_SetPlayerTextureWidth },
    { "GetZoomLevels", &Script_GetZoomLevels },
    { "GetZoom", &Script_GetZoom },
    { "SetZoom", &Script_SetZoom },
    { "PingLocation", &Script_PingLocation },
    { "GetPingPosition", &Script_GetPingPosition }
};
