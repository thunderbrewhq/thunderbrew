#include "gx/Texture.hpp"
#include "gx/texture/CBLPFile.hpp"
#include "util/SFile.hpp"
#include "util/Unimplemented.hpp"
#include <cstring>
#include <storm/Error.hpp>
#include <bc/Memory.hpp>

TSGrowableArray<uint8_t> CBLPFile::s_blpFileLoadBuffer;

uint8_t CBLPFile::s_oneBitAlphaLookup[2] = {
    0x00,
    0xFF
};

uint8_t CBLPFile::s_eightBitAlphaLookup[16] = {
    0x00,
    0x11,
    0x22,
    0x33,
    0x44,
    0x55,
    0x66,
    0x77,
    0x88,
    0x99,
    0xAA,
    0xBB,
    0xCC,
    0xDD,
    0xEE,
    0xFF
};

uint32_t CBLPFile::AlphaBits() {
    return this->m_header.alphaSize;
}

uint32_t CBLPFile::Width() {
    return this->m_header.width;
}

uint32_t CBLPFile::Width(uint32_t mipLevel) {
    auto width = this->m_header.width >> mipLevel;
    if (width <= 1) {
        width = 1;
    }
    return width;
}

uint32_t CBLPFile::Height() {
    return this->m_header.height;
}

uint32_t CBLPFile::Height(uint32_t mipLevel) {
    auto height = this->m_header.height >> mipLevel;
    if (height <= 1) {
        height = 1;
    }
    return height;
}

uint32_t CBLPFile::Pixels() {
    return this->Width() * this->Height();
}

uint32_t CBLPFile::Pixels(uint32_t mipLevel) {
    return this->Width(mipLevel) * this->Height(mipLevel);
}

void CBLPFile::Close() {
    this->m_inMemoryImage = nullptr;

    if (this->m_images) {
        SMemFree(this->m_images, __FILE__, __LINE__, 0x0);
    }

    this->m_images = nullptr;
}

MIPS_TYPE CBLPFile::HasMips() {
    return static_cast<MIPS_TYPE>(this->m_header.hasMips);
}

int32_t CBLPFile::IsValidMip(uint32_t level) {
    if (level) {
        if (!(this->HasMips() & 0xF) || level >= this->m_numLevels) {
            return 0;
        }
    }

    return 1;
}

int32_t CBLPFile::GetFormatSize(PIXEL_FORMAT format, uint32_t mipLevel, uint32_t* size, uint32_t* stride) {
    auto width = this->Width(mipLevel);
    auto height = this->Height(mipLevel);

    auto pixels = width * height;

    auto v8 = pixels >> 2;

    if (!v8) {
        v8 = 1;
    }

    switch (format) {
    case PIXEL_ARGB8888:
        *size = 4 * pixels;
        *stride = 4 * width;
        return 1;
    case PIXEL_ARGB1555:
    case PIXEL_ARGB4444:
    case PIXEL_RGB565:
        *size = 2 * pixels;
        *stride = 2 * width;
        return 1;
    case PIXEL_ARGB2565:
        *size = v8 + 2 * pixels;
        *stride = 2 * width;
        return 1;
    default:
        *size = 0;
        *stride = 0;
        return 0;
    }
}

void CBLPFile::DecompPalFastPath(uint8_t* data, void* tempbuffer, uint32_t colorSize) {
    auto bytes = reinterpret_cast<uint8_t*>(tempbuffer);

    for (auto i = colorSize; i; i--) {
        *reinterpret_cast<BlpPalPixel*>(data) = this->m_header.extended.palette[*bytes];
        data[3] = *(bytes + colorSize);
        bytes++;
        data += 4;
    }
}

void CBLPFile::DecompPalARGB8888(uint8_t* data, void* tempbuffer, uint32_t colorSize) {
    auto pixels = data;
    auto bytes = reinterpret_cast<uint8_t*>(tempbuffer);

    auto i = colorSize;
    while (i != 0) {
        *reinterpret_cast<BlpPalPixel*>(pixels) = this->m_header.extended.palette[*bytes];
        pixels[3] = 0xFF;
        pixels += 4;
        bytes++;
        i--;
    }

    auto alphaBits = this->AlphaBits();

    if (alphaBits == 1) {
        auto v14 = colorSize >> 3;

        for (auto a = 0; a < v14; a++) {
            auto byte = bytes[a];
            data[3] = s_oneBitAlphaLookup[byte & 1];
            data[7] = s_oneBitAlphaLookup[(byte >> 1) & 1];
            data[11] = s_oneBitAlphaLookup[(byte >> 2) & 1];
            data[15] = s_oneBitAlphaLookup[(byte >> 3) & 1];
            data[19] = s_oneBitAlphaLookup[(byte >> 4) & 1];
            data[23] = s_oneBitAlphaLookup[(byte >> 5) & 1];
            data[27] = s_oneBitAlphaLookup[(byte >> 6) & 1];
            data[31] = s_oneBitAlphaLookup[(byte >> 7) & 1];

            data += 32;
        }

        auto v20 = colorSize & 7;
        if (v20) {
            auto byte = bytes[v14];
            auto dest = data + 3;
            do {
                *dest = s_oneBitAlphaLookup[byte & 1];
                byte >>= 1;
                dest += 4;
                v20--;
            } while (v20);
        }
    } else if (alphaBits == 4) {
        for (auto i = colorSize >> 1; i; i--) {
            auto byte = *bytes;
            data[3] = s_eightBitAlphaLookup[byte & 0xF];
            data[7] = s_eightBitAlphaLookup[byte >> 4];

            data += 8;
            bytes++;
        }

        if (colorSize & 1) {
            auto byte = *bytes;
            data[3] = s_eightBitAlphaLookup[byte & 0xF];
            return;
        }
    } else if (alphaBits == 8 && colorSize) {
        auto dest = data + 3;
        do {
            *dest = *bytes;
            dest += 4;
            bytes++;
            colorSize--;
        } while (colorSize);
    }
}

void CBLPFile::DecompPalARGB1555DitherFloydSteinberg(uint8_t* data, void* tempbuffer, uint32_t width, uint32_t height) {
    WHOA_UNIMPLEMENTED();
}

void CBLPFile::DecompPalARGB2565DitherFloydSteinberg(uint8_t* data, void* tempbuffer, uint32_t width, uint32_t height) {
    WHOA_UNIMPLEMENTED();
}

void CBLPFile::DecompPalARGB4444DitherFloydSteinberg(uint8_t* data, void* tempbuffer, uint32_t width, uint32_t height) {
    WHOA_UNIMPLEMENTED();
}

void CBLPFile::DecompPalARGB565DitherFloydSteinberg(uint8_t* data, void* tempbuffer, uint32_t width, uint32_t height) {
    WHOA_UNIMPLEMENTED();
}

int32_t CBLPFile::DecompPal(PIXEL_FORMAT format, uint32_t mipLevel, uint8_t* data, void* tempBuffer) {
    switch (format) {
    case PIXEL_ARGB8888:
        if (this->AlphaBits() == 8) {
            this->DecompPalFastPath(data, tempBuffer, this->Pixels(mipLevel));
        } else {
            this->DecompPalARGB8888(data, tempBuffer, this->Pixels(mipLevel));
        }
        return 1;
    case PIXEL_ARGB1555:
        this->DecompPalARGB1555DitherFloydSteinberg(data, tempBuffer, this->Width(mipLevel), this->Height(mipLevel));
        return 1;
    case PIXEL_ARGB4444:
        this->DecompPalARGB4444DitherFloydSteinberg(data, tempBuffer, this->Width(mipLevel), this->Height(mipLevel));
        return 1;
    case PIXEL_RGB565:
        this->DecompPalARGB565DitherFloydSteinberg(data, tempBuffer, this->Width(mipLevel), this->Height(mipLevel));
        return 1;
    case PIXEL_ARGB2565:
        this->DecompPalARGB2565DitherFloydSteinberg(data, tempBuffer, this->Width(mipLevel), this->Height(mipLevel));
        return 1;
    default:
        return 0;
    }
}

int32_t CBLPFile::Lock2(const char* fileName, PIXEL_FORMAT format, uint32_t mipLevel, uint8_t* data, uint32_t& stride) {
    STORM_ASSERT(this->m_inMemoryImage);

    if (!this->IsValidMip(mipLevel)) {
        return 0;
    }

    uint8_t* mipData = static_cast<uint8_t*>(this->m_inMemoryImage) + this->m_header.mipOffsets[mipLevel];
    size_t mipSize = this->m_header.mipSizes[mipLevel];
    uint32_t formatSize;

    switch (this->m_header.colorEncoding) {
    case COLOR_JPEG:
        SErrPrepareAppFatal(__FILE__, __LINE__); SErrDisplayAppFatal("%s: JPEG decompression not enabled", fileName);
        return 0;

    case COLOR_PAL:
        if (this->GetFormatSize(format, mipLevel, &formatSize, &stride)) {
            this->m_lockDecompMem = data;
            return this->DecompPal(format, mipLevel, data, mipData);
        }
        return 0;
    case COLOR_DXT:
        switch (format) {
            case PIXEL_DXT1:
            case PIXEL_DXT3:
            case PIXEL_DXT5:
                memcpy(data, mipData, mipSize);
                return 1;

            case PIXEL_ARGB8888:
            case PIXEL_ARGB1555:
            case PIXEL_ARGB4444:
            case PIXEL_RGB565:
                // TODO
                return 0;

            case PIXEL_ARGB2565:
                return 0;

            default:
                return 0;
        }

    case COLOR_3:
        memcpy(data, mipData, mipSize);
        return 1;

    default:
        return 0;
    }
}

int32_t CBLPFile::LockChain2(const char* fileName, PIXEL_FORMAT format, MipBits*& images, uint32_t mipLevel, int32_t a6) {
    if (!this->IsValidMip(mipLevel)) {
        return 0;
    }

    if (images) {
        if (a6 && (this->m_header.colorEncoding == COLOR_DXT || this->m_header.colorEncoding == COLOR_3)) {
            if (this->m_header.colorEncoding == COLOR_3 || (format != PIXEL_ARGB4444 && format != PIXEL_RGB565 && format != PIXEL_ARGB1555 && format != PIXEL_ARGB8888)) {
                uint32_t* offset = this->m_header.mipOffsets;

                for (int32_t i = 0; *offset; offset++, i++) {
                    void* address = static_cast<uint8_t*>(this->m_inMemoryImage) + *offset;
                    images->mip[i] = reinterpret_cast<C4Pixel*>(address);
                }

                this->m_inMemoryImage = nullptr;
                return 1;
            }
        }

        MippedImgSet(format, this->Width(mipLevel), this->Height(mipLevel), images);
    } else {
        images = MippedImgAllocA(format, this->Width(mipLevel), this->Height(mipLevel), __FILE__, __LINE__);

        if (!images) {
            return 0;
        }
    }

    for (int32_t level = mipLevel, i = 0; level < this->m_numLevels; level++, i++) {
        if (!this->Lock2(fileName, format, level, reinterpret_cast<uint8_t*>(images->mip[i]), mipLevel)) {
            return 0;
        }
    }

    this->m_inMemoryImage = nullptr;

    return 1;
}

int32_t CBLPFile::Open(const char* filename, int32_t a3) {
    STORM_VALIDATE_BEGIN;
    STORM_VALIDATE(filename);
    STORM_VALIDATE_END;

    this->m_inMemoryImage = nullptr;

    if (this->m_images) {
        SMemFree(this->m_images, __FILE__, __LINE__, 0);
    }

    size_t v8 = a3 != 0;

    this->m_images = nullptr;

    SFile* fileptr;

    if (!SFile::OpenEx(nullptr, filename, v8, &fileptr)) {
        return 0;
    }

    int32_t blpSize = SFile::GetFileSize(fileptr, 0);
    CBLPFile::s_blpFileLoadBuffer.SetCount(blpSize);

    size_t bytesRead;

    SFile::Read(
        fileptr,
        CBLPFile::s_blpFileLoadBuffer.m_data,
        CBLPFile::s_blpFileLoadBuffer.Count(),
        &bytesRead,
        0,
        0
    );

    SFile::Close(fileptr);

    return this->Source(CBLPFile::s_blpFileLoadBuffer.m_data);
}

int32_t CBLPFile::Source(void* fileBits) {
    this->m_inMemoryImage = nullptr;

    if (this->m_images) {
        SMemFree(this->m_images, __FILE__, __LINE__, 0);
    }

    this->m_images = nullptr;
    this->m_inMemoryNeedsFree = 0;
    this->m_inMemoryImage = fileBits;

    memcpy(&this->m_header, fileBits, sizeof(this->m_header));

    if (this->m_header.magic != 0x32504C42 || this->m_header.formatVersion != 1) {
        return 0;
    }

    if (this->m_header.hasMips & 0xF) {
        this->m_numLevels = CalcLevelCount(this->m_header.width, this->m_header.height);
    } else {
        this->m_numLevels = 1;
    }

    return 1;
}
