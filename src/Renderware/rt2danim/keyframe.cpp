// keyframe.cpp - RW 3.7 tool/2danim/keyframe.c (0x6f87a8-0x6fb7e0): keyframe lists, their compact
// stream form, and the per-object frame state they are applied through. Ported from the PS3 library code.
// See Rt2dAnim.h.
//
// A keyframe list's data is a packed array that _rt2dKeyFrameListStreamReadTo builds: per changed object
// a Rt2dKeyFrameSet {flag, objectIdx, 8 unused bytes}, then the parts its flag names in this order:
// the transform (RwMatrix), colorOffs and colorMult (Rt2dKeyFrameColor), show (Rt2dKeyFrameShow) and
// morph (Rt2dKeyFrameMorph, its two object pointers holding directory indices); a set with flag 0x20
// ends it. The parts have their native sizes (the PS3's 0x10/0x40/0x10/0x10/0x10/0x10; on 64-bit hosts
// the morph record is 0x18).
//
// The frame state (Rt2dAnimProps::sceneCurrentState) has one Rt2dAnimObjectUpdate per scene child:
// Advance copies a keyframe's parts into it and marks them pending; Apply interpolates the pending
// transform and colours towards the next keyframe, then hands every pending part to the object.
#include "Renderware/rt2d/Rt2d.h"
#include "Renderware/rt2danim/Rt2dAnimPrivate.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"

namespace {
constexpr RwUInt32 kSetTransform = 0x01;
constexpr RwUInt32 kSetColorOffs = 0x02;
constexpr RwUInt32 kSetColorMult = 0x04;
constexpr RwUInt32 kSetShow = 0x08;
constexpr RwUInt32 kSetMorph = 0x10;
constexpr RwUInt32 kSetEnd = 0x20;

constexpr size_t kSetSize = sizeof(Rt2dKeyFrameSet);
constexpr size_t kTransformSize = sizeof(RwMatrix);
constexpr size_t kColorSize = sizeof(Rt2dKeyFrameColor);
constexpr size_t kShowSize = sizeof(Rt2dKeyFrameShow);
constexpr size_t kMorphSize = sizeof(Rt2dKeyFrameMorph);

RwUInt32 SetFlag(const RwUInt8* set) {
    RwUInt32 flag;
    std::memcpy(&flag, set, 4);
    return flag;
}
RwInt32 SetObjectIndex(const RwUInt8* set) {
    RwInt32 index;
    std::memcpy(&index, set + 4, 4);
    return index;
}
RwReal ReadReal(const RwUInt8* p, size_t at) {
    RwReal value;
    std::memcpy(&value, p + at, 4);
    return value;
}
}  // namespace

// 0x006f87a8 Rt2dKeyFrameListApply_maybe. With 0 < alpha < 1 every pending transform and colour of the
// objects this list changes is first interpolated into the object (from the frame state towards this
// list: fsubs, fmuls, fadds for the transform's pos/right/up rows; fsubs, fmadds for the colours, the
// offset scaled by 255), then every pending part of the frame state goes to its object.
Rt2dKeyFrameList* Rt2dKeyFrameListApply(Rt2dKeyFrameList* keyframeList, Rt2dAnimProps* props, RwReal alpha) {
    if (alpha > 0.0f && alpha < 1.0f && (SetFlag(keyframeList->data) & kSetEnd) == 0) {
        const RwUInt8* set = keyframeList->data;
        do {
            const RwUInt8* part = set + kSetSize;
            Rt2dAnimObjectUpdate* state =
                RwSListEntry<Rt2dAnimObjectUpdate>(props->sceneCurrentState, SetObjectIndex(set));
            if ((SetFlag(set) & kSetTransform) != 0) {
                if (state->hasTransform == 1) {
                    Rt2dObject* object = state->object;
                    const RwMatrix& from = state->transform.matrix;
                    // The keyframe's rows: right +0x00, up +0x10, pos +0x30.
                    RwMatrix* mtm = &object->MTM;
                    mtm->pos.z = alpha * (ReadReal(part, 0x38) - from.pos.z) + from.pos.z;
                    mtm->pos.x = alpha * (ReadReal(part, 0x30) - from.pos.x) + from.pos.x;
                    mtm->pos.y = alpha * (ReadReal(part, 0x34) - from.pos.y) + from.pos.y;
                    mtm->right.z = alpha * (ReadReal(part, 0x08) - from.right.z) + from.right.z;
                    mtm->right.x = alpha * (ReadReal(part, 0x00) - from.right.x) + from.right.x;
                    mtm->right.y = alpha * (ReadReal(part, 0x04) - from.right.y) + from.right.y;
                    mtm->up.x = alpha * (ReadReal(part, 0x10) - from.up.x) + from.up.x;
                    mtm->up.y = alpha * (ReadReal(part, 0x14) - from.up.y) + from.up.y;
                    mtm->up.z = alpha * (ReadReal(part, 0x18) - from.up.z) + from.up.z;
                    RwMatrixUpdate(&object->MTM);
                    Rt2dObjectMTMChanged(state->object);
                    state->hasTransform = 0;
                }
                part += kTransformSize;
            }
            if ((SetFlag(set) & kSetColorOffs) != 0) {
                if (state->hasColorOffs == 1) {
                    const RwRGBAReal& from = state->colorOffs.color;
                    RwRGBAReal* offs = &state->object->colorOffs;
                    offs->red = ppc::fmadds(alpha, ReadReal(part, 0x0) - from.red, from.red) * 255.0f;
                    offs->green = ppc::fmadds(alpha, ReadReal(part, 0x4) - from.green, from.green) * 255.0f;
                    offs->blue = ppc::fmadds(alpha, ReadReal(part, 0x8) - from.blue, from.blue) * 255.0f;
                    offs->alpha = ppc::fmadds(alpha, ReadReal(part, 0xc) - from.alpha, from.alpha) * 255.0f;
                    state->object->flag |= 8;
                    state->hasColorOffs = 0;
                }
                part += kColorSize;
            }
            if ((SetFlag(set) & kSetColorMult) != 0) {
                if (state->hasColorMult == 1) {
                    const RwRGBAReal& from = state->colorMult.color;
                    RwRGBAReal* mult = &state->object->colorMult;
                    mult->red = ppc::fmadds(alpha, ReadReal(part, 0x0) - from.red, from.red);
                    mult->green = ppc::fmadds(alpha, ReadReal(part, 0x4) - from.green, from.green);
                    mult->blue = ppc::fmadds(alpha, ReadReal(part, 0x8) - from.blue, from.blue);
                    mult->alpha = ppc::fmadds(alpha, ReadReal(part, 0xc) - from.alpha, from.alpha);
                    state->object->flag |= 8;
                    state->hasColorMult = 0;
                }
                part += kColorSize;
            }
            const RwUInt32 flag = SetFlag(set);
            if ((flag & kSetShow) != 0) part += kShowSize;
            if ((flag & kSetMorph) != 0) {
                if (state->hasMorph == 1) state->hasMorph = 0;
                part += kMorphSize;
            }
            set = part;
        } while ((SetFlag(set) & kSetEnd) == 0);
    }
    const RwInt32 count = _rwSListGetNumEntries(props->sceneCurrentState);
    Rt2dAnimObjectUpdate* state = RwSListArray<Rt2dAnimObjectUpdate>(props->sceneCurrentState);
    for (RwInt32 i = 0; i < count; ++i, ++state) {
        if (state->hasSomething != 1) continue;
        if (state->hasTransform != 0) {
            Rt2dObjectSetMTM(state->object, &state->transform.matrix);
            state->hasTransform = 0;
        }
        if (state->hasColorOffs != 0) {
            Rt2dObjectSetColorOffset(state->object, &state->colorOffs.color);
            state->hasColorOffs = 0;
        }
        if (state->hasColorMult != 0) {
            Rt2dObjectSetColorMultiplier(state->object, &state->colorMult.color);
            state->hasColorMult = 0;
        }
        if (state->hasShow != 0) {
            if (state->object->depth != state->show.depth) {
                Rt2dObjectSetDepth(state->object, state->show.depth);
                Rt2dSceneSetDepthDirty(props->scene);
            }
            Rt2dObjectSetVisible(state->object, state->show.show);
            state->hasShow = 0;
        }
        if (state->hasMorph != 0 && state->morph.source != nullptr) state->hasMorph = 0;
        state->hasSomething = 0;
    }
    return keyframeList;
}

// 0x006f9828 Rt2dKeyFrameListDestroy_maybe: the data (the compact array, or the locked RwSList form),
// then the list. TRUE for a non-null list.
RwBool Rt2dKeyFrameListDestroy(Rt2dKeyFrameList* keyframeList) {
    if (keyframeList == nullptr) return 0;
    if (keyframeList->isLocked == 0) {
        RwFree(keyframeList->data);
    } else {
        _rwSListDestroy(reinterpret_cast<RwSList*>(keyframeList->data));
    }
    RwFreeListFree(g_rt2dAnimFreeLists[kRt2dAnimFreeListKeyFrameList], keyframeList);
    return 1;
}

// 0x006f98f0 Rt2dAnimState_CreateFrameStateList_maybe: one cleared Rt2dAnimObjectUpdate per directory
// entry (the scene's children), each pointing at its object.
RwSList* _rt2dAnimPropsCreateSceneCurrentState(Rt2dAnimProps* props) {
    RwSList* list = _rwSListCreatePreallocated(static_cast<RwInt32>(sizeof(Rt2dAnimObjectUpdate)),
                                               _rwSListGetNumEntries(props->directory), kRt2dAnimHint);
    if (_rwSListGetNumEntries(props->directory) == 0) return list;
    _rwSListGetNewEntries(list, _rwSListGetNumEntries(props->directory), kRt2dAnimHint);
    Rt2dAnimObjectUpdate* state = RwSListArray<Rt2dAnimObjectUpdate>(list);
    Rt2dAnimObjectUpdate* const end = state + _rwSListGetNumEntries(list);
    Rt2dObject** object = RwSListArray<Rt2dObject*>(props->directory);
    for (; state != end; ++state, ++object) {
        state->hasSomething = 0;
        state->hasTransform = 0;
        state->hasColorOffs = 0;
        state->hasColorMult = 0;
        state->hasShow = 0;
        state->hasMorph = 0;
        state->object = *object;
    }
    return list;
}

// 0x006fa218 Rt2dKeyFrameListAdvance_maybe: copies every part of this list into the frame state of its
// object and marks it pending; a morph's two directory indices become the objects.
Rt2dKeyFrameList* Rt2dKeyFrameListAdvance(Rt2dKeyFrameList* keyframeList, Rt2dAnimProps* props) {
    const RwUInt8* set = keyframeList->data;
    while ((SetFlag(set) & kSetEnd) == 0) {
        const RwUInt8* part = set + kSetSize;
        Rt2dAnimObjectUpdate* state =
            RwSListEntry<Rt2dAnimObjectUpdate>(props->sceneCurrentState, SetObjectIndex(set));
        if ((SetFlag(set) & kSetTransform) != 0) {
            std::memcpy(&state->transform, part, kTransformSize);
            part += kTransformSize;
            state->hasSomething = 1;
            state->hasTransform = 1;
        }
        if ((SetFlag(set) & kSetColorOffs) != 0) {
            std::memcpy(&state->colorOffs, part, kColorSize);
            state->hasColorOffs = 1;
            state->hasSomething = 1;
            part += kColorSize;
        }
        if ((SetFlag(set) & kSetColorMult) != 0) {
            std::memcpy(&state->colorMult, part, kColorSize);
            state->hasColorMult = 1;
            state->hasSomething = 1;
            part += kColorSize;
        }
        if ((SetFlag(set) & kSetShow) != 0) {
            std::memcpy(&state->show, part, kShowSize);
            state->hasShow = 1;
            state->hasSomething = 1;
            part += kShowSize;
        }
        if ((SetFlag(set) & kSetMorph) != 0) {
            std::memcpy(&state->morph, part, kMorphSize);
            state->hasMorph = 1;
            state->hasSomething = 1;
            state->morph.source = _rt2dAnimPropsGet2dObjectByIndex(
                props, static_cast<RwInt32>(reinterpret_cast<intptr_t>(state->morph.source)));
            state->morph.destination = _rt2dAnimPropsGet2dObjectByIndex(
                props, static_cast<RwInt32>(reinterpret_cast<intptr_t>(state->morph.destination)));
            part += kMorphSize;
        }
        set = part;
    }
    return keyframeList;
}

// 0x006face8 _rt2dKeyFrameListStreamReadTo_maybe: the header {version, time, count}, then per object
// {flag, objectIdx} and the parts the flag names (the transform as an rwID_MATRIX chunk, colours as four
// reals, show as {show, depth}, morph as four words), read into a temporary Rt2dAnimObjectUpdate array
// and packed into the compact data (see the top of the file). A failed read frees the temporary array and
// returns null (the list itself is the caller's).
Rt2dKeyFrameList* _rt2dKeyFrameListStreamReadTo(RwStream* stream, Rt2dKeyFrameList* keyframeList) {
    RwInt32 header[3];
    if (RwStreamRead(stream, header, 0xc) != 0xc) return nullptr;
    RwMemNative32(header, 0xc);
    std::memcpy(&keyframeList->time, &header[1], 4);
    const RwInt32 count = header[2];
    Rt2dAnimObjectUpdate* updates = nullptr;
    RwUInt32 dataSize = static_cast<RwUInt32>(kSetSize);
    if (count != 0) {
        updates = static_cast<Rt2dAnimObjectUpdate*>(
            RwMalloc(static_cast<RwUInt32>(count) * static_cast<RwUInt32>(sizeof(Rt2dAnimObjectUpdate)), 0x101a9));
        if (updates == nullptr) return nullptr;
        // The PS3's block is not cleared; the bytes no reader fills (the show pad, the morph pad) are
        // copied into the data and never read. Cleared here so the data is the same on every run.
        if (count > 0) {
            std::memset(updates, 0, static_cast<size_t>(count) * sizeof(Rt2dAnimObjectUpdate));
            RwUInt32 size = 0;
            for (RwInt32 i = 0; i < count; ++i) {
                Rt2dAnimObjectUpdate* update = &updates[i];
                RwInt32 set[2];
                if (RwStreamRead(stream, set, 8) != 8) {
                    RwFree(updates);
                    return nullptr;
                }
                RwMemNative32(set, 8);
                const RwUInt32 flag = static_cast<RwUInt32>(set[0]);
                update->object = static_cast<Rt2dObject*>(Rt2dWordAsPointer(set[1]));
                update->hasSomething = 1;
                update->hasTransform = 0;
                update->hasColorOffs = 0;
                update->hasColorMult = 0;
                update->hasShow = 0;
                update->hasMorph = 0;
                size += static_cast<RwUInt32>(kSetSize);
                if ((flag & kSetTransform) != 0) {
                    if (RwStreamFindChunk(stream, 0xd, nullptr, nullptr) == 0 ||
                        RwMatrixStreamRead(stream, &update->transform.matrix) == nullptr) {
                        RwFree(updates);
                        return nullptr;
                    }
                    size += static_cast<RwUInt32>(kTransformSize);
                    update->hasTransform = 1;
                }
                if ((flag & kSetColorOffs) != 0) {
                    RwReal color[4];
                    if (RwStreamRead(stream, color, 0x10) != 0x10) {
                        RwFree(updates);
                        return nullptr;
                    }
                    size += static_cast<RwUInt32>(kColorSize);
                    RwMemNative32(color, 0x10);
                    update->colorOffs.color = {color[0], color[1], color[2], color[3]};
                    update->hasColorOffs = 1;
                }
                if ((flag & kSetColorMult) != 0) {
                    RwReal color[4];
                    if (RwStreamRead(stream, color, 0x10) != 0x10) {
                        RwFree(updates);
                        return nullptr;
                    }
                    size += static_cast<RwUInt32>(kColorSize);
                    RwMemNative32(color, 0x10);
                    update->colorMult.color = {color[0], color[1], color[2], color[3]};
                    update->hasColorMult = 1;
                }
                if ((flag & kSetShow) != 0) {
                    RwInt32 show[2];
                    if (RwStreamRead(stream, show, 8) != 8) {
                        RwFree(updates);
                        return nullptr;
                    }
                    RwMemNative32(show, 8);
                    size += static_cast<RwUInt32>(kShowSize);
                    update->show.show = show[0] != 0 ? 1 : 0;
                    update->show.depth = show[1];
                    update->hasShow = 1;
                }
                if ((flag & kSetMorph) != 0) {
                    RwInt32 morph[4];
                    if (RwStreamRead(stream, morph, 0x10) != 0x10) {
                        RwFree(updates);
                        return nullptr;
                    }
                    size += static_cast<RwUInt32>(kMorphSize);
                    RwMemNative32(morph, 0x10);
                    update->morph.source = static_cast<Rt2dObject*>(Rt2dWordAsPointer(morph[0]));
                    update->morph.destination = static_cast<Rt2dObject*>(Rt2dWordAsPointer(morph[1]));
                    std::memcpy(&update->morph.alpha, &morph[2], 4);
                    update->morph.pad1 = morph[3];
                    update->hasMorph = 1;
                }
            }
            dataSize = size + static_cast<RwUInt32>(kSetSize);
        }
    }
    RwUInt8* data = static_cast<RwUInt8*>(RwMalloc(dataSize, kRt2dAnimHint));
    RwUInt8* out = data;
    for (RwInt32 i = 0; i < count; ++i) {
        const Rt2dAnimObjectUpdate* update = &updates[i];
        const RwUInt32 flag = (update->hasTransform != 0 ? kSetTransform : 0u) |
                              (update->hasColorOffs != 0 ? kSetColorOffs : 0u) |
                              (update->hasColorMult != 0 ? kSetColorMult : 0u) |
                              (update->hasShow != 0 ? kSetShow : 0u) | (update->hasMorph != 0 ? kSetMorph : 0u);
        Rt2dKeyFrameSet set{};  // bytes 8..15 are left uninitialised by the PS3 and never read
        set.flag = flag;
        set.objectIdx = static_cast<RwInt32>(reinterpret_cast<intptr_t>(update->object));
        std::memcpy(out, &set, kSetSize);
        out += kSetSize;
        if (update->hasTransform != 0) {
            std::memcpy(out, &update->transform, kTransformSize);
            out += kTransformSize;
        }
        if (update->hasColorOffs != 0) {
            std::memcpy(out, &update->colorOffs, kColorSize);
            out += kColorSize;
        }
        if (update->hasColorMult != 0) {
            std::memcpy(out, &update->colorMult, kColorSize);
            out += kColorSize;
        }
        if (update->hasShow != 0) {
            std::memcpy(out, &update->show, kShowSize);
            out += kShowSize;
        }
        if (update->hasMorph != 0) {
            std::memcpy(out, &update->morph, kMorphSize);
            out += kMorphSize;
        }
    }
    const RwUInt32 end = kSetEnd;
    std::memcpy(out, &end, 4);  // the PS3 writes only the flag word of the end set
    keyframeList->isLocked = 0;
    keyframeList->data = data;
    if (updates != nullptr) RwFree(updates);
    return keyframeList;
}

// 0x006fb7e0 Rt2dKeyFrameListStreamRead_maybe: a list from the free list, then
// _rt2dKeyFrameListStreamReadTo (which leaks the list when it fails).
Rt2dKeyFrameList* Rt2dKeyFrameListStreamRead(RwStream* stream) {
    Rt2dKeyFrameList* keyframeList = static_cast<Rt2dKeyFrameList*>(
        RwFreeListAlloc(g_rt2dAnimFreeLists[kRt2dAnimFreeListKeyFrameList], kRt2dKeyFrameHint));
    return _rt2dKeyFrameListStreamReadTo(stream, keyframeList);
}
