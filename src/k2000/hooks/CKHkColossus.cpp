// Reconstructed original translation unit: 0x46bd08-0x46cbe8 (GAME_TOC1, main_toc1), 23 functions, 19 live.
// Primary class: CKHkColossus  key 0x2a42  category Hook  size 0x58  vtable 0xb27460
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x46bd08  RegisterCKHkColossusClass
//   [ ] 0x46bd80  _GLOBAL__I_46bd80
//   [x] 0x46bd90  CKHkColossus_Update  (the sequencer call: a STUB until R06's CKColossusSequenceManager lands)
//   [x] 0x46bde8  CKHkColossus_Resume  (the actor base's 0x3f6e60: inherited)
//   [x] 0x46be10  CKHkColossus_Pause  (the actor base's 0x3f6e58: inherited)
//   [x] 0x46be38  CKHkColossus_Stop  (the sequencer call: a STUB until R06's class lands)
//   [x] 0x46be78  CKHkColossus_PostLoad  (the owner store: a STUB until R06's class lands)
//   [ ] 0x46beb8  CKHkColossus_Save
//   [x] 0x46bee0  CKHkColossus_RecursiveRegistration  (the actor base's 0x3f6ee8: inherited)
//   [ ] 0x46bf08  CKHkColossus_Construct  [dead]
//   [ ] 0x46bf78  CKHkColossus_Construct_2  [dead]
//   [x] 0x46bfe8  CKHkColossus_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x46c088  CKHkColossus_BaseDestructor  (the destructor)
//   [x] 0x46c128  CKHkColossus_Destroy
//   [ ] 0x46c1b0  CKHkColossus_DetachHotSpotVolumes_maybe  [dead]
//   [ ] 0x46c268  CKHkColossus_AttachHotSpotVolumes_maybe  [dead]
//   [x] 0x46c320  CKHkColossus_GetHotSpotRecordByIndex_maybe
//   [x] 0x46c350  CKHkColossus_Start  (the sequencer reset: a STUB until R06's class lands)
//   [x] 0x46c3d8  CKHkColossus_DeletingDestructor  (the destructor)
//   [x] 0x46c488  CKHkColossus_Destructor  (the destructor)
//   [x] 0x46c528  CKHkColossus_Create  (the constructor)
//   [x] 0x46c5a8  CKHkColossus_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x46c698  CKHkColossus_Load  (the elements' owner store: KBase7CCC +0x2c, C2.8 port-final F03)
//
//   [ ] 0x9c4190  CKHkColossus_IsKindOfClass  [inline]
//   [ ] 0x9c41e8  CKHkColossus_GetClassType  [inline]
//   [ ] 0x9c41f0  CKHkColossus_GetClassID  [inline]
#include "k2000/hooks/CKHkColossus.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKColossusSequenceManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/KBase7CCC.h"
#include "k2000/scenegraph/CSGMovable.h"

namespace {

// ---- the sequencer (+0x20, CKColossusSequenceManager) and the sequences (+0x24): other packages' classes ----
// R06's CKColossusSequenceManager. 0x0046b308 ColossusAttackSequencer_Reset_maybe (the hook's Start).
void SequencerReset(IKSerializable* sequencer) { static_cast<CKColossusSequenceManager*>(sequencer)->Reset(); }
// 0x0046b288 ColossusAttackSequencer_StopCurrent_maybe (the hook's Stop).
void SequencerStopCurrent(IKSerializable* sequencer) { static_cast<CKColossusSequenceManager*>(sequencer)->StopCurrent(); }
// 0x0046b368 ColossusAttackSequencer_Update_maybe (the hook's Update).
void SequencerUpdate(IKSerializable* sequencer, IKTime* clock) {
    static_cast<CKColossusSequenceManager*>(sequencer)->Update(clock);
}
// The hook's PostLoad stores itself in the sequencer's word +0x04 (its owner).
void SequencerSetOwner(IKSerializable* sequencer, CKHkColossus* owner) {
    static_cast<CKColossusSequenceManager*>(sequencer)->m_pOwner = owner;
}
// The hook's Load stores itself in each listed object's word +0x2c (its owner): the list holds the attack elements
// (KBase7CCC, whose +0x2c is the colossus; C2.8 port-final F03).
void SequenceSetOwner(IKSerializable* element, CKHkColossus* owner) { static_cast<KBase7CCC*>(element)->m_pOwner = owner; }

// The vectors' append (inlined in the Load): a full vector grows by one element (Mem_ReallocAligned16; a count of 0
// would grow to 1).
template <class T>
void PushBack1(TVector<T, 1>& v, T value) {
    const uint32_t used = v.m_ui32NbUsedElt;
    if (v.m_ui32NbElt == used) {
        uint32_t capacity = used + 1;
        if (capacity == 0) capacity = 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));  // 0x00053190
        v.m_ui32NbElt = capacity;
    }
    v.m_pBlock[v.m_ui32NbUsedElt] = value;
    v.m_ui32NbUsedElt = v.m_ui32NbUsedElt + 1;
}

}  // namespace

CKHkColossus::CKHkColossus() {
    m_pUnk20 = nullptr;
    m_vUnk24.m_pBlock = nullptr;
    m_vUnk24.m_ui32NbElt = 1;
    m_vUnk24.m_ui32NbUsedElt = 0;
    m_vUnk30.m_ui32NbElt = 1;
    m_vUnk30.m_ui32NbUsedElt = 0;
    m_vUnk30.m_pBlock = nullptr;
    // Not set by Create (the fresh heap's zeros).
    m_vUnk3C = {0.0f, 0.0f, 0.0f};
    m_unk48 = 0;
    m_unk4C = 0;
    m_unk50 = 0;
    m_unk54 = 0;
}

CKHkColossus::~CKHkColossus() {
    if (m_vUnk30.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk30.m_pBlock);  // 0x00052fb8
    m_vUnk30.m_ui32NbUsedElt = 0;
    m_vUnk30.m_pBlock = nullptr;
    if (m_vUnk24.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk24.m_pBlock);
    m_vUnk24.m_ui32NbUsedElt = 0;
    m_vUnk24.m_pBlock = nullptr;
}

// 0x0046bd90 CKHkColossus_Update
void CKHkColossus::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68 (empty)
    if (m_pUnk20 != nullptr) SequencerUpdate(m_pUnk20, clock);  // 0x0046b368
}

// 0x0046be38 CKHkColossus_Stop
void CKHkColossus::Stop() {
    CKHkActorBase::Stop();  // 0x003f6e50
    SequencerStopCurrent(m_pUnk20);  // 0x0046b288
}

// 0x0046be78 CKHkColossus_PostLoad
int32_t CKHkColossus::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x003f6e70
    SequencerSetOwner(m_pUnk20, this);
    return 1;
}

// 0x0046c128 CKHkColossus_Destroy
void CKHkColossus::Destroy() {
    CKHkActorBase::Destroy();  // 0x003f6e08
    for (uint32_t i = 0; i < m_vUnk30.m_ui32NbUsedElt; ++i) delete m_vUnk30.m_pBlock[i];  // 0x00a3ce18
    m_vUnk30.m_ui32NbUsedElt = 0;
}

// 0x0046c320 CKHkColossus_GetHotSpotRecordByIndex_maybe
CKHkColossus::HotSpotRecord* CKHkColossus::GetHotSpotRecordByIndex(uint32_t index) const {
    if (m_vUnk30.m_ui32NbUsedElt <= index) return nullptr;  // cmplw / ble
    return m_vUnk30.m_pBlock[index];
}

// 0x0046c350 CKHkColossus_Start
void CKHkColossus::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    SequencerReset(m_pUnk20);  // 0x0046b308
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;  // node +0x04
    m_vUnk3C.x = frame->modelling.at.x;  // frame +0x30
    m_vUnk3C.z = frame->modelling.at.z;
    m_vUnk3C.y = frame->modelling.at.y;
    m_unk4C = 0;
    m_unk54 = m_unk50;
    m_unk48 = 0;
}

// 0x0046c698 CKHkColossus_Load: the actor base's, then for the level type the sequence count (swapped), the sequencer,
// the record count, the records (each: the word +0x04, then the references +0x00 / +0x08 / +0x0c), the sequences (each
// told its owner) and the word +0x50.
int32_t CKHkColossus::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type != K_LEVEL_PLATEFORMS) return 1;
    int32_t sequences = 0;
    ReadS32LE(file, &sequences);
    IKFile_ReadRef(file, &m_pUnk20);
    int32_t records = 0;
    ReadS32LE(file, &records);
    m_vUnk30.m_ui32NbElt = 1;
    m_vUnk30.m_pBlock = static_cast<HotSpotRecord**>(Mem_AllocAligned16(sizeof(HotSpotRecord*)));  // 0x00053198 (one pointer)
    for (int32_t i = 0; i < records; ++i) {
        HotSpotRecord* record = new HotSpotRecord;  // 0x0098d370 OperatorNew(0x10)
        record->m_pUnk0 = nullptr;
        record->m_ui32Unk4 = 0;
        record->m_pUnk8 = nullptr;
        record->m_pUnkC = nullptr;
        ReadU32LE(file, &record->m_ui32Unk4);
        IKFile_ReadRef(file, &record->m_pUnk0);
        IKFile_ReadRef(file, &record->m_pUnk8);
        IKFile_ReadRef(file, &record->m_pUnkC);
        PushBack1(m_vUnk30, record);
    }
    m_vUnk24.m_ui32NbElt = 1;
    m_vUnk24.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    for (int32_t i = 0; i < sequences; ++i) {
        IKSerializable* sequence = nullptr;
        IKFile_ReadRef(file, &sequence);
        SequenceSetOwner(sequence, this);  // the sequence's +0x2c
        PushBack1(m_vUnk24, sequence);
    }
    ReadU32LE(file, &m_unk50);
    return 1;
}
