#include "client/ClientRealmResponseAdapter.hpp"

void AccountDataInitialize(bool a1) {
    // TODO
}

void ClientRealmResponseAdapter::HandleAuthResponse(RealmConnection* realmConnection, uint8_t authResult) {
    auto clientConnection = static_cast<ClientConnection*>(realmConnection);

    // AUTH_WAIT_QUEUE
    if (authResult == 27) {
        clientConnection->AccountLogin_Queued();
    } else {
        clientConnection->AccountLogin_Finish(authResult);
    }

    AccountDataInitialize(true);
}

void ClientRealmResponseAdapter::CharacterListReceived(RealmConnection* realmConnection, void* a2, int32_t success) {
    auto clientConnection = static_cast<ClientConnection*>(realmConnection);

    if (success) {
        clientConnection->Complete(1, 44);
    } else {
        clientConnection->Complete(1, 45);
    }
}
