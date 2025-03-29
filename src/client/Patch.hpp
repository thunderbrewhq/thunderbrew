#ifndef CLIENT_PATCH_HPP
#define CLIENT_PATCH_HPP


#include <storm/Array.hpp>


class PatchFiles {
    public:
        PatchFiles();

        void SearchArchives(const char* locale, int32_t a3);

    public:
        char* path;
        TSGrowableArray<char*> files;

    private:
        static int qsortpatchfiles(const void* a1, const void* a2);

    private:
        struct ListEntry {
            uint32_t num1;
            uint32_t num2;
            bool absolute;
            const char* dataDir;
            const char* pattern;
        };
};



#endif
