#include "gameui/CGUIBindings.hpp"
#include "ui/FrameScript.hpp"
#include "util/CStatus.hpp"
#include "util/SFile.hpp"
#include "util/StringTo.hpp"

#include <common/XML.hpp>

static CStatus s_nullStatus;


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

    const char* defaultValue = node->GetAttributeByName("default");
    if (defaultValue && *defaultValue) {
        if (!this->m_commands.Ptr(defaultValue)) {
            // TODO: CGUIBindings::Bind(0, 0, defaultValue, name);
        }
    }
}

void CGUIBindings::LoadModifiedClick(const char* commandsFile, XMLNode* node, CStatus* status) {
}
