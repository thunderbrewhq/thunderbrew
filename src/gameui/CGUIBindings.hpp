#ifndef GAME_UI_CGUIBINDINGS_HPP
#define GAME_UI_CGUIBINDINGS_HPP

#include <storm/Hash.hpp>
#include <common/MD5.hpp>
#include <common/String.hpp>

class CStatus;
class XMLNode;

enum BINDING_SET {
    BINDING_DEFAULT = 0,
    BINDING_SET_1,
    BINDING_SET_2,
    BINDING_SCRIPT,
};

enum BINDING_MODE {
    BINDING_MODE_0 = 0,
    BINDING_MODE_1,
    BINDING_MODE_2,
    BINDING_MODE_3,
    BINDING_MODE_4
};

class KEYBINDING : public TSHashObject<KEYBINDING, HASHKEY_STRI> {
    public:
    uint32_t flags;
    struct {
        int32_t index;
        RCString command;
    } data[4];
};

class KEYCOMMAND : public TSHashObject<KEYCOMMAND, HASHKEY_STRI> {
    public:
    int32_t index;
    int32_t function;
    int32_t runOnUp;
    int32_t pressure;
    int32_t angle;
};

class MODIFIEDCLICK : public TSHashObject<MODIFIEDCLICK, HASHKEY_STRI> {
    public:
    void SetBinding(BINDING_SET set, const char* binding);

    int32_t index;
};

class CGUIBindings {
    public:
    static CGUIBindings* s_bindings;

    static void Initialize();
    static void LoadBindings();
    static void LoadBindings(BINDING_SET set, const char* buffer);


    CGUIBindings() = default;

    bool Load(const char* commandsFile, MD5_CTX* md5, CStatus* status);
    void LoadBinding(const char* commandsFile, XMLNode* node, CStatus* status);
    void LoadModifiedClick(const char* commandsFile, XMLNode* node, CStatus* status);
    bool Bind(BINDING_SET set, BINDING_MODE mode, const char* keystring, const char* command);
    const char* GetBindingCommand(KEYBINDING* binding, BINDING_MODE mode) const;
    int32_t GetBindingIndex(KEYBINDING* binding, BINDING_MODE mode) const;
    int32_t GetNumCommandKeys(BINDING_SET set, BINDING_MODE mode, const char* command);
    void AdjustCommandKeyIndices(BINDING_SET set, BINDING_MODE mode, const char* command, int32_t index);

    int32_t m_numCommands;
    int32_t m_numHiddenCommands;
    int32_t m_numModifiedClicks;
    TSHashTable<KEYBINDING, HASHKEY_STRI> m_bindings[4];
    TSHashTable<KEYCOMMAND, HASHKEY_STRI> m_commands;
    TSHashTable<MODIFIEDCLICK, HASHKEY_STRI> m_modifiedClicks;
};

#endif // GAME_UI_CGUIBINDINGS_HPP
