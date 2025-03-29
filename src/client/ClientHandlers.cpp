#include "client/ClientHandlers.hpp"

#include <storm/Error.hpp>
#include <common/DataStore.hpp>

#include "console/Line.hpp"


uint32_t s_newZoneID = 0;
C3Vector s_newPosition;
float s_newFacing = 0.0f;
const char* s_newMapname = nullptr;


int32_t NewWorldHandler(void* param, NETMESSAGE msgId, uint32_t time, CDataStore* msg) {
    STORM_ASSERT(msgId == SMSG_NEW_WORLD);

    msg->Get(s_newZoneID);
    msg->Get(s_newPosition.x);
    msg->Get(s_newPosition.y);
    msg->Get(s_newPosition.z);
    msg->Get(s_newFacing);

    if (msg->IsRead()) {
        // TODO
        return 1;
    } else {
        ConsoleWrite("Bad SMSG_NEW_WORLD\n", DEFAULT_COLOR);
        msg->Reset();
        return 1;
    }
}

int32_t LoginVerifyWorldHandler(void* param, NETMESSAGE msgId, uint32_t time, CDataStore* msg) {
    STORM_ASSERT(msgId == SMSG_LOGIN_VERIFY_WORLD);

    uint32_t zoneID;
    msg->Get(zoneID);

    C3Vector position;
    msg->Get(position.x);
    msg->Get(position.y);
    msg->Get(position.z);

    float facing;
    msg->Get(facing);
    // zoneID != ClntObjMgrGetMapID()
    if (false) {
        s_newFacing = facing;
        s_newPosition = position;
        s_newZoneID = zoneID;
        //if (zoneID < dword_AD4170 || zoneID > dword_AD416C || (v0 = *(_DWORD*)(dword_AD4180 + 4 * (zoneID - dword_AD4170))) == 0) {
        //    ConsoleWrite("Bad SMSG_NEW_WORLD zoneID\n", 0);
        //    return 0;
        //}
        //s_newMapname = *(_DWORD*)(v0 + 4);
        //LoadNewWorld(0, 0);
    }
    return 1;
}
