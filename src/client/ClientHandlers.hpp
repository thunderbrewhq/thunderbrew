#ifndef CLIENT_CLIENTHANDLERS_HPP
#define CLIENT_CLIENTHANDLERS_HPP

#include "net/Types.hpp"

class CDataStore;


int32_t NewWorldHandler(void* param, NETMESSAGE msgId, uint32_t time, CDataStore* msg);
int32_t LoginVerifyWorldHandler(void* param, NETMESSAGE msgId, uint32_t time, CDataStore* msg);


#endif // CLIENT_CLIENTHANDLERS_HPP
