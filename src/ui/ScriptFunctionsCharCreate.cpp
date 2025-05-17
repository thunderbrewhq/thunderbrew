#include "ui/ScriptFunctions.hpp"
#include "ui/CSimpleModelFFX.hpp"
#include "ui/Types.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"
#include "db/Db.hpp"
#include "clientobject/Unit_C.hpp"
#include "glue/CCharacterCreation.hpp"
#include "glue/CCharacterComponent.hpp"
#include <cstdint>

int32_t Script_SetCharCustomizeFrame(lua_State* L) {
    if (!lua_isstring(L, 1)) {
        return luaL_error(L, "Usage: SetCharCustomizeFrame(\"frameName\")");
    }

    auto type = CSimpleModel::GetObjectType();
    auto name = lua_tolstring(L, 1, nullptr);
    auto frame = CScriptObject::GetScriptObjectByName(name, type);

    if (frame) {
        CCharacterCreation::SetCharCustomizeFrame(static_cast<CSimpleModel*>(frame));
    }

    return 0;
}

int32_t Script_SetCharCustomizeBackground(lua_State* L) {
    if (!lua_isstring(L, 1)) {
        return luaL_error(L, "Usage: SetCharCustomizeBackground(\"filename\")");
    }

    auto filename = lua_tolstring(L, 1, nullptr);
    CCharacterCreation::SetCharCustomizeModel(filename);

    return 0;
}

int32_t Script_ResetCharCustomize(lua_State*) {
    CCharacterCreation::ResetCharCustomizeInfo();
    return 0;
}

int32_t Script_GetNameForRace(lua_State* L) {
    auto raceID = CCharacterCreation::m_character->m_data.m_info.raceID;
    auto sexID = CCharacterCreation::m_character->m_data.m_info.sexID;
    auto record = g_chrRacesDB.GetRecord(raceID);
    auto raceName = CGUnit_C::GetDisplayRaceNameFromRecord(record, sexID);
    if (record && raceName) {
        lua_pushstring(L, raceName);
        lua_pushstring(L, record->m_clientFileString);
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
    }

    return 2;
}

int32_t Script_GetFactionForRace(lua_State* L) {
    if (!lua_isnumber(L, 1)) {
        return luaL_error(L, "Usage: GetFactionForRace(index)");
    }

    uint32_t index = static_cast<uint32_t>(lua_tonumber(L, 1)) - 1;
    int32_t raceID = 0;
    if (index < CCharacterCreation::m_races.Count()) {
        raceID = CCharacterCreation::m_races[index];
    }

    auto raceRecord = g_chrRacesDB.GetRecord(raceID);
    if (raceRecord) {
        auto factionTemplateRecord = g_factionTemplateDB.GetRecord(raceRecord->m_factionID);
        if (factionTemplateRecord) {
            for (int32_t i = 0; i < g_factionGroupDB.GetNumRecords(); ++i) {
                auto factionGroupRecord = g_factionGroupDB.GetRecordByIndex(i);
                if (!factionGroupRecord || factionGroupRecord->m_maskID == 0) {
                    continue;
                }

                if (((1 << factionGroupRecord->m_maskID) & factionTemplateRecord->m_factionGroup) != 0) {
                    lua_pushstring(L, factionGroupRecord->m_name);
                    lua_pushstring(L, factionGroupRecord->m_internalName);
                    return 2;
                }
            }
        }
    }

    lua_pushnil(L);
    lua_pushnil(L);
    return 2;
}

int32_t Script_GetAvailableRaces(lua_State* L) {
    for (uint32_t i = 0; i < CCharacterCreation::m_races.Count(); ++i) {
        auto raceRecord = g_chrRacesDB.GetRecord(CCharacterCreation::m_races[i]);
        auto raceName = CGUnit_C::GetDisplayRaceNameFromRecord(
            raceRecord,
            CCharacterCreation::m_character->m_data.m_info.sexID);

        lua_pushstring(L, raceName);
        lua_pushstring(L, raceRecord ? raceRecord->m_clientFileString : nullptr);
        // TODO: Expansion Check
        lua_pushnumber(L, 1.0);
    }
    return CCharacterCreation::m_races.Count() * 3;
}

int32_t Script_GetAvailableClasses(lua_State* L) {
    for (int32_t i = 0; i < g_chrClassesDB.GetNumRecords(); ++i) {
        auto record = g_chrClassesDB.GetRecordByIndex(i);
        auto className = CGUnit_C::GetDisplayClassNameFromRecord(
            record,
            CCharacterCreation::m_character->m_data.m_info.sexID);
        if (className) {
            lua_pushstring(L, className);
            lua_pushstring(L, record->m_filename);
            // TODO: Expansion Check
            lua_pushnumber(L, 1.0);
        } else {
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
        }
    }
    return g_chrClassesDB.GetNumRecords() * 3;
}

int32_t Script_GetClassesForRace(lua_State* L) {
    for (uint32_t i = 0; i < CCharacterCreation::m_classes.Count(); ++i) {
        auto record = CCharacterCreation::m_classes[i];
        auto className = CGUnit_C::GetDisplayClassNameFromRecord(
            record,
            CCharacterCreation::m_character->m_data.m_info.sexID);
        if (className) {
            lua_pushstring(L, className);
            lua_pushstring(L, record->m_filename);
            // TODO: Expansion Check
            lua_pushnumber(L, 1.0);            
        } else {
            lua_pushnil(L);
            lua_pushnil(L);
            lua_pushnil(L);
        }
    }
    return CCharacterCreation::m_classes.Count() * 3;
}

int32_t Script_GetHairCustomization(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetFacialHairCustomization(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetSelectedRace(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetSelectedSex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetSelectedClass(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_SetSelectedRace(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_SetSelectedSex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_SetSelectedClass(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_UpdateCustomizationBackground(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_UpdateCustomizationScene(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_CycleCharCustomization(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_RandomizeCharCustomization(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetCharacterCreateFacing(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_SetCharacterCreateFacing(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetRandomName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_CreateCharacter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_CustomizeExistingCharacter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_PaidChange_GetPreviousRaceIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_PaidChange_GetCurrentRaceIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_PaidChange_GetCurrentClassIndex(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_PaidChange_GetName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_IsRaceClassValid(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_IsRaceClassRestricted(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetCreateBackgroundModel(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

FrameScript_Method FrameScript::s_ScriptFunctions_CharCreate[NUM_SCRIPT_FUNCTIONS_CHAR_CREATE] = {
    { "SetCharCustomizeFrame",          &Script_SetCharCustomizeFrame },
    { "SetCharCustomizeBackground",     &Script_SetCharCustomizeBackground },
    { "ResetCharCustomize",             &Script_ResetCharCustomize },
    { "GetNameForRace",                 &Script_GetNameForRace },
    { "GetFactionForRace",              &Script_GetFactionForRace },
    { "GetAvailableRaces",              &Script_GetAvailableRaces },
    { "GetAvailableClasses",            &Script_GetAvailableClasses },
    { "GetClassesForRace",              &Script_GetClassesForRace },
    { "GetHairCustomization",           &Script_GetHairCustomization },
    { "GetFacialHairCustomization",     &Script_GetFacialHairCustomization },
    { "GetSelectedRace",                &Script_GetSelectedRace },
    { "GetSelectedSex",                 &Script_GetSelectedSex },
    { "GetSelectedClass",               &Script_GetSelectedClass },
    { "SetSelectedRace",                &Script_SetSelectedRace },
    { "SetSelectedSex",                 &Script_SetSelectedSex },
    { "SetSelectedClass",               &Script_SetSelectedClass },
    { "UpdateCustomizationBackground",  &Script_UpdateCustomizationBackground },
    { "UpdateCustomizationScene",       &Script_UpdateCustomizationScene },
    { "CycleCharCustomization",         &Script_CycleCharCustomization },
    { "RandomizeCharCustomization",     &Script_RandomizeCharCustomization },
    { "GetCharacterCreateFacing",       &Script_GetCharacterCreateFacing },
    { "SetCharacterCreateFacing",       &Script_SetCharacterCreateFacing },
    { "GetRandomName",                  &Script_GetRandomName },
    { "CreateCharacter",                &Script_CreateCharacter },
    { "CustomizeExistingCharacter",     &Script_CustomizeExistingCharacter },
    { "PaidChange_GetPreviousRaceIndex", &Script_PaidChange_GetPreviousRaceIndex },
    { "PaidChange_GetCurrentRaceIndex", &Script_PaidChange_GetCurrentRaceIndex },
    { "PaidChange_GetCurrentClassIndex", &Script_PaidChange_GetCurrentClassIndex },
    { "PaidChange_GetName",             &Script_PaidChange_GetName },
    { "IsRaceClassValid",               &Script_IsRaceClassValid },
    { "IsRaceClassRestricted",          &Script_IsRaceClassRestricted },
    { "GetCreateBackgroundModel",       &Script_GetCreateBackgroundModel }
};
