#include "gameui/GameScriptFunctions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"


static int32_t Script_SetTaxiMap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_NumTaxiNodes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TaxiNodeName(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TaxiNodePosition(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TaxiNodeCost(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TakeTaxiNode(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_CloseTaxiMap(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TaxiNodeGetType(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TaxiNodeSetCurrent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TaxiGetSrcX(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TaxiGetSrcY(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TaxiGetDestX(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_TaxiGetDestY(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetNumRoutes(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

void CGTaxiMapRegisterScriptFunctions() {
    for (int32_t i = 0; i < NUM_SCRIPT_FUNCTIONS_CGTAXI_MAP; ++i) {
        FrameScript_RegisterFunction(
            GameScript::s_ScriptFunctions_CGTaxiMap[i].name,
            GameScript::s_ScriptFunctions_CGTaxiMap[i].method);
    }
}

FrameScript_Method GameScript::s_ScriptFunctions_CGTaxiMap[NUM_SCRIPT_FUNCTIONS_CGTAXI_MAP] = {
    { "SetTaxiMap", &Script_SetTaxiMap },
    { "NumTaxiNodes", &Script_NumTaxiNodes },
    { "TaxiNodeName", &Script_TaxiNodeName },
    { "TaxiNodePosition", &Script_TaxiNodePosition },
    { "TaxiNodeCost", &Script_TaxiNodeCost },
    { "TakeTaxiNode", &Script_TakeTaxiNode },
    { "CloseTaxiMap", &Script_CloseTaxiMap },
    { "TaxiNodeGetType", &Script_TaxiNodeGetType },
    { "TaxiNodeSetCurrent", &Script_TaxiNodeSetCurrent },
    { "TaxiGetSrcX", &Script_TaxiGetSrcX },
    { "TaxiGetSrcY", &Script_TaxiGetSrcY },
    { "TaxiGetDestX", &Script_TaxiGetDestX },
    { "TaxiGetDestY", &Script_TaxiGetDestY },
    { "GetNumRoutes", &Script_GetNumRoutes },
};
