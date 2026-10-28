// CKSrvPhysics.cpp - reconstructed original translation unit 0x213028-0x218040 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKSrvPhysics  key 0x3c1  category Service  size 0x154  vtable 0xb1fcc0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x213028  CKSrvPhysics_Delete
//   [ ] 0x213078  CKSrvPhysics_Pause
//   [ ] 0x213080  CKSrvPhysics_Resume
//   [ ] 0x213088  CKSrvPhysics_DestroyService
//   [ ] 0x2130c8  RegisterCKSrvPhysicsClass
//   [ ] 0x213140  _GLOBAL__I_213140
//   [ ] 0x213150  CKSrvPhysics_CollideBoxBoxSAT_maybe
//   [ ] 0x213fe0  CKSrvPhysics_IntegrateBodies_maybe
//   [x] 0x214220  CKSrvPhysics_DeleteArray
//   [ ] 0x2142c0  FUN_002142c0  [dead]
//   [x] 0x2143c0  CKSrvPhysics_Destroy
//   [x] 0x214460  CKSrvPhysics_InitializeService
//   [x] 0x2144a8  CKSrvPhysics_Construct
//   [ ] 0x214568  CKSrvPhysics_Construct_2
//   [ ] 0x214628  CKSrvPhysics_Save
//   [ ] 0x214630  CKSrvPhysics_RecursiveRegistration
//   [ ] 0x214638  CKSrvPhysics_Stop  (m_unk20 and m_unk120 ported; the CKPxBody reset is a STUB: no body in LVL010)
//   [ ] 0x214c10  CKSrvPhysics_DetectCollisions_maybe
//   [x] 0x214f30  CKSrvPhysics_CreateArray
//   [x] 0x215090  CKSrvPhysics_Create
//   [ ] 0x215168  CKSrvPhysics_DeletingDestructor
//   [ ] 0x215318  CKSrvPhysics_ProcessBodyContacts_maybe
//   [ ] 0x216668  CKSrvPhysics_GatherContacts_maybe
//   [ ] 0x216aa0  CKSrvPhysics_RunFixedSteps_maybe
//   [x] 0x216c88  UpdateCKSrvPhysics  (the time step; the fixed steps are a STUB: no body in LVL010)
//   [ ] 0x216e28  CKSrvPhysics_Start
//   [ ] 0x217550  CKSrvPhysics_Destructor
//   [x] 0x2176f0  CKSrvPhysics_Load
//   [ ] 0x217ea0  CKSrvPhysics_Destructor_2
//
//   [ ] 0x9b2158  CKSrvPhysics_IsKindOfClass  [inline]
//   [ ] 0x9b2190  CKSrvPhysics_GetClassType  [inline]
//   [ ] 0x9b2198  CKSrvPhysics_GetClassID  [inline]
//   [ ] 0x9b2480  CKSrvPhysics_WakeBodyIsland_maybe  [inline]
#include "k2000/services/CKSrvPhysics.h"

#include <cstring>

#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/memory/CKPxContainer.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"

namespace {
// One Read of count words, then every word byte-swapped in place (lwbrx/stw), as the original does.
void ReadWordsLE(IKFile* file, uint32_t* words, uint32_t count) {
    uint8_t* bytes = reinterpret_cast<uint8_t*>(words);
    file->Read(bytes, count * 4);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        words[i] = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                   (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
    }
}
}  // namespace

// 0x002144a8 CKSrvPhysics_Construct (the same stores inlined in 0x215090 CKSrvPhysics_Create).
CKSrvPhysics::CKSrvPhysics() {
    m_unk30.m_ui32NbElt = 1;
    m_unk30.m_pBlock = nullptr;
    m_unk30.m_ui32NbUsedElt = 0;
    m_unk114.m_ui32NbElt = 1;
    m_unk114.m_pBlock = nullptr;
    m_unk114.m_ui32NbUsedElt = 0;
    m_unk14e = 0;
    for (uint32_t i = 0; i < 5; ++i) m_unk138[i] = 0;
    m_unk14c = 0;
    m_ui32Priority = 0xcd;
    Engine_SetSrvPhysics(this);
}

// 0x00214460 CKSrvPhysics_InitializeService
int32_t CKSrvPhysics::InitializeService() {
    m_unkdc = RwMatrixCreate_Thunk();
    m_unke0 = RwMatrixCreate_Thunk();
    return 1;
}

// 0x00216c88 UpdateCKSrvPhysics: the time step 1/60 (0x3c888889) stored at +0x0c, then
// CKSrvPhysics_RunFixedSteps_maybe 0x216aa0 runs the fixed steps with it (the rest of the function only feeds
// KStub_Nop_106d8 debug prints).
// STUB(later, the first level with CKPxBody; moved from C2.6: LVL010 has no CKPxBody, live dump): the fixed steps (accumulator +0x20, DetectCollisions 0x214c10, the bodies' Integrate 0x213fe0,
// GatherContacts 0x216668) work on CKPxBody (not ported). With no body (LVL010 at the start: +0x38 = 0) the
// accumulator 1/60 is used up by one step of 1/60 and ends 0, which is what +0x20 already holds.
void CKSrvPhysics::Update(IKTime* /*frameClock*/) {
    m_unk0c = 0.016666668f;
    if (m_unk30.m_ui32NbUsedElt != 0) {
        DOTD_STUB_ONCE("UpdateCKSrvPhysics 0x216c88: RunFixedSteps over CKPxBody (later level; moved from C2.6, LVL010 has no body)");
    }
}

// 0x002143c0 CKSrvPhysics_Destroy: the two container lists freed.
void CKSrvPhysics::Destroy() {
    if (m_unk30.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_unk30.m_pBlock);
        m_unk30.m_pBlock = nullptr;
    }
    m_unk30.m_ui32NbUsedElt = 0;
    m_unk30.m_pBlock = nullptr;
    if (m_unk114.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_unk114.m_pBlock);
        m_unk114.m_pBlock = nullptr;
    }
    m_unk114.m_ui32NbUsedElt = 0;
    m_unk114.m_pBlock = nullptr;
    // IKService's part (0x1a5b8, empty) comes last here.
}

// 0x002176f0 CKSrvPhysics_Load
int32_t CKSrvPhysics::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk18);
    const float frequency = m_unk18;
    m_unk20 = 0;
    const float half = frequency * frequency * 0x1p-1f;  // fmuls, then fmuls by the TOC's 0.5
    m_unk10 = 0x1p+0f / frequency;
    m_unk1c = half;
    m_unk14 = 0x1p+0f / half;
    uint32_t vector[3];
    ReadWordsLE(file, vector, 3);  // one 12-byte read
    std::memcpy(&m_unk24, vector, sizeof(vector));

    uint16_t count = 0;
    ReadU16LE(file, &count);
    if (count == 0) {
        m_unk30.m_ui32NbElt = 1;
        m_unk30.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_unk30.m_ui32NbElt = count;
        m_unk30.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (m_unk30.m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = count + 1u;
        if (capacity == 0) capacity = 1;
        m_unk30.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_unk30.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_unk30.m_ui32NbElt = capacity;
    }
    m_unk30.m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, m_unk30.m_pBlock, count);  // also with count 0, as in the original

    IKFile_ReadRef(file, &m_unk3c);
    IKFile_ReadRef(file, &m_unk40);
    IKFile_ReadRef(file, &m_unk44);
    ReadU32LE(file, &m_unk48);
    IKFile_ReadRef(file, &m_unk4c);
    IKFile_ReadRef(file, &m_unk50);
    IKFile_ReadRef(file, &m_unk54);
    ReadWordsLE(file, m_unk58, 32);  // one 0x80-byte read
    IKFile_ReadRef(file, &m_unkd8);

    m_unk114.m_ui32NbElt = 100;
    m_unk114.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(100 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    if (m_unk114.m_ui32NbElt < 100) {  // as in the original: cannot happen right after the assignment
        m_unk114.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_unk114.m_pBlock, 101 * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_unk114.m_ui32NbElt = 101;
    }
    m_unk114.m_ui32NbUsedElt = 100;
    IKFile_ReadObjectRefArray(file, m_unk114.m_pBlock, 100);
    m_unk120 = 0;
    IKFile_ReadRef(file, &m_unk124);
    IKFile_ReadRef(file, &m_unk128);
    ReadF32LE(file, &m_unk12c);
    ReadF32LE(file, &m_unk130);
    ReadF32LE(file, &m_unk134);
    m_unk150 = 0;
    return 1;
}

// 0x00214638 CKSrvPhysics_Stop: every body (the references at +0x30) leaves the physics lists and has its
// forces, velocities and contact lists reset; the second container's list (+0xd8) is emptied.
// STUB(later, the first level with CKPxBody; moved from C2.6: LVL010 has none): CKPxBody (key 0x498c, 0x12c bytes) is not ported (its unit is a skeleton), so neither the body
// reset nor the container's body list can be done. Both are empty until a level with bodies runs
// (LVL000 has none), so the front end's Stop loses nothing; the guards keep the stub honest.
void CKSrvPhysics::Stop() {
    m_unk20 = 0;
    if (m_unk30.m_ui32NbUsedElt != 0) {
        DOTD_STUB_ONCE("CKSrvPhysics_Stop 0x214638: the CKPxBody reset loop (later level; moved from C2.6)");
    }
    if (static_cast<CKPxContainer*>(m_unkd8)->m_unk24 != 0) {
        DOTD_STUB_ONCE("CKSrvPhysics_Stop 0x214638: the container's body list (later level; moved from C2.6)");
    }
    m_unk120 = 0;
}
