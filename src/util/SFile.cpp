#include "util/SFile.hpp"
#include <cstring>
#include <limits>
#include <StormLib.h>
#include <storm/Error.hpp>
#include <storm/Memory.hpp>
#include <storm/String.hpp>
#include <bc/file/File.hpp>
#include "util/Filesystem.hpp"

static char s_basepath[STORM_MAX_PATH] = { 0 };
static char s_datapath[STORM_MAX_PATH] = { 0 };
static char s_datapath2[STORM_MAX_PATH] = { 0 };

// TODO Proper implementation
int32_t SFile::Close(SFile* file) {
    switch (file->m_type) {
    case SFILE_PLAIN:
        Blizzard::File::Close(reinterpret_cast<Blizzard::File::StreamRecord*>(file->m_handle));
        break;
    case SFILE_PAQ:
        SFileCloseFile(file->m_handle);
        break;
    default:
        STORM_ASSERT(0);
    }

    delete file;
    return 1;
}

// TODO Proper implementation
uint32_t SFile::GetFileSize(SFile* file, uint32_t* filesizeHigh) {
    uint32_t high = 0;
    uint32_t low  = 0;

    switch (file->m_type) {
    case SFILE_PAQ: {
        // Get size from stormlib
        DWORD dwHigh = 0;
        DWORD dwLow = SFileGetFileSize(file->m_handle, &dwHigh);
        low = static_cast<uint32_t>(dwLow);
        high = static_cast<uint32_t>(dwHigh);
        break;
    }
    case SFILE_PLAIN: {
        uint64_t size = Blizzard::File::GetFileInfo(reinterpret_cast<Blizzard::File::StreamRecord*>(file->m_handle))->size;
        low = size & 0xFFFFFFFF;
        high = size >> 32;
        break;
    }
    default:
        STORM_ASSERT(0);
    }

    if (filesizeHigh) {
        *filesizeHigh = high;
    }

    return low;
}

// TODO: Proper implementation
int32_t SFile::FileExists(const char* filename) {
    return SFile::FileExistsEx(filename, 0);
}

// TODO: Proper implementation
int32_t SFile::FileExistsEx(const char* filename, uint32_t a2) {
    SFile* test_file;
    if (!SFile::Open(filename, &test_file)) {
        return 0;
    }

    SFile::Close(test_file);
    return 1;
}

int32_t SFile::IsStreamingMode() {
    // TODO
    return 0;
}

// TODO Proper implementation
int32_t SFile::Load(SArchive* archive, const char* filename, void** buffer, size_t* bytes, size_t extraBytes, uint32_t flags, SOVERLAPPED* overlapped) {
    if (!buffer || !filename) {
        return 0;
    }

    *buffer = nullptr;
    if (bytes) {
        *bytes = 0;
    }

    SFile* file = nullptr;
    if (!SFile::OpenEx(nullptr, filename, 0, &file)) {
        return 0;
    }

    uint32_t high = 0;
    uint64_t size = SFile::GetFileSize(file, &high);
    size |= ((uint64_t) high << 32);

    auto data = reinterpret_cast<char*>(SMemAlloc(size + extraBytes, __FILE__, __LINE__, 0));

    if (!SFile::Read(file, data, size, nullptr, nullptr, nullptr)) {
        SMemFree(data, __FILE__, __LINE__, 0);
        SFile::Close(file);
        return 0;
    }

    if (extraBytes) {
        memset(data + size, 0, extraBytes);
    }

    if (bytes) {
        *bytes = size;
    }

    if (buffer) {
        *buffer = data;
    }

    SFile::Close(file);

    return 1;
}

int32_t SFile::Open(const char* filename, SFile** file) {
    return SFile::OpenEx(nullptr, filename, 0, file);
}

// TODO Proper implementation
int32_t SFile::OpenEx(SArchive* archive, const char* filename, uint32_t flags, SFile** file) {
    if (!file || !filename) {
        return 0;
    }

    char path[STORM_MAX_PATH];

    // Overflow protection
    if (SStrLen(filename) + 1 > STORM_MAX_PATH) {
        *file = nullptr;
        return 0;
    }

    SStrCopy(path, filename, STORM_MAX_PATH);

    SFILE_TYPE filetype = SFILE_PLAIN;
    void* filehandle;
    HANDLE handle;

    uint32_t openflags = BC_FILE_OPEN_MUST_EXIST | BC_FILE_OPEN_SHARE_READ | BC_FILE_OPEN_READ;
    Blizzard::File::StreamRecord* stream;

    // Attempt to open plain file first
    if (Blizzard::File::Open(path, openflags, stream)) {
        // plain file was opened
        filehandle = reinterpret_cast<void*>(stream);
    // Attempt to open MPQ archived file
    } else if (SFileOpenFileEx(g_mpqHandle, path, SFILE_OPEN_FROM_MPQ, &handle)) {
        filetype = SFILE_PAQ;
        filehandle = static_cast<void*>(handle);
    } else {
        *file = nullptr;
        // could not open either plain or MPQ archived file
        return 0;
    }

    *file = new SFile;
    (*file)->m_handle = filehandle;
    (*file)->m_type   = filetype;

    return 1;
}

uint32_t SFile::SetFilePointer(SFile* file, int32_t distancetomove, int32_t* distancetomovehigh, uint32_t movemethod) {
    switch (file->m_type) {
    case SFILE_PLAIN: {
        auto stream = reinterpret_cast<Blizzard::File::StreamRecord*>(file->m_handle);
        int32_t whence = movemethod;
        if (whence != 0 && whence != 1) {
            if (whence >= 2) {
                whence = movemethod != 2 ? -1 : 2;
            }
        }
        int64_t offset = distancetomove;
        if (distancetomovehigh) {
            offset |= *distancetomovehigh << 32;
        }
        int64_t pos;
        Blizzard::File::SetPos(stream, offset, whence);
        if (Blizzard::File::GetPos(stream, pos)) {
            if (distancetomovehigh) {
                *distancetomovehigh = (pos >> 32) & 0xFFFFFFFF;
            }
            return pos & 0xFFFFFFFF;
        }

        return 0xFFFFFFFF;
    }
    case SFILE_PAQ: {
        return static_cast<uint32_t>(SFileSetFilePointer(file->m_handle, static_cast<LONG>(distancetomove), reinterpret_cast<LONG*>(distancetomovehigh), static_cast<DWORD>(movemethod)));
    }
    default:
        STORM_ASSERT(0);
    }
}

// TODO Proper implementation
int32_t SFile::Read(SFile* file, void* buffer, size_t bytestoread, size_t* bytesread, SOVERLAPPED* overlapped, TASYNCPARAMBLOCK* asyncparam) {
    switch (file->m_type) {
    case SFILE_PLAIN: {
        auto stream = reinterpret_cast<Blizzard::File::StreamRecord*>(file->m_handle);
        Blizzard::File::Read(stream, buffer, bytestoread, bytesread);
        return 1;
    }
    case SFILE_PAQ: {
        DWORD read = 0;
        if (SFileReadFile(file->m_handle, buffer, static_cast<DWORD>(bytestoread), &read, nullptr)) {
            if (bytesread) {
                *bytesread = read;
            }
            return 1;
        } else {
            if (bytesread) {
                *bytesread = 0;
            }
            return 0;
        }
    }
    default:
        STORM_ASSERT(0);
    }

    return 0;
}

int32_t SFile::Unload(void* ptr) {
    SMemFree(ptr, __FILE__, __LINE__, 0);
    return 1;
}

int32_t SFile::SetBasePath(const char* path) {
    SStrCopy(s_basepath, path, STORM_MAX_PATH);

    if (*s_basepath != '\0') {
        auto len = SStrLen(s_basepath);
        if (s_basepath[len-1] != '\\') {
            SStrPack(s_basepath, "\\", STORM_MAX_PATH);
        }
    }

    // TODO

    // SFileSetBasePath(path);

    return 1;
}

int32_t SFile::SetDataPath(const char* path) {
    SStrCopy(s_datapath, path, STORM_MAX_PATH);

    if (*s_datapath != '\0') {
        auto len = SStrLen(s_datapath);
        if (s_basepath[len-1] != '\\') {
            SStrPack(s_datapath, "\\", STORM_MAX_PATH);
        }
    }

    return 1;
}

int32_t SFile::GetBasePath(char* buffer, size_t bufferchars) {
    SStrCopy(buffer, s_basepath, bufferchars);
    return 1;
}

int32_t SFile::GetDataPath(char* buffer, size_t bufferchars) {
    SStrCopy(buffer, s_datapath, bufferchars);
    return 1;
}

int32_t SFile::SetDataPathAlternate(const char* path) {
    SStrCopy(s_datapath2, path, STORM_MAX_PATH);
    size_t length = SStrLen(s_datapath2);
    if (length && s_datapath2[length - 1] != '\\' && s_datapath2[length - 1] != '/') {
        SStrPack(s_datapath2, "\\", STORM_MAX_PATH);
    }
    return 1;
}

int32_t SFile::RebuildHash() {
    // TODO
    return 1;
}
