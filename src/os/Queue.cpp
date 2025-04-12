#include "os/Queue.hpp"
#include "os/internal/Queue.hpp"

int32_t OsQueueGet(OSINPUT* id, int32_t* param0, int32_t* param1, int32_t* param2, int32_t* param3) {
    if (s_queueTail == s_queueHead) {
        return 0;
    }

    OSEVENT event = s_queue[s_queueTail];

    *id     = event.id;
    *param0 = event.param[0];
    *param1 = event.param[1];
    *param2 = event.param[2];
    *param3 = event.param[3];

    if (s_queueTail == (OS_QUEUE_SIZE - 1)) {
        s_queueTail = 0;
    } else {
        ++s_queueTail;
    }

    return 1;
}

void OsQueuePut(OSINPUT id, int32_t param0, int32_t param1, int32_t param2, int32_t param3) {
    int32_t nextTail = 0;
    int32_t nextHead = 0;

    if (s_queueHead != OS_QUEUE_SIZE - 1) {
        nextHead = s_queueHead + 1;
    }

    if (nextHead == s_queueTail) {
        if (nextHead != OS_QUEUE_SIZE - 1) {
            nextTail = nextHead + 1;
        }

        s_queueTail = nextTail;
    }

    auto event = &s_queue[s_queueHead];

    event->id       = id;
    event->param[0] = param0;
    event->param[1] = param1;
    event->param[2] = param2;
    event->param[3] = param3;

    s_queueHead = nextHead;
}

void OsQueueSetParam(int32_t index, int32_t param) {
    int32_t pos = s_queueTail;

    while (pos != s_queueHead) {
        auto event          = &s_queue[pos];
        event->param[index] = param;

        if (pos == OS_QUEUE_SIZE - 1) {
            pos = 0;
        } else {
            ++pos;
        }
    }
}
