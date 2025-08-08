#ifndef GAME_UI_CGUIBINDINGS_HPP
#define GAME_UI_CGUIBINDINGS_HPP

#include <storm/Hash.hpp>
#include <common/MD5.hpp>

class CStatus;
class XMLNode;

class KEYBINDING : public TSHashObject<KEYBINDING, HASHKEY_STRI> {
    public:
    int32_t index;
    char* command;
};

class KEYCOMMAND : public TSHashObject<KEYCOMMAND, HASHKEY_STRI> {
    public:
    int32_t index;
    int32_t function;
    int32_t runOnUp;
    int32_t pressure;
    int32_t angle;
};

class CGUIBindings {
    public:
    CGUIBindings() = default;

    bool Load(const char* commandsFile, MD5_CTX* md5, CStatus* status);
    void LoadBinding(const char* commandsFile, XMLNode* node, CStatus* status);
    void LoadModifiedClick(const char* commandsFile, XMLNode* node, CStatus* status);

    int32_t m_numCommands;
    int32_t m_numHiddenCommands;
    TSHashTable<KEYBINDING, HASHKEY_STRI> m_bindings;
    TSHashTable<KEYCOMMAND, HASHKEY_STRI> m_commands;
};

#endif // GAME_UI_CGUIBINDINGS_HPP
