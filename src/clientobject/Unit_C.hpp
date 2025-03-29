#ifndef CLIENTOBJECT_UNIT_C_HPP
#define CLIENTOBJECT_UNIT_C_HPP

#include "db/rec/ChrRacesRec.hpp"

class CGUnit_C {
    public:
        static const char* GetDisplayRaceNameFromRecord(ChrRacesRec* record, uint8_t sexIn, uint8_t* sexOut = nullptr);
};

#endif // CLIENTOBJECT_UNIT_C_HPP
