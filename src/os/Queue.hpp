#ifndef OS_QUEUE_HPP
#define OS_QUEUE_HPP

#include "os/Types.hpp"

int32_t OsQueueGet(OSINPUT* id, int32_t* param0, int32_t* param1, int32_t* param2, int32_t* param3);

void OsQueuePut(OSINPUT id, int32_t param0, int32_t param1, int32_t param2, int32_t param3);

void OsQueueSetParam(int32_t index, int32_t param);

#endif
