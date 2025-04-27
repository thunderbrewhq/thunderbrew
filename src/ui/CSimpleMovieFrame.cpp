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

#include <map>
#include <windows.h>

#define XVID_MAKE_VERSION(a, b, c) ((((a) & 0xff) << 16) | (((b) & 0xff) << 8) | ((c) & 0xff))
#define XVID_VERSION_MAJOR(a) ((char)(((a) >> 16) & 0xff))
#define XVID_VERSION_MINOR(a) ((char)(((a) >> 8) & 0xff))
#define XVID_VERSION_PATCH(a) ((char)(((a) >> 0) & 0xff))

#define XVID_MAKE_API(a, b) ((((a) & 0xff) << 16) | (((b) & 0xff) << 0))
#define XVID_API_MAJOR(a) (((a) >> 16) & 0xff)
#define XVID_API_MINOR(a) (((a) >> 0) & 0xff)

#define XVID_VERSION XVID_MAKE_VERSION(1, 4, -127)
#define XVID_API XVID_MAKE_API(4, 4)

extern "C" {

/* xvid_image_t
    for non-planar colorspaces use only plane[0] and stride[0]
    four plane reserved for alpha*/
typedef struct {
    int csp;        /* [in] colorspace; or with XVID_CSP_VFLIP to perform vertical flip */
    void* plane[4]; /* [in] image plane ptrs */
    int stride[4];  /* [in] image stride; "bytes per row"*/
} xvid_image_t;

/* XVID_GBL_INIT param1 */
typedef struct {
    int version;
    unsigned int cpu_flags; /* [in:opt] zero = autodetect cpu; XVID_CPU_FORCE|{cpu features} = force cpu features */
    int debug;              /* [in:opt] debug level */
} xvid_gbl_init_t;

/* XVID_GBL_INFO param1 */
typedef struct {
    int version;
    int actual_version;     /* [out] returns the actual xvidcore version */
    const char* build;      /* [out] if !null, points to description of this xvid core build */
    unsigned int cpu_flags; /* [out] detected cpu features */
    int num_threads;        /* [out] detected number of cpus/threads */
} xvid_gbl_info_t;

#define XVID_GBL_INIT 0    /* initialize xvidcore; must be called before using xvid_decore, or xvid_encore) */
#define XVID_GBL_INFO 1    /* return some info about xvidcore, and the host computer */
#define XVID_GBL_CONVERT 2 /* colorspace conversion utility */

typedef int (*XVID_GLOBAL)(void* handle, int opt, void* param1, void* param2);

#define XVID_DEC_CREATE 0  /* create decore instance; return 0 on success */
#define XVID_DEC_DESTROY 1 /* destroy decore instance: return 0 on success */
#define XVID_DEC_DECODE 2  /* decode a frame: returns number of bytes consumed >= 0 */

typedef int (*XVID_DECORE)(void* handle, int opt, void* param1, void* param2);

/* XVID_DEC_CREATE param 1
    image width & height as well as FourCC code may be specified
    here when known in advance (e.g. being read from container) */
typedef struct {
    int version;
    int width;       /* [in:opt] image width */
    int height;      /* [in:opt] image width */
    void* handle;    /* [out]    decore context handle */
                     /* ------- v1.3.x ------- */
    int fourcc;      /* [in:opt] fourcc of the input video */
    int num_threads; /* [in:opt] number of threads to use in decoder */
} xvid_dec_create_t;

typedef struct {
    int version;
    int general;         /* [in:opt] general flags */
    void* bitstream;     /* [in]     bitstream (read from)*/
    int length;          /* [in]     bitstream length */
    xvid_image_t output; /* [in]     output image (written to) */
                         /* ------- v1.1.x ------- */
    int brightness;      /* [in]	 brightness offset (0=none) */
} xvid_dec_frame_t;

/* XVID_DEC_DECODE param2 :: optional */
typedef struct
{
    int version;

    int type; /* [out] output data type */
    union {
        struct {                /* type>0 {XVID_TYPE_IVOP,XVID_TYPE_PVOP,XVID_TYPE_BVOP,XVID_TYPE_SVOP} */
            int general;        /* [out] flags */
            int time_base;      /* [out] time base */
            int time_increment; /* [out] time increment */

            /* XXX: external deblocking stuff */
            int* qscale;       /* [out] pointer to quantizer table */
            int qscale_stride; /* [out] quantizer scale stride */

        } vop;
        struct {            /* XVID_TYPE_VOL */
            int general;    /* [out] flags */
            int width;      /* [out] width */
            int height;     /* [out] height */
            int par;        /* [out] pixel aspect ratio (refer to XVID_PAR_xxx above) */
            int par_width;  /* [out] aspect ratio width  [1..255] */
            int par_height; /* [out] aspect ratio height [1..255] */
        } vol;
    } data;
} xvid_dec_stats_t;

} // extern "C"

static std::map<uint32_t, void*> s_divxHandles;
static uint32_t s_divxRefCounter = 0;

static XVID_GLOBAL s_xvid_global = nullptr;
static XVID_DECORE s_xvid_decore = nullptr;

static uint32_t LoadDivxDecoder() {
    auto library = LoadLibraryA("xvidcore.dll");
    if (!library) {
        return 0;
    }

    s_xvid_global = reinterpret_cast<XVID_GLOBAL>(GetProcAddress(library, "xvid_global"));
    s_xvid_decore = reinterpret_cast<XVID_DECORE>(GetProcAddress(library, "xvid_decore"));

    if (!s_xvid_global || !s_xvid_decore) {
        FreeLibrary(library);
        return 0;
    }

    xvid_gbl_info_t info = {};
    info.version = XVID_VERSION;

    if (s_xvid_global(nullptr, XVID_GBL_INFO, &info, nullptr) < 0) {
        return 0;
    }

    xvid_gbl_init_t init = {};
    init.version = XVID_VERSION;
    if (s_xvid_global(nullptr, XVID_GBL_INIT, &init, nullptr) < 0) {
        return 0;
    }

    xvid_dec_create_t decoder = {};
    decoder.version = XVID_VERSION;
    decoder.num_threads = info.num_threads;
    if (s_xvid_decore(nullptr, XVID_DEC_CREATE, &decoder, nullptr)) {
        return 0;
    }

    if (++s_divxRefCounter == 0) {
        ++s_divxRefCounter;
    }

    s_divxHandles[s_divxRefCounter] = decoder.handle;
    return s_divxRefCounter;
}

static int32_t DivxDecode(uint32_t decoder, char* input, char* output, int32_t width) {
    xvid_dec_frame_t frame = {};
    xvid_dec_stats_t stats = {};

	frame.version = XVID_VERSION;
    stats.version = XVID_VERSION;

    frame.bitstream = input + 4;
    frame.length = *reinterpret_cast<int*>(input);

    frame.output.plane[0] = output;
    frame.output.stride[0] = 4 * width;
    frame.output.csp = (1 << 15);

    static int frameNo = 0;

    while (true) {
        int bytes = s_xvid_decore(s_divxHandles[decoder], XVID_DEC_DECODE, &frame, &stats);
        if (bytes < 1) {
            break;
        }
        frame.bitstream = (char*)frame.bitstream + bytes;
        frame.length -= bytes;
    }

    frameNo++;

    return 1;
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
        texelStrideInBytes = 4 * width;
        texels = reinterpret_cast<CSimpleMovieFrame::TextureData*>(userData)->data;
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
    this->m_decoder = LoadDivxDecoder();
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

    const uint32_t imageSize = widthByFormat[this->m_textureFormat] * heightByFormat[this->m_textureFormat] * 4;
    this->m_imageData = reinterpret_cast<char*>(ALLOC_ZERO(imageSize));
    if (!this->m_imageData) {
        CloseVideo();
        return 0;
    }

    int32_t hasTextures = 1;
    for (uint32_t i = 0; i < textureCountByFormat[this->m_textureFormat]; ++i) {
        CGxTexParms parms = {};
        parms.target = GxTex_2d;
        parms.width = widthByFormat[this->m_textureFormat];
        parms.height = heightByFormat[this->m_textureFormat];
        parms.format = GxTex_Argb8888;
        parms.dataFormat = GxTex_Argb8888;
        parms.flags = CGxTexFlags(GxTex_Linear, 0, 0, 0, 0, 0, 1);
        parms.userArg = &this->m_textureData[i];
        parms.userFunc = &CSimpleMovieFrame::TextureCallback;
        this->m_textureData[i].params = parms;
        this->m_textureData[i].data = this->m_imageData;
        hasTextures &= GxTexCreate(parms, this->m_textures[i]);
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
}

int32_t CSimpleMovieFrame::DecodeFrame(bool update) {
    auto frameSize = *reinterpret_cast<uint32_t*>(this->m_currentFrameData);
    if (!DivxDecode(this->m_decoder, this->m_currentFrameData, this->m_imageData, this->m_videoWidth)) {
        return 0;
    }
    this->m_currentFrameData += frameSize + 4;

    if (!update) {
        return 1;
    }

    for (uint32_t i = 0; i < textureCountByFormat[this->m_textureFormat]; ++i) {
        GxTexUpdate(this->m_textures[i], 0, 0, this->m_textureData[i].params.width, this->m_textureData[i].params.height, 1);
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

    // TODO

    GxRsPush();
    GxRsSet(GxRs_Lighting, 0);
    GxRsSet(GxRs_Fog, 0);
    GxRsSet(GxRs_BlendingMode, 0);
    GxRsSetAlphaRef();

    for (uint32_t i = 0; i < textureCountByFormat[this->m_textureFormat]; ++i) {
        if (i > 0)
            continue;

        float inX = 0.1f;
        float inY = -0.4f;

        float axX = 0.9f;
        float axY = 0.4f;

        C3Vector position[] = {
            { inX, inY, 0.0f },
            { axX, inY, 0.0f },
            { inX, axY, 0.0f },
            { axX, axY, 0.0f }
        };

        C3Vector normal[] = {
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f }
        };
        C2Vector tex[] = {
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 0.0f, 1.0f },
            { 1.0f, 1.0f }
        };
        GxPrimLockVertexPtrs(4, position, sizeof(C3Vector), nullptr, 0, nullptr, 0, nullptr, 0, tex, sizeof(C2Vector), nullptr, 0);
        GxRsSet(GxRs_Texture0, this->m_textures[i]);
        uint16_t indices[] = { 0, 1, 2, 3 };
        GxDrawLockedElements(GxPrim_TriangleStrip, 4, indices);
        GxPrimUnlockVertexPtrs();
    }

    GxRsPop();
    GxXformSetViewport(minX, maxX, minY, maxY, minZ, maxZ);
}
