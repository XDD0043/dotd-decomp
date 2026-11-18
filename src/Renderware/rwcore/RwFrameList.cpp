// RwFrameList.cpp - see RwFrameList.h.
#include "Renderware/rwcore/RwFrameList.h"
#include <cstddef>

#include <cstdint>
#include <cstring>
#include <mutex>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwSList.h"
#include "Renderware/rwcore/RwStream.h"

// 0x000d1ea8 rwSetHierarchyRoot (RW's static, compiled into the game's CSGMovable unit; k2000/scenegraph).
void rwSetHierarchyRoot(RwFrame* frame, RwFrame* root);

namespace {
// The frame registry's plugin chunks (_rwPluginRegistryReadDataChunks 0x0075d660 with frameTKList): the
// extension chunk, then each plugin chunk to its reader, or skipped. Null (0) on failure.
int32_t FramePluginReadDataChunks(RwStream* stream, RwFrame* frame) {
    uint32_t length = 0, version = 0;
    if (RwStreamFindChunk(stream, 3, &length, &version) == 0) return 0;  // rwID_EXTENSION
    // (RwStreamFindChunk has already checked the version range.)
    while (length > 0) {
        uint32_t readType = 0, readLength = 0;
        if (_rwStreamReadChunkHeader(stream, &readType, &readLength, nullptr, nullptr) == 0) return 0;
        if (readType == 0x11e) {  // rwID_HANIMPLUGIN: HAnimStreamRead_maybe
            if (HAnimStreamRead(stream, static_cast<RwInt32>(readLength), frame) == nullptr) return 0;
        } else if (RwStreamSkip(stream, readLength) == nullptr) {
            return 0;
        }
        length -= readLength + 12;  // rwCHUNKHEADERSIZE
    }
    return 1;
}

// RwMemNative32 + RwMemFloat32ToReal on a little-endian word.
uint32_t Native32(const uint8_t* b) {
    return static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) | (static_cast<uint32_t>(b[2]) << 16) |
           (static_cast<uint32_t>(b[3]) << 24);
}
}  // namespace

// The frame private flags (rwFRAMEPRIVATEHIERARCHYSYNCLTM / SYNCOBJ on a root, SUBTREESYNCLTM / SYNCOBJ on a
// frame).
constexpr RwUInt8 kHierarchySync = 0x3;
constexpr RwUInt8 kSubtreeSync = 0xc;
constexpr RwUInt8 kHierarchySyncLtm = 0x1;
constexpr RwUInt8 kSubtreeSyncLtm = 0x4;
constexpr RwUInt8 kSubtreeSyncObj = 0x8;

// RwFrameRemoveChild (baframe.c; PS3 inlined in 0x74c6a0 RwFrameAddChild).
RwFrame* RwFrameRemoveChild(RwFrame* child) {
    RwFrame* parent = static_cast<RwFrame*>(child->object.parent);
    RwFrame* cur = parent->child;
    if (cur == child) {
        parent->child = child->next;
    } else {
        while (cur->next != child) cur = cur->next;
        cur->next = child->next;
    }
    child->object.parent = nullptr;
    child->next = nullptr;
    rwSetHierarchyRoot(child, child);
    return RwFrameUpdateObjects(child);
}

namespace {
RwLLLink g_dirtyFrames = {&g_dirtyFrames, &g_dirtyFrames};  // RWSRCGLOBAL(dirtyFrameList)
// DOTD: the dirty list is shared by the load worker (CKLoadingManager::LoadLevel on keCThreadPool: RwFrameAddChild in
// IKFile_ReadBoneFrameList, RwFrameTransform in the Flash scenes' Rt2d shapes) and the main thread (_rwFrameSyncDirty in
// RwCameraBeginUpdate while a sector streams in); unlocked, a link changed during the walk crashed the render (G replays,
// one run in three, +15952 / +24944). Not in the original (RW keeps the list unlocked).
std::mutex g_dirtyFramesLock;

void DirtyListAdd(RwFrame* root) {
    std::lock_guard<std::mutex> lock(g_dirtyFramesLock);
    RwLLLink* link = &root->inDirtyListLink;
    if (link->next != nullptr) return;  // DOTD: game code clears the marks itself (CSGLeaf), the link stays
    link->next = g_dirtyFrames.next;
    link->prev = &g_dirtyFrames;
    g_dirtyFrames.next->prev = link;
    g_dirtyFrames.next = link;
}

// FrameSyncHierarchyRecurse (the LTM part).
void SyncHierarchyRecurse(RwFrame* frame, RwUInt8 flags) {
    for (; frame != nullptr; frame = frame->next) {
        const RwUInt8 accumulated = static_cast<RwUInt8>(flags | frame->object.privateFlags);
        if ((accumulated & kSubtreeSyncLtm) != 0) {
            RwMatrixMultiply(&frame->ltm, &frame->modelling, &static_cast<RwFrame*>(frame->object.parent)->ltm);
        }
        frame->object.privateFlags = static_cast<RwUInt8>(frame->object.privateFlags & ~kSubtreeSync);
        SyncHierarchyRecurse(frame->child, accumulated);
    }
}

// FrameSyncHierarchyLTMRecurse: only the LTM mark cleared.
void SyncHierarchyLtmRecurse(RwFrame* frame, RwUInt8 flags) {
    for (; frame != nullptr; frame = frame->next) {
        const RwUInt8 accumulated = static_cast<RwUInt8>(flags | frame->object.privateFlags);
        if ((accumulated & kSubtreeSyncLtm) != 0) {
            RwMatrixMultiply(&frame->ltm, &frame->modelling, &static_cast<RwFrame*>(frame->object.parent)->ltm);
            frame->object.privateFlags = static_cast<RwUInt8>(frame->object.privateFlags & ~kSubtreeSyncLtm);
        }
        SyncHierarchyLtmRecurse(frame->child, accumulated);
    }
}

// FrameSyncHierarchy (the LTM part; FrameSyncHierarchyRecurseNoLTM only syncs objects and clears the object marks).
void SyncHierarchy(RwFrame* root) {
    const RwUInt8 flags = root->object.privateFlags;
    if ((flags & kHierarchySyncLtm) != 0) {
        if ((flags & kSubtreeSyncLtm) != 0) root->ltm = root->modelling;
        SyncHierarchyRecurse(root->child, static_cast<RwUInt8>(flags & kSubtreeSyncLtm));
    } else {
        for (RwFrame* child = root->child; child != nullptr; child = child->next) {
            child->object.privateFlags = static_cast<RwUInt8>(child->object.privateFlags & ~kSubtreeSyncObj);
        }
    }
    root->object.privateFlags = static_cast<RwUInt8>(flags & ~(kHierarchySync | kSubtreeSync));
}
}  // namespace

void _rwFrameSyncHierarchyLTM(RwFrame* root) {
    const RwUInt8 flags = root->object.privateFlags;
    if ((flags & kSubtreeSyncLtm) != 0) root->ltm = root->modelling;
    SyncHierarchyLtmRecurse(root->child, flags);
    root->object.privateFlags = static_cast<RwUInt8>(flags & ~(kHierarchySyncLtm | kSubtreeSyncLtm));
}

void RwFrameDirtyListRemove(RwFrame* frame) {
    std::lock_guard<std::mutex> lock(g_dirtyFramesLock);
    RwLLLink* link = &frame->inDirtyListLink;
    if (link->next == nullptr) return;
    link->prev->next = link->next;
    link->next->prev = link->prev;
    link->next = nullptr;
    link->prev = nullptr;
}

// _rwFrameSyncDirty
void _rwFrameSyncDirty() {
    std::lock_guard<std::mutex> lock(g_dirtyFramesLock);
    for (RwLLLink* link = g_dirtyFrames.next; link != &g_dirtyFrames;) {
        RwLLLink* const next = link->next;
        RwFrame* root = reinterpret_cast<RwFrame*>(reinterpret_cast<uint8_t*>(link) - offsetof(RwFrame, inDirtyListLink));
        SyncHierarchy(root);
        link->next = nullptr;
        link->prev = nullptr;
        link = next;
    }
    g_dirtyFrames.next = &g_dirtyFrames;
    g_dirtyFrames.prev = &g_dirtyFrames;
}

// 0x0074bc80 RwFrameDestroyHierarchy
RwBool RwFrameDestroyHierarchy(RwFrame* frame) {
    if (frame == nullptr) return 1;
    for (RwFrame* child = frame->child; child != nullptr;) {
        RwFrame* next = child->next;
        RwFrameDestroyHierarchy(child);
        child = next;
    }
    _rwFrameDestroyLeaf(frame);  // FrameDestroyRecurseDeInitLeaf: no parent unlink, no RwFrameDestroy
    return 1;
}

// 0x0074a438 RwFrameUpdateObjects
RwFrame* RwFrameUpdateObjects(RwFrame* frame) {
    if ((frame->root->object.privateFlags & kHierarchySync) == 0) DirtyListAdd(frame->root);
    frame->root->object.privateFlags |= kHierarchySync;
    frame->object.privateFlags |= kSubtreeSync;
    return frame;
}

// 0x0074c300 RwFrameAddChildNoUpdate (baframe.c).
RwFrame* RwFrameAddChildNoUpdate(RwFrame* parent, RwFrame* child) {
    if (child->object.parent != nullptr) RwFrameRemoveChild(child);
    child->next = parent->child;
    parent->child = child;
    child->object.parent = parent;  // rwObjectSetParent
    rwSetHierarchyRoot(child, parent->root);
    return parent;
}

// 0x0074c6a0 RwFrameAddChild. The PS3 body: an old parent is left (RwFrameRemoveChild inlined), the frame
// is linked under the new one, a frame that was on the dirty list for its own hierarchy leaves it (its
// private bits 0-1 cleared), then the new root and the frame are marked.
RwFrame* RwFrameAddChild(RwFrame* parent, RwFrame* child) {
    if (child->object.parent != nullptr) RwFrameRemoveChild(child);
    child->next = parent->child;
    parent->child = child;
    child->object.parent = parent;
    rwSetHierarchyRoot(child, parent->root);
    if ((child->object.privateFlags & kHierarchySync) != 0) {
        RwFrameDirtyListRemove(child);
        child->object.privateFlags = static_cast<RwUInt8>(child->object.privateFlags & 0xfc);  // off the dirty list
    }
    RwFrameUpdateObjects(child);
    return parent;
}

// 0x00745280 _rwFrameListStreamRead
rwFrameList* _rwFrameListStreamRead(RwStream* stream, rwFrameList* frameList) {
    uint32_t size = 0, version = 0;
    if (RwStreamFindChunk(stream, 1, &size, &version) == 0) return nullptr;  // rwID_STRUCT
    uint8_t word[4];
    if (RwStreamRead(stream, word, 4) != 4) return nullptr;
    const RwInt32 numFrames = static_cast<RwInt32>(Native32(word));
    frameList->numFrames = numFrames;
    frameList->frames = static_cast<RwFrame**>(RwMalloc(static_cast<RwUInt32>(numFrames) * sizeof(RwFrame*), 0x3000e));
    if (frameList->frames == nullptr) return nullptr;
    if (numFrames < 1) return frameList;
    for (RwInt32 i = 0; i < numFrames; ++i) {
        uint8_t f[0x38];
        if (RwStreamRead(stream, f, 0x38) != 0x38) {
            RwFree(frameList->frames);
            return nullptr;
        }
        RwFrame* frame = RwFrameCreate();
        if (frame == nullptr) {
            RwFree(frameList->frames);
            return nullptr;
        }
        RwMatrix* mat = &frame->modelling;
        RwV3d* rows[4] = {&mat->right, &mat->up, &mat->at, &mat->pos};
        for (int r = 0; r < 4; ++r) {
            uint32_t bits[3] = {Native32(f + r * 12), Native32(f + r * 12 + 4), Native32(f + r * 12 + 8)};
            std::memcpy(rows[r], bits, 12);
        }
        const RwInt32 parentIndex = static_cast<RwInt32>(Native32(f + 0x30));
        // rwMatrixIsOrthonormalPositive(mat, 0.01f) (TOC2 -0x344c 0.01f, -0x3448 0.99f).
        if (_rwMatrixNormalError(mat) > 0x1.47ae14p-7f || _rwMatrixOrthogonalError(mat) > 0x1.47ae14p-7f ||
            _rwMatrixDeterminant(mat) < 0x1.fae148p-1f) {
            mat->flags &= 0xfffdfffcu;  // ~(rwMATRIXINTERNALIDENTITY | rwMATRIXTYPEORTHONORMAL)
        } else {
            mat->flags &= 0xfffdffffu;  // ~rwMATRIXINTERNALIDENTITY
        }
        frameList->frames[i] = frame;
        if (parentIndex >= 0) {
            // _rwFrameListDirtyListUpdate is 1 (0x00c45ad8): RwFrameAddChild (0x0074c6a0), not NoUpdate.
            RwFrameAddChild(frameList->frames[parentIndex], frame);
        }
    }
    for (RwInt32 i = 0; i < numFrames; ++i) {
        RwFrame* frame = frameList->frames[i];
        if (FramePluginReadDataChunks(stream, frame) == 0) {
            RwFrameDestroyHierarchy(frameList->frames[0]);
            RwFree(frameList->frames);
            return nullptr;
        }
        // A root frame (RwFrameGetRoot == the frame): RwFrameUpdateObjects (_rwFrameListDirtyListUpdate is 1).
        if (frame == frame->root) RwFrameUpdateObjects(frame);
    }
    return frameList;
}

// _rwFrameListDeinitialize (babinfrm.c; inlined in IKFile_ReadBoneFrameList 0xc8ef8)
rwFrameList* _rwFrameListDeinitialize(rwFrameList* frameList) {
    if (frameList->numFrames != 0) RwFree(frameList->frames);
    return frameList;
}
