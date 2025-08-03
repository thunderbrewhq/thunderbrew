#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_KBSetup_BeginLoading(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_IsLoaded(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_GetLanguageCount(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_GetLanguageData(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_GetCategoryCount(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_GetCategoryData(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_GetSubCategoryCount(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_GetSubCategoryData(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_GetArticleHeaderCount(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_GetArticleHeaderData(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSetup_GetTotalArticleCount(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBQuery_BeginLoading(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBQuery_IsLoaded(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBQuery_GetArticleHeaderCount(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBQuery_GetArticleHeaderData(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBQuery_GetTotalArticleCount(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBArticle_BeginLoading(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBArticle_IsLoaded(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBArticle_GetData(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSystem_GetMOTD(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSystem_GetServerStatus(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_KBSystem_GetServerNotice(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void KnowledgeBaseRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_KNOWLEDGE_BASE; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_KnowledgeBase[i].name,
            GameScript::s_ScriptFunctions_KnowledgeBase[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_KnowledgeBase[NUM_SCRIPT_FUNCTIONS_KNOWLEDGE_BASE] = {
    { "KBSetup_BeginLoading", &Script_KBSetup_BeginLoading },
    { "KBSetup_IsLoaded", &Script_KBSetup_IsLoaded },
    { "KBSetup_GetLanguageCount", &Script_KBSetup_GetLanguageCount },
    { "KBSetup_GetLanguageData", &Script_KBSetup_GetLanguageData },
    { "KBSetup_GetCategoryCount", &Script_KBSetup_GetCategoryCount },
    { "KBSetup_GetCategoryData", &Script_KBSetup_GetCategoryData },
    { "KBSetup_GetSubCategoryCount", &Script_KBSetup_GetSubCategoryCount },
    { "KBSetup_GetSubCategoryData", &Script_KBSetup_GetSubCategoryData },
    { "KBSetup_GetArticleHeaderCount", &Script_KBSetup_GetArticleHeaderCount },
    { "KBSetup_GetArticleHeaderData", &Script_KBSetup_GetArticleHeaderData },
    { "KBSetup_GetTotalArticleCount", &Script_KBSetup_GetTotalArticleCount },
    { "KBQuery_BeginLoading", &Script_KBQuery_BeginLoading },
    { "KBQuery_IsLoaded", &Script_KBQuery_IsLoaded },
    { "KBQuery_GetArticleHeaderCount", &Script_KBQuery_GetArticleHeaderCount },
    { "KBQuery_GetArticleHeaderData", &Script_KBQuery_GetArticleHeaderData },
    { "KBQuery_GetTotalArticleCount", &Script_KBQuery_GetTotalArticleCount },
    { "KBArticle_BeginLoading", &Script_KBArticle_BeginLoading },
    { "KBArticle_IsLoaded", &Script_KBArticle_IsLoaded },
    { "KBArticle_GetData", &Script_KBArticle_GetData },
    { "KBSystem_GetMOTD", &Script_KBSystem_GetMOTD },
    { "KBSystem_GetServerStatus", &Script_KBSystem_GetServerStatus },
    { "KBSystem_GetServerNotice", &Script_KBSystem_GetServerNotice },
};
