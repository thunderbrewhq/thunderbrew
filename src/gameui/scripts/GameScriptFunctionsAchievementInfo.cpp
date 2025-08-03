#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_GetCategoryList(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetStatisticsCategoryList(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCategoryInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetCategoryNumAchievements(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetComparisonCategoryNumAchievements(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAchievementInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAchievementNumRewards(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAchievementReward(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAchievementNumCriteria(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAchievementCriteriaInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetAchievementComparisonUnit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClearAchievementComparisonUnit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAchievementComparisonInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPreviousAchievement(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNextAchievement(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAchievementCategory(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAchievementLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumCompletedAchievements(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumComparisonCompletedAchievements(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLatestCompletedAchievements(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLatestUpdatedStats(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLatestCompletedComparisonAchievements(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLatestUpdatedComparisonStats(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTotalAchievementPoints(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetAchievementInfoFromCriteria(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetStatistic(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetComparisonStatistic(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetComparisonAchievementPoints(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanShowAchievementUI(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetTrackedAchievements(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AddTrackedAchievement(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RemoveTrackedAchievement(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsTrackedAchievement(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumTrackedAchievements(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_HasCompletedAnyAchievement(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_QueryQuestsCompleted(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetQuestsCompleted(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void AchievementInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_ACHIEVEMENT_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_AchievementInfo[i].name,
            GameScript::s_ScriptFunctions_AchievementInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_AchievementInfo[NUM_SCRIPT_FUNCTIONS_ACHIEVEMENT_INFO] = {
    { "GetCategoryList", &Script_GetCategoryList },
    { "GetStatisticsCategoryList", &Script_GetStatisticsCategoryList },
    { "GetCategoryInfo", &Script_GetCategoryInfo },
    { "GetCategoryNumAchievements", &Script_GetCategoryNumAchievements },
    { "GetComparisonCategoryNumAchievements", &Script_GetComparisonCategoryNumAchievements },
    { "GetAchievementInfo", &Script_GetAchievementInfo },
    { "GetAchievementNumRewards", &Script_GetAchievementNumRewards },
    { "GetAchievementReward", &Script_GetAchievementReward },
    { "GetAchievementNumCriteria", &Script_GetAchievementNumCriteria },
    { "GetAchievementCriteriaInfo", &Script_GetAchievementCriteriaInfo },
    { "SetAchievementComparisonUnit", &Script_SetAchievementComparisonUnit },
    { "ClearAchievementComparisonUnit", &Script_ClearAchievementComparisonUnit },
    { "GetAchievementComparisonInfo", &Script_GetAchievementComparisonInfo },
    { "GetPreviousAchievement", &Script_GetPreviousAchievement },
    { "GetNextAchievement", &Script_GetNextAchievement },
    { "GetAchievementCategory", &Script_GetAchievementCategory },
    { "GetAchievementLink", &Script_GetAchievementLink },
    { "GetNumCompletedAchievements", &Script_GetNumCompletedAchievements },
    { "GetNumComparisonCompletedAchievements", &Script_GetNumComparisonCompletedAchievements },
    { "GetLatestCompletedAchievements", &Script_GetLatestCompletedAchievements },
    { "GetLatestUpdatedStats", &Script_GetLatestUpdatedStats },
    { "GetLatestCompletedComparisonAchievements", &Script_GetLatestCompletedComparisonAchievements },
    { "GetLatestUpdatedComparisonStats", &Script_GetLatestUpdatedComparisonStats },
    { "GetTotalAchievementPoints", &Script_GetTotalAchievementPoints },
    { "GetAchievementInfoFromCriteria", &Script_GetAchievementInfoFromCriteria },
    { "GetStatistic", &Script_GetStatistic },
    { "GetComparisonStatistic", &Script_GetComparisonStatistic },
    { "GetComparisonAchievementPoints", &Script_GetComparisonAchievementPoints },
    { "CanShowAchievementUI", &Script_CanShowAchievementUI },
    { "GetTrackedAchievements", &Script_GetTrackedAchievements },
    { "AddTrackedAchievement", &Script_AddTrackedAchievement },
    { "RemoveTrackedAchievement", &Script_RemoveTrackedAchievement },
    { "IsTrackedAchievement", &Script_IsTrackedAchievement },
    { "GetNumTrackedAchievements", &Script_GetNumTrackedAchievements },
    { "HasCompletedAnyAchievement", &Script_HasCompletedAnyAchievement },
    { "QueryQuestsCompleted", &Script_QueryQuestsCompleted },
    { "GetQuestsCompleted", &Script_GetQuestsCompleted },
};
