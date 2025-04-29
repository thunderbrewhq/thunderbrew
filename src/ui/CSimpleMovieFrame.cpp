#include "ui/CSimpleMovieFrame.hpp"
#include "ui/CSimpleMovieFrameScript.hpp"
#include "util/SFile.hpp"
#include "gx/Buffer.hpp"
#include "gx/RenderState.hpp"
#include "gx/Texture.hpp"
#include "gx/Transform.hpp"
#include "gx/Draw.hpp"
#include <common/Time.hpp>
#include <tempest/Matrix.hpp>

#if defined(WHOA_SYSTEM_WIN)

#include <windows.h>

typedef int32_t(__cdecl* INITIALIZEDIVXDECODER)(uint32_t index, uint32_t width, uint32_t height);
typedef int32_t(__cdecl* SETOUTPUTFORMAT)(uint32_t index, uint32_t unk, uint32_t width, uint32_t height);
typedef int32_t(__cdecl* DIVXDECODE)(uint32_t index, void* data, uint32_t unk);
typedef int32_t(__cdecl* UNINITIALIZEDIVXDECODER)(uint32_t index);

static uint32_t s_divxRefCounter = 0;

static INITIALIZEDIVXDECODER InitializeDivxDecoder = nullptr;
static SETOUTPUTFORMAT SetOutputFormat = nullptr;
static DIVXDECODE DivxDecode = nullptr;
static UNINITIALIZEDIVXDECODER UnInitializeDivxDecoder = nullptr;

static uint32_t LoadDivxDecoder(uint32_t width, uint32_t height) {
    if (!InitializeDivxDecoder || !SetOutputFormat || !DivxDecode || !UnInitializeDivxDecoder) {
        auto library = LoadLibraryA("DivxDecoder.dll");
        if (!library) {
            return 0;
        }

        InitializeDivxDecoder = reinterpret_cast<INITIALIZEDIVXDECODER>(GetProcAddress(library, "InitializeDivxDecoder"));
        SetOutputFormat = reinterpret_cast<SETOUTPUTFORMAT>(GetProcAddress(library, "SetOutputFormat"));
        DivxDecode = reinterpret_cast<DIVXDECODE>(GetProcAddress(library, "DivxDecode"));
        UnInitializeDivxDecoder = reinterpret_cast<UNINITIALIZEDIVXDECODER>(GetProcAddress(library, "UnInitializeDivxDecoder"));

        if (!InitializeDivxDecoder || !SetOutputFormat || !DivxDecode || !UnInitializeDivxDecoder) {
            InitializeDivxDecoder = nullptr;
            SetOutputFormat = nullptr;
            DivxDecode = nullptr;
            UnInitializeDivxDecoder = nullptr;
            FreeLibrary(library);
            return 0;
        }
    }

    if (++s_divxRefCounter == 0) {
        ++s_divxRefCounter;
    }

    if (InitializeDivxDecoder(s_divxRefCounter, width, height)) {
        UnInitializeDivxDecoder(s_divxRefCounter--);
        return 0;
    }

    if (SetOutputFormat(s_divxRefCounter, 1, width, height)) {
        UnInitializeDivxDecoder(s_divxRefCounter--);
        return 0;
    }

    return s_divxRefCounter;
}

#else

static uint32_t LoadDivxDecoder() {
    return 0;
}

#endif


static void UnloadDivxDecoder(uint32_t decoder) {

}

static const uint32_t textureCountByFormat[6] = { 6, 2, 3, 4, 6, 2 };


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

void CSimpleMovieFrame::TextureCallback(EGxTexCommand command, uint32_t width, uint32_t height, uint32_t, uint32_t, void* userData, uint32_t& texelStrideInBytes, const void*& texels) {
    if (command == GxTex_Latch) {
        auto textureData = reinterpret_cast<CSimpleMovieFrame::TextureData*>(userData);
        //texelStrideInBytes = textureData->strideData[3] / 2;
        texelStrideInBytes = 4 * width;
        texels = &textureData->data[textureData->strideData[2]];
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
    this->m_startTime = OsGetAsyncTimeMs();
    this->m_elapsedTime = 0;
    this->m_decoder = LoadDivxDecoder(this->m_videoWidth, this->m_videoHeight);
    this->m_currentFrame = 0;
    this->m_prevFrame = -1;
    this->m_lastKeyFrame = 0;
    this->m_frameAudioSync = 0;

    if (!this->m_decoder) {
        return 0;
    }

    if (this->m_videoWidth == 1024) {
        if (this->m_videoHeight == 576) {
            this->m_textureFormat = 3;
        } else if (this->m_videoHeight == 436) {
            this->m_textureFormat = 5;
        } else {
            this->m_textureFormat = 1;
        }
    } else if (this->m_videoWidth == 800) {
        if (this->m_videoHeight == 448) {
            this->m_textureFormat = 2;
        } else if (this->m_videoHeight == 342 || this->m_videoHeight == 340) {
            this->m_textureFormat = 4;
        } else {
            this->m_textureFormat = 0;
        }
    } else {
        CloseVideo();
        return 0;
    }

    const uint32_t widthByFormat[6] = { 800, 1024, 800, 1024, 800, 1024 };
    const uint32_t heightByFormat[6] = { 384, 512, 512, 576, 384, 512 };
    static uint32_t s_strideData[144] = { 512, 256, 0, 3200, 256, 256, 2048, 3200, 32, 256, 3072, 3200, 512, 128, 819200, 3200, 256, 128, 821248, 3200, 32, 128, 822272, 3200, 512, 512, 0, 4096, 512, 512, 2048, 4096, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 512, 512, 0, 3200, 256, 512, 2048, 3200, 32, 512, 3072, 3200, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 512, 512, 0, 4096, 512, 512, 2048, 4096, 512, 64, 2097152, 4096, 512, 64, 2099200, 4096, 0, 0, 0, 0, 0, 0, 0, 0, 512, 256, 0, 3200, 256, 256, 2048, 3200, 32, 256, 3072, 3200, 512, 128, 819200, 3200, 256, 128, 821248, 3200, 32, 128, 822272, 3200, 512, 512, 0, 4096, 512, 512, 2048, 4096, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    const uint32_t imageSize = widthByFormat[this->m_textureFormat] * heightByFormat[this->m_textureFormat] * 4;
    this->m_imageData = reinterpret_cast<char*>(ALLOC_ZERO(imageSize));
    if (!this->m_imageData) {
        CloseVideo();
        return 0;
    }

    int32_t hasTextures = 1;
    for (uint32_t i = 0; i < textureCountByFormat[this->m_textureFormat]; ++i) {
        uint32_t stride = (6 * this->m_textureFormat + i) * 4;
        this->m_textureData[i].strideData = &s_strideData[stride];
        this->m_textureData[i].data = this->m_imageData;

        hasTextures &= GxTexCreate(
            s_strideData[stride],
            s_strideData[stride + 1],
            GxTex_Argb8888,
            CGxTexFlags(),
            &this->m_textureData[i],
            CSimpleMovieFrame::TextureCallback,
            this->m_textures[i]);
    }

    if (hasTextures) {
        for (uint32_t i = 0; i < textureCountByFormat[this->m_textureFormat]; ++i) {
            GxTexUpdate(this->m_textures[i], 0, 0, 0, 0, 1);
        }
    }

    return 1;
}

void CSimpleMovieFrame::CloseVideo() {
    if (this->m_decoder) {
        UnloadDivxDecoder(this->m_decoder);
        this->m_decoder = 0;
    }

    if (this->m_imageData) {
        FREE(this->m_imageData);
        this->m_imageData = nullptr;
    }

    if (this->m_videoData) {
        FREE(this->m_videoData);
        this->m_videoData = nullptr;
    }

    for (uint32_t i = 0; i < 6; ++i) {
        GxTexDestroy(this->m_textures[i]);
    }
}

int32_t CSimpleMovieFrame::UpdateTiming() {
    bool isAudioPlaying = false; /* SE2::IsPlaying(this->m_audioChannel) */

    if (isAudioPlaying) {
        //this->m_elapsedTime = SE2::GetPositionInMS(this->m_audioChannel);
        //this->m_startTime = OsGetAsyncTimeMs() - this->m_elapsedTime;
    } else {
        this->m_elapsedTime = OsGetAsyncTimeMs() - this->m_startTime;
    }

    int32_t currentFrame = static_cast<int32_t>(this->m_elapsedTime * this->m_frameRate * 0.001 + 0.5);

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
    return 1;
}

int32_t CSimpleMovieFrame::DecodeFrame(bool update) {
#pragma pack(push, 1)
    struct DecoderData
    {
        char* output;
        char* input;
        uint32_t inputSize;
        uint32_t update;
        uint32_t v14;
        uint32_t v15;
    };
#pragma pack(pop)

    DecoderData decoderData = {};

    const uint32_t imageDataOffsets[6] = {
        19200, 98304, 102400, 0, 67200, 155648
    };

    auto frameSize = *reinterpret_cast<uint32_t*>(this->m_currentFrameData);

    decoderData.output = this->m_imageData + imageDataOffsets[this->m_textureFormat];
    decoderData.input = this->m_currentFrameData + 4;
    decoderData.inputSize = frameSize;
    decoderData.update = update ? 1 : 0;

    this->m_currentFrameData += frameSize + 4;

    if (DivxDecode(this->m_decoder, &decoderData, 0)) {
        return 0;
    }

    if (!update) {
        return 1;
    }

    int32_t s_movieTextureUpdate[144] = {
        0, 6, 512, 256, 0, 6, 256, 256, 0, 6, 32, 256, 0, 0, 512, 122,
        0, 0, 256, 122, 0, 0, 32, 122, 0, 24, 512, 512, 0, 0, 512, 488,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 512, 480, 0,
        32, 256, 480, 0, 32, 32, 480, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 512, 512, 0, 0, 512, 512, 0, 0, 512, 64, 0, 0, 512, 64, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 21, 512, 256, 0, 21, 256, 256, 0, 21, 32, 256, 0, 0, 512,
        107, 0, 0, 256, 107, 0, 0, 32, 107, 0, 38, 512, 512, 0, 0, 512, 474, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    for (uint32_t i = 0; i < textureCountByFormat[this->m_textureFormat]; ++i) {
        uint32_t v9 = 4 * (i + 6 * this->m_textureFormat);
        GxTexUpdate(
            this->m_textures[i],
            s_movieTextureUpdate[v9],
            s_movieTextureUpdate[v9 + 1],
            s_movieTextureUpdate[v9 + 2],
            s_movieTextureUpdate[v9 + 3],
            1);
    }

    return 1;
}

void CSimpleMovieFrame::Render() {
    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
    GxXformViewport(minX, maxX, minY, maxY, minZ, maxZ);

    GxXformSetViewport(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f);
    CImVector clearColor = { 0x00, 0x00, 0x00, 0xFF };
    GxSceneClear(3, clearColor);
    C44Matrix matrix;
    GxuXformCreateOrtho(0.0, 1.0, -0.5, 0.5, 0.0, 500.0, matrix);
    GxXformSetView(C44Matrix());
    GxXformSetProjection(matrix);

    static uint32_t s_movieRenderFlag = 0;
    static C3Vector s_movieFrameNormalVec;
    static C2Vector s_movieFrameTexVec[4];

    if ((s_movieRenderFlag & 1) == 0) {
        s_movieFrameNormalVec.x = 0.0;
        s_movieFrameNormalVec.y = 0.0;
        s_movieFrameNormalVec.z = 1.0;
        s_movieRenderFlag |= 1;
    }

    if ((s_movieRenderFlag & 2) == 0) {
        s_movieFrameTexVec[0].x = 0.0;
        s_movieFrameTexVec[0].y = 0.0;
        s_movieFrameTexVec[1].y = 0.0;
        s_movieFrameTexVec[2].x = 0.0;
        s_movieFrameTexVec[1].x = 1.0;
        s_movieFrameTexVec[2].y = s_movieFrameTexVec[1].x;
        s_movieFrameTexVec[3].x = s_movieFrameTexVec[1].x;
        s_movieFrameTexVec[3].y = s_movieFrameTexVec[1].x;
        s_movieRenderFlag |= 2;
    }

    GxRsPush();
    GxRsSet(GxRs_Lighting, 0);
    GxRsSet(GxRs_Fog, 0);
    GxRsSet(GxRs_BlendingMode, 0);
    GxRsSetAlphaRef();

    static float s_layout[] = {0.0, 0.63999999, 0.11, -0.33000001, 0.63999999, 0.95999998, 0.11, -0.33000001, 0.95999998, 1.0, 0.11, -0.33000001, 0.0, 0.63999999, 0.33000001, 0.11, 0.63999999, 0.95999998, 0.33000001, 0.11, 0.95999998, 1.0, 0.33000001, 0.11, 0.0, 0.5, 0.333, -0.333, 0.5, 1.0, 0.333, -0.333, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.63999999, 0.41999999, -0.41999999, 0.63999999, 0.95999998, 0.41999999, -0.41999999, 0.95999998, 1.0, 0.41999999, -0.41999999, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5, 0.32659999, -0.41999999, 0.5, 1.0, 0.32659999, -0.41999999, 0.0, 0.5, 0.41999999, 0.32659999, 0.5, 1.0, 0.41999999, 0.32659999, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.63999999, 0.11, -0.33000001, 0.63999999, 0.95999998, 0.11, -0.33000001, 0.95999998, 1.0, 0.11, -0.33000001, 0.0, 0.63999999, 0.33000001, 0.11, 0.63999999, 0.95999998, 0.33000001, 0.11, 0.95999998, 1.0, 0.33000001, 0.11, 0.0, 0.5, 0.333, -0.333, 0.5, 1.0, 0.333, -0.333, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

    for (uint32_t i = 0; i < textureCountByFormat[this->m_textureFormat]; ++i) {
        float* rect = &s_layout[24 * this->m_textureFormat + 4 * i];

        float v16 = rect[3]; // * aspectCompensation
        float v17 = rect[2]; // * aspectCompensation

        C3Vector position[] = {
            { rect[0], v16, 0.0f },
            { rect[1], v16, 0.0f },
            { rect[0], v17, 0.0f },
            { rect[1], v17, 0.0f }
        };

        GxPrimLockVertexPtrs(4, position, sizeof(C3Vector), &s_movieFrameNormalVec, 0, nullptr, 0, nullptr, 0, s_movieFrameTexVec, sizeof(C2Vector), nullptr, 0);
        GxRsSet(GxRs_Texture0, this->m_textures[i]);
        uint16_t indices[] = { 0, 1, 2, 3 };
        GxDrawLockedElements(GxPrim_TriangleStrip, 4, indices);
        GxPrimUnlockVertexPtrs();
    }

    GxRsPop();
    GxXformSetViewport(minX, maxX, minY, maxY, minZ, maxZ);
}
