#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetMapContinents(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMapZones(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetMapZoom(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ZoomOut(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetDungeonMapLevel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumDungeonMapLevels(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DungeonUsesTerrainMap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetMapToCurrentZone(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMapInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCurrentMapContinent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCurrentMapAreaID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCurrentMapZone(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCurrentMapDungeonLevel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetMapByID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsZoomOutAvailable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ProcessMapClick(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UpdateMapHighlight(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPlayerMapPosition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCorpseMapPosition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetDeathReleasePosition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumMapLandmarks(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMapLandmarkInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumMapOverlays(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMapOverlayInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CreateWorldMapArrowFrame(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_InitWorldMapPing(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CreateMiniWorldMapArrowFrame(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UpdateWorldMapArrowFrames(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PositionWorldMapArrowFrame(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PositionMiniWorldMapArrowFrame(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ShowWorldMapArrowFrame(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ShowMiniWorldMapArrowFrame(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClickLandmark(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumMapDebugObjects(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMapDebugObjectInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TeleportToDebugObject(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_HasDebugZoneMap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetDebugZoneMap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetWintergraspWaitTime(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanQueueForWintergrasp(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void WorldMapRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_WORLD_MAP; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_WorldMap[i].name,
            GameScript::s_ScriptFunctions_WorldMap[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_WorldMap[NUM_SCRIPT_FUNCTIONS_WORLD_MAP] = {
    { "GetMapContinents", &Script_GetMapContinents },
    { "GetMapZones", &Script_GetMapZones },
    { "SetMapZoom", &Script_SetMapZoom },
    { "ZoomOut", &Script_ZoomOut },
    { "SetDungeonMapLevel", &Script_SetDungeonMapLevel },
    { "GetNumDungeonMapLevels", &Script_GetNumDungeonMapLevels },
    { "DungeonUsesTerrainMap", &Script_DungeonUsesTerrainMap },
    { "SetMapToCurrentZone", &Script_SetMapToCurrentZone },
    { "GetMapInfo", &Script_GetMapInfo },
    { "GetCurrentMapContinent", &Script_GetCurrentMapContinent },
    { "GetCurrentMapAreaID", &Script_GetCurrentMapAreaID },
    { "GetCurrentMapZone", &Script_GetCurrentMapZone },
    { "GetCurrentMapDungeonLevel", &Script_GetCurrentMapDungeonLevel },
    { "SetMapByID", &Script_SetMapByID },
    { "IsZoomOutAvailable", &Script_IsZoomOutAvailable },
    { "ProcessMapClick", &Script_ProcessMapClick },
    { "UpdateMapHighlight", &Script_UpdateMapHighlight },
    { "GetPlayerMapPosition", &Script_GetPlayerMapPosition },
    { "GetCorpseMapPosition", &Script_GetCorpseMapPosition },
    { "GetDeathReleasePosition", &Script_GetDeathReleasePosition },
    { "GetNumMapLandmarks", &Script_GetNumMapLandmarks },
    { "GetMapLandmarkInfo", &Script_GetMapLandmarkInfo },
    { "GetNumMapOverlays", &Script_GetNumMapOverlays },
    { "GetMapOverlayInfo", &Script_GetMapOverlayInfo },
    { "CreateWorldMapArrowFrame", &Script_CreateWorldMapArrowFrame },
    { "InitWorldMapPing", &Script_InitWorldMapPing },
    { "CreateMiniWorldMapArrowFrame", &Script_CreateMiniWorldMapArrowFrame },
    { "UpdateWorldMapArrowFrames", &Script_UpdateWorldMapArrowFrames },
    { "PositionWorldMapArrowFrame", &Script_PositionWorldMapArrowFrame },
    { "PositionMiniWorldMapArrowFrame", &Script_PositionMiniWorldMapArrowFrame },
    { "ShowWorldMapArrowFrame", &Script_ShowWorldMapArrowFrame },
    { "ShowMiniWorldMapArrowFrame", &Script_ShowMiniWorldMapArrowFrame },
    { "ClickLandmark", &Script_ClickLandmark },
    { "GetNumMapDebugObjects", &Script_GetNumMapDebugObjects },
    { "GetMapDebugObjectInfo", &Script_GetMapDebugObjectInfo },
    { "TeleportToDebugObject", &Script_TeleportToDebugObject },
    { "HasDebugZoneMap", &Script_HasDebugZoneMap },
    { "GetDebugZoneMap", &Script_GetDebugZoneMap },
    { "GetWintergraspWaitTime", &Script_GetWintergraspWaitTime },
    { "CanQueueForWintergrasp", &Script_CanQueueForWintergrasp },
};
