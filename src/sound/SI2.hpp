#ifndef SOUND_SI2_HPP
#define SOUND_SI2_HPP

#include "ui/Types.hpp"
#include <storm/Log.hpp>
#include <cstdint>
#include <cstdarg>
#include <fmod.hpp>
#include <fmod_errors.h>


#define SI2_ERR(errcode, format, ...) SI2::Log_Write(__LINE__, __FILE__, errcode, format, ##__VA_ARGS__)
#define SI2_LOG(format, ...) SI2::Log_Write(__LINE__, __FILE__, FMOD_OK, format, ##__VA_ARGS__)

class SI2 {
    public:
        // Static variables
        static FrameScript_Method s_ScriptFunctions[];
        static uint32_t sm_logFlags;
        static HSLOG sm_log;
        static FMOD::System* sm_pGameSystem;
        static FMOD::System* sm_pChatSystem;

        // Static functions
        static void RegisterScriptFunctions();
        static int32_t Log_Init();
        static void Log_Write(const char* format, ...);
        static void Log_Write(uint32_t line, const char* filename, FMOD_RESULT errcode, const char* format, ...);
        static void RegisterCVars();
        static int32_t Init(int32_t flag);
        static void StartGlueMusic(const char* filename);
};

#endif
