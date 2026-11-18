// CKSrvInput.cpp - reconstructed original translation unit 0x202248-0x203460 (GAME_TOC1, main_toc1), 39 functions, 30 live.
// Primary class: CKSrvInput  key 0x6c1  category Service  size 0x38  vtable 0xb1efb8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x202248  CKSrvInput_Delete
//   [x] 0x202298  CKSrvInput_Start
//   [x] 0x2022a0  CKSrvInput_Pause
//   [x] 0x2022a8  CKSrvInput_Resume
//   [ ] 0x2022b0  CKSrvInput_GetActiveBlockStep_maybe  [dead]
//   [ ] 0x202358  KStub_ReturnFloat0_202358  [dead]
//   [ ] 0x202360  FUN_00202360  [dead]
//   [ ] 0x2023c0  FUN_002023c0  [dead]
//   [ ] 0x202420  CKSrvInput_GetInputBlock_2_maybe  [dead]
//   [x] 0x202450  CKSrvInput_PushActiveBlock_maybe
//   [x] 0x202460  CKSrvInput_RemoveActiveBlock_maybe
//   [ ] 0x2024d0  RegisterCKSrvInputClass
//   [ ] 0x202558  _GLOBAL__D_202558
//   [ ] 0x202568  _GLOBAL__I_202568
//   [ ] 0x202578  FUN_00202578  [dead]
//   [ ] 0x2025b0  FUN_002025b0  [dead]
//   [x] 0x2025e8  CKSrvInput_PostLoad
//   [x] 0x202638  CKSrvInput_Destroy  (inherited: IKService_Destroy)
//   [x] 0x202660  CKSrvInput_DestroyService
//   [x] 0x2026b8  CKSrvInput_InitializeService
//   [x] 0x202700  CKSrvInput_Construct
//   [x] 0x202778  CKSrvInput_Construct_2  (the not-in-charge copy of the constructor 0x202700: CKSrvInput())
//   [x] 0x2027f0  CKSrvInput_DeleteArray
//   [x] 0x202898  CKSrvInput_Stop
//   [ ] 0x202920  CKSrvInput_GetActivePositionScaled_maybe  [dead]
//   [x] 0x2029b8  UpdateCKSrvInput
//   [x] 0x202a50  CKSrvInput_GetInputBlock_maybe
//   [ ] 0x202a80  CKSrvInput_GetActivePositionNormalizedPtr_maybe  [dead]
//   [ ] 0x202ab8  CKSrvInput_Save
//   [x] 0x202ac0  CKSrvInput_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [ ] 0x202ac8  CKSrvInput_DetachBlock_maybe  [dead: no pointer to its descriptor 0xb79d88]
//   [ ] 0x202c90  CKSrvInput_AppendBlock_maybe  [dead: no pointer to its descriptor 0xb79d90]
//   [x] 0x202d78  CKSrvInput_Load
//   [ ] 0x202ff8  CKSrvInput_AttachBlock_maybe  [dead: no pointer to its descriptor 0xb79da0]
//   [x] 0x203108  CKSrvInput_DeletingDestructor  (~CKSrvInput + delete)
//   [x] 0x203190  CKSrvInput_Create
//   [x] 0x203228  CKSrvInput_CreateArray
//   [x] 0x203360  CKSrvInput_Destructor  (~CKSrvInput)
//   [x] 0x2033e0  CKSrvInput_Destructor_2  (~CKSrvInput)
//
//   [ ] 0x9b15e0  CKSrvInput_IsKindOfClass  [inline]
//   [ ] 0x9b1618  CKSrvInput_GetClassType  [inline]
//   [ ] 0x9b1620  CKSrvInput_GetClassID  [inline]
#include "k2000/services/CKSrvInput.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/KBase60CC.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"

// 0x00202700 CKSrvInput_Construct (the same stores inlined in 0x203190 CKSrvInput_Create).
CKSrvInput::CKSrvInput() {
    m_vRefs.m_ui32NbElt = 1;
    m_vRefs.m_pBlock = nullptr;
    m_vRefs.m_ui32NbUsedElt = 0;
    m_ui32Priority = 0x7a;
    m_unk20 = nullptr;
    Engine_SetSrvInput(this);
}

// 0x00203360 CKSrvInput_Destructor (0x2033e0 / 0x203108 the same; the capacity is kept)
CKSrvInput::~CKSrvInput() {
    if (m_vRefs.m_pBlock != nullptr) Mem_FreeAligned16(m_vRefs.m_pBlock);
    m_vRefs.m_ui32NbUsedElt = 0;
    m_vRefs.m_pBlock = nullptr;
}

// 0x002026b8 CKSrvInput_InitializeService: the vector's first one-element block.
int32_t CKSrvInput::InitializeService() {
    m_vRefs.m_ui32NbElt = 1;
    m_vRefs.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    return 1;
}

// 0x00202660 CKSrvInput_DestroyService (the capacity is kept)
void CKSrvInput::DestroyService() {
    if (m_vRefs.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vRefs.m_pBlock);
        m_vRefs.m_pBlock = nullptr;
    }
    m_vRefs.m_ui32NbUsedElt = 0;
    m_vRefs.m_pBlock = nullptr;
}

// 0x00202d78 CKSrvInput_Load
int32_t CKSrvInput::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk0c);
    ReadU32LE(file, &m_unk10);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (m_vRefs.m_ui32NbElt < count) {  // TVector growth: to count + 1
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_vRefs.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_vRefs.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vRefs.m_ui32NbElt = capacity;
    }
    m_vRefs.m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, m_vRefs.m_pBlock, count);  // also with count 0, as in the original
    ReadF32LE(file, &m_unk34);
    return 1;
}

// 0x00202a50 CKSrvInput_GetInputBlock_maybe
KBase60CC* CKSrvInput::GetInputBlock(uint32_t index) {
    if (index >= m_vRefs.m_ui32NbUsedElt) return nullptr;
    return static_cast<KBase60CC*>(m_vRefs.m_pBlock[index]);
}

// 0x00202450 CKSrvInput_PushActiveBlock_maybe
void CKSrvInput::PushActiveBlock(KBase60CC* block) {
    block->m_unk04 = m_unk20;
    m_unk20 = block;
}

// 0x00202460 CKSrvInput_RemoveActiveBlock_maybe
void CKSrvInput::RemoveActiveBlock(KBase60CC* block) {
    KBase60CC* node = m_unk20;
    if (node == nullptr) return;
    if (block == node) {
        m_unk20 = block->m_unk04;
    } else {
        KBase60CC* previous;
        do {
            previous = node;
            node = previous->m_unk04;
            if (node == nullptr) return;
        } while (block != node);
        previous->m_unk04 = block->m_unk04;
        if (block->m_unk04 != nullptr) block->m_unk04 = nullptr;
    }
    block->m_unk04 = nullptr;
}

// 0x002025e8 CKSrvInput_PostLoad
int32_t CKSrvInput::PostLoad(int32_t type) {
    IKService::PostLoad(type);  // KStub_Return1_1a5b0
    m_unk34 = 0x1p+1f;          // TOC1 -0x1060: 2.0
    m_unk30 = nullptr;
    m_unk24 = 0;
    m_unk28 = 0;
    m_unk2c = 0;
    return 1;
}

// 0x00202898 CKSrvInput_Stop: every active block deactivated (vt+0x54, the next one read first), the
// service's state cleared.
void CKSrvInput::Stop() {
    for (KBase60CC* block = m_unk20; block != nullptr;) {
        KBase60CC* next = block->m_unk04;
        block->OnDeactivate();
        block = next;
    }
    m_unk30 = nullptr;
    m_unk24 = 0;
    m_unk28 = 0;
    m_unk2c = 0;
}

// 0x002029b8 UpdateCKSrvInput (the next block read before each update)
void CKSrvInput::Update(IKTime* frameClock) {
    const float dt = frameClock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];  // +0x20
    for (KBase60CC* block = m_unk20; block != nullptr;) {
        KBase60CC* next = block->m_unk04;
        if (block->m_unk0e != 0) block->Update(dt);  // vt+0x58
        block = next;
    }
}
