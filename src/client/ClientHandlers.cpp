#include "client/ClientHandlers.hpp"

#include <storm/Error.hpp>
#include <common/DataStore.hpp>

#include "console/Console.hpp"
#include "world/World.hpp"
#include "db/Db.hpp"
#include "event/Timer.hpp"


int32_t NewWorldHandler(void* param, NETMESSAGE msgId, uint32_t time, CDataStore* msg) {
    STORM_ASSERT(msgId == SMSG_NEW_WORLD);

    msg->Get(s_newZoneID);
    msg->Get(s_newPosition.x);
    msg->Get(s_newPosition.y);
    msg->Get(s_newPosition.z);
    msg->Get(s_newFacing);

    if (msg->IsRead()) {
        auto record = g_mapDB.GetRecord(s_newZoneID);
        if (!record) {
            ConsoleWrite("Bad SMSG_NEW_WORLD zoneID\n", DEFAULT_COLOR);
            return 0;
        }

        s_newMapname = record->m_directory;
        // TODO: EventSetTimer(0, LoadNewWorld, 1);
        // WORKAROUND:
        LoadNewWorld(nullptr);
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

    if (true /* zoneID != ClntObjMgrGetMapID() */) {
        s_newFacing = facing;
        s_newPosition = position;
        s_newZoneID = zoneID;
        auto record = g_mapDB.GetRecord(s_newZoneID);
        if (!record) {
            ConsoleWrite("Bad SMSG_NEW_WORLD zoneID\n", DEFAULT_COLOR);
            return 0;
        }

        s_newMapname = record->m_directory;
        LoadNewWorld(nullptr);
    }
    return 1;
}
