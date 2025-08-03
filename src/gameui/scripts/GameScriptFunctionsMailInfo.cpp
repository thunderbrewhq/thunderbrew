#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_CloseMail(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClearSendMail(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ClickSendMailItemButton(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSendMailMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSendMailMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSendMailCOD(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSendMailCOD(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumStationeries(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetStationeryInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SelectStationery(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSelectedStationeryTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumPackages(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetPackageInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SelectPackage(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSendMailItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSendMailItemLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSendMailPrice(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SendMail(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CheckInbox(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetInboxNumItems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetInboxHeaderInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetInboxText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetInboxInvoiceInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetInboxItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetInboxItemLink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TakeInboxMoney(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TakeInboxItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TakeInboxTextItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ReturnInboxItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DeleteInboxItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_InboxItemCanDelete(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_HasNewMail(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_ComplainInboxItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanComplainInboxItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetLatestThreeSenders(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSendMailShowing(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_AutoLootMailItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RespondMailLockSendItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void MailInfoRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_MAIL_INFO; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_MailInfo[i].name,
            GameScript::s_ScriptFunctions_MailInfo[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_MailInfo[NUM_SCRIPT_FUNCTIONS_MAIL_INFO] = {
    { "CloseMail", &Script_CloseMail },
    { "ClearSendMail", &Script_ClearSendMail },
    { "ClickSendMailItemButton", &Script_ClickSendMailItemButton },
    { "SetSendMailMoney", &Script_SetSendMailMoney },
    { "GetSendMailMoney", &Script_GetSendMailMoney },
    { "SetSendMailCOD", &Script_SetSendMailCOD },
    { "GetSendMailCOD", &Script_GetSendMailCOD },
    { "GetNumStationeries", &Script_GetNumStationeries },
    { "GetStationeryInfo", &Script_GetStationeryInfo },
    { "SelectStationery", &Script_SelectStationery },
    { "GetSelectedStationeryTexture", &Script_GetSelectedStationeryTexture },
    { "GetNumPackages", &Script_GetNumPackages },
    { "GetPackageInfo", &Script_GetPackageInfo },
    { "SelectPackage", &Script_SelectPackage },
    { "GetSendMailItem", &Script_GetSendMailItem },
    { "GetSendMailItemLink", &Script_GetSendMailItemLink },
    { "GetSendMailPrice", &Script_GetSendMailPrice },
    { "SendMail", &Script_SendMail },
    { "CheckInbox", &Script_CheckInbox },
    { "GetInboxNumItems", &Script_GetInboxNumItems },
    { "GetInboxHeaderInfo", &Script_GetInboxHeaderInfo },
    { "GetInboxText", &Script_GetInboxText },
    { "GetInboxInvoiceInfo", &Script_GetInboxInvoiceInfo },
    { "GetInboxItem", &Script_GetInboxItem },
    { "GetInboxItemLink", &Script_GetInboxItemLink },
    { "TakeInboxMoney", &Script_TakeInboxMoney },
    { "TakeInboxItem", &Script_TakeInboxItem },
    { "TakeInboxTextItem", &Script_TakeInboxTextItem },
    { "ReturnInboxItem", &Script_ReturnInboxItem },
    { "DeleteInboxItem", &Script_DeleteInboxItem },
    { "InboxItemCanDelete", &Script_InboxItemCanDelete },
    { "HasNewMail", &Script_HasNewMail },
    { "ComplainInboxItem", &Script_ComplainInboxItem },
    { "CanComplainInboxItem", &Script_CanComplainInboxItem },
    { "GetLatestThreeSenders", &Script_GetLatestThreeSenders },
    { "SetSendMailShowing", &Script_SetSendMailShowing },
    { "AutoLootMailItem", &Script_AutoLootMailItem },
    { "RespondMailLockSendItem", &Script_RespondMailLockSendItem },
};
