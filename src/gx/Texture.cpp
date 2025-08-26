#include "gx/Texture.hpp"
#include "gx/Device.hpp"
#include "gx/Gx.hpp"
#include "gx/texture/CBLPFile.hpp"
#include "gx/texture/CTgaFile.hpp"
#include "util/Filesystem.hpp"
#include "util/SFile.hpp"
#include <algorithm>
#include <cstring>
#include <bc/Memory.hpp>
#include <storm/Error.hpp>
#include <storm/String.hpp>

namespace Texture {
    int32_t s_createBlpAsync; // Invented name
    MipBits* s_mipBits;
    int32_t s_mipBitsValid;
    TSHashTable<CTexture, HASHKEY_TEXTUREFILE> s_textureCache;

    EGxTexFormat s_pixelFormatToGxTexFormat[10] = {
        GxTex_Dxt1,         // PIXEL_DXT1
        GxTex_Dxt3,         // PIXEL_DXT3
        GxTex_Argb8888,     // PIXEL_ARGB8888
        GxTex_Argb1555,     // PIXEL_ARGB1555
        GxTex_Argb4444,     // PIXEL_ARGB4444
        GxTex_Rgb565,       // PIXEL_RGB565
        GxTex_Unknown,      // PIXEL_A8
        GxTex_Dxt5,         // PIXEL_DXT5
        GxTex_Unknown,      // PIXEL_UNSPECIFIED
        GxTex_Unknown       // PIXEL_ARGB2565
    };
}

static CImVector CRAPPY_GREEN = { 0x00, 0xFF, 0x00, 0xFF };

void AsyncTextureWait(CTexture* texture) {
    // TODO
}

uint32_t CalcLevelCount(uint32_t width, uint32_t height) {
    uint32_t v2 = width;
    uint32_t v3 = height;
    uint32_t levels = 1;
    uint32_t v5;
    uint32_t v6;

    if (width == 6 * height) {
        v2 = width / 6;
    }

    while (v2 > 1 || v3 > 1) {
        v5 = v2 >> 1;

        ++levels;

        v6 = v2 >> 1 < 1;
        v2 = 1;

        if (!v6) {
            v2 = v5;
        }

        if ( v3 >> 1 >= 1 ) {
            v3 >>= 1;
        } else {
            v3 = 1;
        }
    }

    return levels;
}

uint32_t CalcLevelOffset(uint32_t level, uint32_t width, uint32_t height, uint32_t fourCC) {
    uint32_t offset = 0;

    for (int32_t i = 0; i < level; i++) {
        offset += CalcLevelSize(i, width, height, fourCC);
    }

    return offset;
}

uint32_t CalcLevelSize(uint32_t level, uint32_t width, uint32_t height, uint32_t fourCC) {
    uint32_t v4 = std::max(width >> level, 1u);
    uint32_t v5 = std::max(height >> level, 1u);

    if (fourCC == 0 || fourCC == 1 || fourCC == 7) {
        if (v4 == 6 * v5) {
            if (v5 <= 4) {
                v5 = 4;
            }

            v4 = 6 * v5;
        } else {
            if (v4 <= 4) {
                v4 = 4;
            }

            if (v5 <= 4) {
                v5 = 4;
            }
        }
    }

    uint32_t size;

    if (fourCC == 9) {
        uint32_t v6 = v5 * v4;
        uint32_t v7 = v5 * v4 >> 2;

        if (v7 < 1) {
            v7 = 1;
        }

        size = v7 + 2 * v6;
    } else {
        uint32_t v9 = GetBitDepth(fourCC);

        size = (v4 * v5 * v9) >> 3;
    }

    return size;
}

void FillInSolidTexture(const CImVector& color, CTexture* texture) {
    // Treat the value of color as a nonsense pointer to ensure the value remains available
    // when GxuUpdateSingleColorTexture is called
    void* userArg = reinterpret_cast<CImVector*>(color.value);

    CGxTexFlags gxTexFlags = CGxTexFlags(GxTex_Linear, 0, 0, 0, 0, 0, 1);

    texture->gxTex = TextureAllocGxTex(
        GxTex_2d,
        8,
        8,
        0,
        GxTex_Argb8888,
        gxTexFlags,
        userArg,
        GxuUpdateSingleColorTexture,
        GxTex_Argb8888
    );

    if (color.a < 0xFE) {
        texture->flags &= ~0x1;
    } else {
        texture->flags |= 0x1;
    }

    texture->dataFormat = GxTex_Argb8888;
    texture->gxTexFormat = GxTex_Argb8888;
    texture->gxTexTarget = GxTex_2d;
    texture->gxWidth = 8;
    texture->gxHeight = 8;
    texture->gxTexFlags = CGxTexFlags(GxTex_Linear, 0, 0, 0, 0, 0, 1);

    SStrCopy(texture->filename, "SolidTexture", STORM_MAX_PATH);
}

uint32_t GetBitDepth(uint32_t fourCC) {
    switch (fourCC) {
        case 0:
            return 4;

        case 1:
        case 6:
        case 7:
            return 8;

        case 2:
            return 32;

        case 3:
        case 4:
        case 5:
            return 16;

        default:
            return 0;
    }
}

uint32_t GxCalcTexelStrideInBytes(EGxTexFormat format, uint32_t width) {
    static uint16_t word9F103C[] = {
        0,      // GxTex_Unknown
        32,     // GxTex_Abgr8888
        32,     // GxTex_Argb8888
        16,     // GxTex_Argb4444
        16,     // GxTex_Argb1555
        16,     // GxTex_Rgb565
        4,      // GxTex_Dxt1
        8,      // GxTex_Dxt3
        8,      // GxTex_Dxt5
        16,     // GxTex_Uv88
        32,     // GxTex_Gr1616F
        32,     // GxTex_R32F
        32,     // GxTex_D24X8
        0       // GxTexFormats_Last
    };

    static uint16_t word9F1058[] = {
        0,      // GxTex_Unknown
        0,      // GxTex_Abgr8888
        0,      // GxTex_Argb8888
        0,      // GxTex_Argb4444
        0,      // GxTex_Argb1555
        0,      // GxTex_Rgb565
        8,      // GxTex_Dxt1
        16,     // GxTex_Dxt3
        16,     // GxTex_Dxt5
        0,      // GxTex_Uv88
        0,      // GxTex_Gr1616F
        0,      // GxTex_R32F
        0,      // GxTex_D24X8
        0       // GxTexFormats_Last
    };

    if (format == GxTex_Dxt1 || format == GxTex_Dxt3 || format == GxTex_Dxt5) {
        uint32_t v11 = (width >> 2) * word9F1058[format];
        return std::max(v11, static_cast<uint32_t>(word9F1058[format]));
    } else {
        return width * word9F103C[format] >> 3;
    }
}

int32_t GxTexCreate(const CGxTexParms& parms, CGxTex*& texId) {
    return GxTexCreate(
        parms.target,
        parms.width,
        parms.height,
        parms.depth,
        parms.format,
        parms.dataFormat,
        parms.flags,
        parms.userArg,
        parms.userFunc,
        "",
        texId
    );
}

int32_t GxTexCreate(EGxTexTarget target, uint32_t width, uint32_t height, uint32_t depth, EGxTexFormat format, EGxTexFormat dataFormat, CGxTexFlags flags, void* userArg, TEXTURE_CALLBACK* userFunc, const char* name, CGxTex*& texId) {
    texId = nullptr;

    STORM_ASSERT(target <= GxTexTargets_Last);
    STORM_ASSERT(GxCaps().m_texTarget[target] == 1);
    STORM_ASSERT(width >= 8);
    STORM_ASSERT(height >= 8);
    STORM_ASSERT(width <= GxCaps().m_texMaxSize[target]);
    STORM_ASSERT(height <= GxCaps().m_texMaxSize[target]);
    STORM_ASSERT((target != GxTex_Rectangle && target != GxTex_NonPow2) ? (width & (width - 1)) == 0 : 1);
    STORM_ASSERT((target != GxTex_Rectangle && target != GxTex_NonPow2) ? (height & (height - 1)) == 0 : 1);
    STORM_ASSERT((target == GxTex_Rectangle) ? flags.m_filter <= GxTex_Linear : 1);
    STORM_ASSERT(format <= GxTexFormats_Last);
    STORM_ASSERT((flags.m_generateMipMaps) ? (GxCaps().m_generateMipMaps && !(format >= GxTex_Dxt1 && format <= GxTex_Dxt5)) : 1);
    STORM_ASSERT((flags.m_filter == GxTex_Anisotropic) ? GxCaps().m_texFilterAnisotropic : 1);
    STORM_ASSERT(dataFormat <= GxTexFormats_Last);
    STORM_ASSERT(userFunc != nullptr);

    return g_theGxDevicePtr->TexCreate(
        target,
        width,
        height,
        depth,
        format,
        dataFormat,
        flags,
        userArg,
        userFunc,
        name,
        texId
    );
}

int32_t GxTexCreate(uint32_t width, uint32_t height, EGxTexFormat format, CGxTexFlags flags, void* userArg, void (*userFunc)(EGxTexCommand, uint32_t, uint32_t, uint32_t, uint32_t, void*, uint32_t&, const void*&), CGxTex*& texId) {
    return GxTexCreate(
        GxTex_2d,
        width,
        height,
        0,
        format,
        format,
        flags,
        userArg,
        userFunc,
        "Unknown",
        texId
    );
}

void GxTexDestroy(CGxTex* texId) {
    g_theGxDevicePtr->TexDestroy(texId);
}

void GxTexParameters(const CGxTex* texId, CGxTexParms& parms) {
    // TODO
}

bool GxTexReusable(CGxTexParms& parms) {
    // TODO

    return false;
}

void GxTexSetWrap(CGxTex* texId, EGxTexWrapMode wrapU, EGxTexWrapMode wrapV) {
    g_theGxDevicePtr->TexSetWrap(texId, wrapU, wrapV);
}

int32_t ReloadMips(const char* filename, uint32_t a2, MipBits*& mipBits) {
    // TODO

    return 0;
}

void TextureFreeGxTex(CGxTex* texId) {
    STORM_ASSERT(texId);

    CGxTexParms gxTexParms;
    GxTexParameters(texId, gxTexParms);

    if (GxTexReusable(gxTexParms)) {
        // TODO

        return;
    }

    GxTexDestroy(texId);
}

CGxTex* TextureAllocGxTex(EGxTexTarget target, uint32_t width, uint32_t height, uint32_t depth, EGxTexFormat format, CGxTexFlags flags, void* userArg, TEXTURE_CALLBACK* userFunc, EGxTexFormat dataFormat) {
    CGxTexParms gxTexParms;

    gxTexParms.height = height;
    gxTexParms.depth = depth;
    gxTexParms.target = target;
    gxTexParms.dataFormat = dataFormat;
    gxTexParms.userArg = userArg;
    gxTexParms.format = format;
    gxTexParms.width = width;
    gxTexParms.userFunc = userFunc;
    gxTexParms.flags = flags;
    gxTexParms.flags.m_generateMipMaps = 0;

    CGxTexParms gxTexParms2;

    if (!GxTexReusable(gxTexParms) || width > 512 || height > 512) {
        CGxTex* texture = nullptr;
        memcpy(&gxTexParms2, &gxTexParms, sizeof(gxTexParms2));
        GxTexCreate(gxTexParms2, texture);

        return texture;
    }

    uint32_t v9 = width >> 5;
    uint32_t v10 = height >> 5;

    for (int32_t i = 0; !(v9 & 1); i++) {
        v9 >>= 1;
    }

    for (int32_t j = 0; !(v10 & 1); j++) {
        v10 >>= 1;
    }

    // TODO

    return nullptr;
}

MipBits* TextureAllocMippedImg(PIXEL_FORMAT format, uint32_t width, uint32_t height) {
    // TODO: optimizations
    // MipBits cache
    // Free list

    return MippedImgAllocA(format, width, height, __FILE__, __LINE__);
}

void GxTexUpdate(CGxTex* texId, int32_t minX, int32_t minY, int32_t maxX, int32_t maxY, int32_t immediate) {
    CiRect rect = { minY, minX, maxY, maxX };
    GxTexUpdate(texId, rect, immediate);
}

void GxTexUpdate(CGxTex* texId, CiRect& updateRect, int32_t immediate) {
    g_theGxDevicePtr->TexMarkForUpdate(texId, updateRect, immediate);
}

void GxuUpdateSingleColorTexture(EGxTexCommand cmd, uint32_t w, uint32_t h, uint32_t d, uint32_t mipLevel, void* userArg, uint32_t& texelStrideInBytes, const void*& texels) {
    static uint8_t image[256] = { 0 };

    switch (cmd) {
        case GxTex_Lock: {
            // Treat the userArg pointer as the literal color to use while filling the texture
            uint32_t color = reinterpret_cast<uintptr_t>(userArg);

            for (int32_t i = 0; i < sizeof(image) / sizeof(color); i++) {
                reinterpret_cast<uint32_t*>(image)[i] = color;
            }

            return;
        }

        case GxTex_Latch: {
            texelStrideInBytes = 4 * w;
            texels = image;

            return;
        }

        default:
            return;
    }
}

void GetDefaultTexture(uint32_t height, uint32_t width) {
    // TODO
}

void GetTextureFormats(PIXEL_FORMAT* pixFormat, EGxTexFormat* gxTexFormat, PIXEL_FORMAT preferredFormat, int32_t alphaBits) {
    switch (preferredFormat) {
        case PIXEL_DXT1:
            if (GxCaps().m_texFmt[GxTex_Dxt1]) {
                *gxTexFormat = GxTex_Dxt1;
                *pixFormat = PIXEL_DXT1;
            } else if (alphaBits) {
                *gxTexFormat = GxTex_Argb1555;
                *pixFormat = PIXEL_ARGB1555;;
            } else {
                *gxTexFormat = GxTex_Rgb565;
                *pixFormat = PIXEL_RGB565;
            }

            break;

        case PIXEL_DXT3:
            if (GxCaps().m_texFmt[GxTex_Dxt3]) {
                *gxTexFormat = GxTex_Dxt3;
                *pixFormat = PIXEL_DXT3;
            } else {
                *gxTexFormat = GxTex_Argb4444;
                *pixFormat = PIXEL_ARGB4444;
            }

            break;

        case PIXEL_ARGB8888:
            *gxTexFormat = GxTex_Argb8888;
            *pixFormat = PIXEL_ARGB8888;

            break;

        case PIXEL_ARGB1555:
            *gxTexFormat = GxTex_Argb1555;
            *pixFormat = PIXEL_ARGB8888;

            break;

        case PIXEL_ARGB4444:
            *gxTexFormat = GxTex_Argb4444;
            *pixFormat = PIXEL_ARGB8888;

            break;

        case PIXEL_RGB565:
            *gxTexFormat = GxTex_Rgb565;
            *pixFormat = PIXEL_ARGB8888;

            break;

        case PIXEL_DXT5:
            if (GxCaps().m_texFmt[GxTex_Dxt5]) {
                *gxTexFormat = GxTex_Dxt5;
                *pixFormat = PIXEL_DXT5;
            } else {
                *gxTexFormat = GxTex_Argb4444;
                *pixFormat = PIXEL_ARGB4444;
            }

            break;

        case PIXEL_UNSPECIFIED:
            if (alphaBits > 0) {
                if (alphaBits == 1) {
                    *gxTexFormat = GxTex_Argb1555;
                    *pixFormat = PIXEL_ARGB8888;
                } else if (alphaBits == 4) {
                    *gxTexFormat = GxTex_Argb4444;
                    *pixFormat = PIXEL_ARGB8888;
                } else {
                    *gxTexFormat = GxTex_Argb8888;
                    *pixFormat = PIXEL_ARGB8888;
                }
            } else {
                *gxTexFormat = GxTex_Rgb565;
                *pixFormat = PIXEL_ARGB8888;
            }

            break;

        default:
            break;
    }
}

MipBits* MippedImgAllocA(uint32_t fourCC, uint32_t width, uint32_t height, const char* fileName, int32_t lineNumber) {
    uint32_t levelCount = CalcLevelCount(width, height);
    uint32_t levelDataSize = CalcLevelOffset(levelCount, width, height, fourCC);

    MipBits* images = reinterpret_cast<MipBits*>(SMemAlloc(levelDataSize + sizeof(void*) * levelCount + 16, fileName, lineNumber, 0));

    uintptr_t v10 = (reinterpret_cast<uintptr_t>(images) + sizeof(void*) * levelCount + 15) & static_cast<uintptr_t>(-sizeof(void*));
    uintptr_t offset = v10 - reinterpret_cast<uintptr_t>(images);

    MipBits** ptr = reinterpret_cast<MipBits**>(images);

    for (int32_t level = 0; level < levelCount; level++) {
        ptr[level] = images + offset;
        offset += CalcLevelSize(level, width, height, fourCC);
    }

    return images;
}

uint32_t MippedImgCalcSize(uint32_t fourCC, uint32_t width, uint32_t height) {
    uint32_t levelCount = CalcLevelCount(width, height);
    uint32_t levelDataSize = CalcLevelOffset(levelCount, width, height, fourCC);
    uint32_t imgSize = levelDataSize + (sizeof(void*) * levelCount);

    return imgSize;
}

void MippedImgSet(uint32_t fourCC, uint32_t width, uint32_t height, MipBits* bits) {
    uint32_t levelDataSize;
    uint32_t offset = 0;

    auto levelCount = CalcLevelCount(width, height);

    for (int32_t level = 0; level < levelCount; level++) {
        bits->mip[level] = reinterpret_cast<C4Pixel*>(reinterpret_cast<uintptr_t>(bits->mip[levelCount]) + offset);
        levelDataSize = CalcLevelSize(level, width, height, fourCC);
        offset += levelDataSize;
    }
}

// TODO
// - order: width, height or height, width?
void RequestImageDimensions(uint32_t* width, uint32_t* height, uint32_t* bestMip) {
    CGxCaps systemCaps;
    memcpy(&systemCaps, &GxCaps(), sizeof(systemCaps));

    auto maxTextureSize = systemCaps.m_texMaxSize[GxTex_2d];

    if (maxTextureSize) {
        while (*height > maxTextureSize || *width > maxTextureSize) {
            *height >>= 1;
            *width >>= 1;

            ++*bestMip;

            if (!*height) {
                *height = 1;
            }

            if (!*width) {
                *width = 1;
            }
        }
    } else {
        // TODO
        // SErrSetLastError(0x57u);
    }
}

void UpdateBlpTextureAsync(EGxTexCommand cmd, uint32_t w, uint32_t h, uint32_t d, uint32_t mipLevel, void* userArg, uint32_t& texelStrideInBytes, const void*& texels) {
    CTexture* texture = static_cast<CTexture*>(userArg);

    switch (cmd) {
        case GxTex_Lock:
            if (Texture::s_mipBitsValid) {
                return;
            }

            if (!ReloadMips(texture->filename, texture->flags & 0x2, Texture::s_mipBits)) {
                GetDefaultTexture(h, w);

                // TODO
                // GetGlobalStatusObj()->Add(
                //     STATUS_ERROR,
                //     "Texture %s not loaded -- replaced with default.\n",
                //     texture->filename
                // );
            }

            return;

        case GxTex_Latch:
            texelStrideInBytes = GxCalcTexelStrideInBytes(texture->dataFormat, w);

            if (texture->gxTexTarget == GxTex_CubeMap) {
                // TODO
            } else {
                texels = reinterpret_cast<MipBits**>(Texture::s_mipBits)[mipLevel];
            }

            return;

        default:
            return;
    }
}

int32_t PumpBlpTextureAsync(CTexture* texture, void* buf) {
    CBLPFile image;

    if (!image.Source(buf)) {
        texture->loadStatus.Add(
            STATUS_FATAL,
            "BLP Texture failure: \"%s\" invalid file version\n",
            texture->filename
        );

        image.Close();

        return 0;
    }

    if (texture->flags & 0x4 && !(image.m_header.hasMips & 0x10)) {
        texture->flags &= 0xFFFB;
    }

    texture->alphaBits = image.m_header.alphaSize;

    if (image.m_header.alphaSize == 0) {
        texture->flags |= 0x1;
    }

    uint32_t width = image.m_header.width;
    uint32_t height = image.m_header.height;
    uint32_t bestMip = 0;

    RequestImageDimensions(&width, &height, &bestMip);

    texture->bestMip = bestMip;

    PIXEL_FORMAT pixFormat;
    EGxTexFormat gxTexFormat;
    PIXEL_FORMAT preferredFormat = static_cast<PIXEL_FORMAT>(image.m_header.preferredFormat);
    int32_t alphaSize = image.m_header.alphaSize;

    GetTextureFormats(&pixFormat, &gxTexFormat, preferredFormat, alphaSize);

    int32_t mipLevel = texture->bestMip;

    Texture::s_mipBitsValid = 1;

    if (!image.LockChain2(texture->filename, pixFormat, Texture::s_mipBits, mipLevel, 1)) {
        Texture::s_mipBitsValid = 0;

        texture->loadStatus.Add(
            STATUS_FATAL,
            "BLP Texture failure: \"%s\" decompression failed.\n",
            texture->filename
        );

        image.Close();

        return 0;
    }

    uint32_t gxHeight = height;
    uint32_t gxWidth = width;
    EGxTexTarget gxTexTarget = GxTex_2d;

    // Check if texture dimensions indicate cube mapping
    if (width == 6 * height) {
        gxHeight = height;
        gxWidth = width / 6u;
        gxTexTarget = GxTex_CubeMap;
    }

    texture->gxHeight = gxHeight;
    texture->gxWidth = gxWidth;
    texture->gxTexTarget = gxTexTarget;

    EGxTexFormat dataFormat = Texture::s_pixelFormatToGxTexFormat[pixFormat];
    texture->dataFormat = dataFormat;
    texture->gxTexFormat = gxTexFormat;

    if (gxWidth < 256 && image.m_numLevels == 1) {
        if (!texture->gxTexFlags.m_generateMipMaps) {
            texture->gxTexFlags.m_filter = 0;
        }
    }

    if (texture->flags & 0x4) {
        // TODO

        // CTextureAtlas* atlas = CTextureAtlas::Get(v2);

        // texture->atlas = atlas;

        // if (atlas) {
        //    sub_4B50D0(atlas, v2);
        // } else {
        //    texture->flags &= 0xFFFBu;
        // }
    }

    if (!texture->atlas) {
        if (texture->gxTex) {
            TextureFreeGxTex(texture->gxTex);
            texture->gxTex = nullptr;
        }

        CGxTex* gxTex = TextureAllocGxTex(
            texture->gxTexTarget,
            texture->gxWidth,
            texture->gxHeight,
            0,
            texture->gxTexFormat,
            texture->gxTexFlags,
            texture,
            &UpdateBlpTextureAsync,
            texture->dataFormat
        );

        texture->gxTex = gxTex;

        if (!gxTex) {
            Texture::s_mipBitsValid = 0;

            texture->loadStatus.Add(
                STATUS_FATAL,
                "BLP Texture failure: \"%s\" allocating %dx%d texture failed.\n",
                texture->filename,
                gxWidth,
                gxHeight
            );

            image.Close();

            return 0;
        }

        GxTexUpdate(gxTex, 0, 0, gxWidth, gxHeight, 1);
    }

    Texture::s_mipBitsValid = 0;

    image.Close();

    return 1;
}

int32_t FindSubstitution(const char* a1, char* a2) {
    // TODO

    return 0;
}

CTexture* CreateBlpAsync(char* fileExt, char* fileName, int32_t createFlags, CGxTexFlags texFlags) {
    // TODO

    return nullptr;
}

CTexture* CreateBlpSync(int32_t createFlags, char* fileName, char* fileExt, CGxTexFlags texFlags) {
    SFile* file = nullptr;

    // TODO
    // SErrSetLastError(0);

    if (!SFile::OpenEx(nullptr, fileName, (createFlags >> 1) & 1, &file)) {
        // TODO
        // if (!sub_7717E0()) {
        //     SErrSetLastError(2u);
        // }

        return nullptr;
    }

    if (!file) {
        return nullptr;
    }

    auto m = SMemAlloc(sizeof(CTexture), "HTEXTURE", -2, 0x0);
    auto texture = new (m) CTexture();

    texture->gxTexFlags = texFlags;

    if (createFlags & 0x2) {
        texture->flags |= 0x2;
    }

    // TODO
    // if (createFlags & 0x4 && dword_B49C84) {
    //     texture->flags |= 0x4;
    // }

    if (fileExt) {
        *fileExt = 0;
    }

    SStrCopy(texture->filename, fileName, 0x7FFFFFFF);

    size_t fileSize = SFile::GetFileSize(file, 0);

    void* buf = ALLOC(fileSize);

    if (!SFile::Read(file, buf, fileSize, nullptr, nullptr, nullptr)) {
        // nullsub_3();
    }

    if (!PumpBlpTextureAsync(texture, buf)) {
        FillInSolidTexture(CRAPPY_GREEN, texture);
    }

    SFile::Close(file);

    FREE(buf);

    return texture;
}

HTEXTURE CreateBlpTexture(char* fileExt, char* fileName, int32_t createFlags, CGxTexFlags texFlags) {
    if (fileExt) {
        SStrCopy(fileExt, ".blp", 0x7FFFFFFF);
    }

    char* fileExtFinal = fileExt;
    char* fileNameFinal = fileName;

    char fileNameSub[260];

    if (FindSubstitution(fileNameSub, fileName)) {
        fileNameFinal = fileNameSub;
        fileExtFinal = OsPathFindExtensionWithDot(fileNameSub);
    }

    CTexture* texture;

    if (Texture::s_createBlpAsync) {
        texture = CreateBlpAsync(fileExtFinal, fileNameFinal, createFlags, texFlags);
    } else {
        texture = CreateBlpSync(createFlags, fileNameFinal, fileExtFinal, texFlags);
    }

    HTEXTURE handle = texture ? HandleCreate(texture) : nullptr;

    return handle;
}

HTEXTURE CreateTgaTexture(const char* fileName, const char* fileExt, int32_t a3, CGxTexFlags texFlags, CStatus* status) {
    // TODO

    return nullptr;
}

HTEXTURE TextureCacheGetTexture(char* fileName, char* fileExt, CGxTexFlags texFlags) {
    if (fileExt) {
        *fileExt = '\0';
    }

    auto hashval = SStrHashHT(fileName);
    HASHKEY_TEXTUREFILE key = { fileName, texFlags };

    auto texture = Texture::s_textureCache.Ptr(hashval, key);

    if (fileExt) {
        *fileExt = '.';
    }

    if (texture) {
        return HandleCreate(texture);
    }

    return nullptr;
}

HTEXTURE TextureCacheGetTexture(const CImVector& color) {
    // TODO

    return nullptr;
}

void TextureCacheNewTexture(CTexture* texture, CGxTexFlags texFlags) {
    auto hashval = SStrHashHT(texture->filename);
    HASHKEY_TEXTUREFILE key = { texture->filename, texFlags };

    Texture::s_textureCache.Insert(texture, hashval, key);
}

void TextureCacheNewTexture(CTexture* texture, const CImVector& color) {
    // TODO
}

HTEXTURE TextureCreate(const char* fileName, CGxTexFlags texFlags, CStatus* status, int32_t createFlags) {
    STORM_ASSERT(fileName);
    STORM_ASSERT(*fileName);
    STORM_ASSERT(status);

    if (createFlags & 0x1) {
        texFlags.m_filter = CTexture::s_filterMode;
    }

    if (texFlags.m_filter == 5) {
        texFlags.m_maxAnisotropy = CTexture::s_maxAnisotropy;
    } else {
        texFlags.m_maxAnisotropy = 1;
    }

    int32_t v16 = 2;
    int32_t v8 = 1;

    char tmpFileName[260];

    SStrCopy(tmpFileName, fileName, 260);

    char* fileExt = OsPathFindExtensionWithDot(tmpFileName);

    char* v10 = fileExt;

    if (createFlags & 0x8) {
        if (fileExt) {
            v16 = 1;
            v8 = SStrCmpI(fileExt, ".blp", 0x7FFFFFFFu) == 0;
            v10 = 0;
        }
    }

    HTEXTURE texture = TextureCacheGetTexture(tmpFileName, v10, texFlags);

    if (texture) {
        return texture;
    }

    for (int32_t i = 0; i < v16; ++i) {
        if (v8) {
            if (v8 != 1) {
                v8 = (v8 + 1) % 2;
                continue;
            }

            texture = CreateBlpTexture(v10, tmpFileName, createFlags, texFlags);
        } else {
            texture = CreateTgaTexture(tmpFileName, v10, createFlags & 0x2, texFlags, status);
        }

        if (texture) {
            TextureCacheNewTexture(TextureGetTexturePtr(texture), texFlags);
            return texture;
        }

        v8 = (v8 + 1) % 2;
    }

    // TODO
    // FileError(status, "texture", fileName);

    return TextureCreateSolid(CRAPPY_GREEN);

    return nullptr;
}

HTEXTURE TextureCreate(uint32_t width, uint32_t height, EGxTexFormat format, EGxTexFormat dataFormat, CGxTexFlags texFlags, void* userArg, TEXTURE_CALLBACK* userFunc, const char* a8, int32_t a9) {
    return TextureCreate(
        GxTex_2d,
        width,
        height,
        0,
        format,
        dataFormat,
        texFlags,
        userArg,
        userFunc,
        a8,
        a9
    );
}

HTEXTURE TextureCreate(EGxTexTarget target, uint32_t width, uint32_t height, uint32_t depth, EGxTexFormat format, EGxTexFormat dataFormat, CGxTexFlags texFlags, void* userArg, TEXTURE_CALLBACK* userFunc, const char* a10, int32_t a11) {
    auto texture = NEW(CTexture);

    if (a11) {
        texFlags.m_filter = CTexture::s_filterMode;
    }

    texFlags.m_maxAnisotropy = texFlags.m_filter == GxTex_Anisotropic ? CTexture::s_maxAnisotropy : 1;

    texture->gxTex = TextureAllocGxTex(target, width, height, depth, format, texFlags, userArg, userFunc, dataFormat);
    texture->dataFormat = dataFormat;
    texture->gxWidth = width;
    texture->gxHeight = height;
    texture->gxTexFormat = format;
    texture->gxTexTarget = target;
    texture->gxTexFlags = texFlags;
    texture->asyncObject = nullptr;

    const char* filename = a10 ? a10 : "UniqueTexture";
    SStrCopy(texture->filename, filename, STORM_MAX_PATH);

    return HandleCreate(texture);
}

HTEXTURE TextureCreateSolid(const CImVector& color) {
    HTEXTURE textureHandle = TextureCacheGetTexture(color);

    if (textureHandle) {
        return textureHandle;
    }

    auto texture = NEW(CTexture);

    FillInSolidTexture(color, texture);
    textureHandle = HandleCreate(texture);
    TextureCacheNewTexture(texture, color);

    return textureHandle;
}

int32_t TextureGetDimensions(CTexture* texture, uint32_t* width, uint32_t* height, int32_t force) {
    if (texture->asyncObject) {
        if (!force) {
            return 0;
        }

        // TODO
    }

    if (width) {
        *width = texture->gxWidth;
    }

    if (height) {
        *height = texture->gxHeight;
    }

    return 1;
}

int32_t TextureGetDimensions(HTEXTURE textureHandle, uint32_t* width, uint32_t* height, int32_t force) {
    return TextureGetDimensions(TextureGetTexturePtr(textureHandle), width, height, force);
}

CGxTex* TextureGetGxTex(CTexture* texture, int32_t a2, CStatus* status) {
    STORM_ASSERT(texture);

    if (texture->flags & 0x4) {
        if (texture->asyncObject) {
            if (a2 != 1 && (a2 != 2 || texture->asyncObject->char24)) {
                TextureIncreasePriority(texture);
                return nullptr;
            }

            AsyncTextureWait(texture);

            if (status) {
                status->Add(texture->loadStatus);
            }
        }

        if (texture->atlas) {
            // TODO
            // atlas->Reload();

            // TODO
            // - pull texture out of atlas

            return nullptr;
        }
    }

    if (texture->asyncObject) {
        TextureIncreasePriority(texture);
    }

    if (!texture->gxTex) {
        if (a2 != 1 && (a2 != 2 || texture->asyncObject->char24)) {
            return nullptr;
        }

        AsyncTextureWait(texture);

        if (status) {
            status->Add(texture->loadStatus);
        }
    }

    return texture->gxTex;
}

CGxTex* TextureGetGxTex(HTEXTURE handle, int32_t a2, CStatus* status) {
    return TextureGetGxTex(reinterpret_cast<CTexture*>(handle), a2, status);
}

CTexture* TextureGetTexturePtr(HTEXTURE handle) {
    return reinterpret_cast<CTexture*>(handle);
}

void TextureIncreasePriority(CTexture* texture) {
    // TODO
}

void TextureInitialize() {
    uint32_t v0 = MippedImgCalcSize(2, 1024, 1024);
    Texture::s_mipBits = reinterpret_cast<MipBits*>(SMemAlloc(v0, __FILE__, __LINE__, 0));

    // TODO
    // - rest of function
}

int32_t TextureIsSame(HTEXTURE textureHandle, const char* fileName) {
    char buf[STORM_MAX_PATH];
    uint32_t len = SStrCopy(buf, fileName, sizeof(buf));

    if (len >= 4 && buf[len - 4] == '.') {
        len -= 4;
    }
    auto v3 = &buf[len];
    if (*v3 == '.') {
        SStrLower(v3 + 1);
        *v3 = '\0';
    }

    STORM_ASSERT(textureHandle);

    return SStrCmpI(buf, TextureGetTexturePtr(textureHandle)->filename, sizeof(buf)) == 0;
}

int32_t TextureCalcMipCount(uint32_t width, uint32_t height) {
    int32_t mips = 1;

    while (width > 1 || height > 1) {
        mips++;

        width >>= 1;
        if (!width) {
            width = 1;
        }

        height >>= 1;
        if (!height) {
            height = 1;
        }
    }

    return mips;
}

static void RemoveExtension(char* path) {
    auto dot = SStrChrR(path, '.');
    if (dot) {
        *dot = '\0';
    }
}

static void GenerateMipMask(const char* mipZeroName, char* mipMask) {
    SStrCopy(mipMask, mipZeroName, STORM_MAX_PATH);
    RemoveExtension(mipMask);
    SStrPack(mipMask, "_mip%d.tga", STORM_MAX_PATH);
}

static uint32_t LoadPredrawnMips(const CTgaFile& mipZero, const char* filemask, int32_t a3, MipBits* buffer) {
    STORM_ASSERT(filemask);
    STORM_ASSERT(buffer);

    char pathName[STORM_MAX_PATH];

    auto mipZeroWidth = mipZero.Width();
    auto mipZeroHeight = mipZero.Height();

    uint32_t index = 1;

    auto levels = TextureCalcMipCount(mipZeroWidth, mipZeroHeight);
    STORM_ASSERT(levels);

    levels--;

    auto width = mipZeroWidth >> 1;
    auto height = mipZeroHeight >> 1;

    if (levels) {
        auto v23 = a3 != 0;
        while (1) {
            levels--;
            SStrPrintf(pathName, STORM_MAX_PATH, filemask, index);
            if (!SFile::FileExistsEx(pathName, v23)) {
                break;
            }

            CTgaFile mipTga;

            if (!mipTga.Open(pathName, a3) || width != mipTga.Width() || height != mipTga.Height()) {
                mipTga.Close();
                return index;
            }

            if (!mipTga.LoadImageData(2)) {
                mipTga.Close();
                return index;
            }

            if (mipTga.AlphaBits() == 0) {
                mipTga.AddAlphaChannel(nullptr);
            }

            mipTga.SetTopDown(1);

            auto mipTgaPixel = mipTga.ImageTGA32Pixel();

            // TODO: suppress UBsan warnings
            auto bufferPixel = buffer->mip[index];

            index++;

            for (auto i = width * height; i != 0; i--) {
                bufferPixel->a = mipTgaPixel->a;
                bufferPixel->r = mipTgaPixel->r;
                bufferPixel->g = mipTgaPixel->g;
                bufferPixel->b = mipTgaPixel->b;

                bufferPixel++;
                mipTgaPixel++;
            }

            if (width > 1) {
                width >>= 1;
            }

            if (height > 1) {
                height >>= 1;
            }

            mipTga.Close();

            if (levels == 0) {
                return index;
            }

        }
    }

    return index;
}

void FullShrink(C4Pixel* dest, uint32_t destWidth, uint32_t destHeight, C4Pixel* source, uint32_t sourceWidth, uint32_t sourceHeight) {
    auto xScale = sourceWidth / destWidth;
    auto yScale = sourceHeight / destHeight;

    C4LargePixel unweighted;
    C4LargePixel weighted;
    C4Pixel result;

    STORM_ASSERT(destWidth * xScale == sourceWidth);
    STORM_ASSERT(destHeight * yScale == sourceHeight);

    for (auto y = destHeight; y != 0; y--) {
        for (auto x = destWidth; x != 0; x--) {
            memset(&weighted, 0, sizeof(weighted));
            memset(&unweighted, 0, sizeof(unweighted));

            auto currSource = source;

            for (uint32_t i = yScale; i != 0; i--) {
                auto pixel = currSource;

                for (uint32_t j = xScale; j != 0; j--) {
                    weighted.a += pixel->a;
                    weighted.r += pixel->r * pixel->a;
                    weighted.g += pixel->g * pixel->a;
                    weighted.b += pixel->b * pixel->a;

                    unweighted.a++;
                    unweighted.r += pixel->r;
                    unweighted.g += pixel->g;
                    unweighted.b += pixel->b;

                    pixel++;
                }

                currSource += sourceWidth;
            }

            if (weighted.a) {
                STORM_ASSERT(xScale * yScale);

                result.r = weighted.r / weighted.a;
                result.g = weighted.g / weighted.a;
                result.b = weighted.b / weighted.a;
                result.a = weighted.a / (xScale * yScale);
            } else {
                result.r = unweighted.r / unweighted.a;
                result.g = unweighted.g / unweighted.a;
                result.b = unweighted.b / unweighted.a;
                result.a = 0;
            }

            *dest++ = result;
            source += xScale;
        }

        source += (yScale - 1) * sourceWidth;
    }
}

void TextureGenerateMips(uint32_t width, uint32_t height, uint32_t levelsProvided, uint32_t levelsDesired, MipBits* levelBits) {
    uint32_t last_good_level = 0;

    auto mipHeight = height;
    auto mipWidth = width;

    if (levelsDesired > 1) {
        for (uint32_t i = 0; i < levelsDesired; i++) {
            mipWidth = mipWidth >>= 1 != 0 ? mipWidth : 1;
            mipHeight = mipHeight >>= 1 != 0 ? mipHeight : 1;

            if (i >= levelsProvided) {
                FullShrink(levelBits->mip[i], mipWidth, mipHeight, levelBits->mip[last_good_level], width, height);
            }
        }
    }
}

int32_t LoadTgaMips(char* ext, const char* filename, int32_t a3, MipBits*& mipBits, uint32_t* width, uint32_t* height, EGxTexFormat* texFormat, int32_t* isOpaque, uint32_t* alphaBits, PIXEL_FORMAT* dataFormat) {
    STORM_ASSERT(filename);

    if (ext) {
        ext[0] = '.';
        ext[1] = 't';
        ext[2] = 'g';
        ext[3] = 'a';
        ext[4] = '\0';
    }

    CTgaFile texFile;

    if (!texFile.Open(filename, a3)) {
        texFile.Close();
        return 0;
    }

    if (isOpaque) {
        *isOpaque = texFile.AlphaBits() == 0;
    }

    if (!texFile.LoadImageData(3)) {
        texFile.Close();
        return 0;
    }

    texFile.SetTopDown(1);

    auto mipCount = TextureCalcMipCount(texFile.Width(), texFile.Height());

    if (mipBits) {
        MippedImgSet(2, texFile.Width(), texFile.Height(), mipBits);
    } else {
        mipBits = TextureAllocMippedImg(PIXEL_ARGB8888, texFile.Width(), texFile.Height());
    }

    auto size = texFile.Size();

    if (size) {
        auto tga32Pixels = texFile.ImageTGA32Pixel();
        auto mipPixels = mipBits->mip[0];

        for (int32_t i = 0; i < size; i++) {
            auto& mipPixel = mipPixels[i];
            auto& tga32Pixel = tga32Pixels[i];

            mipPixel.b = tga32Pixel.b;
            mipPixel.g = tga32Pixel.g;
            mipPixel.r = tga32Pixel.r;
            mipPixel.a = tga32Pixel.a;
        }
    }

    texFile.Close();

    char mipFileMask[STORM_MAX_PATH];

    GenerateMipMask(filename, mipFileMask);

    auto predrawnLevels = LoadPredrawnMips(texFile, mipFileMask, a3, mipBits);

    TextureGenerateMips(texFile.Width(), texFile.Height(), predrawnLevels, mipCount, mipBits);

    if (width) {
        *width = texFile.Width();
    }

    if (height) {
        *height = texFile.Height();
    }

    if (texFormat) {
        *texFormat = GxTex_Argb8888;
    }

    if (alphaBits) {
        *alphaBits = texFile.AlphaBits();
    }

    if (dataFormat) {
        *dataFormat = PIXEL_ARGB8888;
    }

    return 1;
}

int32_t LoadBlpMips(char* ext, const char* filename, int32_t a3, MipBits*& mipBits, uint32_t* width, uint32_t* height, int32_t* isOpaque, PIXEL_FORMAT* dataFormat) {
    STORM_ASSERT(filename);

    if (ext) {
        ext[0] = '.';
        ext[1] = 'b';
        ext[2] = 'l';
        ext[3] = 'p';
        ext[4] = '\0';
    }

    uint32_t bestMip;

    CBLPFile texFile;

    if (!texFile.Open(filename, a3)) {
        texFile.Close();
        return 0;
    }

    auto imgWidth = texFile.Width();
    auto imgHeight = texFile.Height();

    PIXEL_FORMAT format;
    if (!dataFormat || (format = *dataFormat, format == PIXEL_UNSPECIFIED)) {
        if (texFile.AlphaBits()) {
            format = texFile.AlphaBits() == 1 ? PIXEL_ARGB1555 : PIXEL_ARGB4444;
        } else {
            format = PIXEL_RGB565;
        }
    }

    auto image = TextureAllocMippedImg(format, imgWidth, imgHeight);

    if (!texFile.LockChain2(filename, format, mipBits, 0, 0)) {
        texFile.Close();
        return 0;
    }

    if (width) {
        *width = imgWidth;
    }

    if (height) {
        *height = imgHeight;
    }

    if (isOpaque) {
        *isOpaque = texFile.AlphaBits() == 0;
    }

    if (dataFormat) {
        *dataFormat = format;
    }

    texFile.Close();

    return 1;
}

MipBits* TextureLoadImage(const char* filename, uint32_t* width, uint32_t* height, PIXEL_FORMAT* dataFormat, int32_t* isOpaque, CStatus* status, uint32_t* alphaBits, int32_t a8) {
    STORM_ASSERT(filename);
    STORM_ASSERT(width);
    STORM_ASSERT(height);

    // OsOutputDebugString("TextureLoadImage() blocking load: %s.\n", filename)

    char loadFileName[STORM_MAX_PATH];

    SStrCopy(loadFileName, filename, STORM_MAX_PATH);

    auto ext = OsPathFindExtensionWithDot(loadFileName);

    *ext = '\0';

    uint32_t imageFormat = IMAGE_FORMAT_BLP;
    MipBits* mipImages = nullptr;

    for (uint32_t i = 0; i < NUM_IMAGE_FORMATS; i++) {
        if (imageFormat == IMAGE_FORMAT_TGA) {
            LoadTgaMips(ext, loadFileName, a8, mipImages, width, height, nullptr, isOpaque, alphaBits, dataFormat);
        } else if (imageFormat == IMAGE_FORMAT_BLP) {
            LoadBlpMips(ext, loadFileName, a8, mipImages, width, height, isOpaque, dataFormat);
        }

        imageFormat++;
        imageFormat %= 2;

        if (mipImages) {
            return mipImages;
        }
    }

    status->Add(STATUS_FATAL, "Error loading texure file \"%s\": unsupported image format\n", filename);
    return nullptr;
}

void TextureFreeMippedImg(MipBits* image, PIXEL_FORMAT format, uint32_t width, uint32_t height) {
    // TODO: mip bits cache free list

    if (image) {
        SMemFree(image, __FILE__, __LINE__, 0x0);
    }
}
