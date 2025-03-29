#include "clientobject/Unit_C.hpp"

const char* CGUnit_C::GetDisplayRaceNameFromRecord(ChrRacesRec* record, uint8_t sexIn, uint8_t* sexOut) {
    const char* result;

    if (sexOut) {
        *sexOut = sexIn;
    }
    if (!record) {
        return nullptr;
    }
    if (!sexIn) {
        if (record->m_nameMale[0]) {
            return record->m_nameMale;
        }

        if (record->m_nameFemale[0]) {
            if (sexOut) {
                *sexOut = 1;
            }
            return record->m_nameFemale;
        }

        return record->m_name;
    }

    if (sexIn != 1) {
        return record->m_name;
    }

    if (record->m_nameFemale[0]) {
        return record->m_nameFemale;
    }

    if (!record->m_nameMale[0]) {
        return record->m_name;
    }

    if (sexOut) {
        *sexOut = 0;
    }
    return record->m_nameMale;
}
