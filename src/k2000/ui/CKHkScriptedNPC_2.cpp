// CKHkScriptedNPC_2.cpp - reconstructed original translation unit 0x5c7c80-0x5c9bc0 (GAME_TOC2, main_toc2), 31 functions, 31 live.
// Primary owner: CKHkScriptedNPC (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5c7c80  CKHkScriptedNPC_Resume
//   [x] 0x5c7ca8  CKHkScriptedNPC_Pause
//   [x] 0x5c7cd0  CKHkScriptedNPC_OnLevelExit_maybe
//   [x] 0x5c7da8  CKHkScriptedNPC_ResetRuntime
//   [x] 0x5c7e08  CKHkScriptedNPC_ResetToInitialState_maybe
//   [x] 0x5c7e48  CKHkScriptedNPC_PostLoad
//   [ ] 0x5c7eb0  CKHkScriptedNPC_Save
//   [x] 0x5c7ed8  CKHkScriptedNPC_LevelReset  (RecursiveRegistration: CKHkActorBase's (IKHook's, inherited), then the starter's KStub_Return1_2361b0: nothing)
//   [x] 0x5c7f30  CKHkScriptedNPC_HandleMessage
//   [x] 0x5c8160  CKHkScriptedNPC_Construct_2  (= 0x5c81d0 CKHkScriptedNPC_Construct, CKHkScriptedNPC.h)
//   [x] 0x5c81d0  CKHkScriptedNPC_Construct
//   [x] 0x5c8240  CKHkScriptedNPC_DestroyArray
//   [x] 0x5c82e8  CKHkScriptedNPC_ClearReferences
//   [x] 0x5c8360  CKHkScriptedNPC_vfFC
//   [x] 0x5c83c8  CKHkScriptedNPC_vfF8
//   [x] 0x5c84a8  CKHkScriptedNPC_OnDeactivate
//   [x] 0x5c85d8  CKHkScriptedNPC_OnActivate
//   [x] 0x5c8780  CKHkScriptedNPC_TrySwitchBlock_maybe
//   [x] 0x5c8a08  CKHkScriptedNPC_vfCC
//   [x] 0x5c8ab0  CKHkScriptedNPC_vfD4
//   [x] 0x5c8b58  CKHkScriptedNPC_ResolveTriggerProperty
//   [x] 0x5c8c88  CKHkScriptedNPC_GetAnchorPosition_maybe
//   [x] 0x5c8d30  CKHkScriptedNPC_ReinitRuntime
//   [x] 0x5c8f28  CKHkScriptedNPC_QueueSignalsAndChainNextBlock_maybe
//   [x] 0x5c9050  CKHkScriptedNPC_BaseDestructor
//   [x] 0x5c90f0  CKHkScriptedNPC_DeletingDestructor
//   [x] 0x5c91a0  CKHkScriptedNPC_Destructor
//   [x] 0x5c9240  CKHkScriptedNPC_CreateArray
//   [x] 0x5c9338  CKHkScriptedNPC_Create
//   [x] 0x5c93b8  CKHkScriptedNPC_Update
//   [x] 0x5c9560  CKHkScriptedNPC_Load
//
//   [ ] 0x9cd560  CKHkScriptedNPC_IsKindOf  [inline]
//   [ ] 0x9cd5b8  CKHkScriptedNPC_GetClassGroup  [inline]
//   [ ] 0x9cd5c0  CKHkScriptedNPC_GetClassId  [inline]
#include "k2000/ui/CKHkScriptedNPC.h"
#include "k2000/core/IKInfo.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/logic/CKMarkedFX.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/KBase9C8C.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/core/Stub.h"

namespace {
// The TVector<T, 1> push the Load inlines: grows by one element when full (0 -> 1).
template <class T>
void PushBack(TVector<T, 1>& v, T value) {
    const uint32_t length = v.m_ui32NbUsedElt;
    if (v.m_ui32NbElt == length) {
        uint32_t capacity = length + 1;
        if (capacity == 0) capacity = 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        v.m_ui32NbElt = capacity;
    }
    v.m_pBlock[v.m_ui32NbUsedElt] = value;
    v.m_ui32NbUsedElt = v.m_ui32NbUsedElt + 1;
}
}  // namespace

// 0x005c9560 CKHkScriptedNPC_Load
int32_t CKHkScriptedNPC::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // through TocBridge_CKHkActorBase_d82_maybe_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pUnk2C);
    IKFile_ReadRef(file, &m_pUnk30);
    ReadU8(file, &m_unk4D);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // BUG(original): a new one-element block replaces the old one (not freed); the length is not reset.
    m_vpUnk34.m_ui32NbElt = 1;
    m_vpUnk34.m_pBlock = static_cast<KBase9C8C**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(KBase9C8C*))));
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* ref = nullptr;
        IKFile_ReadRef(file, &ref);
        PushBack(m_vpUnk34, static_cast<KBase9C8C*>(ref));  // the behaviour blocks
    }
    ReadU8(file, &m_unk51);
    ReadU8(file, &m_unk52);
    ReadU8(file, &m_unk53);
    ReadU8(file, &m_unk4E);
    ReadU8(file, &m_unk4F);
    m_tsUnk78.Load(file, 0);
    IKFile_ReadRef(file, &m_pUnk20);
    IKFile_ReadRef(file, &m_pUnk24);
    ReadU32LE(file, &count);
    m_vpUnk40.m_ui32NbElt = 1;
    m_vpUnk40.m_pBlock = static_cast<Entry**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry*))));
    for (uint32_t i = 0; i < count; ++i) {
        Entry* entry = new Entry;  // OperatorNew(8), no constructor
        ReadU8(file, &entry->m_unk0);
        ReadU32LE(file, &entry->m_unk4);
        PushBack(m_vpUnk40, entry);
    }
    return 1;
}

// 0x005c7e08 CKHkScriptedNPC_SetDefaultState: the two default bytes copied to the current ones.
void CKHkScriptedNPC::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    m_unk4C = m_unk4D;
    m_unk50 = m_unk51;
}

// 0x005c7da8 CKHkScriptedNPC_ResetRuntime (the Start). KStub_Nop_5cebf0(+0x20, this) is empty.
void CKHkScriptedNPC::Start() {
    CKHkActorBase::Start();
    m_unk58 = 0xffffffffu;
    m_unk80 = 0;
    m_pUnk28 = nullptr;
    m_unk54 = 0;
}

// 0x005c93b8 CKHkScriptedNPC_Update: the actor base's update (WorldObjectBase_Update_Nop 0x3f6e68, empty), then for an
// active NPC (+0x4c) the block switch (vt+0xf4), the current block's update (vt+0x6c) unless it ended (+0x68), the
// next block's update while it waits (vt+0x78: the one the current block's entry +0x40 names, or the following block
// for -2 when the current one is not the last; not the current one itself nor an index past the blocks), and the
// marked effects of the animation marks (CKMarkedFX_UpdateFromAnimMarks 0x5d0640 on +0x20).
void CKHkScriptedNPC::Update(IKTime* clock) {
    if (m_unk4C == 0) return;
    TrySwitchBlock();  // vt+0xf4 (the clock passed along, not used)
    if (m_unk60 < m_vpUnk34.m_ui32NbUsedElt && m_unk68 == 0) {
        m_vpUnk34.m_pBlock[m_unk60]->Update(clock);  // vt+0x6c
        const uint32_t current = m_unk60;
        const uint32_t count = m_vpUnk34.m_ui32NbUsedElt;
        if (current < count) {
            uint32_t next = m_vpUnk40.m_pBlock[current]->m_unk4;
            bool run = true;
            if (current == next || count <= next) {
                if (next != 0xfffffffeu || count - 1 == current) {
                    run = false;
                } else {
                    next = current + 1;
                }
            }
            if (run) m_vpUnk34.m_pBlock[next]->PreUpdate(clock);  // vt+0x78
        }
    }
    static_cast<CKMarkedFX*>(m_pUnk20)->UpdateFromAnimMarks(clock);  // 0x005d0640
}

// 0x005c8b58 CKHkScriptedNPC_GetInfo, with 0x005c7a30 GetTriggerProp99 (+0x60) and 0x005c7a40 GetTriggerProp9B (+0x58).
// The actor base (KStub_Return1 0x3f7140) answers 1.
int32_t CKHkScriptedNPC::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    if (info->m_ui32Id == 0x99) {
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKHkScriptedNPC*>(o)->m_unk60; }, 1);
    }
    if (info->m_ui32Id == 0x9b) {
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKHkScriptedNPC*>(o)->m_unk58; }, 1);
    }
    return 1;
}

namespace {
// The node's frame (CSGMovable +0x04).
RwFrame* NodeFrame(IKSerializable* node) { return static_cast<CSGMovable*>(node)->m_pRwFrame; }

// The node's hidden bit (+0x10 bit 2) set to the negation of the shown byte +0x50 (OnActivate, ReinitRuntime).
void ApplyShown(IKSerializable* node, uint8_t shown) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | (static_cast<uint32_t>(shown ^ 1u) << 2);
}

// The node back at its position of OnActivate (+0x6c): the frame's modelling position, the identity flag cleared, the
// frame marked dirty (RwFrame_MarkDirty 0x10698).
void RestorePosition(CKHkScriptedNPC* npc) {
    RwFrame* frame = NodeFrame(npc->m_pKGLObject);
    frame->modelling.pos.z = npc->m_unk6C.z;
    frame->modelling.pos.x = npc->m_unk6C.x;
    frame->modelling.pos.y = npc->m_unk6C.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

}  // namespace

// 0x005c7e48 CKHkScriptedNPC_PostLoad: CKHkActorBase's (IKLife_PostLoad), then for type 0 the trigger starter's
// (TriggerEventList_PostLoad_maybe 0x236330); 1.
int32_t CKHkScriptedNPC::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);
    if (type == 0) m_tsUnk78.PostLoad(0);
    return 1;
}

// 0x005c7f30 CKHkScriptedNPC_MessageProc: CKHkActorBase's actor messages first, then the block messages (all answer 0):
// 0x996 (data: a block number from 1) and 0x998 (the block after the current one) make it the next block and try to
// switch to it, the previous next / prepared blocks put back when that fails; 0x997 nothing; 0x999 (data: a block
// number from 1) makes it the next block without chaining (+0x80) and tries to switch. Any other message 1. The two
// answers merged: 3 wins, then 2, then 0 when the base answered 0.
int32_t CKHkScriptedNPC::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x997) {
        own = 0;
    } else if (message == 0x996 || message == 0x998) {
        const uint32_t next =
            message == 0x996 ? static_cast<uint32_t>(*static_cast<const int32_t*>(data) - 1) : m_unk60 + 1;
        const uint32_t savedNext = m_unk64;
        m_unk64 = next;
        const uint32_t savedPrepared = m_unk5C;
        PrepareBlock(next);  // vt+0xf8
        if (TrySwitchBlock() == 0) {  // vt+0xf4 (0)
            m_unk64 = savedNext;
            PrepareBlock(savedPrepared);
        }
        own = 0;
    } else if (message == 0x999) {
        m_unk80 = 1;
        const uint32_t next = static_cast<uint32_t>(*static_cast<const int32_t*>(data) - 1);
        m_unk64 = next;
        PrepareBlock(next);
        TrySwitchBlock();
        own = 0;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base != 0 ? own : 0;
}

// 0x005c8d30 CKHkScriptedNPC_ReinitRuntime (vt+0x54): not ended, +0x54 cleared. Unless the life flag +0x0c bit 2: the
// node back at its position, the first block prepared and switched to when there are blocks and the NPC is active, the
// node shown per +0x50; with it: the prepared block undone, no current block, the first one next, none prepared. Then
// every block's vt+0x58.
void CKHkScriptedNPC::Restart() {
    m_unk68 = 0;
    m_unk54 = 0;
    if ((m_bitArray & 4u) == 0) {
        RestorePosition(this);
        if (m_vpUnk34.m_ui32NbUsedElt != 0 && m_unk4C != 0) {
            m_unk64 = 0;
            PrepareBlock(0);
            TrySwitchBlock();
        }
        ApplyShown(m_pKGLObject, m_unk50);
    } else {
        UnprepareNext();  // vt+0x100
        m_unk60 = 0xffffffffu;
        m_unk64 = 0;
        m_unk5C = 0xffffffffu;
    }
    for (uint32_t i = 0; i < m_vpUnk34.m_ui32NbUsedElt; ++i) m_vpUnk34.m_pBlock[i]->Vf58();
}

// 0x005c82e8 CKHkScriptedNPC_Destroy. BUG(original)?: the entries of +0x40 are counted by the blocks' vector (+0x3c);
// every NPC loads one entry per block.
void CKHkScriptedNPC::Destroy() {
    for (uint32_t i = 0; i < m_vpUnk34.m_ui32NbUsedElt; ++i) delete m_vpUnk40.m_pBlock[i];  // 0x0076ba08 OperatorDelete
}

// 0x005c7cd0 CKHkScriptedNPC_OnLevelExit_maybe (vt+0x68): CKHkActorBase's Stop (empty), the current block left for the
// user (vt+0x68) with no current or next block, the prepared block undone (vt+0x100). KStub_Nop_5cebf8 (the marked
// effects) does nothing.
void CKHkScriptedNPC::Stop() {
    CKHkActorBase::Stop();
    if (m_unk60 < m_vpUnk34.m_ui32NbUsedElt) {
        m_vpUnk34.m_pBlock[m_unk60]->Leave(m_pUnk2C);
        m_unk64 = 0xffffffffu;
        m_unk60 = 0xffffffffu;
    }
    UnprepareNext();
}

// 0x005c85d8 CKHkScriptedNPC_OnActivate (vt+0xa0): CKHkActorBase's (the meca group's active actors), nothing prepared,
// the node's position kept (+0x6c), not ended; with blocks the first one next (prepared and switched to when active),
// else none; the node shown per +0x50; every block's runtime reset (vt+0x50) and the marked effects' channels.
void CKHkScriptedNPC::VfA0() {
    CKHkActorBase::VfA0();
    m_unk5C = 0xffffffffu;
    const RwFrame* frame = NodeFrame(m_pKGLObject);
    m_unk6C.x = frame->modelling.pos.x;
    m_unk6C.z = frame->modelling.pos.z;
    m_unk6C.y = frame->modelling.pos.y;
    m_unk68 = 0;
    if (m_vpUnk34.m_ui32NbUsedElt == 0) {
        m_unk60 = 0xffffffffu;
        m_unk64 = 0xffffffffu;
    } else {
        m_unk60 = 0xffffffffu;
        m_unk64 = 0;
        if (m_unk4C != 0) {
            PrepareBlock(0);
            TrySwitchBlock();
        }
    }
    ApplyShown(m_pKGLObject, m_unk50);
    for (uint32_t i = 0; i < m_vpUnk34.m_ui32NbUsedElt; ++i) m_vpUnk34.m_pBlock[i]->ResetRuntime();  // vt+0x50
    static_cast<CKMarkedFX*>(m_pUnk20)->ResetChannels();  // 0x005cf1c0
}

// 0x005c84a8 CKHkScriptedNPC_OnDeactivate (vt+0xa4): CKHkActorBase's, the node back at its position, every block's
// vt+0x54, the marked channel effects stopped, the prepared block undone (vt+0x100).
void CKHkScriptedNPC::VfA4() {
    CKHkActorBase::VfA4();
    RestorePosition(this);
    for (uint32_t i = 0; i < m_vpUnk34.m_ui32NbUsedElt; ++i) m_vpUnk34.m_pBlock[i]->Vf54();
    static_cast<CKMarkedFX*>(m_pUnk20)->StopAllChannelNodes2();  // 0x005cfb70
    UnprepareNext();
}

// 0x005c8a08 CKHkScriptedNPC_vfCC: off clears the active byte; on (when not active) sets it and, unless the life flag
// +0x0c bit 2, tries to switch to the next block (vt+0xf4).
void CKHkScriptedNPC::SetEnabled(int32_t enabled) {
    if (enabled == 0) {
        if (m_unk4C != 0) m_unk4C = 0;
        return;
    }
    if (m_unk4C != 0) return;
    m_unk4C = 1;
    if ((m_bitArray & 4u) == 0) TrySwitchBlock();
}

// 0x005c8ab0 CKHkScriptedNPC_vfD4: the same code as vt+0xcc.
void CKHkScriptedNPC::VfD4(int32_t enabled, int32_t /*unused*/) {
    if (enabled == 0) {
        if (m_unk4C != 0) m_unk4C = 0;
        return;
    }
    if (m_unk4C != 0) return;
    m_unk4C = 1;
    if ((m_bitArray & 4u) == 0) TrySwitchBlock();
}

// 0x005c8780 CKHkScriptedNPC_TrySwitchBlock_maybe: with a next block (+0x64 below the count), the current block's
// leave test (vt+0x60, when there is one) and the next block's enter test (vt+0x5c, always asked) for the user
// (+0x2c); both passing: the current block left (vt+0x68), the next one entered (vt+0x64) and made current, the block
// its entry (+0x40) names prepared (vt+0xf8; -2: the following one unless it is the last), not ended, no next block,
// +0x80 cleared; 1. Else 0.
uint8_t CKHkScriptedNPC::TrySwitchBlock() {
    if (m_vpUnk34.m_ui32NbUsedElt <= m_unk64) return 0;
    bool canLeave = true;
    if (m_unk60 < m_vpUnk34.m_ui32NbUsedElt && m_vpUnk34.m_pBlock[m_unk60]->CanLeave(m_pUnk2C) == 0) canLeave = false;
    if (m_vpUnk34.m_pBlock[m_unk64]->CanEnter(m_pUnk2C) == 0 || !canLeave) return 0;
    if (m_unk60 < m_vpUnk34.m_ui32NbUsedElt) m_vpUnk34.m_pBlock[m_unk60]->Leave(m_pUnk2C);
    m_vpUnk34.m_pBlock[m_unk64]->Enter(m_pUnk2C);
    const uint32_t current = m_unk64;
    m_unk60 = current;
    const uint32_t follow = m_vpUnk40.m_pBlock[current]->m_unk4;
    if (follow == 0xfffffffeu) {
        if (m_vpUnk34.m_ui32NbUsedElt - 1 != current) PrepareBlock(current + 1);
    } else {
        PrepareBlock(follow);
    }
    m_unk68 = 0;
    m_unk64 = 0xffffffffu;
    m_unk80 = 0;
    return 1;
}

// 0x005c83c8 CKHkScriptedNPC_vfF8: a block other than the prepared one: the prepared one undone (vt+0x100), then, when
// `index` is a block, it is prepared (vt+0x70) and kept (+0x5c).
void CKHkScriptedNPC::PrepareBlock(uint32_t index) {
    if (m_unk5C == index) return;
    UnprepareNext();
    if (index < m_vpUnk34.m_ui32NbUsedElt) {
        m_vpUnk34.m_pBlock[index]->Prepare();
        m_unk5C = index;
    }
}

// 0x005c8360 CKHkScriptedNPC_vfFC: block `index`'s vt+0x74 when it is a block.
void CKHkScriptedNPC::UnprepareBlock(uint32_t index) {
    if (index < m_vpUnk34.m_ui32NbUsedElt) m_vpUnk34.m_pBlock[index]->Unprepare();
}

// 0x005c8f28 CKHkScriptedNPC_QueueSignalsAndChainNextBlock_maybe: the first time (not ended yet) the current block is
// kept (+0x58) and the signals queued (+0x78, QueueTriggerSignals 0x236338); ended. Unless +0x80, a current block
// before the last whose entry chains (+0x00) makes the following one the next block, prepared (vt+0xf8), and tries
// the switch (vt+0xf4); the old next block back when it fails.
void CKHkScriptedNPC::QueueSignalsAndChainNextBlock() {
    if (m_unk68 == 0) {
        m_unk58 = m_unk60;
        QueueTriggerSignals(&m_tsUnk78);  // the NPC as the second argument
    }
    m_unk68 = 1;
    if (m_unk80 != 0) return;
    const uint32_t current = m_unk60;
    if (!(current < m_vpUnk34.m_ui32NbUsedElt - 1u) || m_vpUnk40.m_pBlock[current]->m_unk0 == 0) return;
    const uint32_t savedNext = m_unk64;
    m_unk64 = current + 1;
    PrepareBlock(current + 1);
    if (TrySwitchBlock() == 0) m_unk64 = savedNext;
}

// 0x005c8c88 CKHkScriptedNPC_GetAnchorPosition_maybe
CVector3* CKHkScriptedNPC::GetAnchorPosition(CVector3* out, IKSerializable* owner, uint32_t /*index*/) {
    CKHkScriptedNPC* npc = static_cast<CKHkScriptedNPC*>(owner);
    if (npc->m_pUnk30 != nullptr) {
        CVector3 position;
        static_cast<const CSGHotSpot*>(npc->m_pUnk30)->GetWorldPosition(&position);  // 0x000ce790
        *out = position;
        return out;
    }
    const RwFrame* frame = NodeFrame(npc->m_pKGLObject);
    out->x = frame->ltm.pos.x;  // +0x80
    out->y = frame->ltm.pos.y;
    out->z = frame->ltm.pos.z;
    return out;
}
