// anim.cpp - RW 3.7 tool/2danim/anim.c (0x6f5f80-0x6f7b20): an animation's keyframe schedule and its
// playback time, ported from the PS3 library code. See Rt2dAnim.h.
//
// An Rt2dAnim holds an RwSList of _rt2dAnimKeyFrameSched {time, keyframe list} and three cursors: prev
// (the keyframe last applied), next (the one after it, null past the end) and last (the final one).
// Pointer comparisons between the cursors are the PS3's unsigned compares of addresses in one array.
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"
#include "crt/ppc_ops.h"

namespace {
_rt2dAnimKeyFrameSched* SchedArray(Rt2dAnim* anim) { return RwSListArray<_rt2dAnimKeyFrameSched>(anim->keyframeLists); }

// The forward step the PS3 inlines in Rt2dAnimAddDeltaFrameIndex, GotoKeyFrameListByIndex and
// AddDeltaTime: time = next's, Advance(next), prev = next, next = the following entry (null past last).
void StepForward(Rt2dAnim* anim, Rt2dAnimProps* props) {
    _rt2dAnimKeyFrameSched* next = anim->next;
    anim->currentTime = next->time;
    Rt2dKeyFrameListAdvance(next->keyframeList, props);
    _rt2dAnimKeyFrameSched* current = anim->next;
    anim->prev = current;
    anim->next = anim->last > current ? current + 1 : nullptr;  // cmplw last, current; bgt
}

// The backward step: time = prev's, Advance(prev), next = prev, prev = the entry before (null at 0).
void StepBackward(Rt2dAnim* anim, Rt2dAnimProps* props, _rt2dAnimKeyFrameSched* array) {
    _rt2dAnimKeyFrameSched* prev = anim->prev;
    anim->currentTime = prev->time;
    Rt2dKeyFrameListAdvance(prev->keyframeList, props);
    _rt2dAnimKeyFrameSched* current = anim->prev;
    anim->next = current;
    anim->prev = array < current ? current - 1 : nullptr;  // cmplw array, current; blt
}
}  // namespace

// 0x006f5f80 Rt2dAnimGetCurrentTime
RwReal Rt2dAnimGetCurrentTime(Rt2dAnim* anim) { return anim->currentTime; }

// 0x006f5f88 Rt2dAnimGetFinalKeyFrameListTime_maybe (no null check on last)
RwReal Rt2dAnimGetFinalKeyFrameListTime(Rt2dAnim* anim) { return anim->last->time; }

// 0x006f5f98 Rt2dAnimGetPrevFrameTime_maybe
RwReal Rt2dAnimGetPrevFrameTime(Rt2dAnim* anim) { return anim->prev == nullptr ? 0.0f : anim->prev->time; }

// 0x006f5fb8 Rt2dAnimGetNextFrameTime_maybe: the last keyframe's time past the end.
RwReal Rt2dAnimGetNextFrameTime(Rt2dAnim* anim) {
    if (anim->next != nullptr) return anim->next->time;
    return anim->last->time;
}

// 0x006f5fe0 Rt2dAnimIsInterpolated_maybe
RwBool Rt2dAnimIsInterpolated(Rt2dAnim* anim) { return static_cast<RwBool>((anim->flag >> 1) & 1u); }

// 0x006f5ff0 Rt2dAnimSetInterpolate_maybe
Rt2dAnim* Rt2dAnimSetInterpolate(Rt2dAnim* anim, RwBool interpolate) {
    if (interpolate != 0) {
        anim->flag |= 2u;
        return anim;
    }
    anim->flag &= ~2u;
    return anim;
}

// 0x006f6028 Rt2dAnimGetPrevFrameIndex_maybe: -1 before the first keyframe.
RwInt32 Rt2dAnimGetPrevFrameIndex(Rt2dAnim* anim) {
    _rt2dAnimKeyFrameSched* prev = anim->prev;
    if (prev == nullptr) return -1;
    return static_cast<RwInt32>(prev - SchedArray(anim));
}

// 0x006f6078 Rt2dAnimGetNextFrameIndex_maybe: the keyframe count past the end.
RwInt32 Rt2dAnimGetNextFrameIndex(Rt2dAnim* anim) {
    _rt2dAnimKeyFrameSched* next = anim->next;
    if (next != nullptr) return static_cast<RwInt32>(next - SchedArray(anim));
    return _rwSListGetNumEntries(anim->keyframeLists);
}

// 0x006f60e8 Rt2dAnimGetNumKeyFrameLists_maybe
RwInt32 Rt2dAnimGetNumKeyFrameLists(Rt2dAnim* anim) { return _rwSListGetNumEntries(anim->keyframeLists); }

// 0x006f6210 Rt2dAnimGetKeyFrameListByIndex_maybe (no range check)
Rt2dKeyFrameList* Rt2dAnimGetKeyFrameListByIndex(Rt2dAnim* anim, RwInt32 frameIndex) {
    return RwSListEntry<_rt2dAnimKeyFrameSched>(anim->keyframeLists, frameIndex)->keyframeList;
}

// 0x006f6240 Rt2dAnim_StepKeyFrameLists_maybe (Rt2dAnimAddDeltaFrameIndex: XXL2's function of the same
// shape): steps deltaFrame keyframes forward, advancing each.
// BUG(original): backwards (deltaFrame < 0) the count goes the wrong way (n-1 is never >= 0), so it
// steps back to the first keyframe whatever the count.
Rt2dAnim* Rt2dAnimAddDeltaFrameIndex(Rt2dAnim* anim, Rt2dAnimProps* props, RwInt32 deltaFrame) {
    _rt2dAnimKeyFrameSched* array = SchedArray(anim);
    if (deltaFrame > 0) {
        while (anim->next != nullptr) {
            StepForward(anim, props);
            if (--deltaFrame == 0) break;
        }
    } else if (deltaFrame < 0) {
        while (anim->prev != nullptr) {
            StepBackward(anim, props, array);
            if (--deltaFrame >= 0) break;
        }
    }
    return anim;
}

// 0x006f6390 Rt2dAnim_ResetPlayback_maybe (Rt2dAnimReset): time 0, before the first keyframe, which is
// advanced (its changes go into the frame state) but stays "next".
Rt2dAnim* Rt2dAnimReset(Rt2dAnim* anim, Rt2dAnimProps* props) {
    const RwInt32 count = _rwSListGetNumEntries(anim->keyframeLists);
    anim->currentTime = 0.0f;
    if (count > 0) {
        anim->prev = nullptr;
        anim->next = RwSListEntry<_rt2dAnimKeyFrameSched>(anim->keyframeLists, 0);
        anim->last = RwSListEntry<_rt2dAnimKeyFrameSched>(anim->keyframeLists, count - 1);
        Rt2dKeyFrameListAdvance(anim->next->keyframeList, props);
        return anim;
    }
    anim->last = nullptr;
    anim->prev = nullptr;
    anim->next = nullptr;
    return anim;
}

// 0x006f66a8 Rt2dAnimKeyFrameListDestroyCB_maybe: the per-entry callback of _rt2dAnimDestruct. The flag
// it updates is the caller's (unused) result word.
static Rt2dKeyFrameList* Rt2dAnimKeyFrameListDestroyCB(Rt2dAnim* /*anim*/, Rt2dAnimProps* /*props*/,
                                                       Rt2dKeyFrameList* keyframeList, RwReal /*time*/,
                                                       RwBool* result) {
    RwBool ok = 0;
    if (Rt2dKeyFrameListDestroy(keyframeList) != 0) ok = *result != 0 ? 1 : 0;  // (|x| - 1) >> 31 ^ 1
    *result = ok;
    return keyframeList;
}

// 0x006f67d0 Rt2dAnimTimeUpdate_maybe: applies the frame state; with interpolation (flag bit 1) and
// between two keyframes, interpolated by (time - prev) / (next - prev).
Rt2dAnim* Rt2dAnimTimeUpdate(Rt2dAnim* anim, Rt2dAnimProps* props) {
    Rt2dKeyFrameList* result;
    if ((anim->flag & 2u) != 0 && anim->prev != nullptr) {
        if (anim->next != nullptr) {
            const RwReal prevTime = anim->prev->time;
            const RwReal alpha = (anim->currentTime - prevTime) / (anim->next->time - prevTime);  // fsubs x2, fdivs
            result = Rt2dKeyFrameListApply(anim->next->keyframeList, props, alpha);
            return result != nullptr ? anim : nullptr;
        }
    } else if (anim->next != nullptr) {
        result = Rt2dKeyFrameListApply(anim->next->keyframeList, props, 0.0f);
        return result != nullptr ? anim : nullptr;
    }
    if (anim->last == nullptr) return nullptr;
    result = Rt2dKeyFrameListApply(anim->last->keyframeList, props, 0.0f);
    return result != nullptr ? anim : nullptr;
}

// 0x006f68c8 _rt2dAnimStreamRead_maybe: the keyframe count, then per keyframe its time,
// RwStreamFindChunk(0x1b0) and the keyframe list. last is the entry with the greatest time (the first
// of equal ones). props: passed by the caller, unused.
Rt2dAnim* _rt2dAnimStreamRead(Rt2dAnim* anim, RwStream* stream, Rt2dAnimProps* /*props*/) {
    RwInt32 count = 0;
    if (RwStreamRead(stream, &count, 4) != 4) return nullptr;
    RwMemNative32(&count, 4);
    anim->keyframeLists = _rwSListCreatePreallocated(static_cast<RwInt32>(sizeof(_rt2dAnimKeyFrameSched)), count,
                                                    kRt2dKeyFrameHint);
    if (count != 0) _rwSListGetNewEntries(anim->keyframeLists, count, kRt2dKeyFrameHint);
    anim->currentTime = 0.0f;
    anim->deltaTimeScale = 1.0f;
    anim->flag = 1;
    anim->last = nullptr;
    anim->prev = nullptr;
    anim->next = nullptr;
    _rt2dAnimKeyFrameSched* entry = SchedArray(anim);
    _rt2dAnimKeyFrameSched* const end = entry + count;
    for (; entry != end; ++entry) {
        RwReal time = 0.0f;
        if (RwStreamRead(stream, &time, 4) != 4) return nullptr;
        RwMemNative32(&time, 4);
        entry->time = time;
        if (RwStreamFindChunk(stream, 0x1b0, nullptr, nullptr) == 0) return nullptr;
        Rt2dKeyFrameList* keyframeList = Rt2dKeyFrameListStreamRead(stream);
        if (keyframeList == nullptr) return nullptr;
        entry->keyframeList = keyframeList;
        anim->next = SchedArray(anim);
        if (anim->last == nullptr || anim->last->time < time) anim->last = entry;  // fcmpu; blt
    }
    return anim;
}

// 0x006f6e80 Rt2dAnimGotoKeyFrameListByIndex_maybe: steps to keyframe targetFrameIndex (forwards from the
// current one, or from a reset when the target is before prev), advancing every keyframe on the way.
// BUG(original): the backwards loop has Rt2dAnimAddDeltaFrameIndex's count bug (reached only when prev
// is null, the count being the target index then, which is never negative in practice).
Rt2dAnim* Rt2dAnimGotoKeyFrameListByIndex(Rt2dAnim* anim, Rt2dAnimProps* props, RwInt32 targetFrameIndex) {
    _rt2dAnimKeyFrameSched* target = SchedArray(anim) + targetFrameIndex;
    if (anim->prev > target) {  // cmplw prev, target; bgt: Rt2dAnimReset inlined, then one step
        const RwInt32 count = _rwSListGetNumEntries(anim->keyframeLists);
        anim->currentTime = 0.0f;
        if (count > 0) {
            anim->prev = nullptr;
            anim->next = RwSListEntry<_rt2dAnimKeyFrameSched>(anim->keyframeLists, 0);
            anim->last = RwSListEntry<_rt2dAnimKeyFrameSched>(anim->keyframeLists, count - 1);
            Rt2dKeyFrameListAdvance(anim->next->keyframeList, props);
        } else {
            anim->last = nullptr;
            anim->prev = nullptr;
            anim->next = nullptr;
        }
        SchedArray(anim);  // the PS3 calls _rwSListGetArray and drops the result
        if (anim->next != nullptr) StepForward(anim, props);
    }
    RwInt32 steps = targetFrameIndex;
    if (anim->prev != nullptr) steps = static_cast<RwInt32>(target - anim->prev);  // subf, srawi 3
    _rt2dAnimKeyFrameSched* array = SchedArray(anim);
    if (steps > 0) {
        while (anim->next != nullptr) {
            StepForward(anim, props);
            if (--steps == 0) break;
        }
    } else if (steps < 0) {
        while (anim->prev != nullptr) {
            StepBackward(anim, props, array);
            if (--steps >= 0) break;
        }
    }
    return anim;
}

// 0x006f7350 Rt2dAnimDestruct_maybe (_rt2dAnimDestruct): destroys every keyframe list, then the list.
Rt2dAnim* _rt2dAnimDestruct(Rt2dAnim* anim, Rt2dAnimProps* props) {
    _rt2dAnimKeyFrameSched* entry = SchedArray(anim);
    _rt2dAnimKeyFrameSched* const end = entry + _rwSListGetNumEntries(anim->keyframeLists);
    RwBool result = 0;  // the PS3's local is never initialised; only the callback reads it
    for (; entry != end; ++entry) {
        Rt2dAnimKeyFrameListDestroyCB(anim, props, entry->keyframeList, entry->time, &result);
    }
    _rwSListDestroy(anim->keyframeLists);
    anim->keyframeLists = nullptr;
    return anim;
}

// 0x006f7428 Rt2dAnimAddDeltaTime_maybe: time += deltaTimeScale * deltaTime (fmadds), clamped to
// [0, last keyframe time]; every keyframe crossed is advanced (one step per loop). Past an end the global
// end-reached callback gets the time left over (divided back by the scale).
// BUG(original): a backward step (time going down) runs back to the first keyframe (the count bug of
// Rt2dAnimAddDeltaFrameIndex); the loop then sees the first keyframe at or before the time, takes the
// backward branch again with nothing to do, and never ends. The game never adds a negative time.
Rt2dAnim* Rt2dAnimAddDeltaTime(Rt2dAnim* anim, Rt2dAnimProps* props, RwReal deltaTime) {
    const RwReal currentTime = anim->currentTime;
    const RwReal scale = anim->deltaTimeScale;
    RwReal newTime = ppc::fmadds(scale, deltaTime, currentTime);
    RwInt32 direction = 1;
    if (!(currentTime < newTime)) {
        if (currentTime == newTime) return anim;  // ble after blt not taken: equal
        direction = -1;                           // greater, or unordered
    }
    RwInt32 endReached;
    RwReal remaining;
    if (newTime < 0.0f) {
        remaining = newTime / scale;
        endReached = 1;
        newTime = 0.0f;
    } else {
        const RwReal lastTime = anim->last->time;
        if (newTime > lastTime) {
            const RwReal over = newTime - lastTime;
            newTime = lastTime;
            endReached = 1;
            remaining = over / scale;
        } else {
            remaining = 0.0f;
            endReached = 0;
        }
    }
    for (;;) {
        _rt2dAnimKeyFrameSched* next = anim->next;
        if (next == nullptr || !(next->time <= newTime)) {  // cror lt|eq
            _rt2dAnimKeyFrameSched* prev = anim->prev;
            if (prev == nullptr) break;
            if (prev->time <= newTime) break;  // ble
        }
        _rt2dAnimKeyFrameSched* array = SchedArray(anim);
        if (direction > 0) {
            if (anim->next == nullptr) continue;
            RwInt32 steps = direction;
            do {
                StepForward(anim, props);
                if (--steps == 0) break;
            } while (anim->next != nullptr);
        } else if (direction < 0) {
            if (anim->prev == nullptr) continue;
            RwInt32 steps = direction;
            do {
                StepBackward(anim, props, array);
                if (--steps >= 0) break;
            } while (anim->prev != nullptr);
        }
    }
    anim->currentTime = newTime;
    if (endReached == 1 && g_rt2dAnimOnEndReachedCallBack != nullptr) {
        g_rt2dAnimOnEndReachedCallBack(anim, props, remaining);
    }
    return anim;
}
