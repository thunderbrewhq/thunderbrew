#include "event/Synthesize.hpp"
#include "event/Event.hpp"
#include "event/Queue.hpp"
#include "event/Types.hpp"
#include "event/Scheduler.hpp"
#include "event/EvtContext.hpp"
#include "event/Queue.hpp"
#include <common/Time.hpp>
#include <common/Call.hpp>

#if defined(WHOA_SYSTEM_WIN)
#include <windows.h>
#endif

void SynthesizeDestroy(EvtContext* context) {
    if (!(context->m_schedFlags & 0x1)) {
        context->m_schedFlags |= 0x1;
        context->m_schedLastIdle = OsGetAsyncTimeMs();
        IEvtQueueDispatch(context, EVENT_ID_INITIALIZE, nullptr);
    }

    if (context->m_schedFlags & 0x2) {
        SInterlockedDecrement(&Event::s_interactiveCount);
        if (!Event::s_interactiveCount) {
            IEvtSchedulerShutdown();
        }
    }

    IEvtQueueDispatch(context, EVENT_ID_3, nullptr);
    context->m_critsect.Enter();
    context->m_schedState = EvtContext::SCHEDSTATE_DESTROYED;
    context->m_critsect.Leave();
    IEvtQueueDispatchAll(context);
    IEvtQueueDispatch(context, EVENT_ID_DESTROY, nullptr);

    OsCallResetContext(context->m_callContext);
    PropSelectContext(0);

    int32_t findMask;
    TSingletonInstanceId<EvtContext, offsetof(EvtContext, m_id)>::s_idTable.Ptr(
        context->m_id,
        1,
        &findMask);

    DEL(context);

    if (findMask != -1) {
        TSingletonInstanceId<EvtContext, offsetof(EvtContext, m_id)>::s_idTable.Unlock(
            findMask & (INSTANCE_TABLE_SLOT_COUNT - 1),
            findMask >= INSTANCE_TABLE_SLOT_COUNT
        );
    }
}

void SynthesizeIdle(EvtContext* context, uint32_t currTime, float elapsedSec) {
    bool closed;

    context->m_critsect.Enter();
    closed = context->m_schedState == EvtContext::SCHEDSTATE_CLOSED;
    context->m_critsect.Leave();

    if (closed) {
        return;
    }

    uint32_t schedFlags = context->m_schedFlags;

    if (schedFlags & 0x2) {
        context->m_schedFlags = schedFlags | 0x4;
    }

    EVENT_DATA_IDLE data;
    data.elapsedSec = elapsedSec;
    data.time = currTime;

    IEvtQueueDispatch(context, EVENT_ID_IDLE, &data);
}

int32_t SynthesizeInitialize(EvtContext* context) {
    uint32_t schedFlags = context->m_schedFlags;

    if (schedFlags & 0x1) {
        return 0;
    }

    context->m_schedFlags = schedFlags | 0x1;
    context->m_schedLastIdle = OsGetAsyncTimeMs();

    IEvtQueueDispatch(context, EVENT_ID_INITIALIZE, nullptr);

    return 1;
}

void SynthesizePaint(EvtContext* context) {
    bool closed;

    context->m_critsect.Enter();
    closed = context->m_schedState == EvtContext::SCHEDSTATE_CLOSED;
    context->m_critsect.Leave();

    if (closed) {
        return;
    }

    uint32_t schedFlags = context->m_schedFlags;

    if (schedFlags & 0x4) {
        context->m_schedFlags = schedFlags & ~0x4;
        IEvtQueueDispatch(context, EVENT_ID_PAINT, nullptr);
    }
}

void SynthesizePoll(EvtContext* context) {
    bool closed;

    context->m_critsect.Enter();
    closed = context->m_schedState == EvtContext::SCHEDSTATE_CLOSED;
    context->m_critsect.Leave();

    if (closed) {
        return;
    }

    IEvtQueueDispatch(context, EVENT_ID_POLL, nullptr);
}
