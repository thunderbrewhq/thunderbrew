#include "client/Patch.hpp"

#include <storm/String.hpp>

#include "client/Client.hpp"


PatchFiles::PatchFiles() {
    this->path = nullptr;
}

void PatchFiles::SearchArchives(const char* locale, int32_t a3) {
    char fullPath[256] = {};
    char pattern[256] = {};
    char path[256] = {};

    const size_t listSize = 12;

    ListEntry list[listSize] = {
        { 0, 0, false, "Data\\",         "patch-?.MPQ"    },
        { 0, 0, false, "Data\\%s\\",     "patch-%s-?.MPQ" },
        { 1, 0, false, "Data\\",         "patch.MPQ"      },
        { 1, 0, false, "Data\\%s\\",     "patch-%s.MPQ"   },
        { 1, 1, false, "Data\\",         "patch-4.MPQ"    },
        { 1, 1, false, "Data\\%s\\",     "patch-%s-4.MPQ" },
        { 1, 1, false, "Data\\",         "patch-3.MPQ"    },
        { 1, 1, false, "Data\\%s\\",     "patch-%s-3.MPQ" },
        { 1, 1, false, "..\\Data\\",     "patch-2.MPQ"    },
        { 1, 1, false, "..\\Data\\%s\\", "patch-%s-2.MPQ" },
        { 1, 1, false, "..\\Data\\",     "patch.MPQ"      },
        { 1, 1, false, "..\\Data\\%s\\", "patch-%s.MPQ"   },
    };

    const char* installRoot = UpdateInstallLocation();

    // Warning: assigning pointer to a temporary variable
    // Need this for OsFileList's callback
    this->path = path;

    for (size_t i = 0; i <= 2; ++i) {
        for (size_t j = 0; j < listSize; ++j) {
            auto entry = &list[j];
            if (entry->num1 != i || entry->num2 != (a3 != 0)) {
                continue;
            }

            SStrPrintf(path, sizeof(path), entry->dataDir, locale);
            SStrPrintf(pattern, sizeof(pattern), entry->pattern, locale);
            if (entry->absolute && installRoot && installRoot[0]) {
                SStrPrintf(fullPath, sizeof(fullPath), "%s%s", installRoot, path);
                SStrCopy(path, fullPath, sizeof(path));
                
            }
            // TODO: OsFileList(this->path, pattern, PatchFiles::EnumPatchArchives, this, 0);
        }

        if (i == 0) {
            std::qsort(this->files.Ptr(), this->files.Count(), sizeof(char*), &PatchFiles::qsortpatchfiles);
        }
    }
}

int PatchFiles::qsortpatchfiles(const void* a1, const void* a2) {
    return -SStrCmpI(*((const char**) a1), *((const char**) a2), STORM_MAX_STR);
}
