#ifndef CLIENT_CLIENT_HPP
#define CLIENT_CLIENT_HPP

#include "event/Event.hpp"
#include "tempest/Vector.hpp"
#include <cstdint>

class CVar;

namespace Client {
    extern CVar* g_accountNameVar;
    extern CVar* g_accountListVar;
    extern CVar* g_accountUsesTokenVar;
    extern CVar* g_movieVar;
    extern CVar* g_expansionMovieVar;
    extern CVar* g_movieSubtitleVar;
    extern HEVENTCONTEXT g_clientEventContext;
    extern char g_currentLocaleName[5];
}

void ClientPostClose(int32_t a1);

const char* UpdateInstallLocation();

void CommonMain();

void StormInitialize();

void WowClientInit();

void ClientInitializeGame(int32_t continentID, const C3Vector& position);

#endif
