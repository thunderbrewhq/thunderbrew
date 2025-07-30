#include "net/connection/NetClient.hpp"
#include "net/connection/WowConnection.hpp"
#include "glue/CGlueMgr.hpp"
#include "console/Console.hpp"
#include <cstdlib>
#include <cstring>
#include <new>
#include <common/DataStore.hpp>
#include <common/Prop.hpp>
#include <common/Time.hpp>
#include <storm/Error.hpp>
#include <storm/String.hpp>

HPROPCONTEXT s_propContext;

CLIENT_NETSTATS NetClient::s_stats = {};
int32_t NetClient::s_clientCount = 0;

void InitializePropContext() {
    if (PropGetSelectedContext() != s_propContext) {
        PropSelectContext(s_propContext);
    }
}


NETEVENTQUEUE::~NETEVENTQUEUE() {
    this->Clear();
}

void NETEVENTQUEUE::AddEvent(EVENTID eventId, void* conn, NetClient* client, const void* data, uint32_t bytes) {
    this->m_critSect.Enter();

    auto node = this->m_eventQueue.NewNode(2, 0, 0x0);

    node->m_eventId = eventId;

    if (bytes) {
        node->m_data = SMemAlloc(bytes, __FILE__, __LINE__, 0x0);
        memcpy(node->m_data, data, bytes);
        node->m_dataSize = bytes;
    } else {
        node->m_data = nullptr;
        node->m_dataSize = 0;
    }

    node->m_timeReceived = OsGetAsyncTimeMsPrecise();

    client->AddRef();

    this->m_critSect.Leave();
}

void NETEVENTQUEUE::Poll() {
    this->m_critSect.Enter();

    auto deleted = false;
    auto client = this->m_client;

    client->AddRef();

    for (auto node = this->m_eventQueue.Head(); node; node = this->m_eventQueue.Next(node)) {
        if (!client->GetDelete()) {
            switch (node->m_eventId) {
            case EVENT_ID_NET_DATA:
                client->HandleData(node->m_timeReceived, node->m_data, node->m_dataSize);
                break;

            case EVENT_ID_NET_CONNECT:
                client->HandleConnect();
                break;

            case EVENT_ID_NET_DISCONNECT:
                client->HandleDisconnect();
                break;

            case EVENT_ID_NET_CANTCONNECT:
                client->HandleCantConnect();
                break;

            case EVENT_ID_NET_DESTROY:
                client->SetDelete();
                deleted = true;
                break;

            case EVENT_ID_NET_AUTH_CHALLENGE:
                client->HandleAuthChallenge(static_cast<AuthenticationChallenge*>(node->m_data));
                break;

            default:
                break;
            }
        }

        // Matching 1:1 with the ref added by NETEVENTQUEUE::AddEvent
        client->DelRef();
    }

    if (!deleted) {
        client->HandleIdle();
    }

    client->DelRef();

    this->m_eventQueue.Clear();

    this->m_critSect.Leave();
}

void NETEVENTQUEUE::Clear() {
    this->m_critSect.Enter();
    this->m_eventQueue.Clear();
    this->m_critSect.Leave();
}


void NetClient::LogStats() {
    char message[128];

    uint32_t time = OsGetAsyncTimeMs();
    SStrPrintf(
        message,
        sizeof(message),
        "Client net stats: %Lu bytes sent, %Lu bytes received, %Lu msec elapsed",
        NetClient::s_stats.bytesSent,
        NetClient::s_stats.bytesReceived,
        time - s_stats.logTimestamp);
    ConsoleWrite(message, DEFAULT_COLOR);
}

void NetClient::AddRef() {
    SInterlockedIncrement(&this->m_refCount);
}

void NetClient::AuthChallengeHandler(WowConnection* conn, CDataStore* msg) {
    auto challenge = NEW(AuthenticationChallenge);

    uint32_t v14;
    msg->Get(v14);

    msg->Get(challenge->uint0);

    // TODO calculate client seed?

    if (conn == this->m_serverConnection) {
        this->m_netEventQueue->AddEvent(EVENT_ID_NET_AUTH_CHALLENGE, conn, this, challenge, sizeof(AuthenticationChallenge));
    } else if (conn == this->m_redirectConnection) {
        // TODO
    } else {
        conn->Disconnect();
    }

    DEL(challenge);
}

void NetClient::Connect(const char* addrStr) {
    if (this->m_netState != NS_INITIALIZED) {
        SErrDisplayAppFatal("Expected (m_netState == NS_INITIALIZED), got %d", this->m_netState);
    }

    uint16_t port = 9090;

    char host[1024];
    SStrCopy(host, addrStr, sizeof(host));

    auto portDelim = SStrChr(host, ':');
    if (portDelim) {
        *portDelim = '\0';
        port = atoi(portDelim + 1);
    }

    this->m_serverConnection->SetEncryption(false);
    this->m_netState = NS_INITIALIZED;
    this->ConnectInternal(host, port);
}

void NetClient::Disconnect() {
    if (this->m_redirectConnection) {
        this->m_redirectConnection->SetResponse(nullptr, false);
        this->m_redirectConnection->Disconnect();
        this->m_redirectConnection->Release();
    }

    if (this->m_netState == NS_CONNECTED) {
        this->m_netState = NS_DISCONNECTING;
        this->m_serverConnection->Disconnect();
    } else {
        this->m_serverConnection->SetResponse(nullptr, false);
        this->m_serverConnection->Disconnect();
        this->m_netEventQueue->Clear();
        this->m_serverConnection->Release();

        auto connectionMem = SMemAlloc(sizeof(WowConnection), __FILE__, __LINE__, 0x0);
        if (connectionMem) {
            auto connection = new (connectionMem) WowConnection(this, nullptr);
            this->m_serverConnection = connection;
        } else {
            this->m_serverConnection = nullptr;
        }

        this->m_netState = NS_INITIALIZED;
    }
}

int32_t NetClient::ConnectInternal(const char* host, uint16_t port) {
    if (this->m_netState != NS_INITIALIZED) {
        SErrDisplayAppFatal("Expected (m_netState == NS_INITIALIZED), got %d", this->m_netState);
    }

    this->m_netState = NS_CONNECTING;
    this->m_serverConnection->Connect(host, port, -1);

    if (this->m_redirectConnection) {
        this->m_redirectConnection->SetResponse(nullptr, false);
        this->m_redirectConnection->Disconnect();
        this->m_redirectConnection->Release();
        this->m_redirectConnection = nullptr;
    }

    return 1;
}

void NetClient::DelRef() {
    auto refCount = SInterlockedDecrement(&this->m_refCount);

    if (refCount == 0 && this->m_deleteMe) {
        delete this;
    }
}

void NetClient::EnableEncryption(WowConnection* conn, uint8_t* seed, uint8_t seedLen) {
    conn->SetEncryptionKey(
        this->m_loginData.m_sessionKey,
        sizeof(this->m_loginData.m_sessionKey),
        1,
        seed,
        seedLen
    );

    conn->uint375 = 4;
    conn->uint376 = 2;

    conn->SetEncryption(true);
}

bool NetClient::GetDelete() {
    return this->m_deleteMe;
}

const LoginData& NetClient::GetLoginData() {
    return this->m_loginData;
}

NETSTATE NetClient::GetState() {
    return this->m_netState;
}

void NetClient::Ping() {
    if (!this->m_serverConnection->m_encrypt) {
        return;
    }

    this->m_pingLock.Enter();
    this->m_pingSent = OsGetAsyncTimeMsPrecise();

    CDataStore msg;
    msg.Put(static_cast<uint32_t>(CMSG_PING));
    msg.Put(++this->m_pingSequence);
    if (this->m_netState == NS_CONNECTED) {
        if (this->m_latencyEnd) {
            msg.Put(this->m_latency[this->m_latencyEnd]);
        } else {
            msg.Put(static_cast<uint32_t>(0));
        }
    }
    msg.Finalize();

    this->m_pingLock.Leave();
    this->Send(&msg);
}

int32_t NetClient::HandleCantConnect() {
    this->PushObjMgr();

    STORM_ASSERT(m_netState == NS_CONNECTING);
    this->m_netState = NS_INITIALIZED;

    this->PopObjMgr();

    return 1;
}

int32_t NetClient::ValidateMessageId(uint32_t msgId) {
    // This method does nothing
    return 0;
}

int32_t NetClient::HandleConnect() {
    this->PushObjMgr();

    this->m_netState = NS_CONNECTED;

    this->PopObjMgr();

    return 1;
}

int32_t NetClient::HandleData(uint32_t timeReceived, void* data, int32_t size) {
    this->PushObjMgr();

    NetClient::s_stats.bytesReceived += size + 2;

    if (this->m_netState == NS_CONNECTED) {
        CDataStore msg;
        msg.m_data = static_cast<uint8_t*>(data);
        msg.m_size = size;
        msg.m_alloc = -1;
        msg.m_read = 0;

        this->ProcessMessage(timeReceived, &msg, 0);
    }

    this->PopObjMgr();

    return 1;
}

int32_t NetClient::HandleDisconnect() {
    this->PushObjMgr();

    STORM_ASSERT(this->m_netState == NS_CONNECTED || this->m_netState == NS_DISCONNECTING);

    this->m_netState = NS_INITIALIZED;
    ConsolePrintf("NetClient::HandleDisconnect()");
    CGlueMgr::NetDisconnectHandler(this, nullptr);

    this->PopObjMgr();
    return 1;
}

void NetClient::HandleIdle() {
    s_stats.unk1 = s_stats.bytesSent;
    s_stats.unk2 = s_stats.bytesReceived;
    s_stats.unk3 = s_stats.messagesSent;
    s_stats.unk4 = s_stats.messagesReceived;

    if (OsGetAsyncTimeMsPrecise() - this->m_pingSent >= 30000) {
        this->Ping();
    }
}

int32_t NetClient::Initialize() {
    STORM_ASSERT(this->m_netState == NS_UNINITIALIZED);

    if (NetClient::s_clientCount == 0) {
        s_propContext = PropGetSelectedContext();

        if (!WowConnection::InitOsNet(nullptr, InitializePropContext, 1, false)) {
            return 0;
        }
    }

    NetClient::s_clientCount++;

    auto queueMem = SMemAlloc(sizeof(NETEVENTQUEUE), __FILE__, __LINE__, 0x0);
    auto queue = new (queueMem) NETEVENTQUEUE(this);
    this->m_netEventQueue = queue;

    memset(this->m_handlers, 0, sizeof(this->m_handlers));
    memset(this->m_handlerParams, 0, sizeof(this->m_handlerParams));

    auto connectionMem = SMemAlloc(sizeof(WowConnection), __FILE__, __LINE__, 0x0);
    auto connection = new (connectionMem) WowConnection(this, nullptr);
    this->m_serverConnection = connection;

    this->m_netState = NS_INITIALIZED;

    return 1;
}

void NetClient::Destroy() {
    if (this->m_netState == NS_UNINITIALIZED) {
        return;
    }

    this->Disconnect();

    this->m_serverConnection->SetResponse(nullptr, false);
    this->m_serverConnection->Release();
    this->m_serverConnection = nullptr;

    memset(this->m_handlers, 0, sizeof(this->m_handlers));
    memset(this->m_handlerParams, 0, sizeof(this->m_handlerParams));

    if (this->m_netEventQueue) {
        DEL(this->m_netEventQueue);
    }
    this->m_netEventQueue = nullptr;

    if (--NetClient::s_clientCount == 0) {
        OsSleep(1);
        // TODO: WowConnection::DestroyOsNet();
    }

    this->m_netState = NS_UNINITIALIZED;

    if (NetClient::s_clientCount == 0) {
        NetClient::LogStats();
    }
}

void NetClient::PollEventQueue() {
    this->m_netEventQueue->Poll();
}

void NetClient::PongHandler(WowConnection* conn, CDataStore* msg) {
    if (conn != this->m_serverConnection || this->m_suspended) {
        conn->Disconnect();
        return;
    }

    this->m_pingLock.Enter();

    uint32_t sequence;
    msg->Get(sequence);

    if (sequence == this->m_pingSequence) {
        this->m_latency[this->m_latencyEnd++] = OsGetAsyncTimeMsPrecise() - this->m_pingSent;

        if (this->m_latencyEnd >= 16) {
            this->m_latencyEnd = 0;
        }

        if (this->m_latencyEnd == this->m_latencyStart) {
            ++this->m_latencyStart;
            if (this->m_latencyStart >= 16)
                this->m_latencyStart = 0;
        }
    } else {
        ConsolePrintf("Received pong with old sequence");
    }
    this->m_pingLock.Leave();
}

void NetClient::ProcessMessage(uint32_t timeReceived, CDataStore* msg, int32_t a4) {
    ++NetClient::s_stats.messagesReceived;

    uint16_t msgId;
    msg->Get(msgId);

    this->ValidateMessageId(msgId);

    if (msgId >= NUM_MSG_TYPES || !this->m_handlers[msgId]) {
        msg->Reset();
        return;
    }

    this->m_handlers[msgId](
        this->m_handlerParams[msgId],
        static_cast<NETMESSAGE>(msgId),
        timeReceived,
        msg
    );
}

void NetClient::Send(CDataStore* msg) {
    if (this->m_netState != NS_CONNECTED) {
        return;
    }

    auto v4 = msg->m_size - msg->m_read;

    if (!v4) {
        return;
    }

    if (this->m_suspended) {
        // TODO
    } else {
        this->m_serverConnection->Send(msg, 0);

        // TODO

        this->m_bytesSent += v4;

        if (!this->m_serverConnection->m_encrypt) {
            this->EnableEncryption(this->m_serverConnection, nullptr, 0);
        }
    }
}

void NetClient::SetDelete() {
    this->m_deleteMe = true;
}

void NetClient::SetLoginData(LoginData* loginData) {
    memcpy(&this->m_loginData, loginData, sizeof(this->m_loginData));
}

void NetClient::DisplayNetworkStats() {
    this->m_pingLock.Enter();
    OsGetAsyncTimeMs();

    float bandwidthIn;
    float bandwidthOut;
    uint32_t latency;
    this->GetNetStats(bandwidthIn, bandwidthOut, latency);

    this->m_pingLock.Leave();
}

void NetClient::GetNetStats(float& bandwidthIn, float& bandwidthOut, uint32_t& latency) {
    this->m_pingLock.Enter();

    double v5 = (double)(OsGetAsyncTimeMs() - this->m_connectedTimestamp) * 0.001;
    bandwidthIn = (double)this->m_bytesReceived * 0.0009765625 / v5;
    bandwidthOut = (double)this->m_bytesSent * 0.0009765625 / v5;

    uint32_t latencyStart = this->m_latencyStart;
    uint32_t latencyEnd = this->m_latencyEnd;

    uint32_t v6 = 0;
    uint32_t v9 = 0;

    while (latencyStart != latencyEnd) {
        if (latencyStart >= 16) {
            latencyStart = 0;
            if (!latencyEnd)
                break;
        }
        v9 += this->m_latency[latencyStart];
        ++v6;
        ++latencyStart;
    } ;

    if (!v6) {
        latency = 0;
    } else {
        latency = v9 / v6;
    }

    this->m_pingLock.Leave();
}

void NetClient::PushObjMgr() {
    // TODO
}

void NetClient::PopObjMgr() {
    // TODO
}

void NetClient::SetMessageHandler(NETMESSAGE msgId, MESSAGE_HANDLER handler, void* param) {
    this->m_handlers[msgId] = handler;
    this->m_handlerParams[msgId] = param;
}

void NetClient::ClearMessageHandler(NETMESSAGE msgId) {
    this->m_handlers[msgId] = nullptr;
    this->m_handlerParams[msgId] = nullptr;
}

void NetClient::WCCantConnect(WowConnection* conn, uint32_t timeStamp, NETCONNADDR* addr) {
    if (conn == this->m_redirectConnection) {
        // TODO
    } else if (conn == this->m_serverConnection) {
        this->m_netEventQueue->AddEvent(EVENT_ID_NET_CANTCONNECT, conn, this, nullptr, 0);
    }
}

void NetClient::WCConnected(WowConnection* conn, WowConnection* inbound, uint32_t timeStamp, const NETCONNADDR* addr) {
    if (conn != this->m_serverConnection) {
        return;
    }

    this->m_pingLock.Enter();

    this->m_connectedTimestamp = timeStamp;
    this->m_bytesReceived = 0;
    this->m_bytesSent = 0;
    this->m_latencyStart = 0;
    this->m_latencyEnd = 0;
    this->m_pingSent = OsGetAsyncTimeMsPrecise();

    this->m_pingLock.Leave();

    this->m_netEventQueue->AddEvent(EVENT_ID_NET_CONNECT, conn, this, nullptr, 0);
}

void NetClient::WCDisconnected(WowConnection* conn, uint32_t timeStamp, NETCONNADDR* addr) {
    this->DisplayNetworkStats();
    if (this->m_netEventQueue) {
        this->m_netEventQueue->AddEvent(EVENT_ID_NET_DISCONNECT, conn, this, nullptr, 0);
    }
}

void NetClient::WCMessageReady(WowConnection* conn, uint32_t timeStamp, CDataStore* msg) {
    uint8_t* data;
    msg->GetDataInSitu(reinterpret_cast<void*&>(data), msg->m_size);

    // TODO increment byte counter
    // SInterlockedExchangeAdd(this->m_bytesReceived, msg->m_size);

    msg->m_read = 0;

    uint16_t msgId;
    msg->Get(msgId);

    // TODO SMSG_SUSPEND_COMMS (0x50F)
    // TODO SMSG_FORCE_SEND_QUEUED_PACKETS (0x511)
    // TODO SMSG_REDIRECT_CLIENT (0x50D)

    if (msgId == SMSG_PONG) {
        this->PongHandler(conn, msg);
        return;
    } else if (msgId == SMSG_AUTH_CHALLENGE) {
        this->AuthChallengeHandler(conn, msg);
        return;
    }

    if (conn == this->m_serverConnection && !this->m_suspended) {
        msg->m_read = msg->m_size;
        this->m_netEventQueue->AddEvent(EVENT_ID_NET_DATA, conn, this, data, msg->m_size);
    } else {
        conn->Disconnect();
    }
}
