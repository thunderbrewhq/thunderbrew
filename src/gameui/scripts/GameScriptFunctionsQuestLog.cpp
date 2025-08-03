#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetNumQuestLogEntries(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogTitle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SelectQuestLogEntry(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogSelection(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetAbandonQuest(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAbandonQuestName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAbandonQuestItems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AbandonQuest(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsUnitOnQuest(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogQuestText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumQuestLeaderBoards(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogLeaderBoard(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumQuestItemDrops(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogItemDrop(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestPOILeaderBoard(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogTimeLeft(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsCurrentQuestFailed(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumQuestLogRewards(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumQuestLogChoices(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRewardInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogChoiceInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogItemLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogSpellLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRewardMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRewardXP(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRewardHonor(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRewardSpell(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRequiredMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogPushable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QuestLogPushQuest(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestTimers(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestIndexForTimer(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CollapseQuestHeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ExpandQuestHeader(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestGreenRange(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumQuestWatches(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsQuestWatched(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddQuestWatch(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RemoveQuestWatch(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestIndexForWatch(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogGroupNum(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestResetTime(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRewardTitle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRewardTalents(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRewardArenaPoints(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogSpecialItemInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogSpecialItemCooldown(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsQuestLogSpecialItemInRange(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UseQuestLogSpecialItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ProcessQuestLogRewardFactions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumQuestLogRewardFactions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogRewardFactionInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SortQuestWatches(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ShiftQuestWatches(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestWatchIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QuestMapUpdateAllQuests(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestSortIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestWorldMapAreaID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QuestPOIUpdateTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QuestPOIUpdateIcons(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QuestPOIGetIconInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QuestPOIGetQuestIDByIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QuestPOIGetQuestIDByVisibleIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestLogCompletionText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetPOIIconOverlapDistance(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetPOIIconOverlapPushDistance(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void QuestLogRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_QUEST_LOG; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_QuestLog[i].name,
            GameScript::s_ScriptFunctions_QuestLog[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_QuestLog[NUM_SCRIPT_FUNCTIONS_QUEST_LOG] = {
    { "GetNumQuestLogEntries", &Script_GetNumQuestLogEntries },
    { "GetQuestLogTitle", &Script_GetQuestLogTitle },
    { "SelectQuestLogEntry", &Script_SelectQuestLogEntry },
    { "GetQuestLogSelection", &Script_GetQuestLogSelection },
    { "SetAbandonQuest", &Script_SetAbandonQuest },
    { "GetAbandonQuestName", &Script_GetAbandonQuestName },
    { "GetAbandonQuestItems", &Script_GetAbandonQuestItems },
    { "AbandonQuest", &Script_AbandonQuest },
    { "IsUnitOnQuest", &Script_IsUnitOnQuest },
    { "GetQuestLogQuestText", &Script_GetQuestLogQuestText },
    { "GetNumQuestLeaderBoards", &Script_GetNumQuestLeaderBoards },
    { "GetQuestLogLeaderBoard", &Script_GetQuestLogLeaderBoard },
    { "GetNumQuestItemDrops", &Script_GetNumQuestItemDrops },
    { "GetQuestLogItemDrop", &Script_GetQuestLogItemDrop },
    { "GetQuestPOILeaderBoard", &Script_GetQuestPOILeaderBoard },
    { "GetQuestLogTimeLeft", &Script_GetQuestLogTimeLeft },
    { "IsCurrentQuestFailed", &Script_IsCurrentQuestFailed },
    { "GetNumQuestLogRewards", &Script_GetNumQuestLogRewards },
    { "GetNumQuestLogChoices", &Script_GetNumQuestLogChoices },
    { "GetQuestLogRewardInfo", &Script_GetQuestLogRewardInfo },
    { "GetQuestLogChoiceInfo", &Script_GetQuestLogChoiceInfo },
    { "GetQuestLogItemLink", &Script_GetQuestLogItemLink },
    { "GetQuestLogSpellLink", &Script_GetQuestLogSpellLink },
    { "GetQuestLogRewardMoney", &Script_GetQuestLogRewardMoney },
    { "GetQuestLogRewardXP", &Script_GetQuestLogRewardXP },
    { "GetQuestLogRewardHonor", &Script_GetQuestLogRewardHonor },
    { "GetQuestLogRewardSpell", &Script_GetQuestLogRewardSpell },
    { "GetQuestLogRequiredMoney", &Script_GetQuestLogRequiredMoney },
    { "GetQuestLogPushable", &Script_GetQuestLogPushable },
    { "QuestLogPushQuest", &Script_QuestLogPushQuest },
    { "GetQuestTimers", &Script_GetQuestTimers },
    { "GetQuestIndexForTimer", &Script_GetQuestIndexForTimer },
    { "CollapseQuestHeader", &Script_CollapseQuestHeader },
    { "ExpandQuestHeader", &Script_ExpandQuestHeader },
    { "GetQuestGreenRange", &Script_GetQuestGreenRange },
    { "GetNumQuestWatches", &Script_GetNumQuestWatches },
    { "IsQuestWatched", &Script_IsQuestWatched },
    { "AddQuestWatch", &Script_AddQuestWatch },
    { "RemoveQuestWatch", &Script_RemoveQuestWatch },
    { "GetQuestIndexForWatch", &Script_GetQuestIndexForWatch },
    { "GetQuestLogGroupNum", &Script_GetQuestLogGroupNum },
    { "GetQuestResetTime", &Script_GetQuestResetTime },
    { "GetQuestLink", &Script_GetQuestLink },
    { "GetQuestLogRewardTitle", &Script_GetQuestLogRewardTitle },
    { "GetQuestLogRewardTalents", &Script_GetQuestLogRewardTalents },
    { "GetQuestLogRewardArenaPoints", &Script_GetQuestLogRewardArenaPoints },
    { "GetQuestLogSpecialItemInfo", &Script_GetQuestLogSpecialItemInfo },
    { "GetQuestLogSpecialItemCooldown", &Script_GetQuestLogSpecialItemCooldown },
    { "IsQuestLogSpecialItemInRange", &Script_IsQuestLogSpecialItemInRange },
    { "UseQuestLogSpecialItem", &Script_UseQuestLogSpecialItem },
    { "ProcessQuestLogRewardFactions", &Script_ProcessQuestLogRewardFactions },
    { "GetNumQuestLogRewardFactions", &Script_GetNumQuestLogRewardFactions },
    { "GetQuestLogRewardFactionInfo", &Script_GetQuestLogRewardFactionInfo },
    { "SortQuestWatches", &Script_SortQuestWatches },
    { "ShiftQuestWatches", &Script_ShiftQuestWatches },
    { "GetQuestWatchIndex", &Script_GetQuestWatchIndex },
    { "QuestMapUpdateAllQuests", &Script_QuestMapUpdateAllQuests },
    { "GetQuestSortIndex", &Script_GetQuestSortIndex },
    { "GetQuestWorldMapAreaID", &Script_GetQuestWorldMapAreaID },
    { "QuestPOIUpdateTexture", &Script_QuestPOIUpdateTexture },
    { "QuestPOIUpdateIcons", &Script_QuestPOIUpdateIcons },
    { "QuestPOIGetIconInfo", &Script_QuestPOIGetIconInfo },
    { "QuestPOIGetQuestIDByIndex", &Script_QuestPOIGetQuestIDByIndex },
    { "QuestPOIGetQuestIDByVisibleIndex", &Script_QuestPOIGetQuestIDByVisibleIndex },
    { "GetQuestLogCompletionText", &Script_GetQuestLogCompletionText },
    { "SetPOIIconOverlapDistance", &Script_SetPOIIconOverlapDistance },
    { "SetPOIIconOverlapPushDistance", &Script_SetPOIIconOverlapPushDistance },
};
