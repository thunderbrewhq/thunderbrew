#include "ui/CSimpleMovieFrame.hpp"
#include "ui/CSimpleMovieFrameScript.hpp"

int32_t CSimpleMovieFrame::s_metatable;
int32_t CSimpleMovieFrame::s_objectType;

void CSimpleMovieFrame::CreateScriptMetaTable() {
    lua_State* L = FrameScript_GetContext();
    int32_t ref = FrameScript_Object::CreateScriptMetaTable(L, &CSimpleMovieFrame::RegisterScriptMethods);
    CSimpleMovieFrame::s_metatable = ref;
}

int32_t CSimpleMovieFrame::GetObjectType() {
    if (!CSimpleMovieFrame::s_objectType) {
        CSimpleMovieFrame::s_objectType = ++FrameScript_Object::s_objectTypes;
    }

    return CSimpleMovieFrame::s_objectType;
}

void CSimpleMovieFrame::RegisterScriptMethods(lua_State* L) {
    CSimpleFrame::RegisterScriptMethods(L);
    FrameScript_Object::FillScriptMethodTable(L, SimpleMovieFrameMethods, NUM_SIMPLE_MOVIE_FRAME_SCRIPT_METHODS);
}

FrameScript_Object::ScriptIx* CSimpleMovieFrame::GetScriptByName(const char* name, ScriptData& data) {
    auto parentScript = CSimpleFrame::GetScriptByName(name, data);

    if (parentScript) {
        return parentScript;
    }

    if (!SStrCmpI(name, "OnMovieFinished", STORM_MAX_STR)) {
        return &this->m_onMovieFinished;
    }

    if (!SStrCmpI(name, "OnMovieShowSubtitle", STORM_MAX_STR)) {
        data.wrapper = "return function(self,text) %s end";
        return &this->m_onMovieShowSubtitle;
    }

    if (!SStrCmpI(name, "OnMovieHideSubtitle", STORM_MAX_STR)) {
        return &this->m_onMovieHideSubtitle;
    }

    return nullptr;
}

bool CSimpleMovieFrame::IsA(int32_t type) {
    return type == CSimpleMovieFrame::s_objectType
        || type == CSimpleFrame::s_objectType
        || type == CScriptRegion::s_objectType
        || type == CScriptObject::s_objectType;
}

int32_t CSimpleMovieFrame::GetScriptMetaTable() {
    return CSimpleMovieFrame::s_metatable;
}

void CSimpleMovieFrame::OnFrameRender(CRenderBatch* batch, uint32_t layer) {
}

CSimpleMovieFrame::CSimpleMovieFrame(CSimpleFrame* parent)
    : CSimpleFrame(parent) {
}

int32_t CSimpleMovieFrame::StartMovie(const char* filename, int32_t volume) {
    if (!this->ParseAVIFile(filename) || !this->OpenVideo()) {
        return 0;
    }

    SStrCopy(this->m_filename, filename, 256);
    this->m_volume = volume;

    // this->OpenAudio(this, filename, volume, 0);
    // this->OpenCaptions(this, filename);

    this->m_isPlaying = 1;
    return 1;
}

void CSimpleMovieFrame::StopMovie() {
}

int32_t CSimpleMovieFrame::ParseAVIFile(const char* filename) {
    return 0;
}

int32_t CSimpleMovieFrame::OpenVideo() {
    return 0;
}
