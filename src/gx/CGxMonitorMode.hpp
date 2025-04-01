#ifndef GX_C_GX_MONITOR_MODE_HPP
#define GX_C_GX_MONITOR_MODE_HPP

#include <cstdint>
#include <tempest/Vector.hpp>

class CGxMonitorMode {
    public:
        C2iVector size;
        uint32_t bpp;
        uint32_t refreshRate;
};

int32_t CGxMonitorModeSort(const void* i, const void* j);

#endif
