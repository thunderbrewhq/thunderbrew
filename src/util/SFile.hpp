#ifndef UTIL_S_FILE_HPP
#define UTIL_S_FILE_HPP

#include <cstdint>
#include <cstdlib>

class SArchive;
struct SOVERLAPPED;
struct TASYNCPARAMBLOCK;
namespace Blizzard {
namespace File {
class StreamRecord;
};
};

enum SFILE_TYPE {
    SFILE_PLAIN = 0x0,
    SFILE_COMPRESSED = 0x1,
    SFILE_PAQ = 0x2,
    SFILE_OLD_SFILE = 0x3,
    SFILE_ZIP_FILE = 0x4
};

class SFile {
    public:
        // Static functions
        static int32_t Close(SFile*);
        static uint32_t GetFileSize(SFile*, uint32_t*);
        static int32_t FileExists(const char* filename);
        static int32_t FileExistsEx(const char* filename, uint32_t a2);
        static int32_t IsStreamingMode(void);
        static int32_t Load(SArchive*, const char*, void**, size_t*, size_t, uint32_t, SOVERLAPPED*);
        static int32_t Open(const char*, SFile**);
        static int32_t OpenEx(SArchive*, const char*, uint32_t, SFile**);
        static uint32_t SetFilePointer(SFile* file, int32_t distancetomove, int32_t* distancetomovehigh, uint32_t movemethod);
        static int32_t Read(SFile*, void*, size_t, size_t*, SOVERLAPPED*, TASYNCPARAMBLOCK*);
        static int32_t Unload(void*);
        static int32_t SetBasePath(const char* path);
        static int32_t SetDataPath(const char* path);
        static int32_t GetBasePath(char* path, size_t capacity);
        static int32_t GetDataPath(char* path, size_t capacity);
        static int32_t SetDataPathAlternate(const char* path);
        static int32_t RebuildHash();

        // Member variables
        SFILE_TYPE m_type;
        void*      m_handle;
};

#endif
