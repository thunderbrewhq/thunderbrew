#include "db/Db.hpp"
#include "db/WowClientDB_Base.hpp"

WowClientDB<AchievementRec> g_achievementDB;
WowClientDB<Cfg_CategoriesRec> g_cfg_CategoriesDB;

void LoadDB(WowClientDB_Base* db, const char* filename, int32_t linenumber) {
    db->Load(filename, linenumber);
};

void StaticDBLoadAll(void (*loadFn)(WowClientDB_Base*, const char*, int32_t)) {
    loadFn(&g_achievementDB, __FILE__, __LINE__);
    loadFn(&g_cfg_CategoriesDB, __FILE__, __LINE__);
};

void ClientDBInitialize() {
    // TODO

    StaticDBLoadAll(LoadDB);

    // TODO
}