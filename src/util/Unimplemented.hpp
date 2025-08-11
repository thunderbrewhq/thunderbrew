#ifndef UTIL_UNIMPLEMENTED_HPP
#define UTIL_UNIMPLEMENTED_HPP

#include <cstdio>
#include "os/Debug.hpp"

#define WHOA_UNIMPLEMENTED(...)                                                                                     \
    OsOutputDebugString("Function not yet implemented: %s in %s (line %i)\n", __FUNCTION__, __FILE__, __LINE__);    \
    return __VA_ARGS__;                                                                                             \
    (void)0

#endif
