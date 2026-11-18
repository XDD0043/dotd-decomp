// CinematicStream.cpp - reconstructed original translation unit 0x7f698-0x80a90 (GAME_TOC1, main_toc1), 15 functions, 14 live.
// Primary owner: CinematicStream (not a registered class)
// Other owners: CSGMovable (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x7f698  CinematicStream_RestoreActor_maybe
//   [x] 0x7f860  CinematicStream_RestartActorAnimIfInList_maybe
//   [x] 0x7fae0  CinematicStream_DestroyAnimTrackAnimation_maybe
//   [x] 0x7fb30  CinematicStream_CreateAnimTrackAnimation_maybe
//   [ ] 0x7fc90  CinematicStream_SaveFloatBlock9_maybe  (types 0 / 2 slot +0x30: no code calls it)  [left: save-only]
//   [x] 0x7fcb8  CinematicStream_LoadFloatBlock9_maybe
//   [ ] 0x7fce0  CSGMovable_SetLocalMatrix_NullChecked_maybe  [dead]
//   [x] 0x7fd20  CinematicStream_ResolveSceneLeaf_maybe
//   [x] 0x7fdf0  CinematicStream_RestoreSecondActor_maybe
//   [x] 0x7ff90  CinematicStream_RestartActorAnimAndClearNodeFlag2000_maybe
//   [x] 0x80050  CinematicStream_ApplyAnimTrackTime_maybe
//   [x] 0x80408  CinematicStream_IsActorSceneLeaf_WithSecond_maybe
//   [x] 0x804b0  CinematicStream_AttachActor_maybe
//   [x] 0x80608  CinematicStream_AttachSecondActor_maybe
//   [x] 0x807b0  CinematicStream_SaveActorMatrices_maybe
//
//   [x] 0x99b618  CinematicStream_CreateAnimTrackAnimation_Thunk  [inline]  (type 2's slot: the function itself)
//   [x] 0x99b640  CinematicStream_DestroyAnimTrackAnimation_Thunk  [inline]
//   [x] 0x99b668  CinematicStream_ApplyAnimTrackTime_Thunk  [inline]
//   [ ] 0x99b690  CinematicStream_SaveFloatBlock9_Thunk  [inline]  (slot +0x30, not called)
//   [x] 0x99b6b8  CinematicStream_LoadFloatBlock9_Thunk  [inline]
//   [x] 0x99b6e0  CinematicStream_ResolveAnimatedNode_Thunk  [inline]
//   [x] 0x99b708  CinematicStream_GetFloatBlock9Size_Thunk_maybe  [inline]
//   [x] 0x99b730  U32Array_Reserve_maybe  [inline]  (CKCinematicStreamCpnt.cpp ReserveWords)
#include <cstring>
#include <new>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rtanim/RtAnim.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/components/CKCinematicStreamCpnt.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"

namespace {

using SChannel = CKCinematicStreamCpnt::SChannel;

CSGLeaf* AsLeaf(IKSerializable* object) { return static_cast<CSGLeaf*>(object); }

// The modelling matrix of a node's frame copied into a kept matrix (16 words).
void KeepModelling(CMatrix34* matrix, IKSerializable* node) {
    std::memcpy(matrix, &static_cast<CSGMovable*>(node)->m_pRwFrame->modelling, sizeof(CMatrix34));
}

// The blend slot of the channel's actor: through its hook (vt+0xbc) or its node. The count stays 0 when the node has
// no blend mode the call answers (the original's local is not initialised in RestartActorAnimIfInList; 0 here, the
// node's path, as in CKCinematicBloc.cpp).
AnimBlendSlot* ActorBlendSlot(const SChannel* channel, CAnimatedNode* node, int32_t* count) {
    AnimBlendSlot* slots[2] = {nullptr, nullptr};
    *count = 0;
    if (channel->m_pUnk08 != nullptr) {
        static_cast<IKHook*>(channel->m_pUnk08)->GetBlendSlot(slots, count);  // vt+0xbc
    } else {
        node->GetBlendSlot(slots, count);  // 0x000c9978
    }
    return slots[0];
}

CKAnmKeyFrameController* SlotController(AnimBlendSlot* slot) {
    return static_cast<CKAnmKeyFrameController*>(
        static_cast<CKBlenderController*>(slot->m_pController)->m_apControllers[slot->m_unk10]);
}

// The blend slot's weight back on its active controller (PlayActorAnim's inline).
void SlotRestart(AnimBlendSlot* slot) {
    slot->m_unk14 = 0;
    if (slot->m_pController != nullptr) {
        static_cast<CKBlenderController*>(slot->m_pController)->m_unk58 = slot->m_unk10 != 0 ? 1.0f : 0.0f;  // TOC -0x69b0
    }
}

// Whether `a` or `b` is one of the stream's chunk bodies (the animations it gave its actors).
bool InChunkList(const TVector<uint8_t*, 1>* list, const void* a, const void* b) {
    const uint32_t count = list->m_ui32NbUsedElt;
    if (count == 0) return false;
    for (uint32_t i = 0; i < count; ++i) {
        const void* entry = list->m_pBlock[i];
        if (entry == a || entry == b) return true;
    }
    return false;
}

uint32_t Word(const uint8_t* image, uint32_t offset) {
    uint32_t word;
    std::memcpy(&word, image + offset, 4);
    return CinematicStream_FromBigEndian(word);
}
float Float(const uint8_t* image, uint32_t offset) {
    const uint32_t word = Word(image, offset);
    float value;
    std::memcpy(&value, &word, 4);
    return value;
}

}  // namespace

// 0x0007fb30 CinematicStream_CreateAnimTrackAnimation_maybe (types 0 and 2, slot +0x00): the chunk's animation made
// usable where it lies: its scheme (RpHAnim standard), its key frames' previous-frame indices turned into pointers, its
// custom data's sector entry the channel's block. 1.
uint8_t CinematicStream_CreateAnimTrackAnimation(SCinematicStreamTrackType* type, void* /*data*/) {
    RtAnimAnimation* animation = static_cast<RtAnimAnimation*>(type->m_pChunk->m_pData);
    animation->pFrames = animation + 1;
    RtAnimInterpolatorInfo* info = RtAnimGetInterpolatorInfo(1);
    animation->interpInfo = info;
    if (info->customDataSize < 1) {
        animation->customData = nullptr;
    } else {
        animation->customData = static_cast<uint8_t*>(animation->pFrames) +
                                static_cast<size_t>(animation->numFrames) * static_cast<size_t>(info->animKeyFrameSize);
    }
    RpHAnimStdKeyFrame* frames = static_cast<RpHAnimStdKeyFrame*>(animation->pFrames);
    for (int32_t i = 0; i < animation->numFrames; ++i) {
        // The file's index (0x24 bytes a key frame on the PS3: one key frame here).
        frames[i].prevFrame = frames + reinterpret_cast<uintptr_t>(frames[i].prevFrame);
    }
    RtAnimSectorEntryData* entry = RtAnimSectorEntry(animation);
    const AnimFloatBlock9* block = static_cast<const AnimFloatBlock9*>(type->m_pChannel->m_pBuffer);
    std::memcpy(entry->words00, block->m_aui32Unk00, sizeof(entry->words00));
    std::memcpy(&entry->word10, &block->m_unk10, 4);
    std::memcpy(entry->words14, block->m_av14, sizeof(entry->words14));
    entry->ref20 = block->m_pUnk20;
    type->m_pChunk->m_pData = animation;
    return 1;
}

// 0x0007fae0 CinematicStream_DestroyAnimTrackAnimation_maybe (slot +0x04: no code calls it).
void CinematicStream_DestroyAnimTrackAnimation(SCinematicStreamTrackType* type) {
    RtAnimAnimation* animation = static_cast<RtAnimAnimation*>(type->m_pChunk->m_pData);
    if (animation == nullptr) return;
    RtAnimAnimationDestroy(animation);
    type->m_pChunk->m_pData = nullptr;
}

// 0x00080050 CinematicStream_ApplyAnimTrackTime_maybe (types 0 and 2, slot +0x20): the chunk's animation on the actor
// at the segment's time (the frame in the 60 fps mode); with the first frame it is set, without an animation the
// actor's animation is reset. 1 while the animation goes on.
uint8_t CinematicStream_ApplyAnimTrackTime(SCinematicStreamTrackType* type) {
    SChannel* channel = type->m_pChannel;
    CAnimatedNode* node = static_cast<CAnimatedNode*>(channel->m_pUnk04);
    if (node == nullptr) return 0;
    RtAnimAnimation* animation = static_cast<RtAnimAnimation*>(type->m_pChunk->m_pData);
    int32_t count = 0;
    AnimBlendSlot* slot = ActorBlendSlot(channel, node, &count);
    float time;
    if (type->m_bStopped != 0) {
        time = type->m_fDt;
    } else if (type->m_ui32FrameRate == 0) {
        time = static_cast<float>(type->m_dSegmentTime);  // frsp
    } else {
        time = static_cast<float>(type->m_ui32FrameInSegment) / static_cast<float>(type->m_ui32FrameRate);  // fdivs
    }
    if (count == 0) {
        return static_cast<uint8_t>(node->PlayAnimAtTime(animation, time, type->m_bFirst, type->m_bPlaying, type->m_bStopped));
    }
    // The inline PlayAnimAtTime on the blend slot's active controller.
    if (type->m_bFirst != 0) {
        if (animation == nullptr && type->m_bStopped == 0) return 1;
        SlotRestart(slot);
        SlotController(slot)->SetAnim(0.0f, animation, true);  // 0x0007ab20
        if (animation == nullptr) {
            SlotRestart(slot);
            SlotController(slot)->Reset();  // vt+0x60
        }
    }
    if (type->m_bPlaying == 0 || animation == nullptr) return 0;
    CKAnmKeyFrameController* controller = SlotController(slot);
    if (controller->m_unk58 == nullptr) return 0;
    if (animation->duration < time) return 0;  // fcmpu, blt
    controller->m_unk50 = time;
    return SlotController(slot)->HasEnded(0.0f) ? 0 : 1;
}

// 0x0007f860 CinematicStream_RestartActorAnimIfInList_maybe (type 0's slot +0x18): an actor still playing (or about
// to play) one of the stream's animations is reset.
void CinematicStream_RestartActorAnimIfInList(SCinematicStreamTrackType* type, TVector<uint8_t*, 1>* chunkData,
                                              uint32_t /*withMedia*/) {
    SChannel* channel = type->m_pChannel;
    CAnimatedNode* node = static_cast<CAnimatedNode*>(channel->m_pUnk04);
    if (channel->m_pUnk08 == nullptr && node == nullptr) return;
    int32_t count = 0;
    AnimBlendSlot* slot = ActorBlendSlot(channel, node, &count);
    if (count == 0) {
        if (((node->m_sgProperties >> 9) & 3) - 1 >= 2) return;
        const CKAnmKeyFrameController* controller = node->ActiveController();
        if (!InChunkList(chunkData, controller->m_unk5c, controller->m_unk58)) return;  // GetActiveAnim / GetCurrentAnim
        node->RestartCurrentAnim();  // 0x000c97d8
        return;
    }
    CKAnmKeyFrameController* controller = SlotController(slot);
    if (!InChunkList(chunkData, controller->m_unk5c, controller->m_unk58)) return;
    SlotRestart(slot);
    SlotController(slot)->Reset();  // vt+0x60
}

// 0x000804b0 CinematicStream_AttachActor_maybe (type 0's slot +0x14, Finish): with media, the actor back under the
// parent RestoreActor kept, shown again without a hook, and its kept matrix put back when the channel asks.
void CinematicStream_AttachActor(SCinematicStreamTrackType* type, uint32_t withMedia) {
    SChannel* channel = type->m_pChannel;
    CSGLeaf* node = AsLeaf(channel->m_pUnk04);
    if (node == nullptr || node->IsKindOfClass(0x20b) == 0 || withMedia == 0) return;
    CSGBranch* kept = static_cast<CSGBranch*>(channel->m_pUnk0c);
    CSGBranch* parent = node->m_pParent;
    if (kept != parent && kept != nullptr) {
        parent->RemoveChild(node);  // vt+0x78
        kept->AddChild(node);       // vt+0x70
    }
    if (channel->m_pUnk08 == nullptr) node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4;
    if ((channel->m_unk14 & 1) != 0 && channel->m_pMatrix10 != nullptr) {
        node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(channel->m_pMatrix10));  // 0x000d0be8
    }
}

// 0x0007f698 CinematicStream_RestoreActor_maybe (type 0's slot +0x1c, the stream's first update): when the stream
// takes the actors over (+0xf8), the actor moves under its sector's root at the channel's position, its parent kept;
// without a hook it stops being hidden (+0x10 bit 2 cleared).
void CinematicStream_RestoreActor(SCinematicStreamTrackType* type, uint32_t takeOver) {
    SChannel* channel = type->m_pChannel;
    CSGLeaf* node = AsLeaf(channel->m_pUnk04);
    if (node == nullptr || node->IsKindOfClass(0x20b) == 0 || takeOver == 0) return;
    CSGBranch* parent = node->m_pParent;
    channel->m_pUnk0c = parent;
    const uint32_t sector = node->GetSectorIndex();  // vt+0x6c
    CKSector* owner = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[sector]);
    parent->RemoveChild(node);  // vt+0x78
    owner->m_pSectorRoot->AddChild(node);  // vt+0x70
    node->SetIdentity();  // 0x000d08f0
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.x = channel->m_v28.x;
    frame->modelling.pos.y = channel->m_v28.y;
    frame->modelling.pos.z = channel->m_v28.z;
    frame->modelling.flags &= 0xfffdffffu;  // rwMATRIXINTERNALIDENTITY
    RwFrame_MarkDirty(frame);
    if (channel->m_pUnk08 == nullptr) node->m_sgProperties &= 0xfffffffbu;
}

// 0x000807b0 CinematicStream_SaveActorMatrices_maybe (type 2's slot +0x10): the second node's matrix kept (with
// media), the first node flagged 0x2000 (with media), then the first node's matrix kept. 1.
uint8_t CinematicStream_SaveActorMatrices(SCinematicStreamTrackType* type, uint32_t withMedia) {
    SChannel* channel = type->m_pChannel;
    IKSerializable* second = channel->m_pUnk18;
    if (second != nullptr && second->IsKindOfClass(0x54b) != 0 && withMedia != 0) KeepModelling(channel->m_pMatrix24, second);
    IKSerializable* node = channel->m_pUnk04;
    if (node != nullptr && node->IsKindOfClass(0x54b) != 0 && withMedia != 0) {
        AsLeaf(node)->m_sgProperties = (AsLeaf(node)->m_sgProperties & 0xffffdfffu) | 0x2000;
    }
    node = type->m_pChannel->m_pUnk04;
    if (node != nullptr && node->IsKindOfClass(0x54b) != 0) KeepModelling(type->m_pChannel->m_pMatrix10, node);
    return 1;
}

// 0x00080608 CinematicStream_AttachSecondActor_maybe (type 2's slot +0x14): the second node back under its kept parent
// (detached from the first node's bones), shown, its matrix put back; then AttachActor for the first.
void CinematicStream_AttachSecondActor(SCinematicStreamTrackType* type, uint32_t withMedia) {
    SChannel* channel = type->m_pChannel;
    CSGLeaf* second = AsLeaf(channel->m_pUnk18);
    if (second != nullptr && second->IsKindOfClass(0x20b) != 0 && withMedia != 0) {
        CAnimatedNode* first = static_cast<CAnimatedNode*>(channel->m_pUnk04);
        CSGBranch* kept = static_cast<CSGBranch*>(channel->m_pUnk20);
        if (first != nullptr && first->IsKindOfClass(0x54b) != 0 && second->m_pParent != kept && kept != nullptr) {
            first->DetachChild(second);  // 0x000c9150
            kept->AddChild(second);      // vt+0x70
        }
        if (channel->m_pUnk1c == nullptr) second->m_sgProperties = (second->m_sgProperties & 0xfffffffbu) | 4;
        if ((channel->m_unk14 & 1) != 0 && channel->m_pMatrix24 != nullptr) {
            second->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(channel->m_pMatrix24));
        }
    }
    CinematicStream_AttachActor(type, withMedia & 0xff);
}

// 0x0007ff90 CinematicStream_RestartActorAnimAndClearNodeFlag2000_maybe (type 2's slot +0x18)
void CinematicStream_RestartActorAnimAndClearNodeFlag2000(SCinematicStreamTrackType* type,
                                                          TVector<uint8_t*, 1>* chunkData, uint32_t withMedia) {
    IKSerializable* node = type->m_pChannel->m_pUnk04;
    if (node != nullptr && node->IsKindOfClass(0x54b) != 0 && withMedia != 0) AsLeaf(node)->m_sgProperties &= 0xffffdfffu;
    CinematicStream_RestartActorAnimIfInList(type, chunkData, withMedia & 0xff);
}

// 0x0007fdf0 CinematicStream_RestoreSecondActor_maybe (type 2's slot +0x1c): the second node hung from the first
// node's bone 0 (its parent kept) at the identity; then RestoreActor for the first.
void CinematicStream_RestoreSecondActor(SCinematicStreamTrackType* type, uint32_t takeOver) {
    SChannel* channel = type->m_pChannel;
    CSGLeaf* second = AsLeaf(channel->m_pUnk18);
    if (second != nullptr && second->IsKindOfClass(0x20b) != 0 && takeOver != 0) {
        CAnimatedNode* first = static_cast<CAnimatedNode*>(channel->m_pUnk04);
        CSGBranch* parent = second->m_pParent;
        channel->m_pUnk20 = parent;
        if (first != nullptr && first->IsKindOfClass(0x54b) != 0 && first->GetSubtreeBoneCount(0) != 0) {
            if (parent != nullptr) parent->RemoveChild(second);  // vt+0x78
            first->AttachChildToGroup(0, second);  // 0x000c9218
        }
        second->SetIdentity();
        if (channel->m_pUnk1c == nullptr) second->m_sgProperties &= 0xfffffffbu;
    }
    CinematicStream_RestoreActor(type, takeOver & 0xff);
}

// 0x00080408 CinematicStream_IsActorSceneLeaf_WithSecond_maybe (type 2's PostLoad slot): both nodes' IsKindOfClass(0x20b),
// the answers not used.
void CinematicStream_IsActorSceneLeaf_WithSecond(SCinematicStreamTrackType* type) {
    if (type->m_pChannel->m_pUnk18 != nullptr) type->m_pChannel->m_pUnk18->IsKindOfClass(0x20b);
    if (type->m_pChannel->m_pUnk04 != nullptr) type->m_pChannel->m_pUnk04->IsKindOfClass(0x20b);
}

// 0x0007fd20 CinematicStream_ResolveSceneLeaf_maybe (type 2's slot +0x38, not called): a hook stands for its node.
IKSerializable* CinematicStream_ResolveSceneLeaf(IKSerializable* object) {
    if (object == nullptr) return nullptr;
    if (object->IsKindOfClass(2) != 0) return static_cast<IKHook*>(object)->m_pKGLObject;
    return object->IsKindOfClass(0x20b) != 0 ? object : nullptr;
}

// 0x0007fcb8 CinematicStream_LoadFloatBlock9_maybe
int32_t CinematicStream_LoadFloatBlock9(void* buffer, IKFile* file, int32_t /*type*/) {
    AnimFloatBlock9_LoadByteSwapped(static_cast<AnimFloatBlock9*>(buffer), file);
    return 1;
}

// DOTD (platform, not in the original): see the header. The anim image: the RtAnimAnimation header (0x1c bytes:
// scheme, frame counts, flags, duration, two pointer slots), numFrames RpHAnim key frames of 0x24 bytes (previous-frame
// index, time, quaternion, translation), then the scheme's custom data (its last 0x24 bytes the sector entry). The
// camera image: five words (+0x10 the key pointer slot), then 0x28-byte keys of ten floats.
uint8_t* CinematicStream_ConvertChunkBody(uint32_t type, const uint8_t* image, uint32_t size, uint8_t** nativeRaw) {
    if (image == nullptr) return nullptr;
    size_t nativeSize = 0;
    if (type == 0 || type == 2) {
        if (size < 0x1c) return nullptr;
        const uint32_t numFrames = Word(image, 0x4);
        const RtAnimInterpolatorInfo* info = RtAnimGetInterpolatorInfo(1);
        const uint32_t ps3Custom = 0x24;  // scheme 1's custom data on the PS3: the sector entry alone
        if (static_cast<uint64_t>(0x1c) + static_cast<uint64_t>(numFrames) * 0x24 + ps3Custom > size) return nullptr;
        // BUG(original): some channels get an animation with fewer nodes than their node's hierarchy (LVL010 PS30.KCS:
        // channel 5, a 54-node actor, a 2-frame 1-node animation; channels 7 and 8, 1-node animations for 6 and 54
        // nodes). RtAnimInterpolatorSetCurrentAnim (0x706fa8) takes the key frames of all the interpolator's nodes
        // (2 x its node count) and RpHAnim's interpolation negates the second quaternion in place: the PS3 reads past
        // the chunk (its 0x40 bytes of slack, then the heap behind it) and flips signs there. The host heap cannot be
        // reproduced; zeroed room for 2 x 256 more key frames behind the custom data keeps those reads and writes in
        // the chunk's own block (zero key frames: a zero dot product, nothing negated; the walk stops at the frame count).
        constexpr size_t kOverrunFrames = 2 * 256;
        nativeSize = sizeof(RtAnimAnimation) + static_cast<size_t>(numFrames) * sizeof(RpHAnimStdKeyFrame) +
                     static_cast<size_t>(info->customDataSize) + kOverrunFrames * sizeof(RpHAnimStdKeyFrame);
        uint8_t* raw = static_cast<uint8_t*>(::operator new[](nativeSize + 0x40));
        uint8_t* aligned = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(raw) + 0x3f) & ~static_cast<uintptr_t>(0x3f));
        std::memset(aligned, 0, nativeSize);
        RtAnimAnimation* animation = reinterpret_cast<RtAnimAnimation*>(aligned);
        animation->interpInfo = nullptr;
        animation->numFrames = static_cast<RwInt32>(numFrames);
        animation->numFrames2 = static_cast<RwInt32>(Word(image, 0x8));
        animation->flags = static_cast<RwInt32>(Word(image, 0xc));
        animation->duration = Float(image, 0x10);
        animation->pFrames = nullptr;
        animation->customData = nullptr;
        RpHAnimStdKeyFrame* frames = reinterpret_cast<RpHAnimStdKeyFrame*>(animation + 1);
        for (uint32_t i = 0; i < numFrames; ++i) {
            const uint32_t at = 0x1c + i * 0x24;
            frames[i].prevFrame = reinterpret_cast<RpHAnimStdKeyFrame*>(static_cast<uintptr_t>(Word(image, at)));
            frames[i].time = Float(image, at + 0x4);
            frames[i].q.imag.x = Float(image, at + 0x8);
            frames[i].q.imag.y = Float(image, at + 0xc);
            frames[i].q.imag.z = Float(image, at + 0x10);
            frames[i].q.real = Float(image, at + 0x14);
            frames[i].t.x = Float(image, at + 0x18);
            frames[i].t.y = Float(image, at + 0x1c);
            frames[i].t.z = Float(image, at + 0x20);
        }
        // The custom data: the sector entry at its end (words, the reference slot as read).
        if (info->customDataSize >= static_cast<RwInt32>(sizeof(RtAnimSectorEntryData))) {
            const uint32_t at = 0x1c + numFrames * 0x24 + ps3Custom - 0x24;
            RtAnimSectorEntryData* entry = reinterpret_cast<RtAnimSectorEntryData*>(
                reinterpret_cast<uint8_t*>(frames + numFrames) + info->customDataSize - sizeof(RtAnimSectorEntryData));
            for (uint32_t w = 0; w < 4; ++w) entry->words00[w] = Word(image, at + 4 * w);
            entry->word10 = Word(image, at + 0x10);
            for (uint32_t w = 0; w < 3; ++w) entry->words14[w] = Word(image, at + 0x14 + 4 * w);
            entry->ref20 = nullptr;  // the PS3's slot is overwritten by CreateAnimTrackAnimation
        }
        *nativeRaw = raw;
        return aligned;
    }
    if (type == 1) {
        if (size < 0x14) return nullptr;
        const uint32_t keys = (size - 0x14) / 0x28;
        nativeSize = sizeof(SCinematicCameraTrack) + static_cast<size_t>(keys) * sizeof(SCinematicCameraKey);
        uint8_t* raw = static_cast<uint8_t*>(::operator new[](nativeSize + 0x40));
        uint8_t* aligned = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(raw) + 0x3f) & ~static_cast<uintptr_t>(0x3f));
        std::memset(aligned, 0, nativeSize);
        SCinematicCameraTrack* track = reinterpret_cast<SCinematicCameraTrack*>(aligned);
        track->m_unk00 = Word(image, 0x0);
        track->m_ui32NbKeys = Word(image, 0x4);
        track->m_ui32NbFrames = Word(image, 0x8);
        track->m_fDuration = Float(image, 0xc);
        track->m_pKeys = nullptr;
        SCinematicCameraKey* out = reinterpret_cast<SCinematicCameraKey*>(track + 1);
        for (uint32_t k = 0; k < keys; ++k) {
            for (uint32_t f = 0; f < 10; ++f) out[k].m_af[f] = Float(image, 0x14 + k * 0x28 + 4 * f);
        }
        *nativeRaw = raw;
        return aligned;
    }
    return nullptr;
}
