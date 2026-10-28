// CKHkPressionStone.cpp - reconstructed original translation unit 0x425b98-0x42a308 (GAME_TOC1, main_toc1), 43 functions, 38 live.
// Primary class: CKHkPressionStone  key 0x542  category Hook  size 0xd0  vtable 0xb26100
// Other owners: CarryTarget (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x425b98  CKHkPressionStone_Delete
//   [ ] 0x425be8  CKHkPressionStone_RefreshOccupantHero_maybe  [dead]
//   [ ] 0x425cd0  CKHkPressionStone_SetOccupant_maybe
//   [ ] 0x425d30  FUN_00425d30  [dead]
//   [ ] 0x425d38  FUN_00425d38  [dead]
//   [ ] 0x425da0  RegisterCKHkPressionStoneClass
//   [ ] 0x425e18  _GLOBAL__I_425e18
//   [ ] 0x425e28  CKHkPressionStone_AcquireInputIconFx_maybe
//   [ ] 0x4260d0  CKHkPressionStone_FindPressingObject_maybe
//   [ ] 0x426330  CKHkPressionStone_Resume
//   [ ] 0x426358  CKHkPressionStone_Pause
//   [ ] 0x426380  CKHkPressionStone_Stop
//   [x] 0x4263a8  CKHkPressionStone_Start
//   [ ] 0x426410  CKHkPressionStone_PostLoad
//   [ ] 0x426500  CKHkPressionStone_Save
//   [ ] 0x426528  CKHkPressionStone_RecursiveRegistration
//   [x] 0x426550  CKHkPressionStone_Construct  [dead]
//   [x] 0x426588  CKHkPressionStone_DeleteArray
//   [ ] 0x426628  CKHkPressionStone_BaseDestructor
//   [ ] 0x426658  CKHkPressionStone_Destroy
//   [ ] 0x4266a8  CKHkPressionStone_Construct_2  [dead]
//   [ ] 0x4266e0  CKHkPressionStone_GetInfo
//   [ ] 0x4268f0  CKHkPressionStone_IsOccupiedByHeroProperty_maybe
//   [ ] 0x4269a8  CKHkPressionStone_DeletingDestructor
//   [ ] 0x4269f0  CKHkPressionStone_Destructor
//   [ ] 0x426a20  CKHkPressionStone_AttachSounds
//   [ ] 0x426be8  CarryTarget_GetGroundedPlacementPoint_maybe
//   [x] 0x426d20  CKHkPressionStone_ApplyStatePreset_maybe
//   [x] 0x426e50  CKHkPressionStone_SetDefaultState
//   [x] 0x426ef0  CKHkPressionStone_CreateArray
//   [ ] 0x426fa0  CKHkPressionStone_OnDeactivate
//   [x] 0x427060  CKHkPressionStone_Create
//   [ ] 0x4270b8  CKHkPressionStone_UpdateHotspotSequence_maybe
//   [ ] 0x427380  CKHkPressionStone_StartHotspotSequence_maybe
//   [ ] 0x4275c8  CKHkPressionStone_ClearFlagC28_StartHotspotSequenceIfFlagC27_maybe
//   [ ] 0x427608  CKHkPressionStone_MessageProc
//   [ ] 0x427a28  CKHkPressionStone_UpdateStandingHero_maybe
//   [ ] 0x427f88  CKHkPressionStone_SetNavBoxBlocked_maybe
//   [ ] 0x4280f0  CKHkPressionStone_Restart
//   [ ] 0x4284b8  CKHkPressionStone_Update
//   [x] 0x429618  CKHkPressionStone_Load
//   [ ] 0x429d38  CKHkPressionStone_OnActivate
//   [ ] 0x42a1a8  CKHkPressionStone_SetNavBlockedForGroup_maybe
//
//   [ ] 0x9c30d8  CKHkPressionStone_IsKindOfClass  [inline]
//   [ ] 0x9c3130  CKHkPressionStone_GetClassType  [inline]
//   [ ] 0x9c3138  CKHkPressionStone_GetClassID  [inline]
//   [ ] 0x9c3140  CKHkPressionStone_vfE4  [inline]
//   [ ] 0x9c3148  CKHkPressionStone_GetTriggerPropA2  [inline]
//   [ ] 0x9c3168  CKHkPressionStone_GetTriggerPropA3  [inline]
//   [ ] 0x9c3188  CKHkPressionStone_GetTriggerProp9A  [inline]
//   [ ] 0x9c3198  CKHkPressionStone_GetTriggerPropA4  [inline]
//   [ ] 0x9c31a8  CKHkPressionStone_vfE8  [inline]
//   [ ] 0x9c31b0  CKHkPressionStone_GetTriggerPropA8  [inline]
#include "k2000/hooks/CKHkPressionStone.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x00429618 CKHkPressionStone_Load: everything but the last reference is read for every serialization type.
int32_t CKHkPressionStone::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    IKFile_ReadRef(file, &m_unk64);
    IKFile_ReadRef(file, &m_unk68);
    IKFile_ReadRef(file, &m_unk88);
    IKFile_ReadRef(file, &m_unk78);
    IKFile_ReadObjectRefArray(file, m_apUnk6C, 3);
    IKFile_ReadRef(file, &m_unk8C);
    m_unk9C.Load(file, type);
    m_unkA4.Load(file, type);
    m_unkAC.Load(file, type);
    m_unkB4.Load(file, type);
    m_unkBC.Load(file, type);
    m_unkC4.Load(file, type);
    ReadU8(file, &m_unk7C);
    if (m_unk7C == 0) {
        m_apUnk80 = nullptr;
    } else {
        m_apUnk80 = static_cast<IKSerializable**>(
            Mem_AllocAligned16(static_cast<uint32_t>(m_unk7C * sizeof(IKSerializable*))));
        IKFile_ReadObjectRefArray(file, m_apUnk80, m_unk7C);
    }
    ReadF32LE(file, &m_fMaxClearance);
    ReadF32LE(file, &m_fUpSpeed);
    ReadF32LE(file, &m_fDownSpeed);
    ReadF32LE(file, &m_unk60);
    ReadU16LE(file, &m_ui16HerosToTest);
    ReadU8(file, &m_unk4C);
    ReadF32LE(file, &m_unk5C);
    ReadF32LE(file, &m_unk84);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_unk90);
    return 1;
}

// 0x004263a8 CKHkPressionStone_Start
void CKHkPressionStone::Start() {
    CKHkActorBase::Start();
    m_bitArray &= 0x3fffffffu;
    m_unkCC = 1;
    m_unk20[9] = 0;   // +0x44
    m_unk20[10] = 0;  // +0x48
    m_unk20[8] = 0;   // +0x40
}

// 0x00426e50 CKHkPressionStone_SetDefaultState: bits 17-21 and 27-29 cleared, bits 19 and 29 set, bit 27 =
// bit 11.
void CKHkPressionStone::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    const uint32_t f = m_bitArray;
    m_bitArray = (f & 0xc7c1ffffu) | 0x20080000u | (((f >> 11) & 1) << 27);
}

// 0x00426d20 CKHkPressionStone_ApplyStatePreset_maybe. With a = flags bit 14 (state 0) or 15 (state 1) and b =
// bit 12 (state 0) or 13 (state 1): bits 17 and 18 = a, bit 19 = !a, bits 20 and 21 cleared, bit 27 = b, bit 28
// cleared, bit 29 = !a (the original's rlwimi chain, checked bit by bit).
void CKHkPressionStone::ApplyStatePreset(int32_t state) {
    const uint32_t f = m_bitArray;
    const uint32_t a = (f >> (state == 0 ? 14 : 15)) & 1;
    const uint32_t b = (f >> (state == 0 ? 12 : 13)) & 1;
    uint32_t r = f & ~(0x3e0000u | 0x38000000u);
    r |= (a << 17) | (a << 18) | ((a ^ 1u) << 19) | (b << 27) | ((a ^ 1u) << 29);
    m_bitArray = r;
}
