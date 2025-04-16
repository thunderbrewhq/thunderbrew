#ifndef GX_TEXTURE_C_BLP_FILE_HPP
#define GX_TEXTURE_C_BLP_FILE_HPP

#include "gx/Types.hpp"
#include "gx/texture/CGxTex.hpp"
#include <cstdint>
#include <storm/Array.hpp>

enum MIPS_TYPE {
    MIPS_NONE = 0x0,
    MIPS_GENERATED = 0x1,
    MIPS_HANDMADE = 0x2
};

enum MipMapAlgorithm {
    MMA_BOX = 0x0,
    MMA_CUBIC = 0x1,
    MMA_FULLDFT = 0x2,
    MMA_KAISER = 0x3,
    MMA_LINEARLIGHTKAISER = 0x4,
};

struct BlpPalPixel {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t pad;
};

static_assert(sizeof(BlpPalPixel) == 4);

class CBLPFile {
#pragma pack(push, 1)
    struct BLPHeader {
        uint32_t magic = 0x32504C42;
        uint32_t formatVersion = 1;
        uint8_t colorEncoding;
        uint8_t alphaSize;
        uint8_t preferredFormat = 2;
        uint8_t hasMips;
        uint32_t width;
        uint32_t height;
        uint32_t mipOffsets[16];
        uint32_t mipSizes[16];

        union {
            BlpPalPixel palette[256];

            struct {
                uint32_t headerSize;
                uint8_t headerData[1020];
            } jpeg;
        } extended;
    };
#pragma pack(pop)

    public:
        // Static variables
        static TSGrowableArray<uint8_t> s_blpFileLoadBuffer;
        static uint8_t s_oneBitAlphaLookup[2];
        static uint8_t s_eightBitAlphaLookup[16];

        // Member variables
        MipBits* m_images = nullptr;
        BLPHeader m_header = {};
        void* m_inMemoryImage = nullptr;
        int32_t m_inMemoryNeedsFree;
        uint32_t m_numLevels;
        uint32_t m_quality = 100;
        void* m_colorMapping;
        MipMapAlgorithm m_mipMapAlgorithm = MMA_BOX;
        uint8_t* m_lockDecompMem;

        // Member functions
        uint32_t AlphaBits();
        uint32_t Width();
        uint32_t Width(uint32_t mipLevel);
        uint32_t Height();
        uint32_t Height(uint32_t mipLevel);
        uint32_t Pixels();
        uint32_t Pixels(uint32_t mipLevel);
        MIPS_TYPE HasMips();
        int32_t IsValidMip(uint32_t level);
        int32_t GetFormatSize(PIXEL_FORMAT format, uint32_t mipLevel, uint32_t* size, uint32_t* stride);
        void DecompPalFastPath(uint8_t* data, void* tempbuffer, uint32_t colorSize);
        void DecompPalARGB8888(uint8_t* data, void* tempbuffer, uint32_t colorSize);
        void DecompPalARGB1555DitherFloydSteinberg(uint8_t* data, void* tempbuffer, uint32_t width, uint32_t height);
        void DecompPalARGB2565DitherFloydSteinberg(uint8_t* data, void* tempbuffer, uint32_t width, uint32_t height);
        void DecompPalARGB4444DitherFloydSteinberg(uint8_t* data, void* tempbuffer, uint32_t width, uint32_t height);
        void DecompPalARGB565DitherFloydSteinberg(uint8_t* data, void* tempbuffer, uint32_t width, uint32_t height);
        int32_t DecompPal(PIXEL_FORMAT format, uint32_t mipLevel, uint8_t* data, void* tempBuffer);
        int32_t Lock2(const char*, PIXEL_FORMAT, uint32_t, uint8_t*, uint32_t&);
        int32_t LockChain2(const char*, PIXEL_FORMAT, MipBits*&, uint32_t, int32_t);
        int32_t Open(const char*, int32_t);
        void Close(void);
        int32_t Source(void*);
};

#endif
