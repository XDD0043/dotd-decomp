// RtAnim.cpp - see RtAnim.h.
#include "Renderware/rtanim/RtAnim.h"

#include <cstring>

#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwStream.h"

namespace {
// The registered scheme table (0xcfa04c, 16 entries of 0x34 bytes) and its count (0xced59c).
RtAnimInterpolatorInfo g_interpolatorInfo[kRtAnimMaxInterpolators];
RwInt32 g_numInterpolatorInfo = 0;

// RwStreamReadInt32 / RwStreamReadReal (0x757128 / 0x757200): RwStreamRead, then the little-endian words to native
// (a copy on a little-endian host). 0 when RwStreamRead returns 0.
RwBool ReadWords(RwStream* stream, void* data, RwUInt32 size) { return RwStreamRead(stream, data, size) != 0; }
}  // namespace

// 0x00707870 RtAnimInitialize / 0x00707920 _rtAnimOpen / 0x007078b8 _rtAnimClose: the table is emptied (the close
// of the previous engine run), the animation free list is the host heap.
RwBool RtAnimInitialize() {
    g_numInterpolatorInfo = 0;
    std::memset(g_interpolatorInfo, 0, sizeof(g_interpolatorInfo));
    return 1;
}

// 0x00706a68 RtAnimRegisterInterpolationScheme_maybe
RwBool RtAnimRegisterInterpolationScheme(const RtAnimInterpolatorInfo* info) {
    if (g_numInterpolatorInfo >= kRtAnimMaxInterpolators) return 0;
    for (RwInt32 i = 0; i < g_numInterpolatorInfo; ++i) {
        if (g_interpolatorInfo[i].typeID == info->typeID) return 0;
    }
    g_interpolatorInfo[g_numInterpolatorInfo] = *info;
    ++g_numInterpolatorInfo;
    return 1;
}

// 0x00706b70 RtAnimGetInterpolatorInfo_maybe
RtAnimInterpolatorInfo* RtAnimGetInterpolatorInfo(RwInt32 typeID) {
    for (RwInt32 i = 0; i < g_numInterpolatorInfo; ++i) {
        if (g_interpolatorInfo[i].typeID == typeID) return &g_interpolatorInfo[i];
    }
    return nullptr;
}

namespace {
// The allocation both the stream reader and Create make (RWEngineInstance +0x108 with hint 0x3001b): the header,
// numFrames key frames, numFrames2 second key frames, then the scheme's custom data.
RtAnimAnimation* AllocateAnimation(RtAnimInterpolatorInfo* info, RwInt32 numFrames, RwInt32 numFrames2) {
    const size_t keyFrameBytes = static_cast<size_t>(numFrames) * static_cast<size_t>(info->animKeyFrameSize);
    const size_t keyFrame2Bytes = static_cast<size_t>(numFrames2) * static_cast<size_t>(info->animKeyFrameSize2);
    // The PS3 header is 0x1c bytes (+ 0x1c in the original's size); the host header is sizeof(RtAnimAnimation).
    RtAnimAnimation* animation = static_cast<RtAnimAnimation*>(RwMalloc(
        static_cast<RwUInt32>(keyFrameBytes + static_cast<size_t>(info->customDataSize) + keyFrame2Bytes + sizeof(RtAnimAnimation)),
        0x3001b));
    animation->interpInfo = info;
    animation->numFrames = numFrames;
    animation->numFrames2 = numFrames2;
    animation->pFrames = animation + 1;
    if (info->customDataSize > 0) {
        animation->customData = static_cast<uint8_t*>(animation->pFrames) + keyFrame2Bytes + keyFrameBytes;
    } else {
        animation->customData = nullptr;
    }
    return animation;
}
}  // namespace

// 0x00707d58 RtAnimAnimationStreamRead
RtAnimAnimation* RtAnimAnimationStreamRead(RwStream* stream) {
    RwInt32 version = 0, typeID = 0, numFrames = 0, numFrames2 = 0, flags = 0;
    RwReal duration = 0.0f;
    if (!ReadWords(stream, &version, 4)) return nullptr;
    if (version >= 0x102) return nullptr;
    if (!ReadWords(stream, &typeID, 4)) return nullptr;
    // The scheme is looked up before the counts are read (null: nothing more is read).
    RtAnimInterpolatorInfo* info = RtAnimGetInterpolatorInfo(typeID);
    if (info == nullptr) return nullptr;
    if (version < 0x101) {
        if (!ReadWords(stream, &numFrames, 4)) return nullptr;
        numFrames2 = 0;
    } else {
        if (!ReadWords(stream, &numFrames, 4)) return nullptr;
        if (!ReadWords(stream, &numFrames2, 4)) return nullptr;
    }
    if (!ReadWords(stream, &flags, 4)) return nullptr;
    if (!ReadWords(stream, &duration, 4)) return nullptr;
    RtAnimAnimation* animation = AllocateAnimation(info, numFrames, numFrames2);
    animation->duration = duration;
    animation->flags = flags;
    info->keyFrameStreamReadCB(stream, animation);  // the result is not looked at
    return animation;
}

// 0x00708118 RtAnimAnimationCreate
RtAnimAnimation* RtAnimAnimationCreate(RwReal duration, RwInt32 typeID, RwInt32 numFrames, RwInt32 flags) {
    RtAnimInterpolatorInfo* info = RtAnimGetInterpolatorInfo(typeID);
    if (info == nullptr) return nullptr;
    RtAnimAnimation* animation = AllocateAnimation(info, numFrames, 0);
    animation->duration = duration;
    animation->flags = flags;
    return animation;
}

// 0x00706da0 RtAnimAnimationDestroy_maybe
RwBool RtAnimAnimationDestroy(RtAnimAnimation* animation) {
    RwFree(animation);
    return 1;
}

namespace {
// The key frame walk's step (0x7070b4 and its copies): the first key frame size, or the second when the frame time's
// lowest bit is set (rlwinm r9, time, 2, 29, 29 → +0x28 / +0x2c).
RwInt32 TimeBit(const void* keyFrame) {
    uint32_t bits;
    std::memcpy(&bits, &static_cast<const RtAnimKeyFrameHeader*>(keyFrame)->time, 4);
    return static_cast<RwInt32>(bits & 1);
}
uint8_t* NextKeyFrame(const RtAnimInterpolator* interpolator, void* keyFrame) {
    const RwInt32 size = TimeBit(keyFrame) ? interpolator->currentAnimKeyFrameSize2 : interpolator->currentAnimKeyFrameSize;
    return static_cast<uint8_t*>(keyFrame) + size;
}
RtAnimInterpFrameHeader* InterpFrame(RtAnimInterpolator* interpolator, RwInt32 nodeIndex) {
    return static_cast<RtAnimInterpFrameHeader*>(RtAnimInterpolatorGetInterpFrame(interpolator, nodeIndex));
}

// The body of 0x00706fa8 RtAnimInterpolatorSetCurrentAnim, which AddAnimTime (0x708564, 0x7086d8) and SubAnimTime
// (0x708a90) repeat inline: the scheme's sizes and callbacks, every node interpolated at time 0 between key frame i and
// the i-th frame of the second set, then the frame pairs and the walk's next frame.
void SetCurrentAnimBody(RtAnimInterpolator* interpolator, RtAnimAnimation* animation) {
    interpolator->currentTime = 0.0f;
    interpolator->pCurrentAnim = animation;
    const RtAnimInterpolatorInfo* info = animation->interpInfo;
    const RwInt32 numNodes = interpolator->numNodes;
    interpolator->currentInterpKeyFrameSize = info->interpKeyFrameSize;
    interpolator->currentAnimKeyFrameSize = info->animKeyFrameSize;
    interpolator->currentAnimKeyFrameSize2 = info->animKeyFrameSize2;
    interpolator->keyFrameApplyCB = info->keyFrameApplyCB;
    interpolator->keyFrameBlendCB = info->keyFrameBlendCB;
    interpolator->keyFrameInterpolateCB = info->keyFrameInterpolateCB;
    interpolator->keyFrameAddCB = info->keyFrameAddCB;
    uint8_t* next = static_cast<uint8_t*>(animation->pFrames) + numNodes * info->animKeyFrameSize;
    if (numNodes > 0) {
        uint8_t* second = next;
        RwInt32 i = 0;
        do {
            uint8_t* first = static_cast<uint8_t*>(animation->pFrames) + i * interpolator->currentAnimKeyFrameSize;
            interpolator->keyFrameInterpolateCB(InterpFrame(interpolator, i), first, second, 0.0f, animation->customData, i);
            ++i;
            second = NextKeyFrame(interpolator, second);
        } while (interpolator->numNodes > i);
        uint8_t* first = static_cast<uint8_t*>(animation->pFrames);
        next = first + interpolator->numNodes * interpolator->currentAnimKeyFrameSize;
        if (interpolator->numNodes > 0) {
            RwInt32 k = 0;
            do {
                RtAnimInterpFrameHeader* frame = InterpFrame(interpolator, k);
                ++k;
                frame->keyFrame2 = next;
                frame->keyFrame1 = first;
                first += interpolator->currentAnimKeyFrameSize;
                next = NextKeyFrame(interpolator, next);
            } while (interpolator->numNodes > k);
        }
    }
    interpolator->pNextFrame = next;
}

// The callback calls at the end of AddAnimTime / SubAnimTime: a callback that returns null is cleared.
void RunCallBacks(RtAnimInterpolator* interpolator, RwBool callBack, RwBool loop) {
    if (callBack != 0 && interpolator->pAnimCallBack != nullptr) {
        if (interpolator->pAnimCallBack(interpolator, interpolator->pAnimCallBackData) == nullptr) {
            interpolator->pAnimCallBack = nullptr;
        }
    }
    if (loop != 0 && interpolator->pAnimLoopCallBack != nullptr) {
        if (interpolator->pAnimLoopCallBack(interpolator, interpolator->pAnimLoopCallBackData) == nullptr) {
            interpolator->pAnimLoopCallBack = nullptr;
        }
    }
}
}  // namespace

// 0x00706e30 RtAnimAnimationGetNumNodes
RwInt32 RtAnimAnimationGetNumNodes(const RtAnimAnimation* animation) {
    uint8_t* first = static_cast<uint8_t*>(animation->pFrames);
    uint8_t* frame = first;
    RwInt32 count = 0;
    while (static_cast<RtAnimKeyFrameHeader*>(static_cast<void*>(frame))->prevFrame !=
           static_cast<RtAnimKeyFrameHeader*>(static_cast<void*>(first))) {
        ++count;
        frame += TimeBit(frame) ? animation->interpInfo->animKeyFrameSize2 : animation->interpInfo->animKeyFrameSize;
    }
    return count;
}

// 0x00706e90 RtAnimInterpolatorCreate
RtAnimInterpolator* RtAnimInterpolatorCreate(RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize) {
    // RWEngineInstance +0x108 (hint 0x3001b): 0x50 + numNodes * size (the host: sizeof and the host frame size).
    const RwInt32 hostSize = RtAnimHostInterpKeyFrameSize(maxInterpKeyFrameSize);
    RtAnimInterpolator* interpolator = static_cast<RtAnimInterpolator*>(
        RwMalloc(static_cast<RwUInt32>(numNodes * hostSize) + static_cast<RwUInt32>(sizeof(RtAnimInterpolator)), 0x3001b));
    interpolator->numNodes = numNodes;
    interpolator->currentTime = 0.0f;
    interpolator->animCallBackTime = -1.0f;
    interpolator->currentAnimKeyFrameSize2 = -1;
    interpolator->maxInterpKeyFrameSize = maxInterpKeyFrameSize;
    interpolator->parentAnimation = interpolator;
    interpolator->keyFrameAddCB = nullptr;
    interpolator->pCurrentAnim = nullptr;
    interpolator->pNextFrame = nullptr;
    interpolator->pAnimCallBack = nullptr;
    interpolator->pAnimCallBackData = nullptr;
    interpolator->pAnimLoopCallBack = nullptr;
    interpolator->pAnimLoopCallBackData = nullptr;
    interpolator->currentInterpKeyFrameSize = hostSize;  // PS3: maxInterpKeyFrameSize
    interpolator->currentAnimKeyFrameSize = -1;
    interpolator->isSubInterpolator = 0;
    interpolator->offsetInParent = 0;
    interpolator->keyFrameApplyCB = nullptr;
    interpolator->keyFrameInterpolateCB = nullptr;
    interpolator->keyFrameBlendCB = nullptr;
    return interpolator;
}

// 0x00706f68 RtAnimInterpolatorDestroy
void RtAnimInterpolatorDestroy(RtAnimInterpolator* interpolator) { RwFree(interpolator); }

// 0x00706fa8 RtAnimInterpolatorSetCurrentAnim
RwBool RtAnimInterpolatorSetCurrentAnim(RtAnimInterpolator* interpolator, RtAnimAnimation* animation) {
    SetCurrentAnimBody(interpolator, animation);
    return 1;
}

// 0x00707188 RtAnimInterpolatorSetAnimLoopCallBack
void RtAnimInterpolatorSetAnimLoopCallBack(RtAnimInterpolator* interpolator, RtAnimCallBack callBack, void* data) {
    interpolator->pAnimLoopCallBackData = data;
    interpolator->pAnimLoopCallBack = callBack;
}

// 0x00707198 RtAnimInterpolatorSetAnimCallBack
void RtAnimInterpolatorSetAnimCallBack(RtAnimInterpolator* interpolator, RtAnimCallBack callBack, RwReal time,
                                       void* data) {
    interpolator->pAnimCallBackData = data;
    interpolator->pAnimCallBack = callBack;
    interpolator->animCallBackTime = time;
}

// 0x00707998 RtAnimInterpolatorSetKeyFrameCallBacks
RwBool RtAnimInterpolatorSetKeyFrameCallBacks(RtAnimInterpolator* interpolator, RwInt32 typeID) {
    const RtAnimInterpolatorInfo* info = RtAnimGetInterpolatorInfo(typeID);
    if (info == nullptr) return 0;
    interpolator->keyFrameApplyCB = info->keyFrameApplyCB;
    interpolator->keyFrameBlendCB = info->keyFrameBlendCB;
    interpolator->keyFrameInterpolateCB = info->keyFrameInterpolateCB;
    interpolator->keyFrameAddCB = info->keyFrameAddCB;
    return 1;
}

// 0x00708298 RtAnimInterpolatorAddAnimTime
RwBool RtAnimInterpolatorAddAnimTime(RtAnimInterpolator* interpolator, RwReal time) {
    if (!(time > 0.0f)) return 1;
    RtAnimAnimation* animation = interpolator->pCurrentAnim;
    const RwReal current = interpolator->currentTime;
    const RwReal callBackTime = interpolator->animCallBackTime;
    const RwInt32 numNodes = interpolator->numNodes;
    const RwReal duration = animation->duration;
    RwBool callBack = 0;
    RwBool loop = 0;
    RwReal t;
    if (current < callBackTime) {
        t = time + current;
        callBack = callBackTime <= t;  // the callback time is crossed
    } else {
        t = time + current;
    }
    interpolator->currentTime = t;
    if (duration < t) {
        // The loop: the time wraps (the callback fires again if the wrapped time is past it) and the animation restarts.
        do {
            t = t - duration;
            callBack |= (t >= callBackTime) ? 1 : 0;
            interpolator->currentTime = t;
        } while (duration < t);
        SetCurrentAnimBody(interpolator, animation);
        loop = 1;
        interpolator->currentTime = t;
    }
    if (interpolator->pNextFrame == nullptr) {
        // No next frame (after SubAnimTime): the animation is set again, keeping the time.
        const RwReal kept = interpolator->currentTime;
        SetCurrentAnimBody(interpolator, animation);
        interpolator->currentTime = kept;
    }
    // The key frame walk: while the next frame's previous frame is due, the node that holds it moves on to the next one.
    uint8_t* end = static_cast<uint8_t*>(animation->pFrames) +
                   animation->numFrames2 * interpolator->currentAnimKeyFrameSize2 +
                   animation->numFrames * interpolator->currentAnimKeyFrameSize;
    uint8_t* next = static_cast<uint8_t*>(interpolator->pNextFrame);
    if (next < end) {
        RtAnimKeyFrameHeader* previous = static_cast<RtAnimKeyFrameHeader*>(static_cast<void*>(next))->prevFrame;
        if (!(previous->time > interpolator->currentTime)) {
            RwInt32 search = 0;
            for (;;) {
                RtAnimInterpFrameHeader* frame;
                do {
                    frame = InterpFrame(interpolator, search);
                    ++search;
                    if (!(numNodes > search)) search = 0;
                } while (frame->keyFrame2 != previous);
                frame->keyFrame1 = previous;
                void* taken = interpolator->pNextFrame;
                frame->keyFrame2 = taken;
                next = NextKeyFrame(interpolator, taken);
                interpolator->pNextFrame = next;
                if (!(end > next)) break;
                previous = static_cast<RtAnimKeyFrameHeader*>(static_cast<void*>(next))->prevFrame;
                if (previous->time > interpolator->currentTime) break;
            }
        }
    }
    for (RwInt32 i = 0; i < numNodes; ++i) {
        RtAnimInterpFrameHeader* frame = InterpFrame(interpolator, i);
        interpolator->keyFrameInterpolateCB(frame, frame->keyFrame1, frame->keyFrame2, interpolator->currentTime,
                                            interpolator->pCurrentAnim->customData, i);
    }
    RunCallBacks(interpolator, callBack, loop);
    return 1;
}

// 0x00708870 RtAnimInterpolatorSubAnimTime
RwBool RtAnimInterpolatorSubAnimTime(RtAnimInterpolator* interpolator, RwReal time) {
    const RwReal current = interpolator->currentTime;
    const RwReal callBackTime = interpolator->animCallBackTime;
    RwBool callBack;
    RwReal t;
    bool wrap;
    if (current > callBackTime) {
        t = current - time;
        callBack = (callBackTime >= t) ? 1 : 0;
        interpolator->currentTime = t;
        wrap = !(t >= 0.0f);
    } else {
        t = current - time;
        callBack = 0;
        interpolator->currentTime = t;
        wrap = t < 0.0f;
    }
    RtAnimAnimation* animation = interpolator->pCurrentAnim;
    RwBool loop = 0;
    if (!wrap) {
        // Every node walks back until its first key frame is not after the time, then is interpolated.
        RwInt32 left = interpolator->numNodes - 1;
        if (interpolator->numNodes != 0) {
            uint8_t* frameBytes = static_cast<uint8_t*>(RtAnimInterpolatorGetInterpFrame(interpolator, 0));
            for (;;) {
                RtAnimInterpFrameHeader* frame = static_cast<RtAnimInterpFrameHeader*>(static_cast<void*>(frameBytes));
                RtAnimKeyFrameHeader* first = static_cast<RtAnimKeyFrameHeader*>(frame->keyFrame1);
                while (first->time > interpolator->currentTime) {
                    frame->keyFrame2 = first;
                    first = first->prevFrame;
                    frame->keyFrame1 = first;
                }
                interpolator->keyFrameInterpolateCB(frame, frame->keyFrame1, frame->keyFrame2, interpolator->currentTime,
                                                    interpolator->pCurrentAnim->customData,
                                                    interpolator->numNodes - left - 1);
                if (left == 0) break;
                --left;
                frameBytes += interpolator->currentInterpKeyFrameSize;
            }
        }
        interpolator->pNextFrame = nullptr;
    } else {
        // Under 0: the time wraps up by whole durations, the animation restarts and plays forward to it.
        do {
            t = t + animation->duration;
        } while (t < 0.0f);
        SetCurrentAnimBody(interpolator, animation);
        RtAnimInterpolatorAddAnimTime(interpolator, t);
        if (!(interpolator->currentTime >= interpolator->animCallBackTime)) callBack |= 1;
        loop = 1;
    }
    RunCallBacks(interpolator, callBack, loop);
    return 1;
}

// 0x00708c70 RtAnimInterpolatorSetCurrentTime
RwBool RtAnimInterpolatorSetCurrentTime(RtAnimInterpolator* interpolator, RwReal time) {
    const RwReal delta = time - interpolator->currentTime;
    if (delta < 0.0f) {
        RtAnimInterpolatorSubAnimTime(interpolator, -delta);
    } else {
        RtAnimInterpolatorAddAnimTime(interpolator, delta);
    }
    return 1;
}

// 0x00707c50 RtAnimInterpolatorCreateSubInterpolator_maybe
RtAnimInterpolator* RtAnimInterpolatorCreateSubInterpolator(RtAnimInterpolator* parentAnim, RwInt32 startNode,
                                                            RwInt32 numNodes, RwInt32 maxInterpKeyFrameSize) {
    if (maxInterpKeyFrameSize == -1) maxInterpKeyFrameSize = parentAnim->maxInterpKeyFrameSize;
    const RwInt32 hostSize = RtAnimHostInterpKeyFrameSize(maxInterpKeyFrameSize);
    RtAnimInterpolator* interpolator = static_cast<RtAnimInterpolator*>(
        RwMalloc(static_cast<RwUInt32>(numNodes * hostSize) + static_cast<RwUInt32>(sizeof(RtAnimInterpolator)), 0x3001b));
    interpolator->currentTime = 0.0f;
    interpolator->animCallBackTime = -1.0f;
    interpolator->numNodes = numNodes;
    interpolator->currentAnimKeyFrameSize2 = -1;
    interpolator->maxInterpKeyFrameSize = maxInterpKeyFrameSize;
    interpolator->keyFrameAddCB = nullptr;
    interpolator->parentAnimation = parentAnim;
    interpolator->offsetInParent = startNode;
    interpolator->isSubInterpolator = 1;
    interpolator->pCurrentAnim = nullptr;
    interpolator->pNextFrame = nullptr;
    interpolator->pAnimCallBack = nullptr;
    interpolator->pAnimCallBackData = nullptr;
    interpolator->pAnimLoopCallBack = nullptr;
    interpolator->pAnimLoopCallBackData = nullptr;
    interpolator->currentInterpKeyFrameSize = hostSize;  // PS3: maxInterpKeyFrameSize
    interpolator->currentAnimKeyFrameSize = -1;
    interpolator->keyFrameApplyCB = nullptr;
    interpolator->keyFrameInterpolateCB = nullptr;
    interpolator->keyFrameBlendCB = nullptr;
    return interpolator;
}

// 0x007071a8 RtAnimInterpolatorBlend
RwBool RtAnimInterpolatorBlend(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1, RtAnimInterpolator* inAnim2,
                               RwReal alpha) {
    for (RwInt32 i = 0; i < outAnim->numNodes; ++i) {
        outAnim->keyFrameBlendCB(RtAnimInterpolatorGetInterpFrame(outAnim, i), RtAnimInterpolatorGetInterpFrame(inAnim1, i),
                                 RtAnimInterpolatorGetInterpFrame(inAnim2, i), alpha);
    }
    return 1;
}

// 0x007072a0 RtAnimInterpolatorAddTogether
RwBool RtAnimInterpolatorAddTogether(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim1,
                                     RtAnimInterpolator* inAnim2) {
    for (RwInt32 i = 0; i < outAnim->numNodes; ++i) {
        outAnim->keyFrameAddCB(RtAnimInterpolatorGetInterpFrame(outAnim, i), RtAnimInterpolatorGetInterpFrame(inAnim1, i),
                               RtAnimInterpolatorGetInterpFrame(inAnim2, i));
    }
    return 1;
}

// 0x00707820 RtAnimInterpolatorCopy
RwBool RtAnimInterpolatorCopy(RtAnimInterpolator* outAnim, RtAnimInterpolator* inAnim) {
    std::memcpy(outAnim + 1, inAnim + 1,
                static_cast<size_t>(outAnim->currentInterpKeyFrameSize) * static_cast<size_t>(outAnim->numNodes));
    return 1;
}
