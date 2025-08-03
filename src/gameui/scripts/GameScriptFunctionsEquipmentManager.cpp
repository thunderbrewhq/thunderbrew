#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_SaveEquipmentSet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_DeleteEquipmentSet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_RenameEquipmentSet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_EquipmentManagerIgnoreSlotForSave(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_EquipmentManagerIsSlotIgnoredForSave(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_EquipmentManagerClearIgnoredSlotsForSave(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_EquipmentManagerUnignoreSlotForSave(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetEquipmentSetLocations(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetEquipmentSetItemIDs(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumEquipmentSets(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetEquipmentSetInfo(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetEquipmentSetInfoByName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_EquipmentSetContainsLockedItems(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PickupEquipmentSetByName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_PickupEquipmentSet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_UseEquipmentSet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CanUseEquipmentSets(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void EquipmentManagerRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_EQUIPMENT_MANAGER; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_EquipmentManager[i].name,
            GameScript::s_ScriptFunctions_EquipmentManager[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_EquipmentManager[NUM_SCRIPT_FUNCTIONS_EQUIPMENT_MANAGER] = {
    { "SaveEquipmentSet", &Script_SaveEquipmentSet },
    { "DeleteEquipmentSet", &Script_DeleteEquipmentSet },
    { "RenameEquipmentSet", &Script_RenameEquipmentSet },
    { "EquipmentManagerIgnoreSlotForSave", &Script_EquipmentManagerIgnoreSlotForSave },
    { "EquipmentManagerIsSlotIgnoredForSave", &Script_EquipmentManagerIsSlotIgnoredForSave },
    { "EquipmentManagerClearIgnoredSlotsForSave", &Script_EquipmentManagerClearIgnoredSlotsForSave },
    { "EquipmentManagerUnignoreSlotForSave", &Script_EquipmentManagerUnignoreSlotForSave },
    { "GetEquipmentSetLocations", &Script_GetEquipmentSetLocations },
    { "GetEquipmentSetItemIDs", &Script_GetEquipmentSetItemIDs },
    { "GetNumEquipmentSets", &Script_GetNumEquipmentSets },
    { "GetEquipmentSetInfo", &Script_GetEquipmentSetInfo },
    { "GetEquipmentSetInfoByName", &Script_GetEquipmentSetInfoByName },
    { "EquipmentSetContainsLockedItems", &Script_EquipmentSetContainsLockedItems },
    { "PickupEquipmentSetByName", &Script_PickupEquipmentSetByName },
    { "PickupEquipmentSet", &Script_PickupEquipmentSet },
    { "UseEquipmentSet", &Script_UseEquipmentSet },
    { "CanUseEquipmentSets", &Script_CanUseEquipmentSets },
};
