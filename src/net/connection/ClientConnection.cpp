#include "net/connection/ClientConnection.hpp"
#include "net/Login.hpp"
#include "client/ClientServices.hpp"
#include "ui/FrameScript.hpp"
#include <storm/Error.hpp>
#include <common/DataStore.hpp>


void ClientConnection::AccountLogin(const char* name, const char* password, int32_t region, int32_t locale) {
    STORM_ASSERT(this->m_statusComplete == 1);
    STORM_ASSERT(name);
    STORM_ASSERT(password);
    this->Initiate(COP_AUTHENTICATE, 11, nullptr);
}

void ClientConnection::AccountLogin_Finish(int32_t errorCode) {
    this->Complete(errorCode == 12, errorCode);
}

void ClientConnection::AccountLogin_Queued() {
    this->m_statusCop = COP_WAIT_QUEUE;
    this->m_errorCode = 27;
    this->m_statusComplete = 0;

    // TODO LogConnectionStatus(this->m_statusCop, 27, 1);

    // TODO CGlueMgr::UpdateWaitQueue(this->m_queuePosition);
}

void ClientConnection::GetCharacterList() {
    this->Initiate(COP_GET_CHARACTERS, 43, nullptr);
    if (this->m_connected) {
        this->RequestCharacterEnum();
    } else {
        this->Cancel(4);
    }
}

void ClientConnection::EnumerateCharacters(ENUMERATE_CHARACTERS_CALLBACK fcn, void* param) {
    STORM_ASSERT(fcn);
    for (uint32_t i = 0; i < this->m_characterList.Count(); ++i) {
        fcn(this->m_characterList[i], param);
    }
}

void ClientConnection::CharacterLogin(uint64_t id) {
    this->Initiate(COP_LOGIN_CHARACTER, 76, nullptr);
    if (this->m_connected) {
        this->RequestCharacterLogin(id);
    } else {
        this->Cancel(4);
    }
}

void ClientConnection::DeleteCharacter(uint64_t guid) {
    this->Initiate(COP_DELETE_CHARACTER, 70, nullptr);
    if (this->m_connected) {
        CDataStore msg;
        msg.Put(static_cast<uint32_t>(CMSG_CHAR_DELETE));
        msg.Put(guid);
        msg.Finalize();
        this->Send(&msg);
    } else {
        this->Cancel(4);
    }
}

void ClientConnection::Cancel(int32_t errorCode) {
    this->Complete(0, errorCode);
}

void ClientConnection::Cleanup() {
    if (this->m_cleanup) {
        this->m_cleanup();
        this->m_cleanup = nullptr;
    }
}

void ClientConnection::Complete(int32_t result, int32_t errorCode) {
    this->Cleanup();

    this->m_statusResult = result;
    this->m_errorCode = errorCode;
    this->m_statusComplete = 1;

    // TODO LogConnectionStatus(this->m_statusCop, errorCode, 0);
}

void ClientConnection::Connect() {
    // TODO

    this->m_cleanup = nullptr;
    this->m_statusCop = COP_CONNECT;
    this->m_errorCode = 7;
    this->m_statusComplete = 0;

    // TODO

    ClientServices::LoginConnection()->GetRealmList();
}

int32_t ClientConnection::Disconnect() {
    // TODO
    return 0;
}

int32_t ClientConnection::HandleConnect() {
    this->Complete(1, 5);

    this->m_connected = 1;

    // TODO WardenClient_Initialize();

    return this->NetClient::HandleConnect();
}

void ClientConnection::Initiate(WOWCS_OPS op, int32_t errorCode, void (*cleanup)()) {
    this->m_cleanup = cleanup;
    this->m_statusCop = op;
    this->m_errorCode = errorCode;
    this->m_statusComplete = 0;

    // TODO LogConnectionStatus(this->m_statusCop, errorCode, 1);
}

int32_t ClientConnection::IsConnected() {
    return this->m_connected;
}

int32_t ClientConnection::PollStatus(WOWCS_OPS& op, const char** msg, int32_t& result, int32_t& errorCode) {
    op = this->m_statusCop;
    errorCode = this->m_errorCode;
    result = this->m_statusResult;

    static char altText[256];

    if (this->m_statusComplete) {
        auto errorText = ClientServices::GetErrorToken(errorCode);
        
        auto text = errorText[0]
            ? FrameScript_GetText(errorText, -1, GENDER_NOT_APPLICABLE)
            : nullptr;

        if (!text) {
            SStrPrintf(altText, sizeof(altText), "(%i)", errorCode);
            *msg = altText;
        } else if (errorCode == 27) {
            // TODO
            *msg = "TODO";
        } else {
            *msg = text;
        }

        return this->m_statusComplete;
    }

    *msg = "";

    return this->m_statusComplete;
}
