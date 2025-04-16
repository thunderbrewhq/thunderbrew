#ifndef OS_INTERNAL_QUEUE_HPP
#define OS_INTERNAL_QUEUE_HPP

#define OS_QUEUE_SIZE 32

#include "os/Types.hpp"

extern OSEVENT s_queue[OS_QUEUE_SIZE];

extern int32_t s_queueHead;
extern int32_t s_queueTail;

#endif
