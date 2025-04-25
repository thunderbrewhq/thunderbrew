#include "ui/CSimpleMovieFrame.hpp"
#include "ui/CSimpleMovieFrameScript.hpp"
#include "util/SFile.hpp"
#include <common/Time.hpp>

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

void CSimpleMovieFrame::RenderMovie(void* param) {
    auto movieFrame = reinterpret_cast<CSimpleMovieFrame*>(param);
    if (movieFrame->m_isPlaying) {
        movieFrame->UpdateTiming();
        movieFrame->Render();
    }
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
    this->CSimpleFrame::OnFrameRender(batch, layer);
    if (layer == DRAWLAYER_ARTWORK) {
        batch->QueueCallback(&CSimpleMovieFrame::RenderMovie, this);
    }
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
    if (!this->m_isPlaying) {
        return;
    }

    // UnloadDivxDecoder
    // CloseAudio
    // CloseCaptions
    this->m_isInterrupted = 0;
    this->m_isPlaying = 0;
    if (this->m_onMovieFinished.luaRef) {
        this->RunScript(this->m_onMovieFinished, 0, nullptr);
    }
}

int32_t CSimpleMovieFrame::ParseAVIFile(const char* filename) {
    char path[STORM_MAX_PATH];
    // WARNING(workaround): Remove "Data/enGB/" substring
    SStrPrintf(path, STORM_MAX_PATH, "Data/enGB/%s.avi", filename);

    SFile* videoFile = nullptr;
    if (!SFile::OpenEx(nullptr, path, 1, &videoFile)) {
        return 0;
    }

    // -- ParseAVIHeader --
#pragma pack(push, 1)
    struct
    {
        char id[4];
        uint32_t length;
        char format[4];
    } block;
#pragma pack(pop)

    if (!SFile::Read(videoFile, &block, 12, nullptr, nullptr, nullptr) ||
        SStrCmpI(block.id, "RIFF", 4) || SStrCmpI(block.format, "AVI ", 4)) {
        SFile::Close(videoFile);
        return 0;
    }

    uint32_t fileSize = SFile::GetFileSize(videoFile, nullptr);

    char* data = nullptr;
    uint32_t dataSize = 0;

    uint8_t* indexData = nullptr;
    uint32_t indexDataSize = 0;

    uint32_t moviStart = 0;

    while (true) {
        uint32_t position = SFile::SetFilePointer(videoFile, 0, nullptr, 1);
        if (position >= fileSize) {
            break;
        }

        if (!SFile::Read(videoFile, &block, 8, nullptr, nullptr, nullptr)) {
            break;
        }

        if (SStrCmpI(block.id, "LIST", 4)) {
            if (SStrCmpI(block.id, "idx1", 4)) {
                SFile::SetFilePointer(videoFile, block.length, nullptr, 1);
            } else {
                indexDataSize = block.length;
                indexData = reinterpret_cast<uint8_t*>(alloca(indexDataSize));
                if (!SFile::Read(videoFile, indexData, indexDataSize, nullptr, nullptr, nullptr)) {
                    break;
                }
            }
        } else {
            if (!SFile::Read(videoFile, &block, 4, nullptr, nullptr, nullptr)) {
                break;
            }

            block.length -= 4;

            if (SStrCmpI(block.id, "hdrl", 4)) {
                if (SStrCmpI(block.id, "movi", 4)) {
                    SFile::SetFilePointer(videoFile, block.length, nullptr, 1);
                } else {
                    moviStart = SFile::SetFilePointer(videoFile, 0, nullptr, 1);
                    SFile::SetFilePointer(videoFile, block.length, nullptr, 1);
                }
            } else {
                dataSize = block.length;
                data = reinterpret_cast<char*>(alloca(dataSize));
                if (!SFile::Read(videoFile, data, dataSize, nullptr, nullptr, nullptr)) {
                    break;
                }
            }
        }
    }

    int32_t v41 = 0;
    int32_t v39 = -1;
    int32_t v30 = -1;

    uint32_t offset = 0;

    while (offset < dataSize) {
        if (!SStrCmpI(&data[offset], "LIST", 4)) {
            offset += 12;
            continue;
        }

        uint32_t length = *reinterpret_cast<uint32_t*>(&data[offset + 4]);
        if (SStrCmpI(&data[offset], "strh", 4u)) {
            if (SStrCmpI(&data[offset], "strf", 4)) {
                offset += 8;
            } else {
                offset += 8;
                if (v39 >= 0 && v30 < 0) {
                    this->m_videoWidth = *reinterpret_cast<uint32_t*>(&data[offset + 4]);
                    this->m_videoHeight = *reinterpret_cast<uint32_t*>(&data[offset + 8]);
                }
            }
        } else {
            offset += 8;
            if (!SStrCmpI(&data[offset], "vids", 4)) {
                float scale = *reinterpret_cast<uint32_t*>(&data[offset + 20]);
                float rate = *reinterpret_cast<uint32_t*>(&data[offset + 24]);
                this->m_frameRate = rate / scale;
                this->m_numFrames = *reinterpret_cast<uint32_t*>(&data[offset + 32]);
                v39 = v41;
            }
            if (!SStrCmpI(&data[offset], "auds", 4)) {
                v30 = v41;
            }
            ++v41;
        }
        offset += length;
    }

    // -- ParseAVIIndex --
    this->m_videoBytes = 0;
    this->m_audioBytes = 0;

    offset = 0;
    while (offset < indexDataSize) {
        // IsVideoChunk
        if (indexData[offset + 2] == 100) {
            this->m_videoBytes += *reinterpret_cast<uint32_t*>(&indexData[offset + 12]) + 4;
        }

        // IsAudioChunk
        if (indexData[offset + 2] == 119) {
            this->m_audioBytes += *reinterpret_cast<uint32_t*>(&indexData[offset + 12]);
        }
        offset += 16;
    }

    this->m_videoData = reinterpret_cast<char*>(ALLOC(this->m_videoBytes));
    this->m_audioData = reinterpret_cast<char*>(ALLOC(this->m_audioBytes));

    char* videoData = this->m_videoData;
    char* audioData = this->m_audioData;

    offset = 0;
    while (offset < indexDataSize) {
        // IsVideoChunk
        if (indexData[offset + 2] == 100) {
            uint32_t frameSize = *reinterpret_cast<uint32_t*>(&indexData[offset + 12]);
            uint32_t frameOffset = *reinterpret_cast<uint32_t*>(&indexData[offset + 8]) + moviStart + 4;
            memcpy(videoData, &frameSize, 4);
            videoData += 4;
            SFile::SetFilePointer(videoFile, frameOffset, nullptr, 0);
            SFile::Read(videoFile, videoData, frameSize, nullptr, nullptr, nullptr);
            videoData += frameSize;
        }

        // IsAudioChunk
        if (indexData[offset + 2] == 119) {
            uint32_t frameSize = *reinterpret_cast<uint32_t*>(&indexData[offset + 12]);
            uint32_t frameOffset = *reinterpret_cast<uint32_t*>(&indexData[offset + 8]) + moviStart + 4;
            SFile::SetFilePointer(videoFile, frameOffset, nullptr, 0);
            SFile::Read(videoFile, audioData, frameSize, nullptr, nullptr, nullptr);
            audioData += frameSize;
        }
        offset += 16;
    }

    this->m_currentFrameData = this->m_videoData;

    SFile::Close(videoFile);
    return dataSize > 0;
}

int32_t CSimpleMovieFrame::OpenVideo() {
    return 0;
}

int32_t CSimpleMovieFrame::UpdateTiming() {
    bool isAudioPlaying = false; /* SE2::IsPlaying(this->m_audioChannel) */

    if (isAudioPlaying) {
        //this->m_elapsedTime = SE2::GetPositionInMS(this->m_audioChannel);
        //this->m_startTime = OsGetAsyncTimeMs() - this->m_elapsedTime;
    } else {
        this->m_elapsedTime = OsGetAsyncTimeMs() - this->m_startTime;
    }

    uint32_t currentFrame = static_cast<uint32_t>(this->m_elapsedTime * this->m_frameRate * 0.001 + 0.5);

    if (isAudioPlaying) {
        // TODO
    }

    currentFrame += this->m_frameAudioSync;
    if (currentFrame <= this->m_prevFrame) {
        currentFrame = this->m_prevFrame;
    }

    this->m_currentFrame = currentFrame;

    if (currentFrame >= this->m_numFrames) {
        this->m_isInterrupted = 1;
    }

    if (this->m_isInterrupted) {
        this->StopMovie();
        return 0;
    }

    if (currentFrame == this->m_prevFrame) {
        return 0;
    }

    if (currentFrame != this->m_prevFrame + 1) {
        ++this->m_lastKeyFrame;
    }

    while (this->m_prevFrame < this->m_currentFrame - 1) {
        this->DecodeFrame(false);
        ++this->m_prevFrame;
    }

    if (!this->DecodeFrame(true)) {
        this->m_isInterrupted = 1;
    }

    this->m_prevFrame = this->m_currentFrame;

    // TODO: Subtitle stuff
}

int32_t CSimpleMovieFrame::DecodeFrame(bool unk) {
    return 0;
}

void CSimpleMovieFrame::Render() {
}
