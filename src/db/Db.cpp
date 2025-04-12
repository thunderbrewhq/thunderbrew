#include "db/Db.hpp"
#include "db/WowClientDB_Base.hpp"

#include <cstdio>

void LoadDB(WowClientDB_Base* db, const char* filename, int32_t linenumber) {
    db->Load(filename, linenumber);
    printf("load %s:%d\n", filename, linenumber);
};

void ClientDBInitialize() {
    // TODO

    StaticDBLoadAll(LoadDB);

    // TODO
}
