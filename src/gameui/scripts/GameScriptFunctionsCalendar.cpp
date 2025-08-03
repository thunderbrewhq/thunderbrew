#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_CalendarGetMonthNames(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetWeekdayNames(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetDate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetMinDate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetMaxDate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetMinHistoryDate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetMaxCreateDate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetMonth(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetAbsMonth(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarSetMonth(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarSetAbsMonth(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetNumDayEvents(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetDayEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetDayEventSequenceInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetFirstPendingInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarOpenEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetEventIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarCloseEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetEventInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetHolidayInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetRaidInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarGetNumPendingInvites(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetNumInvites(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetInviteResponseTime(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarAddEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarNewEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarMassInviteGuild(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarMassInviteArenaTeam(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarNewGuildAnnouncement(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarNewGuildEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarDefaultGuildFilter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarUpdateEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarRemoveEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSelectInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetSelectedInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextSelectEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextDeselectEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextGetEventIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextInviteIsPending(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextInviteModeratorStatus(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextInviteStatus(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextInviteType(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextInviteAvailable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextInviteTentative(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextInviteDecline(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextInviteRemove(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextEventSignUp(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextEventRemove(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextEventCopy(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextEventPaste(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextEventClipboard(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextEventCanComplain(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextEventComplain(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextEventCanEdit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarContextEventGetCalendarType(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventRemoveInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventAvailable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventTentative(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventDecline(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSignUp(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSortInvites(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetInviteSortCriterion(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetStatusOptions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetStatus(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetModerator(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventClearModerator(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventCanModerate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventIsModerator(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetTypes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetRepeatOptions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetTitle(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetDescription(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetType(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetRepeatOption(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetSize(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetDate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetTime(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetLockoutDate(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetLockoutTime(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetTextureID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetLocked(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventClearLocked(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventSetAutoApprove(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventClearAutoApprove(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetTextures(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventHasPendingInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventHaveSettingsChanged(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventCanEdit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarEventGetCalendarType(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarCanSendInvite(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarCanAddEvent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CalendarIsActionPending(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_OpenCalendar(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void CalendarRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_CALENDAR; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_Calendar[i].name,
            GameScript::s_ScriptFunctions_Calendar[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_Calendar[NUM_SCRIPT_FUNCTIONS_CALENDAR] = {
    { "CalendarGetMonthNames", &Script_CalendarGetMonthNames },
    { "CalendarGetWeekdayNames", &Script_CalendarGetWeekdayNames },
    { "CalendarGetDate", &Script_CalendarGetDate },
    { "CalendarGetMinDate", &Script_CalendarGetMinDate },
    { "CalendarGetMaxDate", &Script_CalendarGetMaxDate },
    { "CalendarGetMinHistoryDate", &Script_CalendarGetMinHistoryDate },
    { "CalendarGetMaxCreateDate", &Script_CalendarGetMaxCreateDate },
    { "CalendarGetMonth", &Script_CalendarGetMonth },
    { "CalendarGetAbsMonth", &Script_CalendarGetAbsMonth },
    { "CalendarSetMonth", &Script_CalendarSetMonth },
    { "CalendarSetAbsMonth", &Script_CalendarSetAbsMonth },
    { "CalendarGetNumDayEvents", &Script_CalendarGetNumDayEvents },
    { "CalendarGetDayEvent", &Script_CalendarGetDayEvent },
    { "CalendarGetDayEventSequenceInfo", &Script_CalendarGetDayEventSequenceInfo },
    { "CalendarGetFirstPendingInvite", &Script_CalendarGetFirstPendingInvite },
    { "CalendarOpenEvent", &Script_CalendarOpenEvent },
    { "CalendarGetEventIndex", &Script_CalendarGetEventIndex },
    { "CalendarCloseEvent", &Script_CalendarCloseEvent },
    { "CalendarGetEventInfo", &Script_CalendarGetEventInfo },
    { "CalendarGetHolidayInfo", &Script_CalendarGetHolidayInfo },
    { "CalendarGetRaidInfo", &Script_CalendarGetRaidInfo },
    { "CalendarGetNumPendingInvites", &Script_CalendarGetNumPendingInvites },
    { "CalendarEventGetNumInvites", &Script_CalendarEventGetNumInvites },
    { "CalendarEventGetInvite", &Script_CalendarEventGetInvite },
    { "CalendarEventGetInviteResponseTime", &Script_CalendarEventGetInviteResponseTime },
    { "CalendarAddEvent", &Script_CalendarAddEvent },
    { "CalendarNewEvent", &Script_CalendarNewEvent },
    { "CalendarMassInviteGuild", &Script_CalendarMassInviteGuild },
    { "CalendarMassInviteArenaTeam", &Script_CalendarMassInviteArenaTeam },
    { "CalendarNewGuildAnnouncement", &Script_CalendarNewGuildAnnouncement },
    { "CalendarNewGuildEvent", &Script_CalendarNewGuildEvent },
    { "CalendarDefaultGuildFilter", &Script_CalendarDefaultGuildFilter },
    { "CalendarUpdateEvent", &Script_CalendarUpdateEvent },
    { "CalendarRemoveEvent", &Script_CalendarRemoveEvent },
    { "CalendarEventSelectInvite", &Script_CalendarEventSelectInvite },
    { "CalendarEventGetSelectedInvite", &Script_CalendarEventGetSelectedInvite },
    { "CalendarContextSelectEvent", &Script_CalendarContextSelectEvent },
    { "CalendarContextDeselectEvent", &Script_CalendarContextDeselectEvent },
    { "CalendarContextGetEventIndex", &Script_CalendarContextGetEventIndex },
    { "CalendarContextInviteIsPending", &Script_CalendarContextInviteIsPending },
    { "CalendarContextInviteModeratorStatus", &Script_CalendarContextInviteModeratorStatus },
    { "CalendarContextInviteStatus", &Script_CalendarContextInviteStatus },
    { "CalendarContextInviteType", &Script_CalendarContextInviteType },
    { "CalendarContextInviteAvailable", &Script_CalendarContextInviteAvailable },
    { "CalendarContextInviteTentative", &Script_CalendarContextInviteTentative },
    { "CalendarContextInviteDecline", &Script_CalendarContextInviteDecline },
    { "CalendarContextInviteRemove", &Script_CalendarContextInviteRemove },
    { "CalendarContextEventSignUp", &Script_CalendarContextEventSignUp },
    { "CalendarContextEventRemove", &Script_CalendarContextEventRemove },
    { "CalendarContextEventCopy", &Script_CalendarContextEventCopy },
    { "CalendarContextEventPaste", &Script_CalendarContextEventPaste },
    { "CalendarContextEventClipboard", &Script_CalendarContextEventClipboard },
    { "CalendarContextEventCanComplain", &Script_CalendarContextEventCanComplain },
    { "CalendarContextEventComplain", &Script_CalendarContextEventComplain },
    { "CalendarContextEventCanEdit", &Script_CalendarContextEventCanEdit },
    { "CalendarContextEventGetCalendarType", &Script_CalendarContextEventGetCalendarType },
    { "CalendarEventInvite", &Script_CalendarEventInvite },
    { "CalendarEventRemoveInvite", &Script_CalendarEventRemoveInvite },
    { "CalendarEventAvailable", &Script_CalendarEventAvailable },
    { "CalendarEventTentative", &Script_CalendarEventTentative },
    { "CalendarEventDecline", &Script_CalendarEventDecline },
    { "CalendarEventSignUp", &Script_CalendarEventSignUp },
    { "CalendarEventSortInvites", &Script_CalendarEventSortInvites },
    { "CalendarEventGetInviteSortCriterion", &Script_CalendarEventGetInviteSortCriterion },
    { "CalendarEventGetStatusOptions", &Script_CalendarEventGetStatusOptions },
    { "CalendarEventSetStatus", &Script_CalendarEventSetStatus },
    { "CalendarEventSetModerator", &Script_CalendarEventSetModerator },
    { "CalendarEventClearModerator", &Script_CalendarEventClearModerator },
    { "CalendarEventCanModerate", &Script_CalendarEventCanModerate },
    { "CalendarEventIsModerator", &Script_CalendarEventIsModerator },
    { "CalendarEventGetTypes", &Script_CalendarEventGetTypes },
    { "CalendarEventGetRepeatOptions", &Script_CalendarEventGetRepeatOptions },
    { "CalendarEventSetTitle", &Script_CalendarEventSetTitle },
    { "CalendarEventSetDescription", &Script_CalendarEventSetDescription },
    { "CalendarEventSetType", &Script_CalendarEventSetType },
    { "CalendarEventSetRepeatOption", &Script_CalendarEventSetRepeatOption },
    { "CalendarEventSetSize", &Script_CalendarEventSetSize },
    { "CalendarEventSetDate", &Script_CalendarEventSetDate },
    { "CalendarEventSetTime", &Script_CalendarEventSetTime },
    { "CalendarEventSetLockoutDate", &Script_CalendarEventSetLockoutDate },
    { "CalendarEventSetLockoutTime", &Script_CalendarEventSetLockoutTime },
    { "CalendarEventSetTextureID", &Script_CalendarEventSetTextureID },
    { "CalendarEventSetLocked", &Script_CalendarEventSetLocked },
    { "CalendarEventClearLocked", &Script_CalendarEventClearLocked },
    { "CalendarEventSetAutoApprove", &Script_CalendarEventSetAutoApprove },
    { "CalendarEventClearAutoApprove", &Script_CalendarEventClearAutoApprove },
    { "CalendarEventGetTextures", &Script_CalendarEventGetTextures },
    { "CalendarEventHasPendingInvite", &Script_CalendarEventHasPendingInvite },
    { "CalendarEventHaveSettingsChanged", &Script_CalendarEventHaveSettingsChanged },
    { "CalendarEventCanEdit", &Script_CalendarEventCanEdit },
    { "CalendarEventGetCalendarType", &Script_CalendarEventGetCalendarType },
    { "CalendarCanSendInvite", &Script_CalendarCanSendInvite },
    { "CalendarCanAddEvent", &Script_CalendarCanAddEvent },
    { "CalendarIsActionPending", &Script_CalendarIsActionPending },
    { "OpenCalendar", &Script_OpenCalendar },
};
