#include "ui/ScriptFunctions.hpp"
#include "db/Db.hpp"
#include "glue/CCharacterSelection.hpp"
#include "ui/CSimpleModelFFX.hpp"
#include "ui/Types.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"
#include "glue/CGlueMgr.hpp"
#include "db/Db.hpp"
#include "clientobject/Unit_C.hpp"

int32_t Script_SetCharSelectModelFrame(lua_State* L) {
    if (!lua_isstring(L, 1)) {
        return luaL_error(L, "Usage: SetCharSelectModelFrame(\"frameName\")");
    }

    auto type = CSimpleModel::GetObjectType();
    auto name = lua_tolstring(L, 1, nullptr);
    auto frame = CScriptObject::GetScriptObjectByName(name, type);

    if (frame) {
        CCharacterSelection::s_modelFrame = static_cast<CSimpleModelFFX*>(frame);
    }

    return 0;
}

int32_t Script_SetCharSelectBackground(lua_State* L) {
    if (!lua_isstring(L, 1)) {
        return luaL_error(L, "Usage: SetCharSelectBackground(\"filename\")");
    }

    auto modelPath = lua_tolstring(L, 1, nullptr);
    CCharacterSelection::SetBackgroundModel(modelPath);

    return 0;
}

int32_t Script_GetCharacterListUpdate(lua_State* L) {
    // TODO: CCharSelectInfo::ClearCharacterModel();
    // TODO: CCharSelectInfo::ClearPetModel();
    CGlueMgr::GetCharacterList();
    return 0;
}

int32_t Script_GetNumCharacters(lua_State* L) {
    lua_pushnumber(L, CCharacterSelection::GetNumCharacters());

    return 1;
}

int32_t Script_GetCharacterInfo(lua_State* L) {
    if (!lua_isnumber(L, 1)) {
        luaL_error(L, "Usage: GetCharacterInfo(index)");
    }

    int index = static_cast<int>(lua_tonumber(L, 1)) - 1;
    if (index < 0 || index > CCharacterSelection::GetNumCharacters()) {
        lua_pushnil(L); // name
        lua_pushnil(L); // race
        lua_pushnil(L); // class
        lua_pushnumber(L, 0.0); // level
        lua_pushnumber(L, 0.0); // zone
        lua_pushnil(L); // sex
        lua_pushnil(L); // ghost
        lua_pushnil(L); // PCC
        lua_pushnil(L); // PRC
        lua_pushnil(L); // PFC
        return 10;
    }

    auto& character = CCharacterSelection::s_characterList[index].m_characterInfo;
    lua_pushstring(L, character.name);

    auto raceName = CGUnit_C::GetDisplayRaceNameFromRecord(g_chrRacesDB.GetRecord(character.raceID), character.sexID);
    lua_pushstring(L, raceName ? raceName : "");

    // TODO: auto className = CGUnit_C::GetDisplayClassNameFromRecord(g_chrClassesDB.GetRecord(character.classID), character.sexID);
    auto className = "Warrior";
    lua_pushstring(L, className ? className : "");

    lua_pushnumber(L, character.experienceLevel);

    // TODO: auto areaRecord = g_areaTableDB.GetRecord(character.zoneID);
    void* areaRecord = nullptr;
    if (areaRecord) {
        // TODO: lua_pushstring(L, areaRecord->name)
    } else {
        lua_pushnil(L);
    }

    // TODO: Use g_glueFrameScriptGenders[character.sexID]
    lua_pushnumber(L, 0);

    // ghost
    lua_pushboolean(L, character.flags & 0x2000);

    // PCC
    lua_pushboolean(L, character.customizeFlags & 1);

    // PRC
    lua_pushboolean(L, character.customizeFlags & 0x100000);

    // PFC
    lua_pushboolean(L, character.customizeFlags & 0x10000);

    return 10;
}

int32_t Script_SelectCharacter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_DeleteCharacter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_RenameCharacter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_DeclineCharacter(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_UpdateSelectionCustomizationScene(lua_State* L) {
    CCharacterSelection::RenderPrep();

    return 0;
}

int32_t Script_GetCharacterSelectFacing(lua_State* L) {
    // Radian to Degree
    lua_pushnumber(L, CCharacterSelection::s_charFacing * 57.29578f);
    return 1;
}

int32_t Script_SetCharacterSelectFacing(lua_State* L) {
    if (!lua_isnumber(L, 1)) {
        luaL_error(L, "Usage: SetCharacterSelectFacing(degrees)");
    }
    // Degree to Radian
    float facing = lua_tonumber(L, 1) * 0.017453292;
    CCharacterSelection::SetCharFacing(facing);
    return 1;
}

int32_t Script_GetSelectBackgroundModel(lua_State* L) {
    if (!lua_isnumber(L, 1)) {
        return luaL_error(L, "Usage: GetSelectBackgroundModel(index)");
    }

    auto index = static_cast<int32_t>(lua_tonumber(L, 1)) - 1;

    // TODO: if (SFile::IsTrial())
    if (false) {
        lua_pushstring(L, "CharacterSelect");
        return 1;
    }

    // TODO

    ChrRacesRec* racesRec = nullptr;

    if (index < 0 || index >= CCharacterSelection::s_characterList.Count()) {
        racesRec = g_chrRacesDB.GetRecord(2);
    } else {
        auto raceID = CCharacterSelection::s_characterList[index].m_characterInfo.raceID;
        racesRec = g_chrRacesDB.GetRecord(raceID);
    }

    if (racesRec) {
        lua_pushstring(L, racesRec->m_clientFileString);
    } else {
        lua_pushstring(L, "");
    }

    return 1;
}

FrameScript_Method FrameScript::s_ScriptFunctions_CharSelect[NUM_SCRIPT_FUNCTIONS_CHAR_SELECT] = {
    { "SetCharSelectModelFrame",    &Script_SetCharSelectModelFrame },
    { "SetCharSelectBackground",    &Script_SetCharSelectBackground },
    { "GetCharacterListUpdate",     &Script_GetCharacterListUpdate },
    { "GetNumCharacters",           &Script_GetNumCharacters },
    { "GetCharacterInfo",           &Script_GetCharacterInfo },
    { "SelectCharacter",            &Script_SelectCharacter },
    { "DeleteCharacter",            &Script_DeleteCharacter },
    { "RenameCharacter",            &Script_RenameCharacter },
    { "DeclineCharacter",           &Script_DeclineCharacter },
    { "UpdateSelectionCustomizationScene", &Script_UpdateSelectionCustomizationScene },
    { "GetCharacterSelectFacing",   &Script_GetCharacterSelectFacing },
    { "SetCharacterSelectFacing",   &Script_SetCharacterSelectFacing },
    { "GetSelectBackgroundModel",   &Script_GetSelectBackgroundModel }
};
