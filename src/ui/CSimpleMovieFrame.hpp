#ifndef UI_C_SIMPLE_MOVIE_FRAME_HPP
#define UI_C_SIMPLE_MOVIE_FRAME_HPP

#include "ui/CSimpleFrame.hpp"
#include <tempest/Vector.hpp>

class CRect;
class CRenderBatch;

class CSimpleMovieFrame : public CSimpleFrame {
    public:
    // Static variables
    static int32_t s_metatable;
    static int32_t s_objectType;

    // Static functions
    static void CreateScriptMetaTable();
    static int32_t GetObjectType();
    static void RegisterScriptMethods(lua_State* L);
    static void RenderMovie(void* param);

    // Member variables
    int32_t m_isPlaying = 0;
    int32_t m_isStopped = 0;
    int32_t m_enableSubtitles = 0;
    char m_filename[256];
    int32_t m_volume = 100;
    ScriptIx m_onMovieFinished;
    ScriptIx m_onMovieShowSubtitle;
    ScriptIx m_onMovieHideSubtitle;
    float m_frameRate  = 0.0;
    uint32_t m_videoWidth = 0;
    uint32_t m_videoHeight = 0;
    uint32_t m_numFrames = 0;
    char* m_videoData = nullptr;
    uint32_t m_videoBytes = 0;
    char* m_audioData = nullptr;
    uint32_t m_audioBytes = 0;

    // Virtual member functions
    virtual ScriptIx* GetScriptByName(const char* name, ScriptData& data);
    virtual bool IsA(int32_t type);
    virtual int32_t GetScriptMetaTable();
    virtual void OnFrameRender(CRenderBatch* batch, uint32_t layer);

    // Member functions
    CSimpleMovieFrame(CSimpleFrame* parent);
    int32_t StartMovie(const char* filename, int32_t volume);
    void StopMovie();
    int32_t ParseAVIFile(const char* filename);
    int32_t OpenVideo();
};

#endif
