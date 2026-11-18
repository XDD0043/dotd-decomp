// CKHkParticlesSequencer.cpp - reconstructed original translation unit 0x5a8910-0x5a9588 (GAME_TOC2, main_toc2), 34 functions, 31 live.
// Primary owner: CKHkParticlesSequencer (not a registered class)
// Other owners: RegisterCKHkParticlesSequencerClass (1), CKSrvBonus (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5a8910  CKHkParticlesSequencer_Destroy
//   [x] 0x5a8960  CKHkParticlesSequencer_Construct  [dead]
//   [ ] 0x5a89a8  CKHkParticlesSequencer_Construct_2  [dead]
//   [x] 0x5a89f0  CKHkParticlesSequencer_ClearReferences  (Destroy: empty, the default)
//   [x] 0x5a89f8  CKHkParticlesSequencer_vf50  (Start: empty, IKHook's)
//   [x] 0x5a8a00  CKHkParticlesSequencer_vf70  (Pause: empty, IKHook's)
//   [x] 0x5a8a08  CKHkParticlesSequencer_vf78  (Resume: empty, IKHook's)
//   [x] 0x5a8a10  CKHkParticlesSequencer_OnSectorActivate  (SectorLoaded: IKLife's, inherited)
//   [x] 0x5a8a38  CKHkParticlesSequencer_OnSectorDeactivate  (SectorUnload)
//   [ ] 0x5a8aa0  RegisterCKHkParticlesSequencerClass
//   [ ] 0x5a8b18  _GLOBAL__I_5a8b18
//   [x] 0x5a8b28  CKHkParticlesSequencer_ReinitRuntime  (Restart)
//   [x] 0x5a8bb0  CKHkParticlesSequencer_PostLoad
//   [x] 0x5a8c18  CKHkParticlesSequencer_Load
//   [ ] 0x5a8d30  CKHkParticlesSequencer_Save
//   [x] 0x5a8d58  CKHkParticlesSequencer_LevelReset  (RecursiveRegistration: IKHook's, inherited)
//   [x] 0x5a8d80  CKHkParticlesSequencer_DestroyArray
//   [x] 0x5a8e28  CKHkParticlesSequencer_Update  (Update)
//   [x] 0x5a8ed8  CKHkParticlesSequencer_OnLevelExit_maybe  (Stop)
//   [x] 0x5a8f40  CKHkParticlesSequencer_HandleMessage  (MessageProc)
//   [x] 0x5a9110  CKHkParticlesSequencer_vf38  (SetDefaultState, CKHkParticlesSequencer.h)
//   [x] 0x5a9120  CKHkParticlesSequencer_vf3C  (SetGameState)
//   [x] 0x5a9148  CKHkParticlesSequencer_OnActivate  (VfA0 (SectorNowValid))
//   [x] 0x5a91c0  CKHkParticlesSequencer_OnDeactivate  (VfA4 (SectorNowInvalid))
//   [x] 0x5a9200  CKHkParticlesSequencer_Create
//   [x] 0x5a9268  CKHkParticlesSequencer_CreateArray
//   [x] 0x5a9338  CKHkParticlesSequencer_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x5a9358  CKHkParticlesSequencer_Destructor_2  [dead]
//   [x] 0x5a9378  CKHkParticlesSequencer_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x5a93c0  CKHkParticlesSequencer_IsStopped_maybe
//   [x] 0x5a93e0  CKHkParticlesSequencer_IsAtStep_maybe
//   [x] 0x5a9410  CKHkParticlesSequencer_ResolveTriggerProperty  (GetInfo)
//   [x] 0x5a94f8  CKHkParticlesSequencer_HasStoppedAtStep_maybe
//   [x] 0x5a9538  CKSrvBonus_Destroy  (CKSrvBonus_Delete: DOTD_DECLARE_FACTORIES, k2000/ui/CKSrvBonus.h)
//
//   [ ] 0x9cbd80  CKHkParticlesSequencer_IsKindOf  [inline]
//   [ ] 0x9cbdc8  CKHkParticlesSequencer_GetClassGroup  [inline]
//   [ ] 0x9cbdd0  CKHkParticlesSequencer_GetClassId  [inline]
#include "k2000/fx/CKHkParticlesSequencer.h"

#include "k2000/components/CKParticlesSequencerCpnt.h"
#include "k2000/core/IKInfo.h"
#include "k2000/io/IKFile.h"
#include "k2000/services/CKSrvTrigger.h"

namespace {
const CKParticlesSequencerCpnt* Sequencer(const CKHkParticlesSequencer* hook) {
    return static_cast<const CKParticlesSequencerCpnt*>(hook->m_pSequencerPartCpnt);
}
}  // namespace

// 0x005a8bb0 CKHkParticlesSequencer_PostLoad
int32_t CKHkParticlesSequencer::PostLoad(int32_t type) {
    PostLoadLife(type);  // TocBridge_IKLife_PostLoad 0x19f68
    static_cast<CKParticlesSequencerCpnt*>(m_pSequencerPartCpnt)->m_unk24 = this;
    m_tsSequenceEnded.PostLoad(type);  // TocBridge_TriggerEventList_PostLoad_maybe 0x236330
    return 1;
}

// 0x005a9120 CKHkParticlesSequencer_vf3C
int32_t CKHkParticlesSequencer::SetGameState(const SApplyGameState* state) {
    const uint32_t info = state->m_ui32InfoId;
    if (info == 100) m_i32CurSequence = static_cast<int32_t>(state->m_ui32GameStateId) - 1;
    return info == 100 ? 1 : 0;
}

// 0x005a93c0 CKHkParticlesSequencer_IsStopped_maybe
uint32_t CKHkParticlesSequencer::IsStopped() const { return Sequencer(this)->m_i32CurSeq < 0 ? 1u : 0u; }

// 0x005a93e0 CKHkParticlesSequencer_IsAtStep_maybe
uint32_t CKHkParticlesSequencer::IsAtStep(uint32_t step) const {
    return (step - 1u) == static_cast<uint32_t>(Sequencer(this)->m_i32CurSeq) ? 1u : 0u;
}

// 0x005a94f8 CKHkParticlesSequencer_HasStoppedAtStep_maybe
uint32_t CKHkParticlesSequencer::HasStoppedAtStep(uint32_t step) const {
    if (Sequencer(this)->m_i32CurSeq >= 0) return 0;
    return (step - 1u) == static_cast<uint32_t>(Sequencer(this)->m_i32LastSeq) ? 1u : 0u;
}

// 0x005a9410 CKHkParticlesSequencer_ResolveTriggerProperty (TriggerPropertyRequest_SetGetter_maybe, type 0)
int32_t CKHkParticlesSequencer::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 0x15:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t arg) { return static_cast<CKHkParticlesSequencer*>(o)->IsAtStep(arg); }, 0);
    case 0x16:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t arg) {
            return static_cast<CKHkParticlesSequencer*>(o)->HasStoppedAtStep(arg);
        }, 0);
    case 0x14:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<CKHkParticlesSequencer*>(o)->IsStopped(); }, 0);
    default:
        return 1;
    }
}

// 0x005a8c18 CKHkParticlesSequencer_Load
int32_t CKHkParticlesSequencer::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pSequencerPartCpnt);
    m_tsSequenceEnded.Load(file, 0);
    ReadS32LE(file, &m_i32DefaultStartSequence);
    return 1;
}

// C2.8 port-rest R02 (the component runtime exists now).

#include "k2000/math/Quat.h"
#include "k2000/system/IKTime.h"

namespace {
CKParticlesSequencerCpnt* SequencerOf(CKHkParticlesSequencer* hook) {
    return static_cast<CKParticlesSequencerCpnt*>(hook->m_pSequencerPartCpnt);
}
// Message 0x901's placement (the data points to a pointer to it): a position at +4 and a quaternion at +0x10; the
// first word is not read.
struct SequencePlacement {
    uint32_t m_unk00;
    CVector3 m_position;  // +0x04
    float m_quat[4];      // +0x10
};
// The current sequence played when it is valid (not below 0 and below the count, compared signed), else everything
// stopped (Restart / SectorNowValid).
void PlayCurrentOrStop(CKHkParticlesSequencer* hook) {
    const int32_t index = hook->m_i32CurSequence;
    CKParticlesSequencerCpnt* sequencer = SequencerOf(hook);
    if (index > -1 && static_cast<int32_t>(sequencer->m_ui16SeqNb) > index) {
        sequencer->PlaySequence(static_cast<uint32_t>(index));  // TocBridge 0x990400
    } else {
        sequencer->StopAll();  // TocBridge 0x9903f0
    }
}
}  // namespace

// 0x005a8a38 CKHkParticlesSequencer_OnSectorDeactivate
void CKHkParticlesSequencer::SectorUnload(int32_t sector) {
    IKLife::SectorUnload(sector);  // TocBridge_IKLife_SectorUnload
    SequencerOf(this)->Vf54(sector);
}

// 0x005a8b28 CKHkParticlesSequencer_ReinitRuntime
void CKHkParticlesSequencer::Restart() {
    if ((m_bitArray & 0x4u) != 0) return;
    PlayCurrentOrStop(this);
}

// 0x005a8e28 CKHkParticlesSequencer_Update
void CKHkParticlesSequencer::Update(IKTime* frameClock) {
    SequencerOf(this)->Update(frameClock);  // TocBridge 0x990410
    if ((m_baInfos & 0x1u) == 0) return;
    if (SequencerOf(this)->m_i32CurSeq > -1) return;
    QueueTriggerSignals(&m_tsSequenceEnded);  // TocBridge 0x9901b0
    m_baInfos = static_cast<uint8_t>(m_baInfos & ~0x1u);
}

// 0x005a8ed8 CKHkParticlesSequencer_OnLevelExit_maybe
void CKHkParticlesSequencer::Stop() {
    if ((m_bitArray & 0x4u) == 0) SequencerOf(this)->StopAll();
    m_baInfos = static_cast<uint8_t>(m_baInfos & ~0x1u);
    m_i32CurSequence = m_i32DefaultStartSequence;
}

// 0x005a8f40 CKHkParticlesSequencer_HandleMessage
int32_t CKHkParticlesSequencer::MessageProc(uint16_t message, void* data) {
    switch (message) {
    case 0x900: {
        const int32_t index = static_cast<int32_t>(TriggerParamHalf2(data)) - 1;  // lhz 2(r5): the word's low halfword
        m_i32CurSequence = index;
        if (index < 0) return 0;
        SequencerOf(this)->PlaySequence(static_cast<uint32_t>(index));
        m_baInfos = static_cast<uint8_t>((m_baInfos & ~0x1u) | 0x1u);
        return 0;
    }
    case 0x901: {
        const SequencePlacement* placement = *static_cast<SequencePlacement* const*>(data);
        if (placement == nullptr) return 1;
        CMatrix34 matrix;
        Quat_ToMatrixNormalizing(placement->m_quat, &matrix);  // TocBridge 0x98fea0
        matrix.m_pos = placement->m_position;
        matrix.m_ui32Flags &= ~0x20000u;  // rwMATRIXINTERNALIDENTITY
        SequencerOf(this)->StartSequence(&matrix);  // TocBridge 0x990420
        return 0;
    }
    case 0x902:
        SequencerOf(this)->StopAll();
        m_baInfos = static_cast<uint8_t>(m_baInfos & ~0x1u);
        m_i32CurSequence = -1;
        return 0;
    case 0x903: {
        IKSerializable* node = *static_cast<IKSerializable* const*>(data);
        if (node != nullptr) SequencerOf(this)->AttachSequenceFxTo(node);  // TocBridge 0x990430
        return 0;
    }
    default:
        return 1;
    }
}

// 0x005a9148 CKHkParticlesSequencer_OnActivate
void CKHkParticlesSequencer::VfA0() { PlayCurrentOrStop(this); }

// 0x005a91c0 CKHkParticlesSequencer_OnDeactivate
void CKHkParticlesSequencer::VfA4() {
    SequencerOf(this)->StopAll();
    m_i32CurSequence = -1;
}
