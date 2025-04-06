#ifndef CLIENTOBJECT_PLAYER_C_HPP
#define CLIENTOBJECT_PLAYER_C_HPP

#include <cstdint>


class CreatureModelDataRec;


const CreatureModelDataRec* Player_C_GetModelName(uint32_t race, uint32_t sex);
uint32_t Player_C_GetDisplayId(uint32_t race, uint32_t sex);


#endif // CLIENTOBJECT_PLAYER_C_HPP
