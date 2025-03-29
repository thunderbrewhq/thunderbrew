#ifndef CONSOLE_C_VAR_HPP
#define CONSOLE_C_VAR_HPP

#include <cstdint>
#include <common/String.hpp>
#include <storm/Hash.hpp>
#include <bc/os/File.hpp>

#include "console/Types.hpp"

class CVar : public TSHashObject<CVar, HASHKEY_STRI> {
    public:
        // Static variables
        static TSHashTable<CVar, HASHKEY_STRI> s_registeredCVars;
        static bool m_needsSave;

        // Static functions
        static CVar* Lookup(const char* name);
        static CVar* Register(
            const char* name,
            const char* help,
            uint32_t flags,
            const char* value,
            bool (*fcn)(CVar*, const char*, const char*, void*) = nullptr,
            uint32_t category = CATEGORY::DEFAULT,
            bool setCommand = false,
            void* arg = nullptr,
            bool a9 = false
        );
        static void  Initialize(const char* filename);
        static int32_t Load(const char* filename);
        static int32_t Load(HOSFILE fileHandle);
        // Member variables
        uint32_t m_category = 0;
        uint32_t m_flags = 0;
        RCString m_stringValue;
        float m_floatValue = 0.0;
        int32_t m_intValue = 0;
        int32_t m_modified = 0;
        RCString m_defaultValue;
        RCString m_resetValue;
        RCString m_latchedValue;
        RCString m_help;
        bool (*m_callback)(CVar*, const char*, const char*, void*) = nullptr;
        void* m_arg = nullptr;

        // Member functions
        CVar();
        int32_t GetInt();
        const char* GetString(void);
        void InternalSet(const char*, bool, bool, bool, bool);
        bool Set(const char* value, bool setValue, bool setReset, bool setDefault, bool a6);
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
