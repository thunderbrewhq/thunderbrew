#include "console/CVar.hpp"
#include "console/Types.hpp"
#include "console/Console.hpp"
#include "util/SFile.hpp"

#include <bc/os/File.hpp>
#include <storm/String.hpp>

const char* s_filename = nullptr;
bool CVar::m_needsSave;
TSHashTable<CVar, HASHKEY_STRI> CVar::s_registeredCVars;

CVar* CVar::Lookup(const char* name) {
    return name
        ? CVar::s_registeredCVars.Ptr(name)
        : nullptr;
}

CVar* CVar::LookupRegistered(const char* name) {
    if (!name) {
        return nullptr;
    }
    auto cv = s_registeredCVars.Ptr(name);
    if (!cv) {
        return nullptr;
    }
    if (cv->m_flags & 0x80000000) {
        return cv;
    }
    if (cv->m_flags & 0x80) {
        return cv;
    }
    return nullptr;
}

CVar* CVar::Register(const char* name, const char* help, uint32_t flags, const char* value, HANDLER_FUNC fcn, uint32_t category, bool a7, void* arg, bool a9) {
    auto cv = s_registeredCVars.Ptr(name);

    if (cv) {
        bool setReset = cv->m_resetValue.GetString() == nullptr;
        bool setDefault = cv->m_defaultValue.GetString() == nullptr;

        cv->m_flags |= (cv->m_flags & 0xFFFFFFCF);

        cv->m_callback = fcn;
        cv->m_arg = arg;

        bool setValue = false;
        if (fcn && !fcn(cv, cv->GetString(), cv->GetString(), arg)) {
            setValue = true;
        }

        cv->Set(value, setValue, setReset, setDefault, false);

        if (!a7) {
            cv->m_flags |= 0x80000000;
        }

        if (a9 && cv->m_flags) {
            cv->m_flags |= 0x80;
        }
    } else {
        cv = s_registeredCVars.New(name, 0, 0);

        cv->m_stringValue.Copy(nullptr);
        cv->m_floatValue = 0.0f;
        cv->m_intValue = 0;
        cv->m_modified = 0;
        cv->m_category = category;
        cv->m_defaultValue.Copy(nullptr);
        cv->m_resetValue.Copy(nullptr);
        cv->m_latchedValue.Copy(nullptr);
        cv->m_callback = fcn;
        cv->m_flags = 0;
        cv->m_arg = arg;
        cv->m_help.Copy(help);

        if (a7) {
            cv->Set(value, true, true, false, false);
        } else {
            cv->Set(value, true, false, true, false);
        }

        cv->m_flags = flags | 0x1;

        if (!a7) {
            cv->m_flags |= 0x8000000;
        }

        if (a9 && cv->m_flags) {
            cv->m_flags |= 0x80;
        }

        ConsoleCommandRegister(name, CvarCommandHandler, CATEGORY(category), help);
    }

    return cv;
}

CVar::CVar() : TSHashObject<CVar, HASHKEY_STRI>() {
    // TODO
}

int32_t CVar::GetInt() {
    return this->m_intValue;
}

const char* CVar::GetString() {
    return this->m_stringValue.GetString();
}

void CVar::InternalSet(const char* value, bool setValue, bool setReset, bool setDefault, bool a6) {
    if (this->m_flags & 0x4 || !value) {
        return;
    }

    bool modified = false;

    const char* existingValue = this->m_stringValue.GetString();

    if (setValue && (!existingValue || SStrCmpI(value, existingValue, 0x7FFFFFFF))) {
        modified = true;

        this->m_stringValue.Copy(value);
        this->m_intValue = SStrToInt(value);
        this->m_floatValue = SStrToFloat(value);
    }

    if (setReset && !this->m_resetValue.GetString()) {
        modified = true;

        this->m_resetValue.Copy(value);
    }

    if (setDefault && !this->m_defaultValue.GetString()) {
        this->m_defaultValue.Copy(value);
    } else if (!modified) {
        return;
    }

    if (a6) {
        CVar::m_needsSave = 1;
    }
}

bool CVar::Set(const char* value, bool setValue, bool setReset, bool setDefault, bool a6) {
    if (setValue) {
        if (this->m_callback) {
            // TODO
            // sub_86B5A0(this->m_callback);

            if (!this->m_callback(this, this->m_stringValue.GetString(), value, this->m_arg)) {
                return true;
            }
        }

        this->m_modified++;

        if (this->m_flags & 0x2) {
            this->m_latchedValue.Copy(value);
            CVar::m_needsSave = 1;

            return true;
        }
    }

    this->InternalSet(value, setValue, setReset, setDefault, a6);

    return true;
}

void CVar::SetReadOnly(bool readonly) {
    if (readonly) {
        this->m_flags |= 0x4;
    } else {
        this->m_flags &= ~(0x4);
    }
}

bool CVar::Reset() {
    auto value = this->m_resetValue;
    if (value.GetString() == nullptr) {
        value = this->m_defaultValue;
    }

    this->InternalSet(value.GetString(), true, false, false, true);
    return true;
}

bool CVar::Default() {
    auto value = this->m_defaultValue;
    if (value.GetString() == nullptr) {
        value = this->m_resetValue;
    }

    this->InternalSet(value.GetString(), true, false, false, true);
    return true;
}

int32_t CVar::Update() {
    if (!(this->m_flags & 0x2)) {
        return 0;
    }

    if (!this->m_latchedValue.GetString()) {
        return 0;
    }

    this->InternalSet(this->m_latchedValue.GetString(), true, false, false, true);
    this->m_latchedValue.Copy(nullptr);

    return 1;
}

static int32_t s_CreatePathDirectories(const char* szPath) {
    return true == OsCreateDirectory(szPath, 1);
}

int32_t CVar::Load(HOSFILE file) {
    char fastData[CONSOLE_CVAR_MAX_LINE];
    char line[CONSOLE_CVAR_MAX_LINE];
    uint32_t bytesRead;

    auto size = OsGetFileSize(file);
    auto data = size >= CONSOLE_CVAR_MAX_LINE ? reinterpret_cast<char*>(ALLOC(size + 1)) : fastData;
    if (!OsReadFile(file, data, size, &bytesRead)) {
        if (fastData != data) {
            FREE(data);
        }
        return 0;
    }

    const char* curr = data;

    data[size] = '\0';
    // Skip over UTF-8 byte order mark
    if (data && bytesRead >= 3) {
        if (data[0] == '\xEF' && data[1] == '\xBB' && data[2] == '\xBF') {
            curr += 3;
        }
    }

    do {
        SStrTokenize(&curr, line, CONSOLE_CVAR_MAX_LINE, "\r\n", 0);

        // Do not execute commands other than "set ..."
        if (SStrCmpI(line, "SET ", 4) == 0) {
            // Execute without adding to history
            ConsoleCommandExecute(line, 0);
        }
    } while (curr && *curr);

    if (fastData != data) {
        FREE(data);
    }

    return 1;
}

int32_t CVar::Load(const char* filename) {
    char path[STORM_MAX_PATH] = {0};

    auto file = OsCreateFile(filename, OS_GENERIC_READ, 0, OS_OPEN_EXISTING, OS_FILE_ATTRIBUTE_NORMAL, 0x3f3f3f3f);

    if (file == HOSFILE_INVALID) {
        SStrPrintf(path, STORM_MAX_PATH, "WTF\\%s", filename);
        file = OsCreateFile(path, OS_GENERIC_READ, 0, OS_OPEN_EXISTING, OS_FILE_ATTRIBUTE_NORMAL, 0x3f3f3f3f);
        if (file == HOSFILE_INVALID) {
            return 0;
        }
    }

    auto result = CVar::Load(file);

    OsCloseFile(file);

    return result;
}

void CVar::Initialize(const char* filename) {
    STORM_ASSERT(filename);
    s_filename = filename;

    // Get data path
    char path[STORM_MAX_PATH] = {0};
    SFile::GetBasePath(path, STORM_MAX_PATH);
    SStrPrintf(path, STORM_MAX_PATH, "%s%s\\", path, "WTF");

    s_CreatePathDirectories(path);

    ConsoleCommandRegister("set",          SetCommandHandler,         DEFAULT, "Set the value of a CVar");
    ConsoleCommandRegister("cvar_reset",   CvarResetCommandHandler,   DEFAULT, "Set the value of a CVar to it's startup value");
    ConsoleCommandRegister("cvar_default", CvarDefaultCommandHandler, DEFAULT, "Set the value of a CVar to it's coded default value");
    ConsoleCommandRegister("cvarlist",     CvarListCommandHandler,    DEFAULT, "List cvars");

    CVar::Load(s_filename);
}

int32_t CvarResetCommandHandler(const char* command, const char* arguments) {
    char cvarName[256] = {0};
    auto string        = arguments;

    SStrTokenize(&string, cvarName, sizeof(cvarName), " ,;\t\"\r\n", nullptr);

    if (*cvarName) {
        // reset a specific cvar
        auto cvar = CVar::Lookup(cvarName);
        if (cvar) {
            cvar->Reset();
        } else {
            ConsoleWriteA("No such cvar \"%s\"\n", ERROR_COLOR, cvarName);
        }

        return 1;
    } else {
        // reset all cvars
        ConsoleWrite("Resetting all cvars\n", DEFAULT_COLOR);

        for (auto cvar = CVar::s_registeredCVars.Head(); cvar != nullptr; cvar = CVar::s_registeredCVars.Next(cvar)) {
            cvar->Reset();
        }

        return 1;
    }
}

int32_t CvarDefaultCommandHandler(const char* command, const char* arguments) {
    char cvarName[256] = {0};
    auto string        = arguments;

    SStrTokenize(&string, cvarName, sizeof(cvarName), " ,;\t\"\r\n", nullptr);

    if (*cvarName) {
        // restore a specific cvar
        auto cvar = CVar::Lookup(cvarName);
        if (cvar) {
            cvar->Default();
        } else {
            ConsoleWriteA("No such cvar \"%s\"\n", ERROR_COLOR, cvarName);
        }

        return 1;
    } else {
        // restore all cvars
        ConsoleWrite("Restoring all cvars\n", DEFAULT_COLOR);

        for (auto cvar = CVar::s_registeredCVars.Head(); cvar != nullptr; cvar = CVar::s_registeredCVars.Next(cvar)) {
            cvar->Default();
        }

        return 1;
    }
}

int32_t CvarCommandHandler(const char* command, const char* arguments) {
    auto cvar = CVar::Lookup(command);
    STORM_ASSERT(cvar);

    while (*arguments == ' ') {
        arguments++;
    }

    if (arguments[0] != '\0') {
        cvar->Set(arguments, true, true, false, false);
        return 1;
    }

    auto value = cvar->m_stringValue.GetString();

    ConsoleWriteA("CVar \"%s\" is \"%s\"", DEFAULT_COLOR, command, value ? value : "");
    return 1;
}

int32_t SetCommandHandler(const char* command, const char* arguments) {
    char cvarValue[2048] = {0};
    char cvarName[256]   = {0};

    auto str = arguments;

    SStrTokenize(&str, cvarName, sizeof(cvarName), " ,;\t\"\r\n", nullptr);
    SStrTokenize(&str, cvarValue, sizeof(cvarValue), " ,;\t\"\r\n", nullptr);

    auto cvar = CVar::s_registeredCVars.Ptr(cvarName);

    if (!cvar) {
        CVar::Register(cvarName, "", 0, cvarValue, nullptr, DEFAULT, true, nullptr, false);
        return 1;
    }

    if (cvar->m_callback) {
        // FUN_0086b5a0(cv->m_callback);
        if (!cvar->m_callback(cvar, cvar->GetString(), cvarValue, cvar->m_arg)) {
            return 1;
        }
    }

    cvar->m_modified++;
    if (!(cvar->m_flags & 0x2)) {
        cvar->m_latchedValue.Copy(cvarValue);
        CVar::m_needsSave = true;
    } else if (!(cvar->m_flags & 0x4)) {
        if (cvar->GetString() && !SStrCmpI(cvarValue, cvar->GetString(), STORM_MAX_STR)) {
            return 1;
        }

        cvar->m_stringValue.Copy(cvarValue);
        cvar->m_intValue = SStrToInt(cvarValue);
        cvar->m_floatValue = SStrToFloat(cvarValue);
        CVar::m_needsSave = true;
    }

    return 1;
}

int32_t CvarListCommandHandler(const char* command, const char* arguments) {
    char text[256];
    char text2[256];

    for (auto cvar = CVar::s_registeredCVars.Head(); cvar != nullptr; cvar = CVar::s_registeredCVars.Next(cvar)) {
        SStrPrintf(text, sizeof(text), "  \"%s\" is \"%s\"", cvar->m_key.m_str, cvar->m_stringValue.GetString());

        if (cvar->m_defaultValue.GetString()) {
            if (SStrCmp(cvar->m_stringValue.GetString(), cvar->m_defaultValue.GetString(), STORM_MAX_STR)) {
                SStrPrintf(text2, sizeof(text2), " (default \"%s\")", cvar->m_defaultValue.GetString());
                SStrPack(text, text2, sizeof(text));
            }
        }

        if (cvar->m_resetValue.GetString()) {
            if (SStrCmp(cvar->m_stringValue.GetString(), cvar->m_resetValue.GetString(), STORM_MAX_STR)) {
                SStrPrintf(text2, sizeof(text2), " (reset \"%s\")", cvar->m_resetValue.GetString());
                SStrPack(text, text2, sizeof(text));
            }
        }

        ConsoleWrite(text, DEFAULT_COLOR);
    }

    return 1;
}
