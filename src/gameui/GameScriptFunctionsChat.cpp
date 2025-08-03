#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_SendChatMessage(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SendAddonMessage(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SendSystemMessage(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumLanguages(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLanguageByIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetDefaultLanguage(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DoEmote(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LoggingChat(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LoggingCombat(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_JoinChannelByName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_JoinTemporaryChannel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_JoinPermanentChannel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_LeaveChannelByName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ListChannelByName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ListChannels(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChannelList(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChannelPassword(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChannelOwner(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DisplayChannelOwner(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChannelName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelModerator(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelUnmoderator(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelMute(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelUnmute(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelKick(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelBan(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelUnban(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelToggleAnnouncements(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelSilenceVoice(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelSilenceAll(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelUnSilenceVoice(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelUnSilenceAll(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChangeChatColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ResetChatColors(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChatTypeIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChatWindowInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChatWindowSavedPosition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChatWindowSavedDimensions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChatWindowMessages(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChatWindowChannels(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddChatWindowMessages(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RemoveChatWindowMessages(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddChatWindowChannel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RemoveChatWindowChannel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowSize(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowColor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowAlpha(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowLocked(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowDocked(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowUninteractable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowShown(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowSavedPosition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatWindowSavedDimensions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_EnumerateServerChannels(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RequestRaidInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumSavedInstances(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSavedInstanceInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSavedInstanceExtend(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ResetChatWindows(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanComplainChat(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ComplainChat(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumDisplayChannels(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChannelDisplayInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSelectedDisplayChannel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSelectedDisplayChannel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetChannelRosterInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumChannelMembers(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetActiveVoiceChannel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetActiveVoiceChannel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CollapseChannelHeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ExpandChannelHeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelVoiceOn(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ChannelVoiceOff(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DisplayChannelVoiceOn(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DisplayChannelVoiceOff(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsDisplayChannelOwner(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsDisplayChannelModerator(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsVoiceChatEnabled(lua_State* L) {
    /*
    v1 = s_cvarEnableVoiceChat && s_cvarEnableVoiceChat->m_intValue;
    v2 = ComSatClient_IsComsatDisabledByClient();
    if ( CGChat::m_voiceChatSystemStatus && v1 && !v2 )
    {
    lua_pushnumber(a1, 1.0);
    return 1;
    }
    else
    {
    lua_pushnil(a1);
    return 1;
    }
    */

    lua_pushnil(L);
    return 1;
}

static int32_t Script_IsVoiceChatAllowed(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsVoiceChatAllowedByServer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsSilenced(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetMuteStatus(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UnitIsSilenced(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChannelWatch(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClearChannelWatch(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DeclineInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetChatColorNameByClass(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void ChatRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_CHAT; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Chat[i].name,
            GameScript::s_ScriptFunctions_Chat[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_Chat[NUM_SCRIPT_FUNCTIONS_CHAT] = {
    { "SendChatMessage", &Script_SendChatMessage },
    { "SendAddonMessage", &Script_SendAddonMessage },
    { "SendSystemMessage", &Script_SendSystemMessage },
    { "GetNumLanguages", &Script_GetNumLanguages },
    { "GetLanguageByIndex", &Script_GetLanguageByIndex },
    { "GetDefaultLanguage", &Script_GetDefaultLanguage },
    { "DoEmote", &Script_DoEmote },
    { "LoggingChat", &Script_LoggingChat },
    { "LoggingCombat", &Script_LoggingCombat },
    { "JoinChannelByName", &Script_JoinChannelByName },
    { "JoinTemporaryChannel", &Script_JoinTemporaryChannel },
    { "JoinPermanentChannel", &Script_JoinPermanentChannel },
    { "LeaveChannelByName", &Script_LeaveChannelByName },
    { "ListChannelByName", &Script_ListChannelByName },
    { "ListChannels", &Script_ListChannels },
    { "GetChannelList", &Script_GetChannelList },
    { "SetChannelPassword", &Script_SetChannelPassword },
    { "SetChannelOwner", &Script_SetChannelOwner },
    { "DisplayChannelOwner", &Script_DisplayChannelOwner },
    { "GetChannelName", &Script_GetChannelName },
    { "ChannelModerator", &Script_ChannelModerator },
    { "ChannelUnmoderator", &Script_ChannelUnmoderator },
    { "ChannelMute", &Script_ChannelMute },
    { "ChannelUnmute", &Script_ChannelUnmute },
    { "ChannelInvite", &Script_ChannelInvite },
    { "ChannelKick", &Script_ChannelKick },
    { "ChannelBan", &Script_ChannelBan },
    { "ChannelUnban", &Script_ChannelUnban },
    { "ChannelToggleAnnouncements", &Script_ChannelToggleAnnouncements },
    { "ChannelSilenceVoice", &Script_ChannelSilenceVoice },
    { "ChannelSilenceAll", &Script_ChannelSilenceAll },
    { "ChannelUnSilenceVoice", &Script_ChannelUnSilenceVoice },
    { "ChannelUnSilenceAll", &Script_ChannelUnSilenceAll },
    { "ChangeChatColor", &Script_ChangeChatColor },
    { "ResetChatColors", &Script_ResetChatColors },
    { "GetChatTypeIndex", &Script_GetChatTypeIndex },
    { "GetChatWindowInfo", &Script_GetChatWindowInfo },
    { "GetChatWindowSavedPosition", &Script_GetChatWindowSavedPosition },
    { "GetChatWindowSavedDimensions", &Script_GetChatWindowSavedDimensions },
    { "GetChatWindowMessages", &Script_GetChatWindowMessages },
    { "GetChatWindowChannels", &Script_GetChatWindowChannels },
    { "AddChatWindowMessages", &Script_AddChatWindowMessages },
    { "RemoveChatWindowMessages", &Script_RemoveChatWindowMessages },
    { "AddChatWindowChannel", &Script_AddChatWindowChannel },
    { "RemoveChatWindowChannel", &Script_RemoveChatWindowChannel },
    { "SetChatWindowName", &Script_SetChatWindowName },
    { "SetChatWindowSize", &Script_SetChatWindowSize },
    { "SetChatWindowColor", &Script_SetChatWindowColor },
    { "SetChatWindowAlpha", &Script_SetChatWindowAlpha },
    { "SetChatWindowLocked", &Script_SetChatWindowLocked },
    { "SetChatWindowDocked", &Script_SetChatWindowDocked },
    { "SetChatWindowUninteractable", &Script_SetChatWindowUninteractable },
    { "SetChatWindowShown", &Script_SetChatWindowShown },
    { "SetChatWindowSavedPosition", &Script_SetChatWindowSavedPosition },
    { "SetChatWindowSavedDimensions", &Script_SetChatWindowSavedDimensions },
    { "EnumerateServerChannels", &Script_EnumerateServerChannels },
    { "RequestRaidInfo", &Script_RequestRaidInfo },
    { "GetNumSavedInstances", &Script_GetNumSavedInstances },
    { "GetSavedInstanceInfo", &Script_GetSavedInstanceInfo },
    { "SetSavedInstanceExtend", &Script_SetSavedInstanceExtend },
    { "ResetChatWindows", &Script_ResetChatWindows },
    { "CanComplainChat", &Script_CanComplainChat },
    { "ComplainChat", &Script_ComplainChat },
    { "GetNumDisplayChannels", &Script_GetNumDisplayChannels },
    { "GetChannelDisplayInfo", &Script_GetChannelDisplayInfo },
    { "GetSelectedDisplayChannel", &Script_GetSelectedDisplayChannel },
    { "SetSelectedDisplayChannel", &Script_SetSelectedDisplayChannel },
    { "GetChannelRosterInfo", &Script_GetChannelRosterInfo },
    { "GetNumChannelMembers", &Script_GetNumChannelMembers },
    { "SetActiveVoiceChannel", &Script_SetActiveVoiceChannel },
    { "GetActiveVoiceChannel", &Script_GetActiveVoiceChannel },
    { "CollapseChannelHeader", &Script_CollapseChannelHeader },
    { "ExpandChannelHeader", &Script_ExpandChannelHeader },
    { "ChannelVoiceOn", &Script_ChannelVoiceOn },
    { "ChannelVoiceOff", &Script_ChannelVoiceOff },
    { "DisplayChannelVoiceOn", &Script_DisplayChannelVoiceOn },
    { "DisplayChannelVoiceOff", &Script_DisplayChannelVoiceOff },
    { "IsDisplayChannelOwner", &Script_IsDisplayChannelOwner },
    { "IsDisplayChannelModerator", &Script_IsDisplayChannelModerator },
    { "IsVoiceChatEnabled", &Script_IsVoiceChatEnabled },
    { "IsVoiceChatAllowed", &Script_IsVoiceChatAllowed },
    { "IsVoiceChatAllowedByServer", &Script_IsVoiceChatAllowedByServer },
    { "IsSilenced", &Script_IsSilenced },
    { "GetMuteStatus", &Script_GetMuteStatus },
    { "UnitIsSilenced", &Script_UnitIsSilenced },
    { "SetChannelWatch", &Script_SetChannelWatch },
    { "ClearChannelWatch", &Script_ClearChannelWatch },
    { "DeclineInvite", &Script_DeclineInvite },
    { "SetChatColorNameByClass", &Script_SetChatColorNameByClass },
};
