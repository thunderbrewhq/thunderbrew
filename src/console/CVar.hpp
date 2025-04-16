#ifndef CONSOLE_CVAR_HPP
#define CONSOLE_CVAR_HPP

#include <bc/os/File.hpp>
#include <common/String.hpp>
#include <cstdint>
#include <storm/Hash.hpp>

#define CONSOLE_CVAR_MAX_LINE 2048

class CVar : public TSHashObject<CVar, HASHKEY_STRI> {
    public:
        typedef bool (*ITERATE_FUNC)(const char*, const char*, void*);
        typedef bool (*HANDLER_FUNC)(CVar*, const char*, const char*, void*);

        // Static variables
        static TSHashTable<CVar, HASHKEY_STRI> s_registeredCVars;
        static bool m_needsSave;
        static bool m_initialized;

        // Static functions
        static CVar* Lookup(const char* name);
        static CVar* LookupRegistered(const char* name);
        static CVar* Register(const char* name, const char* help, uint32_t flags, const char* value, HANDLER_FUNC fcn, uint32_t category, bool a7, void* arg, bool a9);
        static void Initialize(const char* filename);
        static int32_t IterateForArchive(uint32_t a1, uint32_t a2, ITERATE_FUNC cb, void* param);
        static void Destroy();
        static int32_t Load(const char* filename);
        static int32_t Load(HOSFILE fileHandle);
        static bool SaveCvar(const char* key, const char* value, void* param);
        // Member variables
        uint32_t m_category = 0;
        uint32_t m_flags    = 0;
        RCString m_stringValue;
        float m_floatValue = 0.0;
        int32_t m_intValue = 0;
        int32_t m_modified = 0;
        RCString m_defaultValue;
        RCString m_resetValue;
        RCString m_latchedValue;
        RCString m_help;
        bool (*m_callback)(CVar*, const char*, const char*, void*) = nullptr;
        void* m_arg                                                = nullptr;

        // Member functions
        CVar();
        int32_t GetInt();
        const char* GetString(void);
        void InternalSet(const char*, bool, bool, bool, bool);
        bool Set(const char*, bool, bool, bool, bool);
        void SetReadOnly(bool readonly);
        bool Reset();
        bool Default();
        int32_t Update();
};

int32_t SetCommandHandler(const char* command, const char* arguments);
int32_t CvarResetCommandHandler(const char* command, const char* arguments);
int32_t CvarDefaultCommandHandler(const char* command, const char* arguments);
int32_t CvarListCommandHandler(const char* command, const char* arguments);
int32_t CvarCommandHandler(const char* command, const char* arguments);

#endif
