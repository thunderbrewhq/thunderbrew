#ifndef DB_MESSAGE_HPP
#define DB_MESSAGE_HPP

#include "db/WowClientDB.hpp"
#include "db/rec/Startup_StringsRec.hpp"

#define MSG_TITLE_WOW           1
#define MSG_GX_INIT_FAILED_D3D  2
#define MSG_GX_INIT_FAILED      3
#define MSG_HW_UNSUPPORTED      4
#define MSG_HW_CHANGED          5
#define MSG_GLUEXML_UI_CORRUPT  9
#define MSG_FRAMEXML_UI_CORRUPT 10
#define MSG_GX_NO_DEVICE        11
#define MSG_REMOTE_DESKTOP      12

extern WowClientDB<Startup_StringsRec> g_Startup_StringsDB;

#endif
