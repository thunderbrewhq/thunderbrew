#include "clientobject/Player_C.hpp"
#include "clientobject/Types.hpp"
#include "db/Db.hpp"
#include <storm/Error.hpp>


const CreatureModelDataRec* Player_C_GetModelName(uint32_t race, uint32_t sex) {
    STORM_ASSERT(sex < UNITSEX_LAST);

    auto displayId = Player_C_GetDisplayId(race, sex);
    auto record = g_creatureDisplayInfoDB.GetRecord(displayId);
    if (!record) {
        SErrPrepareAppFatal(__FILE__, __LINE__);
        SErrDisplayAppFatal("Error, unknown displayInfo %d specified for player race %d sex %d!", displayId, race, sex);
    }

    auto modelData = g_creatureModelDataDB.GetRecord(record->m_modelID);
    if (!modelData) {
        SErrPrepareAppFatal(__FILE__, __LINE__);
        SErrDisplayAppFatal("Error, unknown model record %d specified for player race %d sex %d!", record->m_modelID, race, sex);
    }

    return modelData;
}

uint32_t Player_C_GetDisplayId(uint32_t race, uint32_t sex) {
    STORM_ASSERT(sex < UNITSEX_LAST);

    auto record = g_chrRacesDB.GetRecord(race);
    if (!record) {
        SErrPrepareAppFatal(__FILE__, __LINE__);
        SErrDisplayAppFatal("Error, race %d not found in race table!", race);
    }

    if (sex == UNITSEX_MALE) {
        return record->m_maleDisplayID;
    }

    if (sex == UNITSEX_FEMALE) {
        return record->m_femaleDisplayID;
    }

    if (sex == UNITSEX_NONE) {
        SErrPrepareAppFatal(__FILE__, __LINE__);
        SErrDisplayAppFatal("Error, attempted to look up model for player with sex %d (UNITSEX_NONE), all players have sex! =D", 2);
    }

    SErrPrepareAppFatal(__FILE__, __LINE__);
    SErrDisplayAppFatal("Error, unrecognized sex code %d!", sex);
    return 0;
}
