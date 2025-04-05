#ifndef CLIENTOBJECT_UNIT_C_HPP
#define CLIENTOBJECT_UNIT_C_HPP

#include <cstdint>

class ChrRacesRec;
class ChrClassesRec;

class CGUnit_C {
    public:
        static const char* GetDisplayRaceNameFromRecord(ChrRacesRec* record, uint8_t sexIn, uint8_t* sexOut = nullptr);
        static const char* GetDisplayClassNameFromRecord(ChrClassesRec* record, uint8_t sexIn, uint8_t* sexOut = nullptr);
};

#endif // CLIENTOBJECT_UNIT_C_HPP
