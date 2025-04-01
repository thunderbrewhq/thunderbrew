#include "gx/CGxMonitorMode.hpp"

int32_t CGxMonitorModeSort(const void* a, const void* b) {
    auto i = static_cast<const CGxMonitorMode*>(a);
    auto j = static_cast<const CGxMonitorMode*>(b);

    return (i->size.x * i->size.y) - (j->size.x * j->size.y);
}
