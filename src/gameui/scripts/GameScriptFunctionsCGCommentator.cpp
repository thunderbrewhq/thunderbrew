#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_CommentatorSetMode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorToggleMode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetMode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorSetMapAndInstanceIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorSetPlayerIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorUpdatePlayerInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorUpdateMapInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetNumMaps(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetMapInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetInstanceInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorEnterInstance(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorExitInstance(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetNumPlayers(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetPlayerInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorFollowPlayer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorLookatPlayer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorZoomIn(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorZoomOut(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorSetCamera(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetCamera(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetCurrentMapID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorStartInstance(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorAddPlayer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorRemovePlayer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorSetBattlemaster(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorSetMoveSpeed(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorSetCameraCollision(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorSetTargetHeightOffset(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorSetSkirmishMatchmakingMode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorRequestSkirmishQueueData(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetSkirmishQueueCount(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetSkirmishQueuePlayerInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorStartSkirmishMatch(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorRequestSkirmishMode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CommentatorGetSkirmishMode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void CGCommentatorRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_CGCOMMENTATOR; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_CGCommentator[i].name,
            GameScript::s_ScriptFunctions_CGCommentator[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_CGCommentator[NUM_SCRIPT_FUNCTIONS_CGCOMMENTATOR] = {
    { "CommentatorSetMode", &Script_CommentatorSetMode },
    { "CommentatorToggleMode", &Script_CommentatorToggleMode },
    { "CommentatorGetMode", &Script_CommentatorGetMode },
    { "CommentatorSetMapAndInstanceIndex", &Script_CommentatorSetMapAndInstanceIndex },
    { "CommentatorSetPlayerIndex", &Script_CommentatorSetPlayerIndex },
    { "CommentatorUpdatePlayerInfo", &Script_CommentatorUpdatePlayerInfo },
    { "CommentatorUpdateMapInfo", &Script_CommentatorUpdateMapInfo },
    { "CommentatorGetNumMaps", &Script_CommentatorGetNumMaps },
    { "CommentatorGetMapInfo", &Script_CommentatorGetMapInfo },
    { "CommentatorGetInstanceInfo", &Script_CommentatorGetInstanceInfo },
    { "CommentatorEnterInstance", &Script_CommentatorEnterInstance },
    { "CommentatorExitInstance", &Script_CommentatorExitInstance },
    { "CommentatorGetNumPlayers", &Script_CommentatorGetNumPlayers },
    { "CommentatorGetPlayerInfo", &Script_CommentatorGetPlayerInfo },
    { "CommentatorFollowPlayer", &Script_CommentatorFollowPlayer },
    { "CommentatorLookatPlayer", &Script_CommentatorLookatPlayer },
    { "CommentatorZoomIn", &Script_CommentatorZoomIn },
    { "CommentatorZoomOut", &Script_CommentatorZoomOut },
    { "CommentatorSetCamera", &Script_CommentatorSetCamera },
    { "CommentatorGetCamera", &Script_CommentatorGetCamera },
    { "CommentatorGetCurrentMapID", &Script_CommentatorGetCurrentMapID },
    { "CommentatorStartInstance", &Script_CommentatorStartInstance },
    { "CommentatorAddPlayer", &Script_CommentatorAddPlayer },
    { "CommentatorRemovePlayer", &Script_CommentatorRemovePlayer },
    { "CommentatorSetBattlemaster", &Script_CommentatorSetBattlemaster },
    { "CommentatorSetMoveSpeed", &Script_CommentatorSetMoveSpeed },
    { "CommentatorSetCameraCollision", &Script_CommentatorSetCameraCollision },
    { "CommentatorSetTargetHeightOffset", &Script_CommentatorSetTargetHeightOffset },
    { "CommentatorSetSkirmishMatchmakingMode", &Script_CommentatorSetSkirmishMatchmakingMode },
    { "CommentatorRequestSkirmishQueueData", &Script_CommentatorRequestSkirmishQueueData },
    { "CommentatorGetSkirmishQueueCount", &Script_CommentatorGetSkirmishQueueCount },
    { "CommentatorGetSkirmishQueuePlayerInfo", &Script_CommentatorGetSkirmishQueuePlayerInfo },
    { "CommentatorStartSkirmishMatch", &Script_CommentatorStartSkirmishMatch },
    { "CommentatorRequestSkirmishMode", &Script_CommentatorRequestSkirmishMode },
    { "CommentatorGetSkirmishMode", &Script_CommentatorGetSkirmishMode },
};
