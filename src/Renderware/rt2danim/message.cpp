// message.cpp - RW 3.7 tool/2danim/message.c (0x6fe750-0x7001f8): the message store, the message lists
// (frame actions), the queue and its processing, ported from the PS3 library code. See Rt2dAnim.h.
//
// The message store is every message of the movie; a message list entry is the store index of a run of
// messages ended by a NULL-type one. Posting copies messages into the queue (a flat array with a read
// index, messageTop, and a write index, messageBot, both reset to 0 when the last message is read),
// resolving a non-negative index (a label) to its animation and a negative one to the current target;
// SPECIALTELLTARGET messages change the target of the messages after them instead of being queued.
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"

#if __has_include("Renderware/rwcore/RwCamera.h")
#include "Renderware/rwcore/RwCamera.h"
#define DOTD_RT2DANIM_HAS_RWCAMERA 1
#else
#define DOTD_RT2DANIM_HAS_RWCAMERA 0
#endif

namespace {
typedef RwInt32 (*Rt2dMessageStreamGetSizeCallBack)(Rt2dMaestro* maestro, Rt2dMessage* message);
typedef Rt2dMessage* (*Rt2dMessageStreamReadCallBack)(Rt2dMaestro* maestro, Rt2dMessage* message, RwStream* stream);
typedef Rt2dMessage* (*Rt2dMessageStreamWriteCallBack)(Rt2dMaestro* maestro, Rt2dMessage* message, RwStream* stream);

struct Rt2dMessageDescrip {
    Rt2dMessageStreamGetSizeCallBack streamGetSize;
    Rt2dMessageStreamReadCallBack streamRead;
    Rt2dMessageStreamWriteCallBack streamWrite;
};
}  // namespace

// 0x006fe750 _rt2dMessageStreamGetSizeDefaultCallBack_maybe
static RwInt32 _rt2dMessageStreamGetSizeDefaultCallBack(Rt2dMaestro* /*maestro*/, Rt2dMessage* /*message*/) {
    return 0;
}

// 0x006fe758 _rt2dMessageStreamReadDefaultCallBack: reads nothing.
static Rt2dMessage* _rt2dMessageStreamReadDefaultCallBack(Rt2dMaestro* /*maestro*/, Rt2dMessage* message,
                                                          RwStream* /*stream*/) {
    return message;
}

// 0x006fe760 _rt2dMessageStreamWriteDefaultCallBack
static Rt2dMessage* _rt2dMessageStreamWriteDefaultCallBack(Rt2dMaestro* /*maestro*/, Rt2dMessage* message,
                                                           RwStream* /*stream*/) {
    return message;
}

// 0x00c4d468 _rt2dMessageDescripTable: 17 entries (XXL2: 0x198 bytes of 3 pointers), every one the
// defaults in the EBOOT's data and in the running game.
static Rt2dMessageDescrip g_rt2dMessageDescripTable[17] = {
#define DOTD_RT2D_MESSAGE_DEFAULTS                                                                             \
    {_rt2dMessageStreamGetSizeDefaultCallBack, _rt2dMessageStreamReadDefaultCallBack,                         \
     _rt2dMessageStreamWriteDefaultCallBack}
    DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS,
    DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS,
    DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS,
    DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS, DOTD_RT2D_MESSAGE_DEFAULTS,
    DOTD_RT2D_MESSAGE_DEFAULTS,
#undef DOTD_RT2D_MESSAGE_DEFAULTS
};

// 0x006fe8d0 _rt2dMaestroResolveMessageTarget_maybe (_rt2dMessageSpecialMessageTellTarget): the target
// animation of a SPECIALTELLTARGET message, from the current one (currentIndex). intParam1: > 0 go up
// that many parents (the walk starts at the current node and lands on the last node's parent), 0
// relative, -1 absolute, anything else the current one. intParam2: the offset, or with a non-negative
// index the label whose data is the offset.
static Rt2dMessage* _rt2dMessageSpecialMessageTellTarget(Rt2dMaestro* maestro, Rt2dMessage* message,
                                                         RwInt32 currentIndex, RwInt32* target) {
    const RwInt32 levels = message->intParam1;
    if (levels > 0) {
        Rt2dAnimNode* node = _rt2dMaestroGetAnimNodeByIndex(maestro, currentIndex);
        for (RwInt32 n = levels - 1; n != 0; --n) node = _rt2dMaestroGetAnimNodeByIndex(maestro, node->parent);
        if (message->index >= 0) {
            Rt2dStringLabel* label = Rt2dMaestroGetStringLabelByIndex(maestro, message->intParam2);
            *target = node->parent + Rt2dStringLabelData(label);
        } else {
            *target = node->parent + message->intParam2;
        }
        return message;
    }
    if (levels == 0) {
        if (message->index >= 0) {
            *target = currentIndex + Rt2dStringLabelData(Rt2dMaestroGetStringLabelByIndex(maestro, message->intParam2));
        } else {
            *target = currentIndex + message->intParam2;
        }
        return message;
    }
    if (levels == -1) {
        if (message->index >= 0) {
            *target = Rt2dStringLabelData(Rt2dMaestroGetStringLabelByIndex(maestro, message->intParam2));
        } else {
            *target = message->intParam2;
        }
        return message;
    }
    *target = currentIndex;
    return message;
}

// The posting loop Rt2dMaestroPostMessages and _rt2dMaestroMessageListPostByIndex share (inlined twice
// on the PS3): the capacity check (unsigned), then each message queued or, for a tell-target, the target
// changed. A queued message's index: < 0 the target (initially currAnimIndex), else its label's data.
static Rt2dMaestro* PostMessagesToQueue(Rt2dMaestro* maestro, Rt2dMessage* message, RwInt32 num) {
    Rt2dMessageQueue* queue = maestro->messageQueue;
    const RwInt32 currentIndex = maestro->currAnimIndex;
    if (static_cast<RwUInt32>(num + queue->messageBot) > queue->size) return nullptr;
    if (num <= 0) return maestro;
    Rt2dMessage* out = queue->messageQueue + queue->messageBot;
    RwInt32 target = currentIndex;
    for (RwInt32 i = 0; i < num; ++i, ++message) {
        if (message->messageType == rt2dMESSAGETYPESPECIALTELLTARGET) {
            if (_rt2dMessageSpecialMessageTellTarget(maestro, message, currentIndex, &target) == nullptr) return nullptr;
            continue;
        }
        out->messageType = message->messageType;
        out->index = message->index;
        out->intParam1 = message->intParam1;
        out->intParam2 = message->intParam2;
        ++queue->messageBot;
        if (out->index < 0) {
            out->index = target;
        } else {
            out->index = Rt2dStringLabelData(Rt2dMaestroGetStringLabelByIndex(maestro, out->index));
        }
        ++out;
    }
    return maestro;
}

// 0x006feff8 _rt2dMessageStreamRead_maybe: four words, then the type's stream-read callback.
static Rt2dMessage* _rt2dMessageStreamRead(Rt2dMaestro* maestro, Rt2dMessage* message, RwStream* stream) {
    if (RwStreamReadInt32(stream, &message->messageType, 4) == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, &message->index, 4) == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, &message->intParam1, 4) == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, &message->intParam2, 4) == nullptr) return nullptr;
    if (g_rt2dMessageDescripTable[message->messageType].streamRead(maestro, message, stream) == nullptr) return nullptr;
    return message;
}

// 0x006ff1a8 Rt2dMaestro_CreateMessageLists_maybe (_rt2dMaestroCreateMessageList): the message list
// (RwInt32) and the message store (Rt2dMessage).
Rt2dMaestro* _rt2dMaestroCreateMessageList(Rt2dMaestro* maestro) {
    maestro->messageList = _rwSListCreate(static_cast<RwInt32>(sizeof(RwInt32)), kRt2dAnimHint);
    if (maestro->messageList == nullptr) return nullptr;
    maestro->messageStore = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dMessage)), kRt2dAnimHint);
    if (maestro->messageStore == nullptr) return nullptr;
    return maestro;
}

// 0x006ff430 Rt2dMaestroProcessMessages_maybe: re-entry guarded by maestro flag bit 1. Takes the window
// metrics from the Rt2d camera (1/width, 1/height of its raster, view window x/y), then hands every queued
// message to the maestro's handler until the queue is empty; a handler that does not return the message
// stops it (null).
Rt2dMaestro* Rt2dMaestroProcessMessages(Rt2dMaestro* maestro) {
    if ((maestro->flag & 2) != 0) return maestro;
    maestro->flag |= 2;
    RwCamera* camera = Rt2dDeviceGetCamera();
    if (camera != nullptr) {
#if DOTD_RT2DANIM_HAS_RWCAMERA
        // fcfid + frsp of the raster's width/height, fdivs 1.0f by each; view window x / y.
        const RwRaster* raster = camera->frameBuffer;
        maestro->invWinW = 1.0f / static_cast<RwReal>(raster->width);
        maestro->invWinH = 1.0f / static_cast<RwReal>(raster->height);
        maestro->winAspectRatio = camera->viewWindow.x / camera->viewWindow.y;
#else
        // DEV(C1.5): RwCamera's layout comes with family B (rwcore/RwCamera.h); the PS3 reads
        // camera +0x60 (frameBuffer) +0xc/+0x10 (width/height) and +0x68/+0x6c (viewWindow).
        maestro->winAspectRatio = 0.0f;
        maestro->invWinW = 0.0f;
        maestro->invWinH = 0.0f;
#endif
    } else {
        maestro->winAspectRatio = 0.0f;
        maestro->invWinW = 0.0f;
        maestro->invWinH = 0.0f;
    }
    Rt2dMessageQueue* queue = maestro->messageQueue;
    if (queue->messageBot != 0) {
        RwInt32 top = queue->messageTop;
        Rt2dMessage* message = queue->messageQueue + top;
        queue->messageTop = top + 1;
        if (queue->messageBot <= top + 1) {
            queue->messageBot = 0;
            queue->messageTop = 0;
        }
        while (message != nullptr) {
            if (maestro->messageHandler(maestro, message) != message) {
                maestro->flag &= ~2;
                return nullptr;
            }
            if (queue->messageBot == 0) break;
            top = queue->messageTop;
            message = queue->messageQueue + top;
            queue->messageTop = top + 1;
            if (queue->messageBot <= top + 1) {
                queue->messageTop = 0;
                queue->messageBot = 0;
            }
        }
    }
    maestro->flag &= ~2;
    return maestro;
}

// 0x006ff940 Rt2dMaestro_DestroyFrameMessageList_maybe (_rt2dMaestroDestroyMessageQueue)
Rt2dMaestro* _rt2dMaestroDestroyMessageQueue(Rt2dMaestro* maestro) {
    Rt2dMessageQueue* queue = maestro->messageQueue;
    if (queue != nullptr) {
        queue->messageBot = 0;
        queue->messageTop = 0;
        if (queue->messageQueue != nullptr) RwFree(queue->messageQueue);
        RwFreeListFree(g_rt2dAnimFreeLists[kRt2dAnimFreeListMessageQueue], queue);
    }
    maestro->messageQueue = nullptr;
    return maestro;
}

// 0x006ffa10 Rt2dMaestro_CreateFrameMessageList_maybe (_rt2dMaestroCreateMessageQueue): a queue of the
// default size (Rt2dMessageQueueSetDefaultSize). The PS3 leaks the queue when the array allocation fails.
Rt2dMaestro* _rt2dMaestroCreateMessageQueue(Rt2dMaestro* maestro) {
    Rt2dMessageQueue* queue = static_cast<Rt2dMessageQueue*>(
        RwFreeListAlloc(g_rt2dAnimFreeLists[kRt2dAnimFreeListMessageQueue], kRt2dAnimHint));
    if (queue != nullptr) {
        queue->messageQueue = static_cast<Rt2dMessage*>(
            RwMalloc(static_cast<RwUInt32>(g_rt2dMessageQueueDefaultSize) * static_cast<RwUInt32>(sizeof(Rt2dMessage)),
                     kRt2dAnimHint));
        if (queue->messageQueue != nullptr) {
            queue->messageBot = 0;
            queue->messageTop = 0;
            queue->size = static_cast<RwUInt32>(g_rt2dMessageQueueDefaultSize);
            maestro->messageQueue = queue;
            return maestro;
        }
    }
    maestro->messageQueue = nullptr;
    return nullptr;
}

// 0x006ffb28 Rt2dMaestro_DestroyMessageLists_maybe (_rt2dMaestroDestroyMessageList)
Rt2dMaestro* _rt2dMaestroDestroyMessageList(Rt2dMaestro* maestro) {
    if (maestro->messageList != nullptr) _rwSListDestroy(maestro->messageList);
    RwSList* store = maestro->messageStore;
    maestro->messageList = nullptr;
    if (store != nullptr) {
        const RwInt32 count = _rwSListGetNumEntries(store);
        Rt2dMessage* message = RwSListArray<Rt2dMessage>(store);
        for (RwInt32 i = 0; i < count; ++i, ++message) {
            message->messageType = rt2dMESSAGETYPENULL;
            message->intParam1 = 0;
            message->index = -1;
        }
        _rwSListDestroy(store);
    }
    maestro->messageStore = nullptr;
    return maestro;
}

// 0x006ffc08 _rt2dMaestroMessageStoreStreamRead: the count, then the messages.
// BUG(original): without a store it creates both lists (the old message list leaks).
Rt2dMaestro* _rt2dMaestroMessageStoreStreamRead(Rt2dMaestro* maestro, RwStream* stream) {
    RwInt32 count = 0;
    if (RwStreamReadInt32(stream, &count, 4) == nullptr) return nullptr;
    if (count < 1) return maestro;
    if (maestro->messageStore == nullptr) {
        maestro->messageList = _rwSListCreate(static_cast<RwInt32>(sizeof(RwInt32)), kRt2dAnimHint);
        if (maestro->messageList == nullptr) return nullptr;
        maestro->messageStore = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dMessage)), kRt2dAnimHint);
        if (maestro->messageStore == nullptr) return nullptr;
    }
    Rt2dMessage* message =
        static_cast<Rt2dMessage*>(_rwSListGetNewEntries(maestro->messageStore, count, kRt2dAnimHint));
    if (message == nullptr) return nullptr;
    for (RwInt32 i = 0; i < count; ++i, ++message) {
        message->messageType = rt2dMESSAGETYPENULL;
        message->index = -1;
        message->intParam1 = 0;
        if (_rt2dMessageStreamRead(maestro, message, stream) == nullptr) return nullptr;
    }
    return maestro;
}

// 0x006ffd68 _rt2dMaestroMessageListStreamRead: the count, then the store indices as one read.
// BUG(original): without a message list it creates both lists (the old store leaks).
Rt2dMaestro* _rt2dMaestroMessageListStreamRead(Rt2dMaestro* maestro, RwStream* stream) {
    RwInt32 count = 0;
    if (RwStreamReadInt32(stream, &count, 4) == nullptr) return nullptr;
    if (count < 1) return maestro;
    if (maestro->messageList == nullptr) {
        maestro->messageList = _rwSListCreate(static_cast<RwInt32>(sizeof(RwInt32)), kRt2dAnimHint);
        if (maestro->messageList == nullptr) return nullptr;
        maestro->messageStore = _rwSListCreate(static_cast<RwInt32>(sizeof(Rt2dMessage)), kRt2dAnimHint);
        if (maestro->messageList == nullptr) return nullptr;
    }
    void* entries = _rwSListGetNewEntries(maestro->messageList, count, kRt2dAnimHint);
    if (entries == nullptr) return nullptr;
    if (RwStreamReadInt32(stream, entries, static_cast<RwUInt32>(count) << 2) == nullptr) return nullptr;
    return maestro;
}

// 0x006ffe80 Rt2dMaestroAddMessages (Rt2dMaestroPostMessages)
Rt2dMaestro* Rt2dMaestroPostMessages(Rt2dMaestro* maestro, Rt2dMessage* message, RwInt32 num) {
    return PostMessagesToQueue(maestro, message, num);
}

// 0x007001f8 Rt2dMaestroAddFrameMessages_maybe (_rt2dMaestroMessageListPostByIndex): posts message list
// entry index: the store messages from its start up to the NULL-type one.
Rt2dMaestro* _rt2dMaestroMessageListPostByIndex(Rt2dMaestro* maestro, RwInt32 index) {
    const RwInt32 start = RwSListArray<RwInt32>(maestro->messageList)[index];
    Rt2dMessage* message = RwSListEntry<Rt2dMessage>(maestro->messageStore, start);
    if (message->messageType == rt2dMESSAGETYPENULL) return maestro;
    RwInt32 after = start + 1;
    const Rt2dMessage* scan;
    do {
        scan = RwSListEntry<Rt2dMessage>(maestro->messageStore, after);
        ++after;
    } while (scan->messageType != rt2dMESSAGETYPENULL);
    const RwInt32 num = after - start - 1;
    if (num <= 0) return maestro;
    return PostMessagesToQueue(maestro, message, num);
}
