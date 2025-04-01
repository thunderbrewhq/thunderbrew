#include "gx/texture/CTgaFile.hpp"

#include <bc/Memory.hpp>
#include <storm/Error.hpp>

#include <cstring>

int32_t CTgaFile::Open(const char* filename, int32_t a3) {
    STORM_VALIDATE_BEGIN;
    STORM_VALIDATE(filename);
    STORM_VALIDATE(*filename);
    STORM_VALIDATE_END;

    this->Close();

    if (!SFile::OpenEx(0, filename, a3 != 0, &this->m_file)) {
        return 0;
    }

    // Read header
    if (!SFile::Read(this->m_file, &this->m_header, sizeof(this->m_header), nullptr, nullptr, nullptr)) {
        return 0;
    }

    // Read additional header data
    if (this->m_header.bIDLength == 0) {
        this->m_addlHeaderData = nullptr;
    } else {
        this->m_addlHeaderData = static_cast<uint8_t*>(SMemAlloc(this->m_header.bIDLength, __FILE__, __LINE__, 0x0));
        if (!SFile::Read(this->m_file, static_cast<void*>(this->m_addlHeaderData), this->m_header.bIDLength, nullptr, nullptr, nullptr)) {
            return 0;
        }
    }

    // Read color map
    if (this->m_header.bColorMapType == 0) {
        this->m_colorMap = nullptr;
    } else {
        this->m_colorMap = static_cast<uint8_t*>(SMemAlloc(this->ColorMapBytes(), __FILE__, __LINE__, 0x0));
        if (!SFile::Read(this->m_file, static_cast<void*>(this->m_colorMap), this->ColorMapBytes(), nullptr, nullptr, nullptr)) {
            return 0;
        }
    }

    // 3 pixels with alpha channel makes no sense
    if (this->m_header.bPixelDepth == 24 && this->m_header.desc.bAlphaChannelBits == 8) {
        SErrSetLastError(0x8720012E);
        return 0;
    }
    // 4 pixels with no alpha channel makes no sense
    if (this->m_header.bPixelDepth == 32 && this->m_header.desc.bAlphaChannelBits == 0) {
        SErrSetLastError(0x8720012F);
        return 0;
    }

    return 1;
}

void CTgaFile::Close() {
    if (this->m_image) {
        SMemFree(this->m_image, __FILE__, __LINE__, 0x0);
    }
    this->m_image = nullptr;

    if (this->m_file) {
        SFile::Close(this->m_file);
    }
    this->m_file = nullptr;

    if (this->m_addlHeaderData) {
        SMemFree(this->m_addlHeaderData, __FILE__, __LINE__, 0x0);
    }
    this->m_addlHeaderData = nullptr;

    if (this->m_colorMap) {
        SMemFree(this->m_colorMap, __FILE__, __LINE__, 0x0);
    }
    this->m_colorMap = nullptr;
}

uint32_t CTgaFile::ColorMapEntryBytes() const {
    auto v1 = static_cast<uint32_t>(this->m_header.bColorMapEntrySize) / 3;
    if (7 < v1) {
        v1 = 8;
    }

    return (v1 * 3) >> 3;
}

uint32_t CTgaFile::ColorMapEntries() const {
    return this->m_header.wColorMapEntries;
}

uint32_t CTgaFile::ColorMapBytes() const {
    return this->ColorMapEntryBytes() * this->ColorMapEntries();
}

uint32_t CTgaFile::PreImageBytes() const {
    return sizeof(TGAHeader) + this->m_header.bIDLength + this->ColorMapBytes();
}

uint32_t CTgaFile::Width() const {
    return this->m_header.wWidth;
}

uint32_t CTgaFile::Height() const {
    return this->m_header.wHeight;
}

uint32_t CTgaFile::Size() const {
    return this->Width() * this->Height();
}

uint32_t CTgaFile::BytesPerPixel() const {
    return (static_cast<uint32_t>(this->m_header.bPixelDepth) + 7) >> 3;
}

uint32_t CTgaFile::Bytes() const {
    return this->BytesPerPixel() * this->Size();
}

uint8_t CTgaFile::AlphaBits() const {
    return this->m_header.desc.bAlphaChannelBits;
}

void CTgaFile::SetTopDown(int32_t set) {
    if (set) {
        if (this->m_header.desc.bTopBottomOrder) {
            return;
        }
    } else if (!this->m_header.desc.bTopBottomOrder) {
        return;
    }

    if (!(this->m_header.bImageType >= TGA_RLE_COLOR_MAPPED && this->m_header.bImageType <= TGA_RLE_BLACK_N_WHITE)) {
        SErrSetLastError(0xF7200083);
        return;
    }

    auto newImage = static_cast<uint8_t*>(SMemAlloc(this->Bytes(), __FILE__, __LINE__, 0x0));

    if (this->Height()) {
        auto source = this->m_image;
        auto dest = newImage + (this->BytesPerPixel() * this->Width() * (this->Height() - 1));

        auto bytesPerRow = this->Width() * this->BytesPerPixel();

        uint32_t row = this->Height();
        while (row) {
            row--;

            memcpy(dest, source, bytesPerRow);

            source += bytesPerRow;
            dest -= bytesPerRow;
        }
    }

    SMemFree(this->m_image, __FILE__, __LINE__, 0x0);

    this->m_header.desc.bTopBottomOrder = static_cast<uint8_t>(set);

    this->m_image = newImage;
}

int32_t CTgaFile::ValidateColorDepth() {
    if (this->m_header.bPixelDepth - this->m_header.desc.bAlphaChannelBits == 24) {
        return 1;
    }

    if (this->m_header.bPixelDepth == 16) {
        SErrSetLastError(0xF720007C);
    } else {
        SErrSetLastError(0xF720007D);
    }

    return 0;
}

void CTgaFile::AddAlphaChannel(uint8_t* pAlphaData, uint8_t* pNoAlphaData, const uint8_t* alpha) {
    if (alpha) {
        for (auto size = this->Size(); size != 0; size--) {
            memmove(pAlphaData, pNoAlphaData, this->BytesPerPixel());
            pNoAlphaData += this->BytesPerPixel();
            pAlphaData[this->BytesPerPixel()] = *alpha;
            alpha++;
            pAlphaData += this->BytesPerPixel() + 1;
        }
    } else {
        for (auto size = this->Size(); size != 0; size--) {
            memmove(pAlphaData, pNoAlphaData, this->BytesPerPixel());
            pNoAlphaData += this->BytesPerPixel();
            pAlphaData[this->BytesPerPixel()] = 0xFF;
            pAlphaData += this->BytesPerPixel() + 1;
        }
    }
}

int32_t CTgaFile::RemoveAlphaChannels() {
    if (!this->Image()) {
        return 0;
    }

    if (this->m_header.desc.bAlphaChannelBits == 0) {
        if (this->m_header.bPixelDepth == 24) {
            return 1;
        }

        SErrSetLastError(0x8720012D);

        if (this->m_header.bPixelDepth == 32) {
            this->m_header.desc.bAlphaChannelBits = 8;
        }
    }

    if (this->m_header.desc.bAlphaChannelBits != 8) {
        SErrSetLastError(0xF7200082);
        return 0;
    }

    this->m_header.bPixelDepth -= 8;

    this->m_header.desc.bAlphaChannelBits = 0;

    auto dest = this->m_image;
    auto source = this->m_image;
    auto size = this->Size();
    auto stride = this->BytesPerPixel();

    if (size) {
        while (1) {
            --size;
            memcpy(dest, source, stride);
            dest += stride;
            source += stride + 1;
            if (!size) {
                break;
            }
        }
    }

    return 1;
}

int32_t CTgaFile::AddAlphaChannel(const void* pImg) {
    if (!this->Image()) {
        return 0;
    }

    if (this->m_header.bImageType > 8 && this->m_header.bImageType < 12) {
        SErrSetLastError(0xF7200083);
        return 0;
    }

    if (this->m_header.desc.bAlphaChannelBits) {
        this->RemoveAlphaChannels();
    }

    auto newImage = static_cast<uint8_t*>(SMemAlloc((this->BytesPerPixel() + 1) * this->Size(), __FILE__, __LINE__, 0x0));
    if (!newImage) {
        return 0;
    }

    this->AddAlphaChannel(newImage, this->m_image, reinterpret_cast<const uint8_t*>(pImg));

    SMemFree(this->m_image, __FILE__, __LINE__, 0x0);
    this->m_image = newImage;

    return 1;
}

int32_t CTgaFile::ReadRawImage(uint32_t flags) {
    int32_t alpha;

    if (!(flags & 0x1) || this->m_header.desc.bAlphaChannelBits == 0) {
        alpha = 0;
    } else {
        alpha = 1;
    }

    if (SFile::SetFilePointer(this->m_file, this->PreImageBytes(), nullptr, 0) == 0xFFFFFFFF) {
        return 0;
    }

    STORM_ASSERT(this->m_image == nullptr);

    this->m_image = static_cast<uint8_t*>(SMemAlloc(this->Bytes(), __FILE__, __LINE__, 0x0));

    if (this->m_image == nullptr) {
        return 0;
    }

    if (!SFile::Read(this->m_file, this->m_image + (alpha * this->Size()), this->Bytes(), nullptr, nullptr, nullptr)) {
        return 0;
    }

    if (alpha) {
        this->AddAlphaChannel(this->m_image, this->m_image + this->Size(), nullptr);
    }

    return 1;
}

int32_t CTgaFile::RLEDecompressImage(uint8_t* pRLEData, uint8_t* pData) {
    int32_t pixels = this->Size();

    while (pixels) {
        // fetch control byte from
        // input stream
        auto byte = *pRLEData++;
        // data to read after control byte
        auto source = pRLEData;
        if (byte & 0x80) {
            // run length packet
            auto count = (byte & 0x7F) + 1;
            auto bytes = this->BytesPerPixel();
            for (auto i = 0; i < count; i++) {
                memcpy(pData, source, bytes);
                pData += bytes;
            }
            pixels -= count;
            pRLEData += bytes;
        } else {
            // raw packet
            auto count = static_cast<uint32_t>(byte) + 1;
            auto bytes = this->BytesPerPixel() * count;
            memcpy(pData, source, bytes);
            pixels -= count;
            pData += bytes;
            pRLEData += bytes;
        }
    }

    if (pixels <= -1) {
        SErrSetLastError(0xF7200077);
        return 0;
    }

    this->m_header.bImageType -= 8;
    return 1;
}

int32_t CTgaFile::ReadRleImage(uint32_t flags) {
    int32_t alpha;

    if (!(flags & 0x1) || this->m_header.desc.bAlphaChannelBits == 0) {
        alpha = 0;
    } else {
        alpha = 1;
    }

    this->m_image = static_cast<uint8_t*>(SMemAlloc(this->Bytes() + (alpha * this->Size()), __FILE__, __LINE__, 0x0));

    if (!this->m_image) {
        return 0;
    }

    auto filesize = SFile::GetFileSize(this->m_file, nullptr);
    auto imagelength = filesize - this->PreImageBytes();
    if (imagelength > filesize) {
        return 0;
    }
    auto image = static_cast<uint8_t*>(SMemAlloc(imagelength, __FILE__, __LINE__, 0x0));
    if (!image) {
        return 0;
    }

    if (SFile::SetFilePointer(this->m_file, this->PreImageBytes(), nullptr, 0) == -1) {
        return 0;
    }
    if (!SFile::Read(this->m_file, image, imagelength, nullptr, nullptr, nullptr)) {
        return 0;
    }

    auto decompressed = this->RLEDecompressImage(image, this->m_image + (alpha * this->Size()));
    SMemFree(image, __FILE__, __LINE__, 0x0);
    if (!decompressed) {
        return 0;
    }
    if (alpha) {
        this->AddAlphaChannel(this->m_image, this->m_image + this->Size(), nullptr);
    }

    return 1;
}

void CTgaFile::ConvertColorMapped(uint32_t flags) {
    auto pixelDepth = static_cast<uint32_t>(this->m_header.desc.bAlphaChannelBits) + 24;
    uint32_t newImageSize = ((pixelDepth / 8) * this->Size()) + ((flags & 0x1) * this->Size());
    auto oldImage = this->m_image;
    this->m_image = static_cast<uint8_t*>(SMemAlloc(newImageSize, __FILE__, __LINE__, 0x0));

    auto dest = this->m_image + (this->Size() * (flags & 0x1));
    auto source = oldImage;

    for (auto i = this->Size(); i; i--) {
        memcpy(dest, this->m_colorMap + (this->ColorMapEntryBytes() * (static_cast<uint32_t>(*source) - this->m_header.wColorMapStartIndex)), this->ColorMapEntryBytes());
        source++;
        dest += this->ColorMapEntryBytes();
    }

    SMemFree(oldImage, __FILE__, __LINE__, 0x0);

    SMemFree(this->m_colorMap, __FILE__, __LINE__, 0x0);
    this->m_colorMap = nullptr;

    this->m_header.wColorMapEntries = 0;

    this->m_header.bColorMapType = 0;
    this->m_header.bImageType = TGA_TRUE_COLOR;
    this->m_header.bPixelDepth = pixelDepth;
    this->m_imageBytes = this->Bytes();

    if (flags & 0x1) {
        this->AddAlphaChannel(this->m_image, this->m_image + this->Size(), 0);
    }
}

int32_t CTgaFile::ReadColorMappedImage(uint32_t flags) {
    if (!this->m_header.bColorMapType) {
        SErrSetLastError(0xF7200084);
        return 0;
    }

    int32_t status;

    if (this->m_header.bImageType < TGA_RLE_COLOR_MAPPED) {
        status = this->ReadRawImage(0);
    } else {
        status = this->ReadRleImage(0);
    }

    if (this->m_header.bColorMapType != TGA_NO_IMAGE_DATA && (flags & 2)) {
        this->ConvertColorMapped(flags);
    }
}

int32_t CTgaFile::LoadImageData(uint32_t flags) {
    if (this->m_image) {
        SErrSetLastError(ERROR_INVALID_PARAMETER);
        return 1;
    }
    if (!this->m_file) {
        SErrSetLastError(0xF720007E);
        return 1;
    }

    this->m_imageBytes = this->Bytes();

    switch (this->m_header.bImageType) {
    case TGA_NO_IMAGE_DATA:
        SErrSetLastError(0xF7200078);
        return 0;
    case TGA_COLOR_MAPPED:
    case TGA_RLE_COLOR_MAPPED:
        return this->ReadColorMappedImage(flags);
    case TGA_TRUE_COLOR:
        if (!this->ValidateColorDepth()) {
            return 0;
        }
        return this->ReadRawImage(flags);
    case TGA_BLACK_N_WHITE:
    case TGA_RLE_BLACK_N_WHITE:
        SErrSetLastError(0xF720007A);
        return 0;
    case TGA_RLE_TRUE_COLOR:
        if (!this->ValidateColorDepth()) {
            return 0;
        }
        return this->ReadRleImage(flags);
    default:
        return 0;
    }
}

uint8_t* CTgaFile::Image() {
    if (!this->m_image) {
        SErrSetLastError(0xF720007F);
        return nullptr;
    }
    return this->m_image;
}

CTgaFile::TGA32Pixel* CTgaFile::ImageTGA32Pixel() {
    auto image = this->Image();
    if (!image) {
        return nullptr;
    }

    if (this->m_header.bPixelDepth != 32) {
        SErrSetLastError(0xF720007D);
        return nullptr;
    }

    return reinterpret_cast<TGA32Pixel*>(image);
}
