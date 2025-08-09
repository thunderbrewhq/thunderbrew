#include "gameui/CGUIBindings.hpp"
#include "gameui/CGGameUI.hpp"
#include "ui/FrameScript.hpp"
#include "util/CStatus.hpp"
#include "util/SFile.hpp"
#include "util/StringTo.hpp"

#include <common/XML.hpp>
#include <common/Unicode.hpp>
#include <bc/Memory.hpp>
#include <utility>


static CStatus s_nullStatus;
static uint16_t s_initRound = 0;

CGUIBindings* CGUIBindings::s_bindings = nullptr;


static bool ValidateKeyString(const char* key) {
    static std::pair<const char*, size_t> s_prefixes[3] = {
        { "SHIFT-", 6 },
        { "CTRL-", 5 },
        { "ALT-", 4 }
    };
    static std::pair<const char*, size_t> s_numberedKeys[6] = {
        { "F", 1 },
        { "NUMPAD", 6 },
        { "BUTTON", 6 },
        { "JOYSTICK", 8 },
        { "JOYAXIS", 7 },
        { "JOYBUTTON", 9 },
    };

    static const char* s_namedKeys[31] = {
        "SPACE",
        "NUMPADPLUS",
        "NUMPADMINUS",
        "NUMPADMULTIPLY",
        "NUMPADDIVIDE",
        "NUMPADDECIMAL",
        "ESCAPE",
        "ENTER",
        "BACKSPACE",
        "TAB",
        "LEFT",
        "UP",
        "RIGHT",
        "DOWN",
        "INSERT",
        "DELETE",
        "HOME",
        "END",
        "PAGEUP",
        "PAGEDOWN",
        "NUMLOCK",
        "CAPSLOCK",
        "PRINTSCREEN",
        "NUMPADEQUALS",
        "MOUSEWHEELDOWN",
        "MOUSEWHEELUP",
        "JOYHAT",
        "JOYHATUP",
        "JOYHATRIGHT",
        "JOYHATDOWN",
        "JOYHATLEFT"
    };

    for (uint32_t i = 0; i < 3; ++i) {
        if (SStrCmp(s_prefixes[i].first, key, s_prefixes[i].second)) {
            break;
        }

        key += s_prefixes[i].second;
    }

    int32_t chars = 0;
    sgetu8(reinterpret_cast<const uint8_t*>(key), &chars);
    if (!key[chars]) {
        return true;
    }

    uint32_t index;
    for (index = 0; index < 6; ++index) {
        if (!SStrCmp(s_numberedKeys[index].first, key, s_numberedKeys[index].second)) {
            auto ch = key[s_numberedKeys[index].second];
            if (ch >= '0' && ch <= '9') {
                break;
            }
        }
    }

    if (index >= 6) {
        for (uint32_t i = 0; i < 31; ++i) {
            if (!SStrCmp(key, s_namedKeys[i], STORM_MAX_STR)) {
                return true;
            }
        }
        return false;
    }

    const char* tail = &key[s_numberedKeys[index].second];
    while (*tail >= '0' && *tail <= '9') {
        ++tail;
    }

    if (*tail &&
        (SStrCmp(s_numberedKeys[index].first, "JOYAXIS", STORM_MAX_STR)
        || SStrCmp(tail, "POS", STORM_MAX_STR)
        && SStrCmp(tail, "NEG", STORM_MAX_STR))) {
        return false;
    }

    return true;
}

void MODIFIEDCLICK::SetBinding(BINDING_SET a1, const char* binding) {
}


void CGUIBindings::Initialize() {
    CGUIBindings::s_bindings = NEW(CGUIBindings);
    while (!s_initRound) {
        ++s_initRound;
    }
}

bool CGUIBindings::Load(const char* commandsFile, MD5_CTX* md5, CStatus* status) {
    if (!status) {
        status = &s_nullStatus;
    }

    char* buffer = nullptr;
    size_t bytesRead = 0;
    if (!SFile::Load(nullptr, commandsFile, reinterpret_cast<void**>(&buffer), &bytesRead, 0, 1, nullptr)) {
        status->Add(STATUS_ERROR, "Couldn't open %s", commandsFile);
        return false;
    }

    MD5Update(md5, reinterpret_cast<uint8_t*>(buffer), static_cast<uint32_t>(bytesRead));

    auto tree = XMLTree_Load(buffer, static_cast<uint32_t>(bytesRead));

    SFile::Unload(buffer);

    if (!tree) {
        status->Add(STATUS_ERROR, "Couldn't parse XML in %s", commandsFile);
        return false;
    }

    auto node = XMLTree_GetRoot(tree)->m_child;
    while (node) {
        if (!SStrCmpI(node->GetName(), "Binding", STORM_MAX_STR)) {
            this->LoadBinding(commandsFile, node, status);
        } else if (!SStrCmpI(node->GetName(), "ModifiedClick", STORM_MAX_STR)) {
            this->LoadModifiedClick(commandsFile, node, status);
        } else {
            status->Add(STATUS_WARNING, "Unknown node type %s in %s", node->GetName(), commandsFile);
        }

        node = node->m_next;
    }

    XMLTree_Free(tree);
    return true;
}

void CGUIBindings::LoadBinding(const char* commandsFile, XMLNode* node, CStatus* status) {
    const char* name = node->GetAttributeByName("name");
    if (!name || !*name) {
        status->Add(STATUS_WARNING, "Found binding with no name in %s", commandsFile);
        return;
    }

    const char* debug = node->GetAttributeByName("debug");
#ifndef WHOA_BUILD_ASSERTIONS
    if (StringToBOOL(debug)) {
        return;
    }
#endif

#if defined(WHOA_SYSTEM_WIN)
    const char* thisPlatform = "windows";
#elif defined(WHOA_SYSTEM_MAC)
    const char* thisPlatform = "mac";
#else
    const char* thisPlatform = "linux";
#endif

    const char* platform = node->GetAttributeByName("platform");
    if (platform && SStrCmpI(platform, thisPlatform, STORM_MAX_STR)) {
        return;
    }

    if (this->m_commands.Ptr(name)) {
        status->Add(STATUS_WARNING, "Binding %s is defined more than once in %s", name, commandsFile);
        return;
    }

    const char* header = node->GetAttributeByName("header");
    if (header && *header) {
        char headerBuf[1024];
        SStrPrintf(headerBuf, sizeof(headerBuf), "HEADER_%s", header);
        if (this->m_commands.Ptr(headerBuf)) {
            status->Add(STATUS_WARNING, "Binding header %s is defined more than once in %s", header, commandsFile);
        } else {
            auto headerCommand = this->m_commands.New(headerBuf, 0, 0);
            headerCommand->index = this->m_numCommands++;
            headerCommand->function = -1;
        }
    }

    auto command = this->m_commands.New(name, 0, 0);

    const char* hidden = node->GetAttributeByName("hidden");
    const char* joystick = node->GetAttributeByName("joystick");

    if (StringToBOOL(hidden) || StringToBOOL(joystick) /* && GetJoystick() == -1 */) {
        command->index = -(++this->m_numHiddenCommands);
    } else {
        command->index = this->m_numCommands++;
    }

    const char* script = node->m_body;
    if (script && *script) {
        command->function = FrameScript_CompileFunction(
            name,
            "return function(keystate, pressure, angle, precision) %s end",
            script,
            status);
    } else {
        status->Add(STATUS_WARNING, "Found binding %s with no script in %s", name, commandsFile);
        command->function = -1;
    }

    const char* runOnUp = node->GetAttributeByName("runOnUp");
    command->runOnUp = StringToBOOL(runOnUp);

    const char* pressure = node->GetAttributeByName("pressure");
    command->pressure = StringToBOOL(pressure);

    const char* angle = node->GetAttributeByName("angle");
    command->angle = StringToBOOL(angle);

    const char* binding = node->GetAttributeByName("default");
    if (binding && *binding) {
        if (!this->m_bindings[BINDING_DEFAULT].Ptr(binding)) {
            this->Bind(BINDING_DEFAULT, BINDING_MODE_0, binding, name);
        }
    }
}

void CGUIBindings::LoadModifiedClick(const char* commandsFile, XMLNode* node, CStatus* status) {
    const char* action = node->GetAttributeByName("action");
    if (!action || !*action) {
        status->Add(STATUS_WARNING, "Found modified click with no action in %s", commandsFile);
        return;
    }

    if (this->m_modifiedClicks.Ptr(action)) {
        status->Add(STATUS_WARNING, "Modified click %s is defined more than once in %s", action, commandsFile);
        return;
    }

    auto modifiedClick = this->m_modifiedClicks.New(action, 0, 0);
    this->m_numModifiedClicks++;

    const char* binding = node->GetAttributeByName("default");
    if (binding && *binding) {
        modifiedClick->SetBinding(BINDING_DEFAULT, binding);
    }
}

bool CGUIBindings::Bind(BINDING_SET set, BINDING_MODE mode, const char* keystring, const char* command) {
    if (!CGGameUI::CanPerformAction(13) || !keystring) {
        return false;
    }

    if (!command || !*command) {
        command = "NONE";
    }

    static char s_character[2] = {};

    const char* key = keystring;

    if (!SStrCmpI(keystring, "LEFTBRACKET", STORM_MAX_STR)) {
        s_character[0] = '[';
        key = s_character;
    } else if (!SStrCmpI(keystring, "RIGHTBRACKET", STORM_MAX_STR)) {
        s_character[0] = ']';
        key = s_character;
    } else if (!SStrCmpI(keystring, "SLASH", STORM_MAX_STR)) {
        s_character[0] = '/';
        key = s_character;
    } else if (!SStrCmpI(keystring, "BACKSLASH", STORM_MAX_STR)) {
        s_character[0] = '\\';
        key = s_character;
    } else if (!SStrCmpI(keystring, "SEMICOLON", STORM_MAX_STR)) {
        s_character[0] = ';';
        key = s_character;
    } else if (!SStrCmpI(keystring, "APOSTROPHE", STORM_MAX_STR)) {
        s_character[0] = '\'';
        key = s_character;
    } else if (!SStrCmpI(keystring, "COMMA", STORM_MAX_STR)) {
        s_character[0] = ',';
        key = s_character;
    } else if (!SStrCmpI(keystring, "PERIOD", STORM_MAX_STR)) {
        s_character[0] = '.';
        key = s_character;
    } else if (!SStrCmpI(keystring, "TILDE", STORM_MAX_STR)) {
        s_character[0] = '`';
        key = s_character;
    } else if (!SStrCmpI(keystring, "PLUS", STORM_MAX_STR)) {
        s_character[0] = '=';
        key = s_character;
    } else if (!SStrCmpI(keystring, "MINUS", STORM_MAX_STR)) {
        s_character[0] = '-';
        key = s_character;
    }

    if (!ValidateKeyString(key)) {
        return false;
    }

    auto binding = this->m_bindings[set].Ptr(key);
    if (!binding) {
        binding = this->m_bindings[set].New(key, 0, 0);
    }

    if (set != BINDING_DEFAULT) {
        binding->flags &= ~1u;
    } else {
        binding->flags |= 1u;
    }

    auto bindingCommand = this->GetBindingCommand(binding, mode);
    if (!bindingCommand || !command || SStrCmp(bindingCommand, command, STORM_MAX_STR)) {
        if (bindingCommand) {
            auto index = this->GetBindingIndex(binding, mode);
            this->AdjustCommandKeyIndices(set, mode, bindingCommand, index);
        }
        auto index = this->GetNumCommandKeys(set, mode, command);
        binding->data[mode].command.Copy(command);
        binding->data[mode].index = index;
    }

    return true;
}

const char* CGUIBindings::GetBindingCommand(KEYBINDING* binding, BINDING_MODE mode) const {
    if (mode != BINDING_MODE_4) {
        return binding->data[mode].command.GetString();
    }

    for (int32_t m = BINDING_MODE_3; m >= BINDING_MODE_0; --m) {
        // TODO
        auto result = binding->data[m].command.GetString();
        if (result)
            return result;
    }

    return nullptr;
}

int32_t CGUIBindings::GetBindingIndex(KEYBINDING* binding, BINDING_MODE mode) const {
    if (mode != BINDING_MODE_4) {
        return binding->data[mode].index;
    }

    for (int32_t m = BINDING_MODE_3; m >= BINDING_MODE_0; --m) {
        // TODO
        if (binding->data[m].command.GetString())
            return binding->data[m].index;
    }

    return -1;
}

int32_t CGUIBindings::GetNumCommandKeys(BINDING_SET set, BINDING_MODE mode, const char* command) {
    auto binding = this->m_bindings[set].Head();

    int32_t result = 0;

    while (binding) {
        auto bindingCommand = this->GetBindingCommand(binding, mode);
        if (bindingCommand && !SStrCmpI(bindingCommand, command, STORM_MAX_STR)) {
            ++result;
        }

        binding = this->m_bindings[set].Next(binding);
    }

    return result;
}

void CGUIBindings::AdjustCommandKeyIndices(BINDING_SET set, BINDING_MODE mode, const char* command, int32_t index) {
    auto binding = this->m_bindings[set].Head();

    int32_t result = 0;

    while (binding) {
        auto bindingCommand = this->GetBindingCommand(binding, mode);
        if (bindingCommand && !SStrCmpI(bindingCommand, command, STORM_MAX_STR)) {
            auto bindingIndex = this->GetBindingIndex(binding, mode);
            if (bindingIndex > index) {
                --binding->data[mode].index;
            }
        }

        binding = this->m_bindings[set].Next(binding);
    }
}
