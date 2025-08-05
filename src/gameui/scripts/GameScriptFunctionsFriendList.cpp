#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetNumFriends(lua_State* L) {
    // TODO
    lua_pushnumber(L, 10.0);
    lua_pushnumber(L, 0.0);
    return 2;
}

static int32_t Script_GetFriendInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSelectedFriend(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSelectedFriend(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddOrRemoveFriend(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddFriend(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RemoveFriend(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ShowFriends(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetFriendNotes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumIgnores(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetIgnoreName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSelectedIgnore(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSelectedIgnore(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddOrDelIgnore(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddIgnore(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DelIgnore(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumMutes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMuteName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSelectedMute(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSelectedMute(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddOrDelMute(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddMute(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DelMute(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsIgnored(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsMuted(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsIgnoredOrMuted(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SendWho(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumWhoResults(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetWhoInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetWhoToUI(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SortWho(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void FriendListRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_FRIEND_LIST; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_FriendList[i].name,
            GameScript::s_ScriptFunctions_FriendList[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_FriendList[NUM_SCRIPT_FUNCTIONS_FRIEND_LIST] = {
    { "GetNumFriends", &Script_GetNumFriends },
    { "GetFriendInfo", &Script_GetFriendInfo },
    { "SetSelectedFriend", &Script_SetSelectedFriend },
    { "GetSelectedFriend", &Script_GetSelectedFriend },
    { "AddOrRemoveFriend", &Script_AddOrRemoveFriend },
    { "AddFriend", &Script_AddFriend },
    { "RemoveFriend", &Script_RemoveFriend },
    { "ShowFriends", &Script_ShowFriends },
    { "SetFriendNotes", &Script_SetFriendNotes },
    { "GetNumIgnores", &Script_GetNumIgnores },
    { "GetIgnoreName", &Script_GetIgnoreName },
    { "SetSelectedIgnore", &Script_SetSelectedIgnore },
    { "GetSelectedIgnore", &Script_GetSelectedIgnore },
    { "AddOrDelIgnore", &Script_AddOrDelIgnore },
    { "AddIgnore", &Script_AddIgnore },
    { "DelIgnore", &Script_DelIgnore },
    { "GetNumMutes", &Script_GetNumMutes },
    { "GetMuteName", &Script_GetMuteName },
    { "SetSelectedMute", &Script_SetSelectedMute },
    { "GetSelectedMute", &Script_GetSelectedMute },
    { "AddOrDelMute", &Script_AddOrDelMute },
    { "AddMute", &Script_AddMute },
    { "DelMute", &Script_DelMute },
    { "IsIgnored", &Script_IsIgnored },
    { "IsMuted", &Script_IsMuted },
    { "IsIgnoredOrMuted", &Script_IsIgnoredOrMuted },
    { "SendWho", &Script_SendWho },
    { "GetNumWhoResults", &Script_GetNumWhoResults },
    { "GetWhoInfo", &Script_GetWhoInfo },
    { "SetWhoToUI", &Script_SetWhoToUI },
    { "SortWho", &Script_SortWho },
};
