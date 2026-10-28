// CKHkContextualMeca.cpp - reconstructed original translation unit 0x459be0-0x460790 (GAME_TOC1, main_toc1), 47 functions, 42 live.
// Primary class: CKHkContextualMeca  key 0x2a82  category Hook  size 0x120  vtable 0xb27218
// Other owners: GetHeroModelNodeByDragonIndex (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x459be0  CKHkContextualMeca_Delete
//   [ ] 0x459c30  CKHkContextualMeca_ResetInteractionState_maybe  [dead]
//   [ ] 0x459c88  FUN_00459c88  [dead]
//   [ ] 0x459c90  CKHkContextualMeca_GetProgressRatio_maybe
//   [ ] 0x459d20  RegisterCKHkContextualMecaClass
//   [ ] 0x459d98  _GLOBAL__I_459d98
//   [ ] 0x459da8  CKHkContextualMeca_UpdateLoopSounds
//   [ ] 0x459f98  CKHkContextualMeca_TriggerAtRestFx_maybe
//   [ ] 0x45a288  CKHkContextualMeca_SetSlotActivatorsEnabled_maybe
//   [ ] 0x45a3a0  CKHkContextualMeca_ReleaseHeroes
//   [ ] 0x45a550  CKHkContextualMeca_UpdateCollisionActive_maybe  [dead]
//   [ ] 0x45a618  CKHkContextualMeca_IsHeroPullingAway_maybe
//   [ ] 0x45a760  CKHkContextualMeca_PlaceSlotActivators_maybe
//   [ ] 0x45a990  CKHkContextualMeca_OnDeactivate
//   [ ] 0x45a9b8  CKHkContextualMeca_Resume
//   [ ] 0x45a9e0  CKHkContextualMeca_Pause
//   [ ] 0x45aa08  CKHkContextualMeca_Stop
//   [x] 0x45aa30  CKHkContextualMeca_PostLoad
//   [ ] 0x45ab30  CKHkContextualMeca_Save
//   [ ] 0x45ab58  CKHkContextualMeca_RecursiveRegistration
//   [ ] 0x45ab80  CKHkContextualMeca_Destroy
//   [x] 0x45ac38  CKHkContextualMeca_DeleteArray
//   [x] 0x45ace0  CKHkContextualMeca_Construct  [dead]
//   [ ] 0x45ad18  CKHkContextualMeca_BaseDestructor
//   [ ] 0x45ad48  CKHkContextualMeca_MessageProc
//   [ ] 0x45afd0  CKHkContextualMeca_Construct_2  [dead]
//   [x] 0x45b008  CKHkContextualMeca_ApplyStatePreset_maybe
//   [ ] 0x45b138  GetHeroModelNodeByDragonIndex_2
//   [ ] 0x45b178  CKHkContextualMeca_DeletingDestructor
//   [ ] 0x45b1c0  CKHkContextualMeca_Destructor
//   [ ] 0x45b1f0  CKHkContextualMeca_GetInfo
//   [x] 0x45b330  CKHkContextualMeca_SetDefaultState
//   [ ] 0x45b420  CKHkContextualMeca_SnapHeroToSlot_maybe
//   [x] 0x45b850  CKHkContextualMeca_Create
//   [x] 0x45b8a8  CKHkContextualMeca_CreateArray
//   [x] 0x45b960  CKHkContextualMeca_Start
//   [x] 0x45b9f0  CKHkContextualMeca_Load
//   [ ] 0x45c940  CKHkContextualMeca_TriggerInteractionFx_maybe
//   [ ] 0x45cc48  CKHkContextualMeca_SpawnStepFx_maybe
//   [ ] 0x45cfe0  CKHkContextualMeca_SetVisible
//   [ ] 0x45d120  CKHkContextualMeca_Restart
//   [ ] 0x45d3f0  CKHkContextualMeca_MoveTo
//   [ ] 0x45d9d0  CKHkContextualMeca_SetEnabled
//   [ ] 0x45dbd0  CKHkContextualMeca_UpdateHeroInteraction
//   [ ] 0x45f420  CKHkContextualMeca_UpdateAtRest
//   [ ] 0x4601d8  CKHkContextualMeca_Update
//   [ ] 0x460450  CKHkContextualMeca_OnActivate
//
//   [ ] 0x9c3f58  CKHkContextualMeca_IsKindOfClass  [inline]
//   [ ] 0x9c3fb0  CKHkContextualMeca_GetClassType  [inline]
//   [ ] 0x9c3fb8  CKHkContextualMeca_GetClassID  [inline]
//   [ ] 0x9c3fc0  CKHkContextualMeca_GetIsBeingOperated  [inline]
//   [ ] 0x9c4020  CKHkContextualMeca_GetIsAtEnd  [inline]
//   [ ] 0x9c4048  CKHkContextualMeca_GetProgress  [inline]
#include "k2000/hooks/CKHkContextualMeca.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// Mem_AllocAligned16(count * 4) then one contiguous reference read (vt+0x28) of count references.
IKSerializable** AllocAndReadRefs(IKFile* file, uint8_t count) {
    IKSerializable** refs =
        static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(count * sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, refs, count);
    return refs;
}
}  // namespace

// 0x0045aa30 CKHkContextualMeca_PostLoad: CKHkActorBase's part (0x3f6e70 = IKLife_PostLoad 0x19f68: level
// type only, bit 2 of the bit array), the six trigger lists' PostLoad (0x236330, returns 1) and the 0x30-byte
// records at +0x10c: OperatorNewArray(count * 0x30 + 4), the count as the cookie, +0x10c behind it. The
// records are not constructed.
int32_t CKHkContextualMeca::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;  // IKLife_PostLoad returns 1 for it, and so does the rest
    m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
    m_unk9C.PostLoad(0);
    m_unkA4.PostLoad(0);
    m_unkAC.PostLoad(0);
    m_unkB4.PostLoad(0);
    m_unkBC.PostLoad(0);
    m_unkC4.PostLoad(0);
    const uint32_t count = m_unk5C;
    uint32_t* block = reinterpret_cast<uint32_t*>(new uint8_t[count * 0x30 + 4]);
    block[0] = count;
    m_unk10C = block + 1;
    return 1;
}

// 0x0045b9f0 CKHkContextualMeca_Load
int32_t CKHkContextualMeca::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_unk48);
    m_apUnk4C = AllocAndReadRefs(file, m_unk48);
    IKFile_ReadRef(file, &m_unk20);
    ReadU8(file, &m_unk50);
    ReadF32LE(file, &m_unk54);
    ReadF32LE(file, &m_unk58);
    IKFile_ReadRef(file, &m_unk2C);
    ReadF32LE(file, &m_unk30);
    ReadF32LE(file, &m_unk34);
    ReadU8(file, &m_unk40);
    IKFile_ReadRef(file, &m_unk24);
    IKFile_ReadRef(file, &m_unk28);
    ReadU8(file, &m_unk5C);
    ReadU8(file, &m_unk5E);
    if (m_unk5E == 0) {
        m_apUnk70 = nullptr;
        m_apUnk60 = nullptr;
        m_apUnk68 = nullptr;
        m_apUnk88 = nullptr;
    } else {
        m_apUnk60 = AllocAndReadRefs(file, m_unk5E);
        m_apUnk68 = AllocAndReadRefs(file, m_unk5E);
        m_apUnk88 = AllocAndReadRefs(file, m_unk5E);
        if ((m_bitArray & 0x1000u) == 0) {
            m_apUnk70 = nullptr;
        } else {
            m_apUnk70 = AllocAndReadRefs(file, m_unk5E);
        }
    }
    ReadU8(file, &m_unk5F);
    if (m_unk5F == 0) {
        m_apUnk74 = nullptr;
        m_apUnk64 = nullptr;
        m_apUnk6C = nullptr;
        m_apUnk8C = nullptr;
    } else {
        m_apUnk64 = AllocAndReadRefs(file, m_unk5F);
        m_apUnk6C = AllocAndReadRefs(file, m_unk5F);
        m_apUnk8C = AllocAndReadRefs(file, m_unk5F);
        if ((m_bitArray & 0x1000u) == 0) {
            m_apUnk74 = nullptr;
        } else {
            m_apUnk74 = AllocAndReadRefs(file, m_unk5F);
        }
    }
    ReadF32LE(file, &m_unk78);
    ReadF32LE(file, &m_unk7C);
    ReadF32LE(file, &m_unk90);
    ReadF32LE(file, &m_unk94);
    ReadF32LE(file, &m_unk80);
    ReadF32LE(file, &m_unk84);
    m_unk9C.Load(file, K_LEVEL_PLATEFORMS);
    m_unkA4.Load(file, K_LEVEL_PLATEFORMS);
    m_unkAC.Load(file, K_LEVEL_PLATEFORMS);
    m_unkB4.Load(file, K_LEVEL_PLATEFORMS);
    m_unkBC.Load(file, K_LEVEL_PLATEFORMS);
    m_unkC4.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unk44);
    ReadF32LE(file, &m_unkCC);
    ReadU32LE(file, &m_unkD0);
    IKFile_ReadRef(file, &m_unkD8);
    IKFile_ReadRef(file, &m_unkE0);
    ReadF32LE(file, &m_unkE4);
    ReadF32LE(file, &m_unkE8);
    IKFile_ReadRef(file, &m_unkF0);
    ReadF32LE(file, &m_unk98);
    ReadF32LE(file, &m_unk38);
    ReadF32LE(file, &m_unk3C);
    IKFile_ReadRef(file, &m_unkDC);
    ReadF32LE(file, &m_unkD4);
    IKFile_ReadRef(file, &m_unkF4);
    return 1;
}

// 0x0045b960 CKHkContextualMeca_Start: the run-time words cleared, the float +0x110 set to -1.0f (TOC1 +0x5658),
// flags bits 19 and 20 cleared and bit 22 set.
void CKHkContextualMeca::Start() {
    CKHkActorBase::Start();
    m_unkF8[1] = 0;
    m_unkF8[2] = 0;
    m_unkF8[3] = 0;
    m_unkF8[4] = 0;
    m_unkF8[0] = 0;
    m_bitArray = (m_bitArray & 0xffa7ffffu) | 0x400000u;
    m_unk11C = 0;
    m_fUnk110 = -1.0f;
    m_unk5D = 0;
    m_unk118 = 0;
    m_unkEC = 0;
}

// 0x0045b330 CKHkContextualMeca_SetDefaultState: state 0 always, state 1 only with bit 6. Bit 17 cleared,
// bit 18 = bit 5, bit 24 = bit 13, bit 21 = bit 9 (the original's rlwimi chain, checked bit by bit).
void CKHkContextualMeca::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    const uint32_t f = m_bitArray;
    if (flag != 0 && (f & 0x40) == 0) return;
    uint32_t r = f & ~(0x20000u | 0x40000u | 0x200000u | 0x1000000u);
    r |= (((f >> 5) & 1) << 18) | (((f >> 9) & 1) << 21) | (((f >> 13) & 1) << 24);
    m_bitArray = r;
}

// 0x0045b008 CKHkContextualMeca_ApplyStatePreset_maybe: with s = 0 (state 0) or 1: bit 17 cleared, bit 18 =
// bit 7+s, bit 21 = bit 10+s, bit 24 = bit 14+s.
void CKHkContextualMeca::ApplyStatePreset(int32_t state) {
    const uint32_t s = state == 0 ? 0u : 1u;
    const uint32_t f = m_bitArray;
    uint32_t r = f & ~(0x20000u | 0x40000u | 0x200000u | 0x1000000u);
    r |= (((f >> (7 + s)) & 1) << 18) | (((f >> (10 + s)) & 1) << 21) | (((f >> (14 + s)) & 1) << 24);
    m_bitArray = r;
}
